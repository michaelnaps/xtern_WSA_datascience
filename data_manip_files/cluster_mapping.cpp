// File: cluster_mapping.cpp
// Created by: Michael Napoli
// Created on: 10/11/2019

/* 
	Program that uses preset cluster sizes to find average battery
	level of scooters and orders the clusters from lowest battery level
	to highest.
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>  // needed only for temporary command prompt data evaluation
using namespace std;

// POINT CLASS TYPE
// class type made for the calculation of distance values and coordinate manipulation
class Point
{
	private:
	double x;  // x-coordinate
	double y;  // y-coordinate
	
	public:
	
	// set class functions (sets the x and y coordinate respectively)
	void setX(const double temp_x) { x = temp_x; }
	void setY(const double temp_y) { y = temp_y; }
	void setXY(const double temp_x, const double temp_y) {
		x = temp_x;
		y = temp_y;
	}
	
	// returns the appropriate value
	double getX() { return x; }
	double getY() { return y; }
	void getCoordinates() { cout << "(" << x << "," << y << ")"; }
};

// FUNCTION INITIALIZATIONS
double distance(Point &pt1, Point &pt2);
bool open_scooter_data(string filename, vector<Point> &pt_vect, vector<int> &batt_vect);
bool write_cluster_data(const string filename, const vector<int> cl_count, const vector<int> cl_batt_total, const int scooter_total);

int main()
{
	Point temp_point;  // temporary point value for transfer to cluster vector
	vector<Point> scooter_location;  // x-y coordinates for all scooters
	vector<int> battery_level;  // battery levels for all scooters
	vector<int> cluster_battery_total(19, 0);  // vector for the battery totals within each cluster
	vector<int> cluster_scooter_count(19, 0);  // initialize all cluster counts to 0
	const double CLUSTER_RADIUS(0.04);  // approximate cluster radius
	
	// point coordinates for all cluster centers
	vector<Point> cluster;
	
	// set x-y coordinates for all cluster centers (approximations)
	// for every 'temp_point' there is a subsequent push_back in the clusters vector
	temp_point.setXY(-0.2629, 0.0257554); cluster.push_back(temp_point);
	temp_point.setXY(-0.14166, 0.044576); cluster.push_back(temp_point);
	temp_point.setXY(-0.121695, 0.32001745); cluster.push_back(temp_point);
	temp_point.setXY(-0.15734775, -0.225367); cluster.push_back(temp_point);
	temp_point.setXY(-0.0783579, -0.089191762); cluster.push_back(temp_point);
	temp_point.setXY(0.25259396, -0.255784); cluster.push_back(temp_point);
	temp_point.setXY(0.3670516, -0.133839); cluster.push_back(temp_point);
	temp_point.setXY(0.224613, -0.0397119); cluster.push_back(temp_point);
	temp_point.setXY(0.2248988, 0.128302156); cluster.push_back(temp_point);
	temp_point.setXY(0.4084014, 0.05894188); cluster.push_back(temp_point);
	temp_point.setXY(0.753407026, 0.582915994); cluster.push_back(temp_point);
	temp_point.setXY(0.899725064, 0.79902133); cluster.push_back(temp_point);
	temp_point.setXY(0.971003419, 0.729568099); cluster.push_back(temp_point);
	temp_point.setXY(0.940631136, 0.897551968); cluster.push_back(temp_point);
	temp_point.setXY(0.598929847, 1.028950732); cluster.push_back(temp_point);
	temp_point.setXY(1.342009952, 0.878407338); cluster.push_back(temp_point);
	temp_point.setXY(0.83996793, 1.163331194); cluster.push_back(temp_point);
	temp_point.setXY(0.961196543, 1.296743324); cluster.push_back(temp_point);
	temp_point.setXY(1.16733764, 1.3264618); cluster.push_back(temp_point);
	
	if (open_scooter_data("data_set_simplified_format.txt", scooter_location, battery_level)) {		
		// for all scooter locations
		for (int i(0); i < scooter_location.size(); ++i) {
			// check to see what cluster they are located in
			for (int k(0); k < cluster.size(); ++k) {
				// if they are in the given cluster
				if (distance(cluster[k], scooter_location[i]) < CLUSTER_RADIUS) {
					cluster_battery_total[k] += battery_level[i];  // add their battery value to the cluster total
					++cluster_scooter_count[k];  // iterate the cluster's population value
					break;  // break loop and continue to next scooter
				}
			}
		}
	}
	
	// The following for loop was used to evaluate data in command prompt before writing to file
	/*
	for (int i(0); i < cluster_scooter_count.size(); ++i) {
		cout << "Cluster " << i << ").  ";
		
		//number of scooters in cluster
		cout << setw(6) << right << cluster_scooter_count[i];
		
		// average battery level of scooters in cluster
		cout << setw(15) << right << ((double)cluster_battery_total[i] / (double)cluster_scooter_count[i]);
		
		// percent of total scooters located in given cluster
		cout << setw(15) << right << (((double)cluster_scooter_count[i] / (double)scooter_location.size()) * 100)  << endl;
	}
	*/
	
	// write data to appropriate file for final evaluation
	if (write_cluster_data("cluster_data.csv", cluster_scooter_count, cluster_battery_total, scooter_location.size())) {
		cout << "Data saved successfully." << endl;
	}
	
	return 0;
}

// FUCNTION DEFINTIONS

// FUNCTION: distance()
// calculate the distance between two point values (class type) and returns it
double distance(Point &pt1, Point &pt2) {
	// use pythagorean's theorem to calculate distance
	return (sqrt(pow((pt1.getX() - pt2.getX()), 2) + pow((pt1.getY() - pt2.getY()), 2)));
}

// FUNCTION: open_scooter_data()
// open the appropraite data file and read in x-y coordinates 
bool open_scooter_data(string filename, vector<Point> &pt_vect, vector<int> &batt_vect) {
	ifstream fin;  // stream variable for reading from data file
	int scooter_ID(0), temp_batt(0);  // temporary values for battery level and scooter ID
	double temp_x(0), temp_y(0);  // temporary variables for x-y cooridnates
	Point temp_pt;  // temporary variabled for Point to be added to vector
		
	fin.open(filename, ios::in);
	
	// if file is not opened, exit function with error message
	if (!fin.is_open()) { 
		cout << "ERROR: Data file not accessible." << endl; 
		return false;
	}
	
	while (!fin.eof()) {		
		fin >> scooter_ID;  // scooter ID number (irrelevant to data manipulation)
		fin >> temp_x;  // scooter x-coordinate		
		fin >> temp_y;  // scooter y-coordinate		
		fin >> temp_batt;  // scooter battery level
		
		temp_pt.setX(temp_x);  // apply changes to the temporaray Point variable
		temp_pt.setY(temp_y);
		pt_vect.push_back(temp_pt);  // add point to appropriate vecotor		
		batt_vect.push_back(temp_batt);  // add to battery level vector
	}
	
	fin.close();
	
	return true;
}

bool write_cluster_data(const &string filename, const vector<int> &cl_count, const vector<int> &cl_batt_total, const int &scooter_total) {
	ofstream fout;
	
	// open file specified
	fout.open(filename.c_str(), ios::ate);
	// check if file is open
	if (!fout.is_open()) {
		cout << "ERROR: Could not access/create " << filename << endl;
		return false;
	}
	
	// check data is equal in vector length before writing
	if (cl_batt_total.size() != cl_count.size()) {
		cout << "ERROR: Cluster battery total and cluster count not equal." << endl;
		return false;
	}
	
	// place collumn titles in file location
	fout << "cluster_ID" << "," << "cluster_total" << "," << "percent_scooters" << "," << "battery_average" << endl;
	
	// print data to appropriate collumns
	for (int i(0); i < cl_count.size(); ++i) {
		fout << i << ",";
		fout << cl_count[i] << ",";
		fout << (((double)cl_count[i] / (double)scooter_total) * 100) << ",";
		fout << ((double)cl_batt_total[i] / (double)cl_count[i]) << "," << endl;
	}
	
	fout.close();
	
	return true;
}

































