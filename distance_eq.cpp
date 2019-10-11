// File: distance_eq.cpp
// Created by: Michael Napoli
// Created on: 10/10/2019

/*
	Program that reads in x and y values for scooter locations
	and calculates their distance from the bus parking spot.
	
	Assumptions made about prompt:
		- a given point on the x-y plane is equal to 1 mile
		- the bus will travel to the first cluster at maximum speed (average 50 mph)
		- the bus will travel in between clusters at maximium speed (average 50 mph)
		- travel time between scooters within a given cluster is negligible
			- thus the time needed to charge all scooters in each cluster is equal to:
				time = (5 - average battery value of scooters in cluster) * (number of scooters in cluster)
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
bool open_scooter_data(const string &filename, vector<Point> &pt_vect, vector<int> &batt_vect);
bool write_vect_data(const string &filename, vector<double> &vec);

int main()
{
	Point BUS_LOC;  // location of bus
	vector<Point> scooter_location;
	vector<int> battery_level;
	vector<double> scooter_distance;
	double d_total(0), d_average(0);
	double battery_total(0), battery_average(0);
	
	BUS_LOC.setX(20.19);
	BUS_LOC.setY(20.19);
	
	// if battery_level and scooter_location are not equal, the vectors were in correctly assigned at some point
	if (battery_level.size() != scooter_location.size()) {
		cout << "ERROR: Battery vector length and location vector length not equal." << endl;
		return 0;
	}
	
	if (open_scooter_data("data_set_simplified_format.txt", scooter_location, battery_level)) {
		// loop that adds all distance values to a single total
		for (int i(0); i < scooter_location.size(); ++i) {
			scooter_distance.push_back(distance(BUS_LOC, scooter_location[i]));
			d_total += scooter_distance[i];
		}
		cout << "Total distance of all scooters from bus: " << d_total << endl;
			
		// calulate average distance from bus for all scooters
		d_average = (d_total / scooter_location.size());
		cout << "Average distance from bus: " << d_average << endl;
		
		// for loop that adds all battery power levels together
		for (int i(0); i < battery_level.size(); ++i) {
			battery_total =+ (double)battery_level[i];
		}
		battery_average = (battery_total / battery_level.size());  // find average of all battery levels
		cout << "Average battery charge for all scooters: " << battery_average << endl;
		cout << "Average time needed to charge scooter battery: " << (5 - battery_average) << " hours" << endl << endl;
		
		// save the distance data
		write_vect_data("distance_from_bus_data.csv", scooter_distance);
	}
	
	return 0;
}

// FUCNTION DEFINTIONS

// FUNCTION: distance()
// calculate the distance between two point values (class type) and returns it
double distance(Point &pt1, Point &pt2) {
	double distance;
	
	// calculate the distance between points using pythagorean's theorem
	distance = sqrt(pow((pt1.getX() - pt2.getX()), 2) + pow((pt1.getY() - pt2.getY()), 2));
	
	return distance;
}

// FUNCTION: open_scooter_data()
// open the appropraite data file and read in x-y coordinates 
bool open_scooter_data(const string &filename, vector<Point> &pt_vect, vector<int> &batt_vect) {
	ifstream fin;  // stream variable for reading from data file
	int scooter_ID(0), temp_batt(0);  // temporary values for battery level and scooter ID
	double temp_x(0), temp_y(0);  // temporary variables for x-y cooridnates
	Point temp_pt;  // temporary variabled for Point to be added to vector
		
	fin.open(filename, ios::in);
	
	// if file is not opened, exit function with error message
	if (!fin.is_open()) { 
		cout << "ERROR: Data file, " << filename << ", not accessible." << endl; 
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

bool write_vect_data(const string &filename, vector<double> &vec) {
	ofstream fout;
	
	fout.open(filename.c_str(), ios::ate);
	
	if (!fout.is_open()) {
		cout << "ERROR: The file " << filename << " did not open correctly." << endl;
		return false;
	}
	
	for (int i(0); i < vec.size(); ++i) {
		fout << vec[i] << "," << endl;
	}
	
	cout << "Distance data saved successfully." << endl;
	
	fout.close();
	
	return true;
}

































