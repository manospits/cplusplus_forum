#include <stdio.h>
#include "../include/Forum.h"

Forum::Forum(string name, int id, int *LFID, int *LTID, int *LPID) : BasicObject(name)
{
    this->id = id;
    LastForumID = LFID;
    LastThreadID = LTID;
    LastPostID = LPID;
}



void Forum::print()
{
    cout << name << "  (ID: " << id << ")" << endl;
}

void Forum::show_forums()
{
    list<Forum>::iterator it;
    if (fora.empty()) cout << "     --None." << endl;
    for (it = fora.begin() ; it != fora.end() ; ++it)
    {
        cout<<"     --";
        it->print();
    }
}

void Forum::show_threads(System& s)
{
    list<Thread>::iterator it;
    if (threads.empty()) cout << "      +-None." << endl;
    for (it = threads.begin() ; it != threads.end() ; ++it)
    {
        if (it->is_sticky()){
            cout<<"         +-";
            it->print(s);
        }
    }

    for (it = threads.begin() ; it != threads.end() ; ++it)
        if (!(it->is_sticky())){
            cout<<"         +-";
            it->print(s);
        }
}

void Forum::add_forum(string name)
{

    *LastForumID += 1;
    Forum temp(name, *LastForumID, LastForumID, LastThreadID, LastPostID);
    fora.push_back(temp);
}
void Forum::add_forum(Forum& temp)
{
    fora.push_back(temp);
}
void Forum::add_thread(Thread& temp)
{
    threads.push_back(temp);
}
void Forum::add_forum(string name, int id) //used in reading the file, when the id is given by value (not from LastForumID)
{
    Forum temp(name, id, LastForumID, LastThreadID, LastPostID);
    fora.push_back(temp);
}

Forum* Forum::find_forum(int id)
{
    list<Forum>::iterator it;
    for (it = fora.begin() ; it != fora.end() ; ++it)
        if (it->get_id() == id)
            return &(*it);
    cout << "Error: Forum with ID: " << id << " not found." << endl;
    return NULL;
}

void Forum::delete_forum(int id)
{
    list<Forum>::iterator it;
    bool found = false;
    for (it = fora.begin() ; it != fora.end() ; ++it)
    {
        if (it->get_id() == id)
        {
            found = true;
            fora.erase(it);
            break;
        }
    }
    if (!found) cout << "Error: Forum with ID: " << id << " not found." << endl;
}

void Forum::add_thread(string thread_name, int creator_id, string content)
{
    *LastThreadID += 1;
    Thread temp(thread_name, creator_id, content, *LastThreadID, LastPostID);
    threads.push_back(temp);
}

void Forum::add_thread(string thread_name, int creator_id, int id, bool sticky, bool locked)
{   //used in reading the file, when the id is given by value (not from LastThreadID)
    Thread temp(thread_name, creator_id, id, LastPostID, sticky, locked);
    threads.push_back(temp);
}

Thread * Forum::find_thread(int id)
{
    list<Thread>::iterator it;
    for (it = threads.begin() ; it != threads.end() ; ++it)
        if (it->get_id() == id){
            return &(*it);
        }
    cout << "Error: Thread with ID: " << id << " not found." << endl;
    return NULL;
}

void Forum::delete_thread(int id)
{
    list<Thread>::iterator it;
    bool found = false;
    for (it = threads.begin() ; it != threads.end() ; ++it)
    {
        if (it->get_id() == id)
        {
            found = true;
            threads.erase(it);
            break;
        }
    }
    if (!found) cout << "Error: Thread with ID: " << id << " not found." << endl;
}

void Forum::save(fstream& file_fora, fstream& file_threads, fstream& file_posts, string str, bool first_call)
{
    string path(str);
    if (!first_call) path += '.';   //if we call save() for the first time (in other words, this forum is in the system), then we must not put a dot in the path
    char buffer[33];
    sprintf(buffer, "%d", id);
    path += string(buffer);
    //save this forum's info
    file_fora << path << ' ' << this->Getname() << '\n';

    //save subfora and their threads, posts
    list<Forum>::iterator it;
    for (it = fora.begin() ; it != fora.end() ; ++it)
        it->save(file_fora, file_threads, file_posts, path, false);

    //save threads, posts
    list<Thread>::iterator it2;
    for (it2 = threads.begin() ; it2 != threads.end() ; ++it2)
    {
        it2->save(file_threads, file_posts, path);
    }
}
