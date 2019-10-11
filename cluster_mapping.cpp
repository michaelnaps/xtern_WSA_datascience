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
#include <fstream>
#include <string>
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

int main()
{
	vector<Point> scooter_location;  // x-y coordinates for all scooters
	vector<int> battery_level;  // battery levels for all scooters
	vector<int> cluster_battery_total;  // vector for the battery totals within each cluster
	vector<int> cluster_scooter_count(19, 0);  // initialize all cluster counts to 0
	
	// point coordinates for all cluster centers (approximations)
	Point cluster0, cluster1, cluster2, cluster3, cluster4;
	Point cluster5, cluster6, cluster7, cluster8, cluster9;
	Point cluster10, cluster11, cluster12, cluster13, cluster14;
	Point cluster15, cluster16, cluster17, cluster18;
	
	// set x-y coordinates for all cluster centers (approximations)
	cluster0.setXY(-0.2629, 0.0257554);
	cluster1.setXY(-0.14166, 0.044576);
	cluster2.setXY(-0.121695, 0.032001745);
	cluster3.setXY(-0.15734775, -0.225367);
	cluster4.setXY(-0.0783579, -0.089191762);
	cluster5.setXY(0.25259396, -0.255784);
	cluster6.setXY(0.3670516, -0.133839);
	cluster7.setXY(0.224613, -0.0397119);
	cluster8.setXY(0.2248988, 0.128302156);
	cluster9.setXY(0.4084014, 0.05894188);
	cluster10.setXY(0.753407026, 0.582915994);
	cluster11.setXY(0.899725064, 0.79902133);
	cluster12.setXY(0.971003419, 0.729568099);
	cluster13.setXY(0.940631136, 0.897551968);
	cluster14.setXY(0.598929847, 1.028950732);
	cluster15.setXY(1.342009952, 0.878407338);
	cluster16.setXY(0.83996793, 1.163331194);
	cluster17.setXY(0.961196543, 1.296743324);
	cluster18.setXY(1.16733764, 1.3264618);
	
	if (open_scooter_data("data_set_simplified_format.txt", scooter_location, battery_level)) {
		for (int i(0); i < scooter_location.size(); ++i) {
			if (distance(cluster0, scooter_location[i]) < 0.35) {
				cluster_battery_total[0] += battery_level[i];
				++cluster_scooter_count[0];
			}
			else if (distance(cluster1, scooter_location[i]) < 0.35) {
				cluster_battery_total[1] += battery_level[i];
				++cluster_scooter_count[1];
			}
		}
	}
	
	for (int i(0); i < cluster_scooter_count.size(); ++i) {
		cout << "There are " << cluster_scooter_count[i] << " scooters in cluster " << i << "." << endl;
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
	
	cout << "Data file read in successfully." << endl;
	
	fin.close();
	
	return true;
}


































