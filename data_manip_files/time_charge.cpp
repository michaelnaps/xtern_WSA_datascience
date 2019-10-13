// File: time_charge.cpp
// Created by: Michael Napoli
// Created on: 10/12/2019

/* 
	Program that uses cluster averages to calculate the time
	required to charge all scooters in a given cluster to its
	maximum value (5).
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <fstream>
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
bool open_cluster_data(string filename, vector<int> &cluster_num, vector<double> &battery_average);
bool write_cluster_time(const string filename, const vector<double> &cluster_time);

int main()
{
	vector<int> cluster_scooters;
	vector<double> battery_level;
	vector<double> cluster_charge_time;
	double temp_charge_time(0);
	
	// if data file is opened and read successfully
	if (open_cluster_data("simplified_cluster_data.txt", cluster_scooters, battery_level)) {
		// loop through all cluster elements
		for (int i(0); i < battery_level.size(); ++i) {
			// calculate total time to charge all scooters individually
			temp_charge_time = (5 - battery_level[i]) * (double)cluster_scooters[i];
			cluster_charge_time.push_back(temp_charge_time);  // add to cluster time vector
		}
	}
	
	// write charge time data to .csv file for excel data evaluation
	if (write_cluster_time("time_per_cluster.csv", cluster_charge_time)) {
		cout << "Data saved successfully." << endl;
	}
	
	return 0;
}

// FUNCTION: distance()
// calculate the distance between two point values (class type) and returns it
double distance(Point &pt1, Point &pt2) {
	// use pythagorean's theorem to calculate distance
	return (sqrt(pow((pt1.getX() - pt2.getX()), 2) + pow((pt1.getY() - pt2.getY()), 2)));
}

// FUNCTION: open_scooter_data()
// open the appropraite data file and read in cluster data
bool open_cluster_data(string filename, vector<int> &cluster_num, vector<double> &battery_average) {
	ifstream fin;  // stream variable for reading from data file
	int cluster_ID(0), temp_scooter_num(0);  // temporary values for 
	double temp_cluster_percent(0), temp_batt_ave(0);
		
	fin.open(filename.c_str(), ios::in);
	
	// if file is not opened, exit function with error message
	if (!fin.is_open()) { 
		cout << "ERROR: Data file not accessible." << endl; 
		return false;
	}
	
	while (!fin.eof()) {		
		fin >> cluster_ID;  // cluster ID number (irrelevant to data manipulation)
		fin >> temp_scooter_num;  // temporary value for number of scooters
		fin >> temp_cluster_percent;  // percent of scooters in a given cluster (irrelevant to data manipulation)
		fin >> temp_batt_ave;  // cluster average battery level

		cluster_num.push_back(temp_scooter_num);
		battery_average.push_back(temp_batt_ave);  // add to battery average vector
	}
	
	fin.close();
	
	return true;
}

bool write_cluster_time(const string filename, const vector<double> &cluster_time) {
	ofstream fout;
	
	// open file specified
	fout.open(filename.c_str(), ios::ate);
	
	// check if file is open
	if (!fout.is_open()) {
		cout << "ERROR: Could not access/create " << filename << endl;
		return false;
	}
	
	// place collumn titles in file location
	fout << "cluster_ID" << "," << "scooter_charge_time" << "," << "bus_charge_time" << endl;
	
	// print data to appropriate collumns
	for (int i(0); i < cluster_time.size(); ++i) {
		fout << i << ",";  // cluster ID
		fout << cluster_time[i] << ",";  // time to charge all scooters individually
		fout << (cluster_time[i] / 100) << endl;  // time to charge using only bus (assumption bus hold 100 scooters)
	}
	
	fout.close();
	
	return true;
}

































