#include <iostream>
using namespace std;

int main(){
    int doorCode = 0000;
    int passwordTrial = 5;
    while(true){
        int trial;
        cout << "Enter password to open door please: ";
        cin >> trial;
        if(trial == doorCode){
            cout << "door is open\t feel free to come in :)" << std::endl;
            break;
        } else if(trial != doorCode){
            cout << "it is incorrect password" << std::endl;
            --passwordTrial;
            cout << "you have more " << passwordTrial << " chances left to open door\n";
        if (passwordTrial == 0){
            cout << "door is locked. I called to the police";
            break;
        }
        } else{ cout << "systematic problem has been occured"; break;}
    }
}