#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>

class Student {
public:
    Student();
    ~Student();

    void setName(const std::string name);
    void setAge(const int age);
    void setAttendance(const double attendance);
    void setGrades(const std::vector<int>& newGrades);
    void setGrades(const int* grade, int length);

    std::string getName() const;
    const char* getNameStr() ;
    int getAge() const;
    double getAttendance() const;
    double getGPA() const;
    std::vector<int> getGrades() const;
    int* getGradesPtr(size_t* size) const; 

private:
    std::string name;
    int age;
    double attendance;
    double gpa;
    std::vector<int> grades;

    void calculateGPA();
};

#endif