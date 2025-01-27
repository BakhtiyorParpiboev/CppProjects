#include <iostream>
#include <pqxx/pqxx>
#include <string>
#include <memory>
#include <mutex>
using namespace std;

class DatabaseConnection
{
    private:
    static std::unique_ptr<DatabaseConnection> instance; // singleton instance
    static std:: mutex mutex_;
    std::unique_ptr<pqxx::connection> connection;
    
    DatabaseConnection(){
        try{
            connection = std::make_unique<pqxx::connection>("dbname=library_system user=postgres password=1234 host=localhost port=5432");
            if(connection->is_open()){
                cout << "Database Connected: " << connection -> dbname() << endl;
            }
            else{
                throw std::runtime_error("Failed to open database connection.");
            }
        }
        catch(const std::exception & e){
            std::cerr << e.what() << endl;
            throw;
        }   
    }
    DatabaseConnection(const DatabaseConnection & ) = delete; //prevent copying 
    DatabaseConnection & operator = (const DatabaseConnection &) = delete;

    public:
    static DatabaseConnection &  getInstance(){
        std::lock_guard<std::mutex> lock(mutex_);
        if(!instance){
            instance = std::unique_ptr<DatabaseConnection>(new DatabaseConnection());
        }
        return *instance;
    }
    pqxx::connection & getConnection(){
        return *connection;
    }
    ~DatabaseConnection(){
        if(connection && connection -> is_open()){
            connection-> disconnect();
            std::cout<<"database connection closed." << endl;
        }
    }
};
std::unique_ptr<DatabaseConnection> DatabaseConnection::instance = nullptr;
std::mutex DatabaseConnection::mutex_;