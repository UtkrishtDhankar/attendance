#include <iostream>
#include <string>
#include <fstream>

#include "StudentContainer.hpp"

std::string prog_name;

const std::string save_file_name = ".attendance_db";

void update_prog_name(const std::string& name)
{
    prog_name = name;
}

void print_usage()
{
    std::cout << "Usage: " << prog_name << " [command options]\n\n";
    std::cout << "Commands:\n";
    std::cout << "\tadd [name] [roll number] [number of classes attended (optional)]\n";
    std::cout << "\tremove [roll number]\n";
    std::cout << "\troll\n";
    std::cout << "\tshow\n";
}

void print_command_not_recognized(const std::string& command)
{
    std::cout << prog_name << ": Command " << command << " not recognized.\n";
}

int main(int argc, char* argv[])
{
    StudentContainer sc;

    std::ifstream save_file_input { save_file_name };
    save_file_input >> sc;
    save_file_input.close();

    update_prog_name(argv[0]);

    if (argc < 2) {
        print_usage();
        return 1;
    }

    std::string command { argv[1] };
    if (command == "add") {
        if (argc < 4 || argc > 5) {
            print_usage();
            return 3;
        }

        std::string name { argv[2] };
        std::string roll { argv[3] };
        unsigned attendedClasses = 0;
        if (argc == 5) {
            int attendedClassesInt = std::stoi(argv[4]);
            if (attendedClassesInt < 0) {
                attendedClasses = 0;
            } else {
                attendedClasses = (unsigned) attendedClassesInt;
            }
        }

        Student s {name, roll};
        s.SetAttendedClasses(attendedClasses);

        sc.AddStudent(s);
    } else if (command == "remove") {
        if (argc != 3) {
            print_usage();
            return 4;
        }

        sc.RemoveByRoll(argv[2]);
    } else if (command == "roll") {
        std::cout << "Press enter for present, any character and then enter for absent.\n";

        auto it = sc.GetIterator();

        while (it.HasNext()) {
            Student& s = it.GetNext();
            std::cout << s.GetRoll() << ": " << s.GetName() << " = ";

            std::string inp;
            std::getline(std::cin, inp);

            if (inp.size() == 0) {
                s.AttendClass();
            }
        }
    } else if (command == "show") {
        auto it = sc.GetIterator();

        while (it.HasNext()) {
            Student& s = it.GetNext();
            std::cout << s.GetRoll() << " - " << s.GetName() << " - " << s.GetAttendedClasses() << "\n";
        }
    } else {
        print_command_not_recognized(command);
        print_usage();
        return 2;
    }

    std::ofstream save_file_out { save_file_name };
    save_file_out << sc;
    save_file_out.close();

    return 0;
}