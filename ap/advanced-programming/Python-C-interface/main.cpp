#include "Student.h"
#include <iostream>
#include <string>
#include <vector>

// compile with: g++ Student.cpp main.cpp -o main

int main() {
    Student* student = new Student();

    student->setName("Bob");
    student->setAge(23);
    student->setAttendance(43.5);
    std::vector<int> grades = {65, 68, 59, 65, 44};
    student->setGrades(grades);

    std::cout << "Name: " << student->getName() << "\n";
    std::cout << "Age: " << student->getAge() << "\n";
    std::cout << "Attendace: " << student->getAttendance() << "\n";
    std::vector<int> readgrades = student->getGrades();
    std::cout << "Grades: ";
    for (int grade: readgrades) {
        std::cout << grade << ", ";
    }
    std::cout << "\nGPA: " << student->getGPA() << "\n";

    return 0;
}