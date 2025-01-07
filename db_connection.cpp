#include <iostream>
#include <pqxx/pqxx>

int main(){
    try{
        pqxx::connection conn("dbname=university user=postgres password=1234 host=localhost port=5432");
        pqxx:: work avax(conn);

        avax.exec("SELECT * FROM test_table");
        avax.commit();

        // avax.exec("CREATE TABLE IF NOT EXISTS test_table(name VARCHAR(255), price VARCHAR(100), brand_name VARCHAR(255))");
        // std::cout << "table created successfully in database of " << conn.dbname() << std::endl;

        // avax.exec("INSERT INTO test_table(name, price, brand_name) VALUES ('piano','5200', 'Artel')");
        // std::cout << "new Data inserted to table successfully" << "\n";
        // avax.commit();

        if(conn.is_open()){
            std::cout << "connected to the database: " << conn.dbname() << "\n";
        } else{
            std::cout<< "connection failed :(";
            return 1;
        }
        conn.disconnect();
    }
    catch(const std::exception &e){
        std:: cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}