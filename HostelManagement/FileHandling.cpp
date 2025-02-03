#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
    ofstream writeFile("shokhruz.txt", ios::out); // write-only mode 
    if(writeFile.is_open()){
        writeFile << "yo toshkent nima nima gap.\n";
        writeFile << "nima buvotti\n";
    }
    writeFile.close();


    fstream appendFile("shokhruz.txt", ios::app); // append mode
    if(appendFile.is_open()){
        appendFile << "unable to go trip to uzbekistan for winter season.\n";
        appendFile.close();
    }


    ifstream readFile("shokhruz.txt", ios::in); // read-only mode
    string file;
    while(getline(readFile, file)){
        cout << file << endl;
    }
    readFile.close();


    // removing file from folder
    if(remove("samandar.txt") == 0){ 
        cout << "File deleted successfully.\n";
    } 
    else
     {
         cerr << "\nUnable to remove file\n";
    }

    //renaming file inside of folder
    if (rename("example.txt", "new_file.txt") == 0) { 
        cout << "File renamed successfully.\n"; 
    } else {
        cerr << "Error renaming file.\n";
    }
    system("pause > 0");
}