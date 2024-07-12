#include "Restaurant.h"
#include <vector>
#include <iostream>

using namespace std;


// main implementation
int main() {
    // Create the meal, side, and drink options
    vector<Meal> meals;
    meals.push_back(Meal("Beef Burger", 5.99));
    meals.push_back(Meal("Chicken Burger", 5.69));
    meals.push_back(Meal("Veggie Burger", 5.49));
    meals.push_back(Meal("Beef Sandwich", 7.49));
    meals.push_back(Meal("Chicken Sandwich", 6.49));
    

    vector<Side> sides;
    sides.push_back(Side("Fries", 2.49));
    sides.push_back(Side("Onion Rings", 2.99));
    sides.push_back(Side("Salad", 3.49));

    vector<Drink> drinks;
    drinks.push_back(Drink("Coke", 1.99));
    drinks.push_back(Drink("Sprite", 1.99));
    drinks.push_back(Drink("Dr. Pepper", 1.99));
    drinks.push_back(Drink("Iced Tea", 1.99));
    drinks.push_back(Drink("Milkshake", 2.99));
    drinks.push_back(Drink("Soda", 1.99));
    drinks.push_back(Drink("Water", 0.99));
    drinks.push_back(Drink("Coffee", 2.49));

    cout << "Welcome to our Fast Food Restaurant!" << endl;

    // declare variables to store user choices and total price
    int mealChoice = -1, sideChoice = -1, drinkChoice = -1;
    float total = 0.0;

    // Show the options and ask the user to choose
    showMealOptions(meals);
    cin >> mealChoice;
    if (mealChoice != 0) {
        if (mealChoice < 0 || mealChoice > meals.size()) {
            cout << "Invalid choice. Please try again." << endl;
            return 1;
        }
        meals[mealChoice - 1].chooseSauce();
        total += meals[mealChoice - 1].price;
    }

    showSideOptions(sides);
    cin >> sideChoice;
    if (sideChoice != 0) {
        if (sideChoice < 0 || sideChoice > sides.size()) {
            cout << "Invalid choice. Please try again." << endl;
            return 1;
        }
        sides[sideChoice - 1].askSpicy();
        sides[sideChoice - 1].chooseSauce();
        total += sides[sideChoice - 1].price;
    }

    showDrinkOptions(drinks);
    cin >> drinkChoice;
    if (drinkChoice != 0) {
        if (drinkChoice < 0 || drinkChoice > drinks.size()) {
            cout << "Invalid choice. Please try again." << endl;
            return 1;
        }
        total += drinks[drinkChoice - 1].price;
    }

    // Show the order summary
    cout << "\nYour order summary:\n";
    if (mealChoice != 0) meals[mealChoice - 1].describe();
    if (sideChoice != 0) sides[sideChoice - 1].describe();
    if (drinkChoice != 0) drinks[drinkChoice - 1].describe();
    cout << "Total price: £" << total << endl;
    cout << "Thank you for your order!" << endl;
    cout << "Please feel free to find an available table and you will be notified to pick up your food when it is ready!" << endl;

    return 0;
}