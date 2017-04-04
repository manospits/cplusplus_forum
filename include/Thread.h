#ifndef THREAD_H
#define THREAD_H
#include <iostream>
#include "BasicObject.h"
#include <string>
#include "System.h"
#include <fstream>
#include <list>
#include "Post.h"

using namespace std;

class Thread : public BasicObject
{
    public:
        Thread(string, int, string, int, int *); //thread name, creator id, first post (content) and thread id (and LastPostID)
        Thread(string, int, int, int *, bool, bool);//thread name, id, LTID, sticky, locked
        int get_id() { return id; }
        Thread& ret_thread(){return *this;}
        void set_id(int val) { id = val; }
        int get_creator_id() { return creator_id; }
        void set_creator_id(int val) { creator_id = val; }
        void set_name(string val) { name = val; }
        string get_name() { return name; }
        bool is_sticky() { return sticky; }
        void set_sticky(bool val) { sticky = val; }
        bool is_locked() { return locked; }
        void set_locked(bool val) { locked = val; }
        void print(System&);
        void show_posts(System&);
        void add_post(Post&);
        void add_post(int, string);
        void add_post(int, string, int);
        Post* find_post(int);
        void delete_post(int);
        void save(fstream&, fstream&, string);
    protected:
    private:
        int id, creator_id;
        int *LastPostID;
        bool sticky;
        bool locked;
        list<Post> posts;
};

#endif // THREAD_H
