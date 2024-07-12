#include "Student.h"
#include <string>
#include <iostream>

// compile with: g++ -shared -fPIC -o StudentWrapper.so StudentWrapper.cpp Student.cpp

#ifdef _MSC_VER
#define EXPORT __declspec(dllexport)
#else
#define EXPORT
#endif

extern "C" {

    EXPORT Student* Student_new() { return new Student(); }
    EXPORT void Student_delete(Student* student) { delete student; }

    EXPORT void Student_setName(Student* student, const char* name){
        student->setName(name);
    }

    EXPORT const char* Student_getName(Student* student) {
        return student->getNameStr();
    }

    EXPORT void Student_setAge(Student* student, int age) {
        student->setAge(age);
    }

    EXPORT int Student_getAge(Student* student) {
        std::cout << student->getAge();
        return student->getAge();
    }

    EXPORT void Student_setAttendance(Student* student, double attendance) {
        student->setAttendance(attendance);
    }

    EXPORT double Student_getAttendance(Student* student){
        return student->getAttendance();
    }

    EXPORT double Student_getGPA(Student* student) {
        return student->getGPA();
    }

    EXPORT void Student_setGrades(Student* student, const int* grades, int length) {
        student->setGrades(grades, length);
    }

    EXPORT const int* Student_getGrades(Student* student, size_t* size) {
        int* arr = student->getGradesPtr(size);
        return arr;
    }

    EXPORT void Student_freeMemory(int* arr) {
        delete[] arr;
    }
}