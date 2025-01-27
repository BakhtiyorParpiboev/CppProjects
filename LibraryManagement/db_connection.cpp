#include <iostream>
#include <pqxx/pqxx>

int main(){
    try{
        pqxx::connection conn("dbname=library_system user=postgres password=1234 host=localhost port=5432");
        pqxx:: work avax(conn);
        if(conn.is_open()){
            std::cout << "connection successful to " << conn.dbname() << " database\n";
            pqxx::result res = avax.exec("INSERT INTO books(book_id, title, author, publisher, published_year, isbn, copies_available, total_copies)"
                                        "VALUES(2, 'baxtiyor oila', 'shayx muhammadsodiq muhammadyusuf', 'hilol nashr', 2020,'111-2004-21-571-9', 12321, 21000)");
            avax.commit();
            std:: cout << "new Data is not inserted to students table !!" << std::endl;
        }
        else{
            // std::cerr << "failed to connect db=" << conn.dbname() << std::endl;
            throw std::runtime_error("database is not open\n");
        }
    }
    catch(const pqxx::sql_error & e){
        std::cerr << "SQL error"<< e.what() << std::endl;
        return 1;
    }
    return 0;
}