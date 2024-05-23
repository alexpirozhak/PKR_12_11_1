#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Bus {
    int busNumber;
    string driverName;
    int routeNumber;
    Bus* next;
    Bus* prev;
};

// Додавання автобуса до списку
void addBus(Bus*& head, int busNumber, string driverName, int routeNumber) {
    Bus* newBus = new Bus{busNumber, driverName, routeNumber, nullptr, nullptr};
    if (!head) {
        head = newBus;
    } else {
        Bus* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newBus;
        newBus->prev = current;
    }
}

// Видалення автобуса зі списку
void removeBus(Bus*& fromList, Bus*& toList, int busNumber) {
    if (!fromList) {
        cout << "Bus not found.\n";
        return;
    }

    Bus* current = fromList;
    while (current && current->busNumber != busNumber) {
        current = current->next;
    }

    if (current) {
        if (current->prev) {
            current->prev->next = current->next;
        } else {
            fromList = current->next;
        }

        if (current->next) {
            current->next->prev = current->prev;
        }

        current->next = nullptr;
        current->prev = nullptr;

        if (!toList) {
            toList = current;
        } else {
            Bus* toListCurrent = toList;
            while (toListCurrent->next) {
                toListCurrent = toListCurrent->next;
            }
            toListCurrent->next = current;
            current->prev = toListCurrent;
        }
    } else {
        cout << "Bus not found.\n";
    }
}

// Виведення інформації про автобуси
void printBuses(Bus* head) {
    Bus* current = head;
    while (current) {
        cout << "Bus Number: " << current->busNumber << ", Driver: " << current->driverName << ", Route: " << current->routeNumber << endl;
        current = current->next;
    }
}

// Збереження списку автобусів у файл
void saveToFile(Bus* head, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cout << "Error opening file for writing.\n";
        return;
    }
    Bus* current = head;
    while (current) {
        outFile << current->busNumber << " " << current->driverName << " " << current->routeNumber << endl;
        current = current->next;
    }
    outFile.close();
}

// Завантаження списку автобусів із файлу
void loadFromFile(Bus*& head, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Error opening file for reading.\n";
        return;
    }
    head = nullptr;
    int busNumber;
    string driverName;
    int routeNumber;
    while (inFile >> busNumber >> driverName >> routeNumber) {
        addBus(head, busNumber, driverName, routeNumber);
    }
    inFile.close();
}

// Меню програми
int main() {
    Bus* park = nullptr;
    Bus* onRoute = nullptr;
    int choice;
    do {
        cout << "1. Add Bus to Park\n";
        cout << "2. Remove Bus from Park to Route\n";
        cout << "3. Remove Bus from Route to Park\n";
        cout << "4. Print Buses in Park\n";
        cout << "5. Print Buses on Route\n";
        cout << "6. Save Buses to File\n";
        cout << "7. Load Buses from File\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1: {
                int busNumber;
                string driverName;
                int routeNumber;
                cout << "Enter bus number: ";
                cin >> busNumber;
                cout << "Enter driver name: ";
                cin.ignore();
                getline(cin, driverName);
                cout << "Enter route number: ";
                cin >> routeNumber;
                addBus(park, busNumber, driverName, routeNumber);
                break;
            }
            case 2: {
                int busNumber;
                cout << "Enter bus number to remove from park: ";
                cin >> busNumber;
                removeBus(park, onRoute, busNumber);
                break;
            }
            case 3: {
                int busNumber;
                cout << "Enter bus number to remove from route: ";
                cin >> busNumber;
                removeBus(onRoute, park, busNumber);
                break;
            }
            case 4:
                printBuses(park);
                break;
            case 5:
                printBuses(onRoute);
                break;
            case 6: {
                string filename;
                cout << "Enter filename to save: ";
                cin >> filename;
                saveToFile(park, filename);
                break;
            }
            case 7: {
                string filename;
                cout << "Enter filename to load: ";
                cin >> filename;
                loadFromFile(park, filename);
                break;
            }
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);
}


