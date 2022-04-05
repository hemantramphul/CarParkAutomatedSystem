#pragma once
#define _GNU_SOURCE //to remove warning: implicit declaration of ‘strptime’
#include<iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <ctime>
#include <vector>
#include "Helper.h"

using namespace std;

string pathRecord = "record.txt";
string pathTemp = "temp.txt";
string pathHistory = "history.txt";
char pound = 156;

void writeEntry(string plate) {
	std::ofstream outfile;

	outfile.open(pathRecord, std::ios_base::app); // append instead of overwrite

	// Number; DateTimeEntry; DateTimeExit; Price
	outfile << plate << "," << getNowTime() << "," << "," << ";" << "\n";
}

void writeExit(string plate, string dtEntry, string dtExit, double hours, double price) {
	std::ofstream outfile;

	outfile.open(pathHistory, std::ios_base::app); // append instead of overwrite

	// Number; DateTimeEntry; DateTimeExit; Parking Hours; Price
	outfile << plate << "," << dtEntry << "," << dtExit << "," << hours << "," << price << ",;" << "\n";
}


string searchText(string plate) {
	ifstream in(pathRecord);
	string line;
	string f = "";

	if (!in.is_open())
	{
		cout << "Unable to open " << pathRecord << ", please make sure file exists!" << endl;
	}

	ofstream out(pathTemp); //temp file that will have our records with out the deleted line
	
	//Now our file (record.txt) is open lets loop through an find our customer name which was
	while (getline(in, line))
	{
		std::size_t found = line.find(plate);
		//if last name is found delete the whole line			
		if (found != std::string::npos) {
			f = line;
		}
		else {
			out << line << "\n";
		}
	}

	//close our files, because were done!
	in.close();
	out.close();

	//delete the original file
	remove("record.txt");
	//rename old to new
	rename("temp.txt", "record.txt");
	//system("pause");

	return f;
}

double calculatePriceForParking(double hours) {
	double price = 0; // less than 30 minutes

	// Up to 1 hour
	if ((hours >= 0.5) && (hours < 1)) {
		price = 1.50;
	}

	// Up to 2 hours
	if ((hours >= 1) && (hours < 2)) {
		price = 3.00;
	}

	// Up to 4 hours
	if ((hours >= 2) && (hours < 4)) {
		price = 5.00;
	}

	// Up to 8 hours
	if ((hours >= 4) && (hours < 8)) {
		price = 15.00;
	}

	// Over 8 hours
	if (hours > 8) {
		price = 30.00;
	}

	cout << "\nPrice\t: " << pound << price << "\n";

	return price;
}

void calculate(string exit) {
	vector<string> record = split_c(exit);

	if (record.size() >= 1) {
		string exitTime = getNowTime();

		cout << "\n[ENTRY DETAILS]\nVehicle\t: " << record[0] << "\nDate\t: " << record[1];
		cout << "\n\n[EXIT DETAILS]\nExit at\t: " << exitTime;

		string nowT(exitTime);
		string vehicleT(record[1]);

		char* time1 = &vehicleT[0];// end
		char* time2 = &nowT[0];// beg
		struct tm tm1, tm2; // intermediate datastructes 
		time_t t1, t2; // used in difftime

		//(1) convert `String to tm`:  (note: %T same as %H:%M:%S)  
		if (strptime(time1, "%Y/%m/%d %T", &tm1) == NULL)
			printf("\nstrptime failed-1\n");
		if (strptime(time2, "%Y/%m/%d %T", &tm2) == NULL)
			printf("\nstrptime failed-2\n");

		//(2) convert `tm to time_t`:    
		t1 = mktime(&tm1);
		t2 = mktime(&tm2);
		//(3) Convert Seconds into hours
		double hours = difftime(t2, t1) / 60 / 60;
		cout << "\nHours\t: " << hours;

		double price = calculatePriceForParking(hours);

		// Number; DateTimeEntry; DateTimeExit; Parking Hours; Price
		writeExit(record[0], record[1], exitTime, hours, price);
	}
}

void entryVehicle() {
	string plate = "";
	cout << "[ENTRY] Enter vehicle plate no:\t";
	cin >> plate;
	writeEntry(plate);
}

void exitVehicle() {
	string plate = "";
	cout << "[EXIT] Enter vehicle plate no:\t";
	cin >> plate;

	string found = searchText(plate);
	if (found.size() > 0) {
		calculate(found);
	}
	else {
		cout << "\nVehicle not found with " << plate << " plate number !!\n";
	}
}

void viewAll() {
	ifstream ifs(pathRecord);

	if (ifs.is_open())
	{
		std::string line;
		vector<string> record;

		cout << "Plate No\t\tEntry DateTime" << endl;
		cout << "-----------\t\t--------------------" << endl;
		while (!ifs.eof()) // for each vehicle word read from the file 
		{
			std::getline(ifs, line, ';');
			record = split_c(line);

			if (record.size() >= 1) {
				cout << record[0] << "\t\t" << record[1];
			}
		}
		cout << "\n";
		ifs.close();
	}
}

void viewHistory() {
	ifstream ifs(pathHistory);

	if (ifs.is_open())
	{
		std::string line;
		vector<string> record;

		// Number; DateTimeEntry; DateTimeExit; Parking Hours; Price

		cout << "Plate No\tEntry DateTime\t\tExit DateTime\t\tParking Hours\tPrice\t" << endl;
		cout << "-----------\t-----------\t\t-----------\t\t-----------\t-----------\t" << endl;
		while (!ifs.eof()) // for each vehicle word read from the file 
		{
			std::getline(ifs, line, ';');
			record = split_c(line);

			if (record.size() >= 1) {
				cout << record[0] << "\t\t"; //Number
				cout << record[1] << "\t"; //DateTimeEntry
				cout << record[2] << "\t"; //DateTimeExit
				cout << std::fixed << std::setprecision(2) << stod(record[3]); //Parking Hours
				cout << "\t\t" << pound << record[4] << "\t"; //Price
			}
		}
		cout << "\n";
		ifs.close();
	}
}

void parking_prices() {
	// Parking prices
	cout << "Duration\t\tPrice" << endl;
	cout << "-----------\t\t-----------\t" << endl;
	cout << "less than 30 minutes\tFREE" << endl;
	cout << "Up to 1 hour\t\t" << pound << "1.50" << endl;
	cout << "Up to 2 hours\t\t" << pound << "3.00" << endl;
	cout << "Up to 4 hours\t\t" << pound << "5.00" << endl;
	cout << "Up to 8 hours\t\t" << pound << "15.00" << endl;
	cout << "Over 8 hours\t\t" << pound << "30.00" << endl;
	cout << endl;
}