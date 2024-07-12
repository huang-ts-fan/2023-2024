#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

Student::Student() {
    std::cout << "Inside the constructor \n";
    this->name = "unknown";
    this->age = 0;
    this->attendance = 0.0;
    this->gpa = 0.0;
}

Student::~Student() {
    std::cout << "In the destructor \n";
}

void Student::setName(const std::string name) {
    this->name = name;
}

void Student::setAge(const int age) {
    this-> age = age;
}

void Student::setAttendance(const double attendance) {
    this->attendance = attendance;
}

void Student::setGrades(const std::vector<int>& newGrades) {
    this->grades = newGrades;
    this->calculateGPA();
}

void Student::setGrades(const int* grades, int length) {
    this->grades = std::vector<int>(grades, grades+length);
    this->calculateGPA();
}

void Student::calculateGPA() {
    int sum = 0;
    for (int grade: this->grades) {
        sum+= grade;
    }
    this->gpa = double(sum) / this->grades.size();
}

std::string Student::getName() const {
    return this->name;
}

const char* Student::getNameStr() {
    return this->name.c_str();
}

int Student::getAge() const {
    return this->age;
}

double Student::getAttendance() const {
    return this->attendance;
}

double Student::getGPA() const {
    return this->gpa;
}

std::vector<int> Student::getGrades() const {
    return this->grades;
}

int* Student::getGradesPtr(size_t* size) const {
    *size = this->grades.size();
    int* arr = new int[*size];
    for (size_t i=0; i<*size; i++) {
        arr[i] = this->grades[i];
    }
    return arr;
}