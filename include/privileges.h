#ifndef PRIVILEGES_H
#define PRIVILEGES_H
#include <iostream>

class privileges
{
    public:
        privileges(int);
        bool Getread() { return read; }
        void Setread(bool val) { read = val; }
        bool Getcrthread() { return crthread; }
        void Setcrthread(bool val) { crthread = val; }
        bool Getrespond() { return respond; }
        void Setrespond(bool val) { respond = val; }
        bool Getthrmanage() { return thrmanage; }
        void Setthrmanage(bool val) { thrmanage = val; }
        bool Getmksticky() { return mksticky; }
        void Setmksticky(bool val) { mksticky = val; }
        bool Getlock() { return lock; }
        void Setlock(bool val) { lock = val; }
        bool Getcrforum() { return crforum; }
        void Setcrforum(bool val) { crforum = val; }
        bool Getdelforum() { return delforum; }
        void Setdelforum(bool val) { delforum = val; }
        bool Getmvforum() { return mvforum; }
        void Setmvforum(bool val) { mvforum = val; }
        bool Getrnforum() { return rnforum; }
        void Setrnforum(bool val) { rnforum = val; }
        bool Getmvuser() {return mvuser;}
        void Setmvuser(bool val) { mvuser=val; }
        bool Getchuname() { return chuname; }
        void Setchuname(bool val) { chuname = val; }
        bool Getchuserpassw() { return chuserpassw; }
        void Setchuserpassw(bool val) { chuserpassw = val; }
        void print_system_options();
        void print_forum_options();
        void standard_prints();
        void print_thread_options();
        void print_user_management_options();
    protected:
    private:
        bool read;
        bool crthread;
        bool respond;
        bool thrmanage;
        bool mksticky;
        bool lock;
        bool crforum;
        bool delforum;
        bool mvforum;
        bool rnforum;
        bool mvuser;
        bool chuname;
        bool chuserpassw;
};

#endif // PRIVILEGES_H
