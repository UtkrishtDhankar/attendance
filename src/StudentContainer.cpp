//
// Created by Utkrisht Dhankar on 01/09/17.
//

#include <StudentContainer.hpp>

StudentContainer::StudentContainer()
{

}

void StudentContainer::AddStudent(const Student& student)
{
    students.push_back(student);
}

void StudentContainer::RemoveStudent(const Student& student)
{
    auto found = std::find(students.begin(), students.end(), student);
    if (found < students.end()) {
        students.erase(found);
    }
}

Student& StudentContainer::GetStudentByIndex(size_t index)
{
    if (index < students.size()) {
        return students[index];
    } else {
        throw std::range_error("Given index not in range.");
    }
}

Student& StudentContainer::GetStudentByRoll(const std::string& roll)
{
    auto found = std::find_if(students.begin(), students.end(),
                               [&](const Student& s) { return s.GetRoll() == roll; });
    if (found >= students.end()) {
        throw std::runtime_error("Given roll number not found.");
    }

    return *found;
}

size_t StudentContainer::GetSize() const
{
    return students.size();
}

StudentContainer::Iterator StudentContainer::GetIterator()
{
    return Iterator(students);
}

StudentContainer::Iterator::Iterator(std::vector<Student>& student)
    : begin { student.begin() }, end { student.end() }
{

}

bool StudentContainer::Iterator::HasNext()
{
    return begin < end;
}

Student& StudentContainer::Iterator::GetNext()
{
    if (begin >= end) {
        throw std::range_error("Can't get next, out of range.");
    }

    Student& student = *begin;
    begin++;

    return student;
}

std::ostream& operator<<(std::ostream& out, const StudentContainer& studentContainer)
{
    for (const auto& s : studentContainer.students) {
        out << s;
    }

    return out;
}

std::istream& operator>>(std::istream& in, StudentContainer& studentContainer)
{
    while (true) {
        try {
            Student s;
            in >> s;

            studentContainer.AddStudent(s);
        } catch (...) {
            break;
        }
    }

    return in;
}

bool StudentContainer::operator==(const StudentContainer& other)
{
    if(other.GetSize() == GetSize()) {
        return std::equal(students.begin(), students.end(), other.students.begin());
    } else {
        return false;
    }
}

void StudentContainer::RemoveByRoll(const std::string& roll)
{
    auto found = std::find_if(students.begin(), students.end(), [&](Student& s) { return s.GetRoll() == roll; });
    if (found < students.end()) {
        students.erase(found);
    }
}

