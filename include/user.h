#ifndef USER_H
#define USER_H
#include <iostream>
#include <string>
#include "privileges.h"
using namespace std;

class user
{
    public:
        user( string , string , int , int );
        string GetName() { return Name; }
        void SetName(string val) { Name = val; }
        int GetID() { return ID; }
        void SetID(int val) { ID = val; }
        int Getpriv_ID() { return priv_ID; }
        void Setpriv_ID(int val) { priv_ID = val; }
        privileges& Getpriv(){ return priv; }
        string GetPassword() { return Password; }
        void SetPassword(string val) { Password = val; }
        bool checkPass(string val){ return val == Password; }
        void Setposition(int val){position = val;}
        int Getposition(){return position;}
        char print_options(int&);
        void change_user_cat(int);
        void print_user_info();
    protected:
    private:
        string Name;
        int ID;
        int priv_ID;
        string Password;
        privileges priv;
        int position;
        //pointer se system-forum-thread
};

#endif // USER_H
