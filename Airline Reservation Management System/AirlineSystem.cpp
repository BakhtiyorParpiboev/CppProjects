#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Flight {
public:
    std::string flightNumber; // BA2490 or 2490
    std::string departure;
    std::string destination;
    std::string date;
    
    std::vector <Flight> flights;
    std::string flightsFile = "flightsFile.txt";

    Flight() : flightNumber("Unknown"), departure("Unknown"), destination("Unknown"),date("Unknown"){}

    Flight(std::string flight,std::string depart, std::string destiny, std::string datee) 
        :   flightNumber(flight), departure(depart), destination(destiny), date(datee){}

    public:
    void inputFlightDetails(){
        std::cout << "--Inserting Flight info--\n";
        std::cout << "Please enter Flight Number: ";
        std::cin >> flightNumber;
        std::cout << "Departure Time: ";
        std::cin >> departure;
        std::cin.ignore();
        std::cout << "Destination: ";
        std::getline(std::cin,destination);
        std::cout << "Date: (dd.mm.yyyy)";
        std::cin >> date; 

        flights.push_back(Flight(flightNumber,departure,destination,date));
        
        std::ofstream file(flightsFile, std::ios::app);
        if(!file){
            std::cerr << "File has never opened yet.\n";
            return;
        }
        else{
            for(const auto & flight : flights){
            file << flight.flightNumber << " "<< flight.departure << " " << flight.destination << " "<< flight.date << std::endl;
            }
            std::cout << "New Flight has been added to flights schedule." << std::endl;
        }
        file.close();

    }; 

    void displayFlightDetails(){
        std::ifstream file(flightsFile, std::ios::out);
        if(!file){
            std::cout << "File is not opened.\n";
            return;
        }
        flights.clear();
        std::string flight,depart,destiny, datee;
        while(file >> flight >> depart >> destiny >> datee){
            flights.emplace_back(flight,depart,destiny,datee);
        }
        for(const auto & f : flights){
            std::cout << "--Flight Details--\n";
            std::cout << "Flight Number: " << f.flightNumber
                    << "\nDeparture: " << f.departure
                    << "\nDestination: " << f.destination
                    << "\nDate: " << f.date << std::endl;
        }
        file.close();
    }
};

class Passenger{
    public:
    std::string passengerName;
    std::string passportNumber;
    std::vector <Passenger> passengers;
    std::string passengersFile = "passengersFile.txt";

    Passenger() : passengerName("Unknown"),passportNumber("Unknown"){}
    public:
    Passenger(std::string passenger, std::string passport) : 
        passengerName(passenger),passportNumber(passport){}  

    public:
    void inputPassengerDetails(){
        std::cout << "--Open new Account--\n";
        std::cout << "Please use this Format(SohibaAbdullayeva)\n";
        std::cout << "Enter your Name: ";
        std::cin.ignore();
        std::getline(std::cin,passengerName);
        std::cout << "Passport Number:";
        std::getline(std::cin,passportNumber);

        passengers.push_back(Passenger(passengerName,passportNumber));

        std::ofstream file(passengersFile, std::ios::app);
        if(!file) return;

        file << passengerName << " " << passportNumber << std::endl;
        std::cout << "Passengers info inserted successfully.\n\n";
        file.close();
    }

    void displayPassengerDetails(){        
        std::string passenger, passport;
        passengers.clear();
        std::ifstream file(passengersFile, std::ios::out);
        if(!file)return;
        while(file >> passenger >> passport){
            passengers.emplace_back(passenger,passport);
        }
        std::cout << "--Passenger Info--\n";
        for(const auto & p : passengers){
            std::cout << "PassengerName: " << p.passengerName
                    << "  PassportNumber: " << p.passportNumber << std::endl;
        }
        file.close();
    }
};

class Reservation{
    public:
        int ticketId;
        Flight f;
        Passenger p;
        std::vector <std::string> matchedFlights;
        std::string reservationInfo = "reservationInfo.txt";

    public:
    void searchTicket(){
        std::ifstream file(f.flightsFile);
        if(file.is_open()){
            std::string destinationInput;
            std::cout << "--Search a Ticket--\nOnly use this format for perfect matches(NEW-YORK or SEOUL)\n";
            std::cout << "Where To: ";
            std::cin >> destinationInput;
            
            std::string flightNumber,departure,destination,date;
            bool found = false; // FIXED
            while(file >> flightNumber >> departure >> destination >> date){
                    if(destinationInput==destination){
                        found = true;
                        std::string flightDetails = flightNumber + " | Time:" + departure + " |  City:" + destination + " |  Date:" + date; // FIXED
                        matchedFlights.emplace_back(flightDetails);
                    }
            }
                if(found){
                    std::cout << "--Here are the Matched flights--\n";
                    for(const auto & flight : matchedFlights){
                        std::cout << flight <<std::endl;
                    }
                } else{
                        std::cerr << "No flights found for your destionation:" << destinationInput << std::endl;
                }
        }
        else{
            std::cerr << "Error: Could not open file. There is something went wrong.\n";
            return;    
        }
    }
    
   void bookTicket() {
        while (true) {
            int userChoice;
            std::cout << "--Ticket Booking Center--\n";
            std::cout << "1. Book a Ticket.\n"
                        << "2. Search Ticket (get flight number of your destination).\n"
                        << "3. Exit.\n";
            std::cout << "Enter your choice: ";
            std::cin >> userChoice;

            switch (userChoice) {
                case 2:
                    searchTicket();
                    break;

                case 1: {
                    std::string userPassportNumber;
                    std::cout << "Please enter your Passport Number: ";
                    std::cin >> userPassportNumber;

                    std::ifstream file1(p.passengersFile);
                    if (!file1.is_open()) {
                        std::cerr << "Error: Could not open passengers file.\n";
                        break;
                    }

                    std::string passengerName, passportNumber;
                    bool foundPassenger = false;
                    std::string passengerInfo;

                    while (file1 >> passengerName >> passportNumber) {
                        if (userPassportNumber == passportNumber) {
                            foundPassenger = true;
                            passengerInfo = "Passenger: " + passengerName + " " +
                                            " | Passport: " + passportNumber;
                            break;
                        }
                    }
                    file1.close();

                    if (!foundPassenger) {
                        std::cerr << "Error: Passport number not found in the system.\n";
                        break;
                    }

                    std::string userFlightNumber;
                    std::cout << "I will direct you for reserving your ticket.\n";
                    std::cout << "Please enter only the flight number of your destination: ";
                    std::cin >> userFlightNumber;

                    std::ifstream file(f.flightsFile);
                    if (!file.is_open()) {
                        std::cerr << "Error: Could not open flights file.\n";
                        break;
                    }

                    std::string flightNumber, departure, destination, date;
                    bool foundFlight = false;
                    std::string flightBooking;

                    while (file >> flightNumber >> departure >> destination >> date) {
                        if (userFlightNumber == flightNumber) {
                            foundFlight = true;
                            flightBooking = flightNumber + " " + departure +
                                            " " + destination + " " + date;
                            break;
                        }
                    }
                    file.close();

                    if (!foundFlight) {
                        std::cerr << "Error: Flight number mismatched. Go to searchTicket first.\n";
                        break;
                    }

                    std::ofstream reservationFile(reservationInfo, std::ios::app);
                    if (!reservationFile.is_open()) {
                        std::cerr << "Error: Could not open reservation file.\n";
                        break;
                    }

                    reservationFile << passengerInfo << " | " << flightBooking << "\n";
                    reservationFile.close();

                    std::cout << "\nTicket successfully booked! Thank you.\n\n";
                    break;
                }

                case 3:
                    std::cout << "System is stopping execution. Thanks for using our service.\n";
                    return;

                default:
                    std::cerr << "Error: Invalid input. Please try again.\n";
                    break;
            }
        }
    }

    void cancelTicket(){
        std::ifstream oldFile(reservationInfo);
        std::ofstream newFile("temp.txt");
        if(!oldFile.is_open() || !newFile.is_open()){
            std::cerr << "File is not opened.\n";
        }

        std::string userPassportNumber;
        std::string userFlightNumber;

        std::cout << "--Cancel Your Ticket--"<<std::endl;
        std::cout << "Please enter your Passport Number:";
        std::cin >> userPassportNumber;
        std::cout << "Please enter your flightNumber:";
        std::cin >> userFlightNumber;

        std::string line;
        bool boolean;
        while(std::getline(oldFile,line)){ // FIXED
            if (line.find(userPassportNumber) != std::string::npos || line.find(userFlightNumber) != std::string::npos) {
                boolean = true;
                continue;
            }
            newFile << line << "\n";
        }
        oldFile.close();
        newFile.close();

        if(!boolean){
            std::cerr << "FlightNumber or PassportNumber is mismatched. Please check your ticket data.\n";
        }
        else{
            remove(reservationInfo.c_str());
            rename("temp.txt",reservationInfo.c_str());
            std::cout << "Your ticket has been cancelled successfully.\n";
        }
    }

    void checkPassengerTicket(){
        std::ifstream fine(reservationInfo);
        if(!fine.is_open()){
            std::cerr << "Error: Could not open reservation file.\n";
            return;
        } 

        std::string passengerPassport;
        std::cout << "--Check your Ticket--" << std::endl;
        std::cout << "Enter your passportNumber.(FA1280011)     ";
        std::cin >> passengerPassport;

        std::string passenger,passport,flight,time,city,date;
        bool isFound = false;
        while(fine >> passenger >> passport>>flight>>time>>city>>date){
            if(passport==passengerPassport){
                isFound = true;
                std::cout << "--Passenger Ticket Info--\n";
                std::string passengerTicketInfo = "Name: " + passenger +"\nPassportNumber: " + passport + "\nFlightNumber: " + flight + "\nDeparture: " + time + "\nDestination: " + city + "\nDate: " + date;
                std::cout << passengerTicketInfo << std::endl;
                break;
            }
        }
        fine.close();
        if(!isFound){
            std::cerr << "There is no ticket with given passportNumber:" << passengerPassport << "\n\n";
        }
    }
};

class AirlinesSystem{
    public:
    Flight f;
    Passenger p;
    Reservation r;
    
    void showServerSideMenu(){
        int serverChoice;
        std::string password = "Ss.911.44.99";
        std::string passwordCheck;
        int passwordAttemptsLeft = 5;
        while(true){
            std::cout << "Enter password for accessing Data Center:";
            std::cin >> passwordCheck;
            if(passwordCheck == password){
                std::cout << "--Welcome To Asiana Airlines Data Center--\n";
                std::cout << "1. Add new Flights.\n"
                            << "2. Display all Flights.\n"
                            << "3. Display allPassengers Info.\n"
                            << "4. Exit.\n";
                std::cout << "Enter your choice with numbers (1~4)\n";
                std::cin >> serverChoice;
                switch(serverChoice){
                    case 1:
                        f.inputFlightDetails();
                        break;
                    case 2:
                        f.displayFlightDetails();
                        break;
                    case 3: 
                        p.displayPassengerDetails();
                        break;
                    case 4:
                        std::cerr << "Program has stopped.\n";
                        break;
                    default:
                        std::cerr << "Invalid Input. Only numbers (1~4)\n";
                }
            }
            else{
                passwordAttemptsLeft --;
                if(passwordAttemptsLeft!=0){
                    std::cout << "-----------------------------------------------------------\n";
                    std::cout << "Incorrect password.You have " << passwordAttemptsLeft << " attempts left to access server side.\n";
                    std::cout << "-----------------------------------------------------------\n";
                }
                else{
                    std::cerr << "You are Forcible kicked out of program.\n";
                    return mainMenu();
                }
            }
        }
    }

    void showClintSideMenu(){
        int clientChoice;
        while(true){
            std::cout << "--Welcome To Happy Airlines--\n";
            std::cout<<"1. SignUp as a New Member.\n" 
                    << "2. Book Ticket.\n"
                    << "3. Search new Flights.\n"
                    << "4. Check your reserved Ticket.\n"
                    << "5. Cancel your reserved Ticket.\n"
                    << "6. Exit.\n";
            std::cout << "Please enter with (1~6):";
            std::cin >> clientChoice;
            switch(clientChoice){
                case 1:
                    p.inputPassengerDetails();
                    break;
                case 2:
                    r.bookTicket();
                    break;
                case 3:
                    r.searchTicket();
                    break;
                case 4:
                    r.checkPassengerTicket();
                    break;
                case 5:
                    r.cancelTicket();
                    break;
                case 6:
                    std::cout << "Program has stopped.Thanks for being with us.\n";
                    break;
                default:
                    std::cerr << "Invalid input.Please enter only 1~6.\n";
            }
        } 
    }

    void mainMenu(){
    std::cout << "--Main menu--\n";
    bool stopButton = false;
    int choice;
    std::cout << "Warning! If you are user. You can not choose first option. \nYou will be given permanent ban to use this side\n";
    while(!stopButton){
        std::cout << "1. Data Center.( users X )\n"
                    << "2. Display Client Server.\n"
                    << "3. Exit.\n";
        std::cout << "Enter only following options (2~3), If you are an user:";
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cerr << "Invalid input. Please enter a valid option (1-3).\n";
            continue;
        }
        switch(choice){
            case 1:
                stopButton = true;
                showServerSideMenu();
                break;
            case 2:
                stopButton = true;
                showClintSideMenu();
                break;
            case 3:
                stopButton = true;
                std::cout << "Thanks for choosing Happy Airlines. Enjoy all you moments with us.\n";
                break;
            default:
                std::cerr << "Invalid input. Please only enter single Number (1~3).\n";
                break;
        }
    }
}
};

int main(){
    AirlinesSystem a;
    a.mainMenu();
}