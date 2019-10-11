// File: distance_eq.cpp
// Created by: Michael Napoli
// Created on: 10/10/2019

/*
	Program that reads in x and y values for scooter locations
	and calculates their distance from the bus parking spot.
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
	double x;
	double y;
	
	public:
	void setX(double temp_x) { x = temp_x; }
	void setY(double temp_y) { y = temp_y; }
	
	double getX() { return x; }
	double getY() { return y; }
};

// FUNCTION INITIALIZATIONS
double distance(Point &pt1, Point &pt2);
bool open_scooter_data(string filename, vector<Point> &pt_vect, vector<int> &batt_vect);

int main()
{
	Point BUS_LOC;  // location of bus
	vector<Point> scooter_location;
	vector<int> battery_level;
	double d_total(0), d_average(0);
	
	BUS_LOC.setX(20.19);
	BUS_LOC.setY(20.19);
	
	if (battery_level.size() != scooter_location.size()) {
		cout << "ERROR: Battery vector length and location vector length not equal." << endl;
		return 0;
	}
	
	if (open_scooter_data("data_set_simplified_format.txt", scooter_location, battery_level)) {	
		for (int i(0); i < scooter_location.size(); ++i) {
			d_total += distance(scooter_location[i], BUS_LOC);
		}
		cout << "Total distance of all scooters from bus: " << d_total << endl;
			
		d_average = (d_total / scooter_location.size());
		cout << "Average distance from bus: " << d_average << endl;
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

































