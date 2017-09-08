#ifndef ATTENDANCE_STUDENT_HPP
#define ATTENDANCE_STUDENT_HPP

#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

class Student
{
public:
    Student();

    Student(const std::string& name, const std::string& roll);

    const std::string& GetName() const;
    void SetName(const std::string& newName);

    const std::string& GetRoll() const;
    void SetRoll(const std::string& newRoll);

    unsigned GetAttendedClasses() const;
    void AttendClass();
    void SetAttendedClasses(unsigned newAttendedClasses);

    bool operator == (const Student& other) const;

private:
    std::string name;
    std::string roll;
    unsigned numClassesAttended;

    void InitializeNumClasses();
};

std::ostream& operator<<(std::ostream& out, const Student& student);

std::istream& operator>>(std::istream& in, Student& student);

#endif //ATTENDANCE_STUDENT_HPP
