#ifndef POST_H
#define POST_H
#include <iostream>
#include "System.h"
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

class Post
{
    public:
        Post(string, int, int);
        int get_id() { return id; }
        void set_id(int val) { id = val; }
        int get_creator_id() { return creator_id; }
        void set_creator_id(int val) { creator_id = val; }
        string get_content() { return content; }
        void set_content(string val) { content = val; }
        void print(System&);
        void save(fstream&, string);
    protected:
    private:
        int id, creator_id;
        string content;
};

#endif // POST_H
