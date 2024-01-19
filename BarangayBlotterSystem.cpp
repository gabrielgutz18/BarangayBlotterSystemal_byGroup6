#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <cstring>
#include <cctype>

using namespace std;

struct Citizen {
    string personName;
    string address;
    int age;
};

struct BlotterCase {
    string personName;
    string report;
    string date;
};

struct BlotterRecord {
    string personName;
    string report;
    string date;

    bool operator<(const BlotterRecord& other) const {
        return date < other.date;
    }
};

struct Official {
    string position;
    string name;
};

string generateRandomName() {
    string names[] = {"John Paul Vibal", "Crissa Arias ", "Robert Anthony Macam", "Lennard Monteiro", "Charles Mirando", "John Del Matalog", "Gian Hachaso", "Arturo Rovales", "Jeorge Assis Malabanan", "Sophia Toning"};
    return names[rand() % 10];
}

string generateRandomAddress() {
    string streets[] = {"Main St", "Oak Ave", "Elm Blvd", "Pine Rd", "Cedar Ln", "Birch Ct", "Maple Dr", "Spruce Ln", "Pineapple St", "Mango Ave"};
    return to_string(rand() % 1000 + 1) + " " + streets[rand() % 10];
}

int generateRandomAge() {
    return rand() % 50 + 18;
}

int findPersonIndex(const vector<Citizen>& citizens, const string& personName) {
    auto it = find_if(citizens.begin(), citizens.end(),
                      [&](const Citizen& c) {
                          return (strcasecmp(c.personName.c_str(), personName.c_str()) == 0);
                      });

    if (it != citizens.end()) {
        return distance(citizens.begin(), it);
    } else {
        return -1;
    }
}

bool isValidDate(const string& date) {
    if (date.length() != 10 || date[4] != '-' || date[7] != '-') {
        return false;
    }

    int year, month, day;
    try {
        year = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day = stoi(date.substr(8, 2));
    } catch (const invalid_argument& e) {
        return false;
    }

    if (year < 2024 || year > 2026 || month < 1 || month > 12 || day < 1 || day > 31) {
        return false;
    }

    if (month == 2 && day > 29) {
        return false;
    }

    return true;
}

void displayCitizens(const vector<Citizen>& citizens, unordered_set<string>& displayedNames) {
    cout << "List of Citizens in Brgy. Anastacia:" << endl;
    for (const auto& citizen : citizens) {
        if (displayedNames.find(citizen.personName) == displayedNames.end()) {
            cout << "Name: " << citizen.personName << endl;
            cout << "Address: " << citizen.address << endl;
            cout << "Age: " << citizen.age << endl;
            cout << "-----------------------------------------------" << endl;
            displayedNames.insert(citizen.personName);
        }
    }
}

void displayBlotterCases(const vector<BlotterCase>& blotterCases) {
    cout << "List of Blotter Cases:" << endl;
    for (const auto& blotterCase : blotterCases) {
        cout << "Person: " << blotterCase.personName << endl;
        cout << "Report: " << blotterCase.report << endl;
        cout << "Date: " << blotterCase.date << endl;
        cout << "-----------------------------------------------" << endl;
    }
}

void displaySuccessfulCases(const vector<BlotterRecord>& successfulCases) {
    cout << "List of Successful Blotter Cases (Sorted by Date):" << endl;
    for (const auto& successfulCase : successfulCases) {
        cout << "Person: " << successfulCase.personName << endl;
        cout << "Report: " << successfulCase.report << endl;
        cout << "Date: " << successfulCase.date << endl;
        cout << "-----------------------------------------------" << endl;
    }
}

void displayStatistics(const vector<BlotterCase>& blotterCases, const vector<Official>& officials) {
    cout << "Statistics:" << endl;
    cout << "Total Blotter Cases: " << blotterCases.size() << endl;

    int successfulCases = count_if(blotterCases.begin(), blotterCases.end(),
                                   [](const BlotterCase& b) { return !b.report.empty(); });
    cout << "Successful Cases: " << successfulCases << endl;

    int casesInCurrentMonth = blotterCases.size(); // Placeholder for current month logic
    cout << "Cases in Current Month: " << casesInCurrentMonth << endl;

    cout << "Assigned Officials:" << endl;
    for (const auto& official : officials) {
        cout << "Position: " << official.position << endl;  // <-- Add closing quotation mark and semicolon here
        cout << "Name: " << official.name << endl;
        cout << "-----------------------------------------------" << endl;
    }
}

bool isNumeric(const string& str) {
    stringstream ss(str);
    int num;
    return (ss >> num >> ws).eof();
}

int main() {
    cout << "+---------------------------------------------------+" << endl;
    cout << "|   Hello! Welcome to Brgy.Anastacia Blotter System  |" << endl;
    cout << "+---------------------------------------------------+" << endl;

    const int maxCitizens = 200;
    vector<Citizen> citizens;
    vector<BlotterCase> blotterCases;
    vector<BlotterRecord> successfulCases;
    vector<Official> officials = {{"Chairman", "Juan Dela Cruz"}, {"Kagawad", "Maria Santos"}};
    unordered_set<string> displayedNames;

    srand(time(0));

    for (int i = 0; i < maxCitizens; ++i) {
        Citizen randomCitizen;
        randomCitizen.personName = generateRandomName();
        randomCitizen.address = generateRandomAddress();
        randomCitizen.age = generateRandomAge();
        citizens.push_back(randomCitizen);
    }

    int choice;
    string input;
    bool invalidChoice = false;

    do {
        displayedNames.clear(); // Clear displayedNames at the start of the loop

        if (invalidChoice) {
            cout << "Your input is wrong. Enter your choice" << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        cout << "Please select an option:" << endl;
        cout << "1. File a Blotter Case" << endl;
        cout << "2. View Citizens" << endl;
        cout << "3. View Existing Blotter Cases" << endl;
        cout << "4. View Statistics" << endl;
        cout << "5. View Successful Cases" << endl;
        cout << "6. Exit" << endl;
        cout << "7. Add New Citizen and File Blotter Case" << endl;
        cout << "Enter your choice (1, 2, 3, 4, 5, 6, or 7): ";

        cin >> input;

        if (!isNumeric(input)) {
            invalidChoice = true;
            continue;
        }

        choice = stoi(input);
        invalidChoice = false;

        switch (choice) {
            case 1: {
                cout << "You chose to file a blotter case." << endl;

                displayCitizens(citizens, displayedNames);

                string personToBlotter;
                bool personNotFound;
                do {
                    personNotFound = false;
                    cout << "Enter the name of the person being blottered (type 'exit' to go back): ";

                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    getline(cin, personToBlotter);

                    if (personToBlotter == "exit") {
                        break;
                    }

                    int personIndex = findPersonIndex(citizens, personToBlotter);

                    if (personIndex != -1) {
                        cout << "Person found!" << endl;
                        cout << "Name: " << citizens[personIndex].personName << endl;
                        cout << "Address: " << citizens[personIndex].address << endl;
                        cout << "Age: " << citizens[personIndex].age << endl;

                        string reportDetails;
                        cout << "Enter the report details: ";
                        getline(cin, reportDetails);

                        string date;
                        do {
                            cout << "Enter the date of the blotter case (YYYY-MM-DD): ";
                            getline(cin, date);

                            if (!isValidDate(date)) {
                                cout << "Invalid date format or out of range. Please enter a valid date." << endl;
                            }
                        } while (!isValidDate(date));

                        BlotterCase newCase = {citizens[personIndex].personName, reportDetails, date};
                        blotterCases.push_back(newCase);

                        if (!newCase.report.empty()) {
                            BlotterRecord successfulCase = {citizens[personIndex].personName, reportDetails, date};
                            successfulCases.push_back(successfulCase);
                        }

                        cout << "Blotter case filed successfully!" << endl;
                        cout << "Person: " << personToBlotter << endl;
                        cout << "Report: " << reportDetails << endl;
                        cout << "Date: " << date << endl;
                    } else {
                        cout << "Person not found in the list. Please enter a valid person name." << endl;
                        personNotFound = true;
                    }
                } while (personNotFound);
            }
            break;
            case 2:
                displayCitizens(citizens, displayedNames);
                break;
            case 3:
                displayBlotterCases(blotterCases);
                break;
            case 4:
                displayStatistics(blotterCases, officials);
                break;
            case 5:
                sort(successfulCases.begin(), successfulCases.end());
                displaySuccessfulCases(successfulCases);
                break;
            case 6:
                cout << "Exiting the program. Thank you!" << endl;
                break;
            case 7: {
                cout << "You chose Add New Citizen and File Blotter Case." << endl;

                cin.ignore(numeric_limits<streamsize>::max(), '\n');

                string newPersonName;
                int newPersonAge;
                string newPersonAddress;

                cout << "Enter the name of the new citizen: ";
                getline(cin, newPersonName);

                if (newPersonName == "exit") {
                    break;
                }

                auto existingCitizen = find_if(citizens.begin(), citizens.end(),
                                               [&](const Citizen& c) {
                                                   return c.personName == newPersonName;
                                               });

                if (existingCitizen != citizens.end()) {
                    cout << "Person already exists in the list." << endl;
                    break;
                }

                cout << "Enter the age of the new citizen: ";
                cin >> newPersonAge;
                cin.ignore();

                cout << "Enter the address of the new citizen: ";
                getline(cin, newPersonAddress);

                Citizen newCitizen;
                newCitizen.personName = newPersonName;
                newCitizen.age = newPersonAge;
                newCitizen.address = newPersonAddress;
                citizens.push_back(newCitizen);

                string reportDetails;
                cout << "Enter the report details: ";
                getline(cin, reportDetails);

                string date;
                do {
                    cout << "Enter the date of the blotter case (YYYY-MM-DD): ";
                    getline(cin, date);

                    if (!isValidDate(date)) {
                        cout << "Invalid date format or out of range. Please enter a valid date." << endl;
                    }
                } while (!isValidDate(date));

                BlotterCase newCase = {newPersonName, reportDetails, date};
                blotterCases.push_back(newCase);

                if (!newCase.report.empty()) {
                    BlotterRecord successfulCase = {newPersonName, reportDetails, date};
                    successfulCases.push_back(successfulCase);
                }

                cout << "New citizen added successfully, and blotter case filed!" << endl;
                cout << "Name: " << newPersonName << endl;
                cout << "Age: " << newPersonAge << endl;
                cout << "Address: " << newPersonAddress << endl;
                cout << "Report: " << reportDetails << endl;
                cout << "Date: " << date << endl;

                displayCitizens(citizens, displayedNames);
            }
            break;

            default:
                invalidChoice = true;
                break;
        }
    } while (choice != 6);

    return 0;
}
