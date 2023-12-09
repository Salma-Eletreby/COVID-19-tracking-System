//Salma Eletreby & Alshayma & Fajer
#include <iostream>	//header file for cin & cout
#include <fstream>	//header file for file processing
#include <string>	//header file for string variables
using namespace std;
int main()
{
	int choice;	//variable decleration for the menu

	//variable and file declerations that will be used in all cases
	long int tCases, nCases, tDeath, nDeath;
	int ctryCode;
	string ctryName, header, record;
	fstream COVID;	//for both read & write operations

	//code to get number of lines (used later in the code)
	int no_lines = 0;
	string data;

	COVID.open("Covid19_information.txt");
	COVID.ignore(256, '\n');
	while (getline(COVID, data))
	{
		no_lines++;
	}
	COVID.close();

	do
	{
		//displays menu with choices
		cout << "COVID 19 tracking system: \n \t [1] Add a record of a new country. \n";
		cout << "\t [2] List the information of all countries. \n \t [3] Search for a specific country.";
		cout << "\n \t [4] Display a report of all countries with total number of cases higher than a specified value from user.";
		cout << "\n \t [5] End." << endl;
		cout << "Your choice: ";
		cin >> choice;

		switch (choice)
		{
			case 1: //Alshaima - adding a record
			{
				//displaying to the user what they picked
				cout << "You chose:  Add a record of a new country." << endl << "__________________" << endl << endl;

				COVID.open("Covid19_information.txt", ios::app); //opening file - app indicates end of file

				ctryCode = ++no_lines; //automatically assigns country code

				//display what the users needs to input and save it in variables
				cout << "\tEnter country name: ";
				cin >> ctryName;
				cout << "\tEnter total cases: ";
				cin >> tCases;
				cout << "\tEnter number of New cases: ";
				cin >> nCases;
				cout << "\tEnter number of deaths: ";
				cin >> tDeath;
				cout << "\tEnter number of new deaths: ";
				cin >> nDeath;

				//writes the data to the files
				COVID << endl << ctryCode << "\t \t" << ctryName << '\t' << tCases << "\t \t" << nCases << "\t \t \t" << tDeath << '\t' << nDeath; // inserting data into the txt file
				COVID.close(); // closes the file

				cout << "\nYou made a valid country record, and record is saved." << endl << "__________________" << endl << endl;
			}
				break;
			case 2: //Salma - list information 
			{
				//displaying to the user what they picked
				cout << "You chose: List the information of all countries." << endl << "__________________" << endl << endl;

				COVID.open("Covid19_information.txt");	//opens file

				getline(COVID, header);
				cout << header << endl;

				//loop to get all lines in a file
				while (COVID >> ctryCode)
				{
					cout << ctryCode;
					getline(COVID, record);
					cout << record << endl;
				}

				COVID.close();
				cout << "__________________" << endl << endl;

			}
				break;
			case 3: //Salma - search for specific country
			{
				//displaying to the user what they picked
				cout << "You chose: Search for a specific country." << endl << "__________________" << endl << endl;

				int ctryCode_user; 	//variables we need that have not been declared
				
				//displays a list of countries and their country code
				COVID.open("Covid19_information.txt");
				COVID.ignore(256, '\n');
				cout << "Country codes:" << endl;
				while (COVID >> ctryCode)
				{
					string disregard;
					cout << '\t' << ctryCode;
					COVID >> ctryName;
					cout << '\t' << ctryName << endl;
					getline(COVID, disregard);
				}
				COVID.close();

				//displays what the user needs to input and store it in variables
				cout << endl << "Please enter desired country code: ";
				cin >> ctryCode_user;

				//loop to validate data - ensure it is in range
				while (ctryCode_user > no_lines || ctryCode_user <= 0)
				{
					cout << "\nInvalid. Country code entered doesn't exist." << endl;
					cout << "Please enter valid country code: ";
					cin >> ctryCode_user;
					cout << endl;
				}

				COVID.open("Covid19_information.txt");	//open file

				getline(COVID, header);
				COVID >> ctryCode;
				
				//loop to get country code that the user asked for
				while (!(ctryCode_user == ctryCode))
				{
					COVID.ignore(256, '\n');
					COVID >> ctryCode;
				}
 
				getline(COVID, record); //gets the respective record of country code
				cout << endl << header << endl << ctryCode << record << endl;

				COVID.close(); //close file

				cout << "__________________" << endl << endl;

			}
				break;
			case 4: //Fajer - display countires with higher total cases then user 
			{
				//displaying to the user what they picked
				cout << "You chose: ";
				cout << "Display a report of all countries with total number of cases higher than a specified value from user." << endl;
				cout << "__________________" << endl << endl;

				long int user_tCases; //variables we need that have not been declared
				cout << "Enter your specified value to get Total cases higher than your value : ";
				cin >> user_tCases;
				cout << endl;

				COVID.open("Covid19_information.txt");

				int i = 1;
				
				if (COVID.is_open()) //checks if file exists and is open
				{
					string line;

					while (getline(COVID, line))// condition to get lines from file
					{
						COVID >> ctryCode >> ctryName >> tCases >> nCases >> tDeath >> nDeath;// data input from file
						if (user_tCases > tCases)
							cout << "";
						else
						{
							i++;
							if (user_tCases < tCases) // checks if user value is smaller than total case
							{
								//cout << line;
								cout << endl << ctryCode << "\t \t" << ctryName << "\t" << tCases;
								cout << "\t \t" << nCases << "\t \t \t" << tDeath << "\t" << nDeath;

							}
						}
					}
					if (i == 1) //if value entered is greater than in database
						cout << "\nUser Value entered is greater than Total Case value of countries in database. " << endl;
				}
				else {
					cout << "file not found!!!";
				}
				COVID.close();
				cout << endl << "__________________" << endl << endl;
			}
				break;
			case 5: cout << "Thank you for using our program. Come again!" << endl;
				break;
			default:
			{
				//If number smaller than zero or greater than 5 entered
				cout << "Inavlid input entered. Please try again." << endl;
				cout << "Please enter a number in between 1 and 5." << endl;
				cout << endl;
			}
		}
	} while (choice < 5 || choice > 5); //condition to continue loop
	return 0;
}
