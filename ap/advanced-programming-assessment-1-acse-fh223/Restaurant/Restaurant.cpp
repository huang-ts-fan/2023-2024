#include "Restaurant.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Meal implementation
Meal::Meal(string name, float price) : name(name), price(price), sauce("None") {}

// Ask the user if they want any special sauce with their meal
void Meal::chooseSauce() {
    cout << "Do you want any special sauce with your " << name << "? (Enter 'None' or sauce name): ";
    cin >> sauce;
    cout << "You've chosen " << (sauce != "None" ? sauce : "no") << " sauce for your " << name << "." << endl;
}

// Describe the meal
void Meal::describe() const {
    cout << name << " with " << (sauce != "None" ? sauce : "no") << " sauce - £" << price << endl;
}

// Side implementation
Side::Side(string name, float price, bool spicy) : name(name), price(price), spicy(spicy), sauce("None") {}

// Ask the user if they want their side to be spicy
void Side::askSpicy() {
    cout << "Do you want your " << name << " to be spicy? (1 for Yes, 0 for No): ";
    int choice;
    cin >> choice;
    spicy = (choice == 1);
}

// Ask the user if they want any special sauce with their side
void Side::chooseSauce() {
    cout << "Do you want any special sauce with your " << name << "? (Enter 'None' or sauce name): ";
    cin >> sauce;
    cout << "You've chosen " << (sauce != "None" ? sauce : "no") << " sauce for your " << name << "." << endl;
}

// Describe the side
void Side::describe() const {
    cout << name << (spicy ? " (Spicy)" : "") << " with " << (sauce != "None" ? sauce : "no") << " sauce - £" << price << endl;
}

// Drink implementation
Drink::Drink(string name, float price) : name(name), price(price) {}

// Describe the drink
void Drink::describe() const {
    cout << name << " - £" << price << endl;
}

// Show the meal options
void showMealOptions(const vector<Meal>& meals) {
    cout << "Please choose a meal (Enter 0 to skip):" << endl;
    cout << "0. None" << endl; 
    for (int i = 0; i < meals.size(); ++i) {
        cout << i + 1 << ". " << meals[i].name << " - £" << meals[i].price << endl;
    }
}

// Show the side options
void showSideOptions(const vector<Side>& sides) {
    cout << "Please choose a side (Enter 0 to skip):" << endl;
    cout << "0. None" << endl; 
    for (int i = 0; i < sides.size(); ++i) {
        cout << i + 1 << ". " << sides[i].name << " - £" << sides[i].price << endl;
    }
}

// Show the drink options
void showDrinkOptions(const vector<Drink>& drinks) {
    cout << "Please choose a drink (Enter 0 to skip):" << endl;
    cout << "0. None" << endl; 
    for (int i = 0; i < drinks.size(); ++i) {
        cout << i + 1 << ". " << drinks[i].name << " - £" << drinks[i].price << endl;
    }
}
