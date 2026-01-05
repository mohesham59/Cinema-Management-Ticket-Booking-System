#include <iostream>
#include <string>
#include "sqlite3.h"
#include "db_utils.h"
#include "/include/customer.hpp"
#include "frequent.h"

using namespace std;




bool login(sqlite3* db, string& role)
{
    sqlite3_stmt* stmt;
    string query;
    string email,password,role;
    cout << "Enter your email: ";
    cin >> email;
    cout << "\nEnter your password: ";
    cin >> password;

    query = "SELECT email, password FROM users WHERE password='" + password +"' AND email='" + email + "';";
    //SELECT email, password FROM users WHERE password='v_password' AND email='v_email';
    if(executeSQL(db, "BEGIN TRANSACTION;"))
    if(executeSQL(db, query))
    if(executeSQL(db, "COMMIT;"))
    {
        query = "SELECT role FROM users WHERE password='" + password +"' AND email='" + email + "';";
        if(sqlite3_prepare_v2(db, query, -1, &stmt, nullptr) == SQLITE_OK)
        {
            while(sqlite3_step(stmt) == SQLITE_ROW)
            {
                role = sqlite3_column_text(stmt, 0);
            }
        }
        
    }
}

bool reg(sqlite3* db)
{
    string query;
    string name,email,password,role;
    cout << "Enter your email: ";
    cin >> email;
    cout << "\nEnter your password: ";
    cin >> password;
    cout<< "\nName: ";
    cin >> name;
    role = 'customer';
    query = "INSERT INTO users(name,email,password,role) VALUES('" + name +"', '" + email + "', '" + password + "', 'customer')";
    if(executeSQL(db, "BEGIN TRANSACTION;"))
    if(executeSQL(db, query))
    if(executeSQL(db, "COMMIT;")) return true;

}

int main()
{
    sqlite3* db;
    string role;

    if (sqlite3_open("cinema.db", &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }



    if(reg(db)) cout << "\nregistered successfully!!";

    if(login(db, role))
    {
        cout << "You're a " << role << endl;
    }


    switch(role)
    {   
        //we still need to retrieve customer id so we can create an object using it 
        case 'customer':
        customer* C1 = new customer(db,user_id);
            int choice;
            cout << "Enter your choice: \n1) View Movies\n2) Reserve a movie" << endl;
            cin >> choice;
            switch(choice)
            {
                case 1:
                    C1->viewMovies();
                    break;
                case 2:
                    C1->reserveMovie();
                    break;
                default:
                cout << "Enter a valid choice!!" << endl;
                break;
            }
            break;
        case 'admin':
        //admin options and 
    }
    
    



    return 0;
}
