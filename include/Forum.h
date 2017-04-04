#ifndef FORUM_H
#define FORUM_H
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <list>
#include "BasicObject.h"
#include "System.h"
#include "Thread.h"

using namespace std;

class Forum : public BasicObject
{
    public:
        Forum(string, int, int *, int *, int *);
        int get_id() { return id; }
        void set_id(int val) { id = val; }
        void print();
        void show_forums();
        void show_threads(System&);
        void add_forum(string);
        void add_forum(Forum&);
        void add_forum(string, int);
        Forum * find_forum(int);
        void delete_forum(int);
        Forum& ret_forum(){return *this;}
        void add_thread(Thread&);
        void add_thread(string, int, string);
        void add_thread(string, int, int, bool, bool);
        Thread * find_thread(int);
        void delete_thread(int);
        void save(fstream&, fstream&, fstream&, string, bool);
    protected:
    private:
        int id;
        int *LastForumID, *LastThreadID, *LastPostID;
        list<Forum> fora;
        list<Thread> threads;
};

#endif // FORUM_H
