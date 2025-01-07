#include <pqxx/pqxx>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class BookRent_management {
    vector <string> names;

    public:
    string name;
    string book_name;

    cout << "your name:";
    cin >> name;
    for(name : names){
        if(name == names){
            cout << "write name of your book that you want to borrow:"
            cin >> book_name;
            bookRent_info();
        }
        else{ cout << "something went wrong";}
    }
    void setName(string name){
        name = name;
    }
    void bookRent_info(){
        cout << name << " has borrowed " << book_name << " from bakhtiyor's library" << std::endl;
    }
};
class Return{
    string name;
    string book_name;
    cout << "please enter your name:";
    cin >> name;
    cout << "name of book that you take:";
    cin >> book_name;
};
int main(){

    int userChoice;
    std::cout << "welcome to official library website\n\n";
    cout << "choose please\n 1. borrow a book 2. give back a book:";
    cin >> userChoice;
    try{
        if(userChoice == 1){
        BookRent_management b;
        b.bookRent_info();
    } else {
        Return returning;
    }
    }
    catch(int userChoice){
        cout << "access is denied - you must choose your choice with digit 1,2...";
    }
    return 0;
}