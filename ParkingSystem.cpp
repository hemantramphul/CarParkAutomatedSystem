#include<iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include "Header.h"
using namespace std;

void main() {
	int user_input;

	// Menu
	while (true)
	{
		cout << endl;
		cout << "#########################################################" << endl;
		cout << "#                   Parking Systems                     #" << endl;
		cout << "#########################################################" << endl;
		cout << "Press 1\t: Entry of a vehicle" << endl;
		cout << "Press 2\t: Exit of a vehicle" << endl;
		cout << "Press 3\t: View all vehicles still in parking" << endl;
		cout << "Press 4\t: View history" << endl;
		cout << "Press 5\t: View parking prices" << endl;
		cout << endl;
		cout << "Action\t: ";
		cin >> user_input;
		cout << "#########################################################\n" << endl;

		switch (user_input) {
			case 1:
				// Press 1: Entry of a vehicle
				entryVehicle();
				break;
			case 2:
				// Press 2: Exit of a vehicle
				exitVehicle();
				break;
			case 3:
				// Press 3: View all vehicles
				viewAll();
				break;
			case 4:
				// Press 4: View history
				viewHistory();
				break;
			case 5:
				// Press 5: View parking prices
				parking_prices();
				break;
		}
	}
}