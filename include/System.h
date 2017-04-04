#ifndef SYSTEM_H
#define SYSTEM_H
#include <iostream>
#include <string>
#include <list>
#include <fstream>
#include "BasicObject.h"
#include "Forum.h"
#include "user.h"

using namespace std;
void raw( bool b );
class System : public BasicObject
{
    public:
        System(string);
        ~System();
        void show_forums();
        void add_forum(string);
        void add_forum(string, int);
        void add_forum(Forum&);
        void delete_forum(int);
        void show_users();
        void add_user(string,string,int);
        void add_user(string,string,int, int);
        void delete_user(int);
        user& ret_user(string);
        void change_user_category(int,int);
        void change_user_username(int,string);
        void change_user_password(int,string);
        int move_forum(Forum&,string);
        int move_thread(Thread&,string);
        int move_post(Post&,string);
        user& ret_user(int);
        string get_username_from_id(int);
        Forum* find_forum(int);
        int operate(int);
        void save();
    protected:
    private:
        string name;
        list<Forum> fora;
        int *LastForumID, *LastThreadID, *LastPostID, LastUserID;
        list<user> users;
        int load_forums();
        int load_threads();
        int load_posts();
        int load_users();
};

#endif // SYSTEM_H
