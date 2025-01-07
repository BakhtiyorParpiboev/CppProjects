#include <iostream>
#include <pqxx/pqxx>

int main(){
    try{
        pqxx::connection conn("dbname=university user=postgres password=1234 host=localhost port=5432");
        pqxx::work ton(conn);
        if(conn.is_open()){
            std::cout << "connected to " << conn.dbname() << " database.\n\n";

            // ton.exec("CREATE TABLE IF NOT EXISTS practice(name VARCHAR(255), age int, country VARCHAR(255));");
            // ton.commit();

            // ton.exec("INSERT INTO practice(name, age, country) VALUES"
            //                                                                         "('Macheal', 31, 'Germany'),"
            //                                                                         "('Arlan', 19, 'Kazakhstan'),"
            //                                                                         "('Lesa', 24, 'Brazil'),"
            //                                                                         "('Lina', 23, 'Belarus');");
            // ton.abort();
            // std::cout << "Data is not inserted\n";

            // ton.exec("DELETE FROM practice WHERE name = 'Lesa'");
            // ton.commit();

            // ton.exec("UPDATE practice SET name = 'Hitler' WHERE country = 'Germany';");
            // ton.commit();
            // std::cout << "Record updated successfully !" << std::endl;

            // pqxx::work avax(conn);
            // pqxx::result res = avax.exec("SELECT DISTINCT * FROM practice;");
            // for(auto row : res){
            //     std::cout <<  "Name: " << row["name"].c_str()
            //     << " Age: " << row["age"].as<int>()
            //     << " Country: " << row["country"].c_str()
            //     << std::endl;
            // }
            ton.exec("DROP TABLE practice;");
            std::cout<<"Table has been dropped after practice finished"<<std::endl;
            ton.commit();

        } else{
            throw std::runtime_error("database is not open");
        }
    }

    catch(const std::exception & e){
        std::cerr << "Error: " << e.what() << std::endl;
        std::cout << "something went wrong. Please try again";
        return 1;
    }
    return 0;
}