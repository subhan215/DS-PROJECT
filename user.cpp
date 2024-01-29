#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <cstdio>
#include <stack>
using namespace std;
struct browseHistory {
    public:
    char point1[100] ; 
    char point2[100] ; 
} ; 
class user
{
private:
    string user_name;
    string user_id;
    string user_email;
    string user_password;

public:
    user() {}
    bool login()
    {
        bool check = false;
        string email, password;
        cout << "email :";
        cin >> email;
        //email = "Email : " + email;

        cout << "password :";
        cin >> password;
        //password = "Password : " + password;

        ifstream read;
        read.open("All_app_users.txt");

        getline(read, user_name);
        getline(read, user_id);
        getline(read, user_email);
        getline(read, user_password);

        if (read.is_open())
        {
            cout << "Verifying details in the system\n\n";
            while (!read.eof())
            {
                if (email == user_email && password == user_password)
                {
                    cout << "Welcome back " << user_name << endl;
                    check = true;
                    return true;
                    break;
                }
                else
                {
                    getline(read, user_name);
                    getline(read, user_id);
                    getline(read, user_email);
                    getline(read, user_password);
                }
            }
            if (check == false)
            {
                cout << "No account exist for this email and password . Enter correct email and password." << endl;
                return false;
            }
        }
        return true;
    }
    string get_name(){
        return user_name;
    }
    string get_email(){
        return user_email;
    }
    string get_password(){
        return user_password;
    }
    string get_id(){
        return user_id;
    }
    void set_id(string id){
        this->user_id=id;
    }
    void set_name(string name){
        this->user_name=name;
    }
    void set_email(string email){
        this->user_email=email;
    }
    void set_password(string password){
        this->user_password=password;
    }
    // This Fucntion will add data to file
		void Add_to_file() {
			ofstream write;
			write.open("All_app_users.txt", ios::binary | ios::app);
			write << user_name << endl;
			write << user_id << endl;
			write << user_email << endl;
			write << user_password << endl;
			//Similar to the above work, we will write every attribute into file , or only those that are of our need
			write.close();
			cout << "Data Saved to file\n";
		}
    void browsingHistoryFunc () {
    stack<browseHistory> s ; 
    string browsing_history;
	browsing_history = user_id + "_history.txt";
	FILE *fp ;
    char cStr[100] ;
   browsing_history.copy(cStr, sizeof(cStr), 0);
    cStr[sizeof(cStr) - 1] = '\0'; // Ensure null-termination
    fp = fopen( cStr, "rb") ; 
    browseHistory temp ; 
    while(fread(&temp ,  sizeof(browseHistory), 1 ,fp )){
        s.push(temp) ; 
    }    
    fclose(fp) ; 
    cout << "\nBrowsing History! " ; 
    int count = 1 ; 
    while(!s.empty()) {
          temp = s.top() ; 
          cout << count << ": \n" ; 
          cout << "\nPoint 1: " << temp.point1 ;
          cout << "\nPoint 2: " << temp.point2 ;  
          s.pop() ; 
          count++ ; 
    }
    }
    
};

//This function will check the validity of password
bool isPasswordValid(string password) {
	// Password should be at least 8 characters long
	if (password.length() < 8) {
		return false;
	}

	// Check if password contains at least one uppercase letter, one lowercase letter and one digit
	bool hasUppercase = false;
	bool hasLowercase = false;
	bool hasDigit = false;

	for (int i = 0; i < password.length(); i++) {
		if (isupper(password[i])) { 
			hasUppercase = true;
		} else if (islower(password[i])) {
			hasLowercase = true;
		} else if (isdigit(password[i])) {
			hasDigit = true;
		}
	}

	if (!hasUppercase || !hasLowercase || !hasDigit) {
		return false;
	}

	return true;
}
//This function will check string
bool check_string(string s) {
	bool check = false;
	for (int i = 0; i < s.length(); i++) {
		if (!isalpha(s[i])) {
			check = true;
		}
	}
	if (check == true) {
		return false;
	}
	return true;
}

void sign_up_of_person() {
	//read ID from file "ID" then assign to user then write user's data in file then write incremented ID in file of "ID"

	int IDint;
	string IDstring,first_name,last_name, email, password, name;
	bool dot_present = false, rate_present = false;

	//reading  ID from file "ID.txt"
	ifstream read;
	read.open("ID.txt");
	if (!read.is_open()) {
		cout << "ID error\n";
		return ;
	} else {
		cout << "Reading ID from file\n";
		read >> IDstring;
		cout << "ID:" << IDstring << endl;
	}
	read.close();

	//incrementing ID by typecasting into int
	IDint = stoi(IDstring);
	IDint++;
	IDstring = to_string(IDint);


	user person;

	//ID of person has been set
	person.set_id(IDstring);

	do {

		cout << "Email:";
		fflush(stdin);
        cin >> email;
		for (int i = 0; i < email.length(); i++) {
			if (email[i] == '@') {
				rate_present = true;
			}
			if (email[i] == '.') {
				dot_present = true;
			}
		}
		if (dot_present == false || rate_present == false) {
			cout << "invalid mail,enter again\n";
		}
	} while (dot_present == false || rate_present == false);
	
    person.set_email(email);
//    cout<<person.get_email()<<endl;

	do {
		cout << "Password(Password should be at least 8 characters long and contain at least one uppercase letter, one lowercase letter, and one digit.):";
		cin >> password;

		if (isPasswordValid(password) == false) {
			cout << "Invalid Format.Enter again.\n";
		}
	} while (isPasswordValid(password) == false);
    
    person.set_password(password);
//	cout<<person.get_password();
    do {
		cout << "Fist name:";
		cin >> first_name;
		if (check_string(first_name) == false) {
			cout << "Invalid character\n";
		}
	} while (check_string(first_name) == false);


	do {
		cout << "Last Name:";
		cin >> last_name;
		if (check_string(last_name) == false) {
			if (check_string(first_name) == false) {
				cout << "Invalid character\n";
			}
		}
	} while (check_string(last_name) == false);

	string fname = first_name + " " + last_name;
	person.set_name(fname);
	

	person.Add_to_file();

	//writing incremented ID in file "ID"
	ofstream writeID;
	writeID.open("ID.txt");
	writeID << IDint;
	writeID.close();

    //making browsing history file
    string browsing_history;
	browsing_history = IDstring + "_history.txt";
	ofstream browsing_history_file;
	browsing_history_file.open(browsing_history);
	browsing_history_file.close();

}

void user_interface()
{
    int choice1;
    int choice2;
    int choice3;
    user user_object;
    for (;;)
    {
        cout << "Login as : \n1. Admin  \n2. User  \n3.Exit\n Your choice :";
        cin >> choice1;
        switch (choice1)
        {
        case 1:
            // admin ki class ka call kar
            break;
        case 2:
        for(;;){
            cout<<"1. Login \n2. Sign Up \n3.Back\nYour Choice:";
            cin>>choice3;
            if(choice3==1){
            if (user_object.login())
            {/*
                cout<<"1.View routes of People's Bus Service in Karachi.\n";
                cout<<"2.Search for a desire route.\n";
                cout<<"3.View previously searched routes.\n";
                //user ko baki options dekhanay hain
                cin>>choice4;
                if(choice4==1){

                }else if(choice4==2){

                }else if(choice4==3){

                }else {

                }*/
                
            }else{
                cout<<"Try Again.\n";
            }
            }else if(choice3==2){
                sign_up_of_person();
                cout<<"Your account has been created successfully.\n";
            }else if(choice3==3){
                break;
            }
        }
        case 3:
            exit(0);
        default:
            cout<<"Invalid Choice.\n";
            break;
        }
    }
}

int main(){
    user_interface();
}