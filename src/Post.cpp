#include <stdio.h>
#include "../include/Post.h"

Post::Post(string content, int creator_id, int id)
{
    this->content = content;
    this->creator_id = creator_id;
    this->id = id;
}

void Post::print(System& s)
{
    cout << s.get_username_from_id(creator_id) << ": " << content << "  (ID: " << id << ")" << endl;
}

void Post::save(fstream& file_posts, string str)
{
    string path(str);
    path += '.';
    char buffer[33];
    sprintf(buffer, "%d", id);
    path += string(buffer);
    //save this post's info
    file_posts << path << ' ' << creator_id << ' ' << content << '\n';
}
