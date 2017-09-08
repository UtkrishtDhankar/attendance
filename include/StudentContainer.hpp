#ifndef ATTENDANCE_STUDENTCONTAINER_HPP
#define ATTENDANCE_STUDENTCONTAINER_HPP

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>

#include "Student.hpp"

class StudentContainer
{
public:
    StudentContainer();

    void                        AddStudent(const Student& student);
    void                        RemoveStudent(const Student& student);
    void                        RemoveByRoll(const std::string& roll);

    Student&                    GetStudentByRoll(const std::string& roll);
    Student&                    GetStudentByIndex(size_t index);

    size_t                      GetSize() const;

    bool operator == (const StudentContainer& other);

    friend std::ostream& operator<<(std::ostream& out, const StudentContainer& studentContainer);
    friend std::istream& operator>>(std::istream& in, StudentContainer& studentContainer);

    class Iterator {
    public:
        explicit Iterator(std::vector<Student>& vector);
        bool                            HasNext();
        Student&                        GetNext();
    private:
        std::vector<Student>::iterator  begin;
        std::vector<Student>::iterator  end;
    };

    Iterator  GetIterator();

private:
    std::vector<Student> students;
};


std::ostream& operator<<(std::ostream& out, const StudentContainer& studentContainer);
std::istream& operator>>(std::istream& in, StudentContainer& studentContainer);


#endif //ATTENDANCE_STUDENTCONTAINER_HPP
