#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

class Students {
public:
    std::string rollNumber;
    std::string name;
    int age;
    long int contact;

    Students() : rollNumber("Unknown"), name("Unknown"), age(0), contact(0) {}

    Students(std::string roll, std::string name, int age, long int contact)
        : rollNumber(roll), name(name), age(age), contact(contact) {}

    void displayStudentInfo() const {
        std::cout << "Name: " << name
                  << "\nRoll Number: " << rollNumber
                  << "\nAge: " << age
                  << "\nContact: " << contact
                  << "\n-------------------\n";
    }
};

class Room {
public:
    int roomNumber;
    bool occupiedStatus;
    std::string assignedStudentRoll;

    Room() : roomNumber(0), occupiedStatus(false), assignedStudentRoll("None") {}

    Room(int r) : roomNumber(r), occupiedStatus(false), assignedStudentRoll("None") {}

    void assignRoom(const std::string& studentRoll) {
        if (!occupiedStatus) {
            assignedStudentRoll = studentRoll;
            occupiedStatus = true;
            std::cout << "Room " << roomNumber << " has been assigned to " << assignedStudentRoll << "\n";
        } else {
            std::cerr << "Room " << roomNumber << " is already occupied by student: " << assignedStudentRoll << "\n";
        }
    }

    void vacateRoom() {
        if (occupiedStatus) {
            std::cout << "Room " << roomNumber << " vacated by student: " << assignedStudentRoll << "\n";
            assignedStudentRoll = "None";
            occupiedStatus = false;
        } else {
            std::cerr << "Room " << roomNumber << " is already vacant.\n";
        }
    }

    void displayRoom() const {
        std::cout << "Room " << roomNumber << ": "
                  << (occupiedStatus ? "Occupied (Assigned to: " + assignedStudentRoll + ")" : "Vacant")
                  << std::endl;
    }
};

class Hostel {
private:
    std::vector<Students> students;
    std::vector<Room> rooms;
    const std::string studentFile = "students.txt";
    const std::string roomFile = "rooms.txt";

public:
    Hostel() {
        loadStudents();
        loadRooms();
    }
    void addStudent() {
        std::string rollNumber, name;
        int age;
        long int contact;

        std::cout << "Enter Student Roll Number: ";
        std::cin >> rollNumber;
        std::cout << "Enter Student Name: ";
        std::cin >> name;
        std::cout << "Enter Age: ";
        std::cin >> age;
        std::cout << "Enter Contact: ";
        std::cin >> contact;

        auto it = std::find_if(students.begin(), students.end(), [&](const Students& s) {
            return s.rollNumber == rollNumber;
        });

        if (it != students.end()) {
            std::cerr << "Student with roll number " << rollNumber << " already exists.\n";
            return;
        }

        students.emplace_back(rollNumber, name, age, contact);
        saveStudents();
        std::cout << "Student added successfully.\n";
    }

    void addRoom() {
        int roomNumber;
        std::cout << "Enter Room Number: ";
        std::cin >> roomNumber;

        auto it = std::find_if(rooms.begin(), rooms.end(), [&](const Room& r) {
            return r.roomNumber == roomNumber;
        });

        if (it != rooms.end()) {
            std::cerr << "Room " << roomNumber << " already exists.\n";
            return;
        }

        rooms.emplace_back(roomNumber);
        saveRooms();
        std::cout << "Room " << roomNumber << " added successfully.\n";
    }

    void assignRoom() {
        int roomNumber;
        std::string rollNumber;
        
        std::cout << "Enter Room Number: ";
        std::cin >> roomNumber;
        std::cout << "Enter Student Roll Number: ";
        std::cin >> rollNumber;

        auto studentIt = std::find_if(students.begin(), students.end(), [&](const Students& s) {
            return s.rollNumber == rollNumber;
        });

        if (studentIt == students.end()) {
            std::cerr << "Student with roll number " << rollNumber << " not found.\n";
            return;
        }

        auto roomIt = std::find_if(rooms.begin(), rooms.end(), [&](const Room& r) {
            return r.roomNumber == roomNumber;
        });

        if (roomIt == rooms.end()) {
            std::cerr << "Room " << roomNumber << " not found.\n";
            return;
        }

        roomIt->assignRoom(rollNumber);
        saveRooms();
    }

    void vacateRoom() {
        int roomNumber;
        std::cout << "Enter Room Number to Vacate: ";
        std::cin >> roomNumber;

        auto roomIt = std::find_if(rooms.begin(), rooms.end(), [&](const Room& r) {
            return r.roomNumber == roomNumber;
        });

        if (roomIt == rooms.end()) {
            std::cerr << "Room " << roomNumber << " is not found.\n";
            return;
        }

        roomIt->vacateRoom();
        saveRooms();
    }

    void loadStudents() {
        std::ifstream file(studentFile);
        if (!file) return;

        students.clear();
        std::string rollNumber, name;
        int age;
        long int contact;

        while (file >> rollNumber >> name >> age >> contact) {
            students.emplace_back(rollNumber, name, age, contact);
        }

        file.close();
    }

    void saveStudents(){
        std::ofstream file(studentFile);
        if(!file) return;
        
        for(const auto & s : students){
            file << s.rollNumber << " " << s.name << " " << s.age << " " << s.contact << std::endl;
        }
        file.close();
    }

    void loadRooms() {
        std::ifstream file(roomFile);
        if (!file) return;

        rooms.clear();
        int roomNumber;
        int occupiedStatus;
        std::string assignedRoll;

        while (file >> roomNumber >> occupiedStatus >> assignedRoll) {
            Room r(roomNumber);
            r.occupiedStatus = (occupiedStatus == 1);
            r.assignedStudentRoll = assignedRoll;
            rooms.emplace_back(r);
        }

        file.close();
    }

    void saveRooms() {
        std::ofstream file(roomFile);
        if (!file) return;

        for (const auto& room : rooms) {
            file << room.roomNumber << " " << room.occupiedStatus << " " << room.assignedStudentRoll << std::endl;
        }

        file.close();
    }

    void displayAllStudents() const {
        if(!students.empty()){
            std::cout << "\n-------------------\n";
            std:: cout << "Total Students: " << students.size() << std::endl;
            std::cout << "\n-------------------\n";
            for (const auto& student : students) {
                student.displayStudentInfo();
            }
        }
        else{ 
            std::cerr << "The students list is empty :(. Please add new rooms." << std::endl;
        }
    }

    void displayAllRooms() const {
        if(!rooms.size() == 0){
            std::cout << "Total rooms: " << rooms.size() << std::endl;
            std::cout << "\n-------------------\n";
            for(const auto& room : rooms) {
                room.displayRoom();
            }
       }
       else{
            std::cerr << "Room list is blank :( \n";
       }
    }

    
};

int main() {
    Hostel hostel;
    int choice;

    do {
        std::cout << "\n--- Hostel Management System ---\n";
        std::cout << "1. Add Student\n";
        std::cout << "2. Add Room\n";
        std::cout << "3. Assign Room to Student\n";
        std::cout << "4. Vacate Room\n";
        std::cout << "5. Display All Students\n";
        std::cout << "6. Display All Rooms\n";
        std::cout << "7. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                hostel.addStudent();
                break;
            case 2:
                hostel.addRoom();
                break;
            case 3:
                hostel.assignRoom();
                break;
            case 4:
                hostel.vacateRoom();
                break;
            case 5:
                hostel.displayAllStudents();
                break;
            case 6:
                hostel.displayAllRooms();
                break;
            case 7:
                std::cout << "Exiting program. Data saved successfully.\n";
                break;
            default:
                std::cerr << "Invalid choice! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
