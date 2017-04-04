#ifndef BASICOBJECT_H
#define BASICOBJECT_H
#include <string>
#include <fstream>

class Forum;
class Thread;
class Post;
class System;
class user;

using namespace std;

class BasicObject
{
    public:
        BasicObject(string);
        string Getname() { return name; }
        void Setname(string val) { name = val; }
        //Used in multiple Subclasses
        virtual void show_forums() {}
        virtual void show_threads(System&) {}
        virtual void show_posts(System&) {}
        virtual void add_forum(string){}
        virtual void add_forum(string, int){}
        virtual void delete_forum(int){}
        virtual Forum * find_forum(int){return NULL;}
        virtual int get_id(){return 0;}
        virtual void set_id(int){}
        virtual void print(){}
        virtual void print(System&){}
        //System
        virtual void show_users(){}
        virtual void add_user(string,string,int){}
        virtual void add_user(string,string,int, int){}
        virtual void delete_user(int){}
        virtual void change_user_category(int,int){}
        virtual void change_user_username(int,string){}
        virtual void change_user_password(int,string){}
        virtual void add_forum(Forum&){}
        virtual user& ret_user(int){}
        virtual string get_username_from_id(int){return "";}
        virtual void save(){}
        //Forum
        virtual void add_thread(Thread&){}
        virtual Forum& ret_forum(){}
        virtual void add_thread(string, int, string){}
        virtual void add_thread(string, int, int, bool, bool){}
        virtual Thread * find_thread(int){return NULL;}
        virtual void delete_thread(int){}
        virtual void save(fstream&, fstream&, fstream&, string, bool){}
        //Thread
        virtual Thread& ret_thread(){}
        virtual int get_creator_id(){return 0;}
        virtual void set_creator_id(int){}
        virtual bool is_sticky(){return false;}
        virtual void set_sticky(bool){}
        virtual bool is_locked(){return false;}
        virtual void set_locked(bool){}
        virtual void add_post(Post&){}
        virtual void add_post(int, string){}
        virtual void add_post(int, string, int){}
        virtual Post* find_post(int){return NULL;}
        virtual void delete_post(int){}
        virtual void save(fstream&, fstream&, string){}
        void visit(user& ,int ,bool& ,BasicObject*,bool&,bool&,System&);

    protected:
        string name;
    private:
};

#endif // BASICOBJECT_H
