#include <gtest/gtest.h>
//#include "../main.cpp"

#include <iostream>
#include <string>

using namespace std;

// Структура для зберігання інформації про автобус
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

// Функція для перевірки списку (для тестів)
string listToString(Bus* head) {
    string result;
    Bus* current = head;
    while (current) {
        result += to_string(current->busNumber) + " ";
        current = current->next;
    }
    return result;
}


TEST(BusListTest, AddBus) {
    Bus* head = nullptr;

    addBus(head, 1, "Driver1", 101);
    addBus(head, 2, "Driver2", 102);
    addBus(head, 3, "Driver3", 103);

    string expected = "1 2 3 ";
    ASSERT_EQ(listToString(head), expected);

    while (head) {
        Bus* temp = head;
        head = head->next;
        delete temp;
    }
}
