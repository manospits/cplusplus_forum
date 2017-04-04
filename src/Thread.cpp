#include <stdio.h>
#include "../include/Thread.h"

Thread::Thread(string thread_name, int creator_id, string content, int id, int *LPID) : BasicObject(thread_name)
{
    LastPostID = LPID;
    this->creator_id = creator_id;
    this->id = id;
    sticky=false;
    locked = false;
    *LastPostID += 1;
    Post temp(content, creator_id, *LastPostID);
    posts.push_back(temp);
}

Thread::Thread(string thread_name, int creator_id, int id, int *LPID, bool st, bool lk) : BasicObject(thread_name)
{   //used in reading the file
    LastPostID = LPID;
    this->creator_id = creator_id;
    this->id = id;
    sticky = st;
    locked = lk;
}

void Thread::print(System& s)
{
    if (sticky)
    cout << "Pinned: ";
    cout << name << ", created by " << s.get_username_from_id(creator_id) << "  (ID: " << id << ")" << endl;
}

void Thread::show_posts(System& s)
{
    list<Post>::iterator it;
    for (it = posts.begin() ; it != posts.end() ; ++it)
    {
        cout<<"     ";
        it->print(s);
    }
}

void Thread::add_post(int cr_id, string content)
{
    *LastPostID += 1;
    Post temp(content, cr_id, *LastPostID);
    posts.push_back(temp);
}

void Thread::add_post(int cr_id, string content, int id)
{
    Post temp(content, cr_id, id);
    posts.push_back(temp);
}
void Thread::add_post(Post& pos){
    posts.push_back(pos);
}

Post * Thread::find_post(int id)
{
    list<Post>::iterator it;
    for (it = posts.begin() ; it != posts.end() ; ++it)
        if (it->get_id() == id)
            return &(*it);
    cout << "Error: Post with ID: " << id << " not found." << endl;
    return NULL;
}

void Thread::delete_post(int id)
{
    list<Post>::iterator it;
    bool found = false;
    for (it = posts.begin() ; it != posts.end() ; ++it)
    {
        if (it->get_id() == id)
        {
            found = true;
            posts.erase(it);
            break;
        }
    }
    if (!found) cout << "Error: Post with ID: " << id << " not found." << endl;
}

void Thread::save(fstream& file_threads, fstream& file_posts, string str)
{
    string path(str);
    path += '.';
    char buffer[33];
    sprintf(buffer, "%d", id);
    path += string(buffer);
    char s, l;
    if (sticky) s = 'S';
    else s = 'N';
    if (locked) l = 'L';
    else l = 'N';
    //save this thread's info
    file_threads << path << ' ' << s << ' ' << l << ' ' << creator_id << ' ' << this->Getname() << '\n';

    //save posts info
    list<Post>::iterator it;
    for (it = posts.begin() ; it != posts.end() ; ++it)
        it->save(file_posts, path);
}
