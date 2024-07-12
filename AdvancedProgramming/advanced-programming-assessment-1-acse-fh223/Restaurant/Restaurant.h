#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <string>
#include <vector>

// Meal, Side, and Drink classes
class Meal {
public:
    std::string name;
    float price;
    std::string sauce;
    Meal(std::string name, float price);
    void chooseSauce();
    void describe() const;
};

class Side {
public:
    std::string name;
    float price;
    bool spicy;
    std::string sauce;
    Side(std::string name, float price, bool spicy = false);
    void askSpicy();
    void chooseSauce();
    void describe() const;
};

class Drink {
public:
    std::string name;
    float price;
    Drink(std::string name, float price);
    void describe() const;
};

void showMealOptions(const std::vector<Meal>& meals);
void showSideOptions(const std::vector<Side>& sides);
void showDrinkOptions(const std::vector<Drink>& drinks);

#endif
