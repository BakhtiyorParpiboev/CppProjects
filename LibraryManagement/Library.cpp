#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include "DatabaseConnection.h"
// using namespace std;

void addBook()
{
    try
    {
        // Get the database connection from the singleton
        pqxx::connection & conn = DatabaseConnection::getInstance().getConnection();
        pqxx::work txn(conn);

        std::string title, author, publisher, isbn;
        int published_year, copies;

        std::cout << "Enter book title: ";
        std::getline(std::cin, title);
        std::cout << "Enter author: ";
        std::getline(std::cin, author);
        std::cout << "Enter publisher: ";
        std::getline(std::cin, publisher);
        std::cout << "Enter published year: ";
        std::cin >> published_year;
        std::cin.ignore();
        std::cout << "Enter ISBN: ";
        std::getline(std::cin, isbn);
        std::cout << "Enter number of copies: ";
        std::cin >> copies;
        std::cin.ignore();

        txn.exec0("INSERT INTO books (title, author, publisher, published_year, isbn, copies_available, total_copies) "
                  "VALUES (" +
                  txn.quote(title) + ", " + txn.quote(author) + ", " + txn.quote(publisher) + ", " +
                  txn.quote(published_year) + ", " + txn.quote(isbn) + ", " + txn.quote(copies) + ", " + txn.quote(copies) +
                  ");");

        txn.commit();
        std::cout << "Book added successfully!" << std::endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error adding book: " << e.what() << std::endl;
    }
}
void registerUsers()
{
    try
    {
        pqxx::connection & con = DatabaseConnection::getInstance().getConnection();
        pqxx::work eth(con);

        std::string name, email, phone, membership_date;

        std::cout << "\nwelcome to our library ) "<< std::endl;
        std::cout << "enter your name: " << std::endl;
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(std::cin, name);
        std::cout << "your email please: " << std::endl;
        std::getline(std::cin, email);
        std::cout << "your phone number please: " << std::endl;
        std::getline(std::cin, phone);

        std::string query = ("INSERT INTO users(name, email, phone) VALUES(" +
                             eth.quote(name) + ", " + eth.quote(email) + ", " + eth.quote(phone) + ");");
        eth.exec(query);
        eth.commit();
        std::cout << "new user added successfully" << "\n";
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}
void getUserInfo() {
    try {
        pqxx::connection &c = DatabaseConnection::getInstance().getConnection();
        pqxx::work link(c);

        std::string nameCheck;
        std::cout << "Enter your name to get all your info from our database:\n";
        std::cin >> nameCheck;
        // std::getline(std::cin, nameCheck);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        pqxx::result resume = link.exec("SELECT * FROM users WHERE LOWER(name) = " + link.quote(nameCheck));
        if (!resume.empty()) {
            std::cout << "User Found:\n";
            for (const auto & row : resume) {
                std::cout << "ID: " << row["user_id"].as<int>() << "\n"
                          << "Name: " << row["name"].as<std::string>() << "\n"
                          << "Email: " << row["email"].as<std::string>() << "\n"
                          << "Phone Number: " << row["phone"].as<std::string>() << "\n"
                          << "-----------------------" << std::endl;
            }
        } else {
            std::cerr << "There is nothing matched with: " << nameCheck << std::endl;
        }
    } catch (const std::exception &e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}


void rentBooks()
{
    try
    {

        int permission; // asks user who is new or already member of library.
        std::cout << "please choose with number(1,2,3): 1. Login. 2. SignUp. 3. Forgot my data." << std::endl;
        std::cin >> permission;

        if (permission == 1)
        {
            pqxx::connection & c = DatabaseConnection::getInstance().getConnection();
            pqxx::work apt(c);
            std::string nameCheck;
            std::cout << "please enter your name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // FIXED
            std::getline(std::cin, nameCheck);

            pqxx::result res = apt.exec("SELECT COUNT(*) AS memberCheck FROM users WHERE name = " + apt.quote(nameCheck));
            if (!res.empty() && res[0]["membercheck"].as<int>() > 0)
            { // FIXED
                std::cout << nameCheck << " is a library member. You are in a library." << std::endl;

                string bookName;
                std::cout << "Please enter name of book (lowercase): " << std::endl;
                std::getline(std::cin, bookName);

                pqxx::result bookCopy = apt.exec("SELECT copies_available FROM books WHERE title = " + apt.quote(bookName));
                if (!bookCopy.empty())
                { // FIXED
                    int copies_available = bookCopy[0]["copies_available"].as<int>();
                    if (copies_available > 0)
                    {
                        apt.exec("UPDATE books SET copies_available = copies_available - 1 WHERE title = " + apt.quote(bookName));
                        std::cout << "your rent is successfull :)" << std::endl;
                        apt.commit(); // Avoid commit(): For read-only operations (SELECT).
                    }
                    else
                    {
                        std::cerr << "all books that you mentioned is taken by our users" << std::endl;
                    }
                }
                else
                {
                    std::cerr << "unfortunately, we don't have a book named " << bookName << std::endl;
                }
            }
            else
            {
                std::cout << nameCheck << " is not a library member. Redirecting to sign-up..." << std::endl;
                registerUsers();
            }
        }
        else if (permission == 2)
        {
            registerUsers();
        }
        else if(permission == 3)
        {
            getUserInfo(); 
        }
        else
        {
            std::cerr << "Invalid input. Please choose as it shown " << std::endl;
        }

    }
    catch (const std::exception &e)
    {
        std::cerr << "Error:" << e.what() << std::endl;
    }
}


void return_book(pqxx::connection &conn) {
    try {
        pqxx::work txn(conn);

        int rental_id;
        std::cout << "Enter rental ID: ";
        std::cin >> rental_id;
        std::cin.ignore();

        // Update rental record
        txn.exec0("UPDATE rentals SET return_date = CURRENT_DATE, status = 'returned' WHERE rental_id = " + txn.quote(rental_id) + ";");

        // Update book copies
        txn.exec0("UPDATE books SET copies_available = copies_available + 1 WHERE book_id = (SELECT book_id FROM rentals WHERE rental_id = " + txn.quote(rental_id) + ");");

        txn.commit();
        std::cout << "Book returned successfully!" << std::endl;
    } catch (const std::exception &e) {
        std::cerr << "Error returning book: " << e.what() << std::endl;
    }
}
void more(){
        try{
            pqxx::connection & c = DatabaseConnection::getInstance().getConnection();
            int option;
            do{
                std::cout << "More options menu:\n"
                << "1. get your Info.\n"
                << "2. are you looking for books\n" 
                << "3. exit" << std::endl;
                std::cin >> option;
                // std::cin.ignore();
                switch(option){
                case 1:
                    getUserInfo();
                    break;
                case 2: 
                    std::cerr << "our developers working on this side of our program\n";
                    break;
                case 3:
                    std::cerr << "you are redirecting to main page ..." << std::endl;
                    break;
                default:
                    std::cerr<<"Invalid operation. Something went wrong\n"; 
                    break;
            }
            } while(option !=3);
        }
        catch(const std::exception & e){
            std::cerr << "Error" << e.what() << std::endl;
        }
}
int main()
{
    try{
        pqxx::connection & d = DatabaseConnection::getInstance().getConnection();
        int choice;
        do{
            std::cout << "Library system menu:\n"
                    << "1. Add a book.\n"
                    << "2. Sign Up.\n"
                    << "3. Rent a book.\n"
                    << "4. Return a book.\n"
                    << "5. More(you will be using more functions in here).\n"
                    << "6. Exit from system\n"
                    << "Enter your choice: " << std::endl;
            std::cin >> choice;
            std::cin.ignore();
        switch (choice)
        {
        case 1:
            addBook(); 
            break;
        case 2:
            registerUsers();
            break;
        case 3:
            rentBooks();
            break;
         case 4:
            return_book(d);
            break;
        case 5: 
            more();
            break;
        case 6:
            std::cout << "Existing from system. Thanks for being with us :)" << std::endl;
            break;
        default:
            std::cerr<<"Invalid operation. Something went wrong\n"; 
            break;
        }
    } while (choice !=6);
    }
    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
    }
    return 0;
}