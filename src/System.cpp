#if defined(_WIN32) || defined(WIN32) || defined(__CYGWIN__) || defined(__MINGW32__) ||defined (__BORLANDC__)
#define OS_WIN
#endif
#include <stdio.h>
#include "../include/System.h"
#ifndef OS_WIN
#include <unistd.h>
#include <termios.h>
#endif

extern const int MAXUSERNAMESIZE=12;
extern const int MAXPASSWORDSIZE=12;
static user emptyuser("","",0,0);
System::System(string name): BasicObject(name)
{
    LastForumID = new int;
    *LastForumID = 0;
    LastThreadID = new int;
    *LastThreadID = 0;
    LastPostID = new int;
    *LastPostID = 0;
    LastUserID = 0;
    //read file
    if (load_forums())
        cout << "Error opening fora save file!" << endl;
    else
    {
        if (load_threads())
            cout << "Error opening threads save file!" << endl;
        else
        {
            if (load_posts())
                cout << "Error opening post save file!" << endl;
        }
    }
    if (load_users()) cout << "Error opening users save file!" << endl;
}

System::~System()
{
    delete LastPostID;
    delete LastThreadID;
    delete LastForumID;
}

void System::show_forums()
{
    list<Forum>::iterator it;
    if (fora.empty()) cout << "Error! list is empty s" << endl;

    for (it = fora.begin() ; it != fora.end() ; ++it)
    {
        cout<<"     --";
        it->print();
    }
}

void System::add_forum(string name)
{
    *LastForumID += 1;
    Forum temp(name, *LastForumID, LastForumID, LastThreadID, LastPostID);
    fora.push_back(temp);
}

void System::add_forum(string name, int id) //used in reading the file, when the id is given by value (not from LastForumID)
{
    Forum temp(name, id, LastForumID, LastThreadID, LastPostID);
    fora.push_back(temp);
}

Forum* System::find_forum(int id)
{
    list<Forum>::iterator it;
    for (it = fora.begin() ; it != fora.end() ; ++it)
        if (it->get_id() == id)
            return &(*it);
    cout << "Error: Forum with ID: " << id << " not found." << endl;
    return NULL;
}

void System::delete_forum(int id)
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

void System::show_users()
{
    list<user>::iterator it;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        it->print_user_info();
    }
}

void System::add_user(string N,string P, int PID)
{
    LastUserID += 1;
    user temp(N,P,LastUserID,PID);
    users.push_back(temp);
}

void System::add_user(string N,string P, int PID, int id)
{
    user temp(N,P,id,PID);
    users.push_back(temp);
}

void System::delete_user(int id)
{
    list<user>::iterator it;
    bool found = false;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        if (it->GetID() == id)
        {
            found = true;
            users.erase(it);
            break;
        }
    }
    if (!found) cout << "Error: User with ID: " << id << " not found." << endl;
}
user& System::ret_user(int id){
    list<user>::iterator it;
    bool found = false;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        if (it->GetID() == id)
        {
            found = true;
            return (*it);
            break;
        }
    }
    if (!found) cout << "Error: User with ID: " << id << " not found." << endl;
}

string System::get_username_from_id(int id)
{
    list<user>::iterator it;
    for (it = users.begin() ; it != users.end() ; ++it)
        if (it->GetID() == id)
            return it->GetName();
    return "Unknown user";
}

void System::change_user_category(int id,int pr)
{
    list<user>::iterator it;
    bool found = false;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        if (it->GetID() == id)
        {
            found = true;
            (*it).change_user_cat(pr);
            break;
        }
    }
    if (!found) cout << "Error: User with ID: " << id << " not found." << endl;
}

void System::change_user_username(int id,string N)
{
    list<user>::iterator it;
    bool found = false;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        if (it->GetID() == id)
        {
            found = true;
            (*it).SetName(N);
            break;
        }
    }
    if (!found) cout << "Error: User with ID: " << id << " not found." << endl;
}

void System::change_user_password(int id,string passw)
{
    list<user>::iterator it;
    bool found = false;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        if (it->GetID() == id)
        {
            found = true;
            (*it).SetPassword(passw);
            break;
        }
    }
    if (!found) cout << "Error: User with ID: " << id << " not found." << endl;
}

int cton(char c)    //convert character to number
{
    if (c == '0') return 0;
    if (c == '1') return 1;
    if (c == '2') return 2;
    if (c == '3') return 3;
    if (c == '4') return 4;
    if (c == '5') return 5;
    if (c == '6') return 6;
    if (c == '7') return 7;
    if (c == '8') return 8;
    if (c == '9') return 9;
    return 0;
}

int System::load_forums()
{
    fstream file;
    BasicObject *move_ptr = this;  //pointer that is used to move in the system
    char c;
    const char* buff;
    string path, name;
    int num = 0, buff_counter = 0;
    file.open("data/forumhierarchy.save", ios::in);
    if (file == NULL) return 1;
    else
    {
        /*
        c = file.get(); // debugging \/
        while (!file.eof())
        {
            cout << c;
            c = file.get();
        }
        cout << endl;

        file.clear();
        file.seekg(0);  // debugging /\
        */
        cout << "Loading Fora data..." << endl;
        file >> *LastForumID >> *LastThreadID >> *LastPostID >> LastUserID;
        //take the '\n'
        c = file.get();
        while (!file.eof())
        {
            //load fora
            num = 0;
            move_ptr = this;
            if (!isdigit(c = file.peek()))  //catches the last '\n' before EOF, and other possible errors
            {
                c = file.get();
                continue;
            }
            getline(file, path, ' ');
            getline(file, name);
            //cout << path << ' ' << name << endl;  //DEBUGGING
            buff = path.data();
            buff_counter = path.length();
            for (int i = 0 ; i <= buff_counter ; ++i)
            {
                if (isdigit(buff[i]))
                {
                    num *= 10;
                    num += cton(buff[i]);
                }
                else if (buff[i] == '.')
                {
                    //move to the next forum
                    move_ptr = move_ptr->find_forum(num);
                    //cout << num << endl;  //debugging
                    num = 0;
                }
                if (i == buff_counter)
                {
                    //cout << num << endl;  //debugging
                    //create forum
                    move_ptr->add_forum(name, num);
                }
            }
        }
        cout << "Loading complete." << endl;
        cout << endl;
    }
    return 0;
}

int System::load_threads()
{
    fstream file;
    BasicObject *move_ptr = this;  //pointer that is used to move in the system
    char c;
    const char* buff;
    string path, name;
    bool s, l;
    int num = 0, buff_counter = 0, id;
    file.open("data/thread.save", ios::in);
    if (file == NULL) return 1;
    else
    {
        /*
        c = file.get(); // debugging \/
        while (!file.eof())
        {
            cout << c;
            c = file.get();
        }
        cout << endl;

        file.clear();
        file.seekg(0);   // debugging /\
        */
        cout << "Loading Threads data..." << endl;
        while (!file.eof())
        {
            num = 0;
            move_ptr = this;
            id = 0;
            if (!isdigit(c = file.peek()))  //catches the last '\n' before EOF, and other possible errors
            {
                c = file.get();
                continue;
            }
            //read path
            getline(file, path, ' ');
            //read sticky
            c = file.get();
            if (c == 'S') s = true;
            else if (c == 'N') s = false;
            else
            {
                s = false;
                cout << "Error reading thread save file. 'sticky' variable is neither N nor S." << endl;
            }
            //take the space
            c = file.get();
            //read locked
            c = file.get();
            if (c == 'L') l = true;
            else if (c == 'N') l = false;
            else
            {
                l = false;
                cout << "Error reading thread save file. 'locked' variable is neither N nor S." << endl;
            }
            //take the space
            c = file.get();
            //read user (creator) id
            file >> id;
            //take the space
            c = file.get();
            //read thread name
            getline(file, name);
            //cout << path << ' ' << s << ' ' << l << ' ' << id << ' ' << name << endl;    // debugging
            buff = path.data();
            buff_counter = path.length();
            for (int i = 0 ; i <= buff_counter ; ++i)
            {
                if (isdigit(buff[i]))
                {
                    num *= 10;
                    num += cton(buff[i]);
                }
                else if (buff[i] == '.')
                {
                    //move to the next forum
                    move_ptr = move_ptr->find_forum(num);
                    //cout << num << endl;  //debugging
                    num = 0;
                }
                if (i == buff_counter)
                {
                    //cout << num << endl;  //debugging
                    //create thread
                    move_ptr->add_thread(name, id, num, s, l);  //NA DW AN XREIAZETAI ID
                }
            }
        }
        cout << "Loading complete." << endl;
        cout << endl;
    }
    return 0;
}

int System::load_posts()
{
    fstream file;
    BasicObject *move_ptr = this;  //pointer that is used to move in the system
    char c;
    const char* buff;
    string path, content;
    int num = 0, buff_counter = 0, id, forumid = -1, threadid = -1, postid = -1;   //id refers to user (creator) id
    file.open("data/post.save", ios::in);
    if (file == NULL) return 1;
    else
    {
        /*
        c = file.get(); // debugging \/
        while (!file.eof())
        {
            cout << c;
            c = file.get();
        }
        cout << endl;

        file.clear();
        file.seekg(0);   // debugging /\
        */
        cout << "Loading Posts data..." << endl;
        while (!file.eof())
        {
            num = 0;
            move_ptr = this;
            id = 0;
            forumid = -1;
            threadid = -1;
            postid = -1;
            if (!isdigit(c = file.peek()))  //catches the last '\n' before EOF, and other possible errors
            {
                c = file.get();
                continue;
            }
            //read path
            getline(file, path, ' ');
            //read user (creator) id
            file >> id;
            //take the space
            c = file.get();
            //read post content
            getline(file, content);
            //cout << path << ' ' << id << ' ' << content << endl;    // debugging
            buff = path.data();
            buff_counter = path.length();
            for (int i = 0 ; i <= buff_counter ; ++i)
            {
                if (isdigit(buff[i]))
                {
                    num *= 10;
                    num += cton(buff[i]);
                }
                else if (buff[i] == '.')
                {
                    forumid = threadid; //when we read a deeper hierarchy path, it means that the id we thought it was a thread's id was actually a forum's id
                    threadid = num;
                    //move to the next forum
                    if (forumid != -1)
                        move_ptr = move_ptr->find_forum(forumid);
                    //cout << num << endl;  //debugging
                    num = 0;
                }
                if (i == buff_counter)
                {
                    //cout << num << endl;  //debugging
                    postid = num;
                    //create thread
                    if (forumid != -1 && threadid != -1 && postid != -1)
                    {
                        move_ptr = move_ptr->find_thread(threadid);
                        move_ptr->add_post(id, content, postid);
                    }
                    else cout << "Error (probably syntax) in post path" << endl;
                }
            }
        }
        cout << "Loading complete." << endl;
        cout << endl;
    }
    return 0;
}
void System::add_forum(Forum& temp)
{
    fora.push_back(temp);
}
int System::load_users()
{
    fstream file;
    string username, password;
    int id, priv_id;
    char c;
    file.open("data/users.save", ios::in);
    if (file == NULL) return 1;
    else
    {
        cout << "Loading users data..." << endl;
        while (!file.eof())
        {
            if (!isdigit(c = file.peek()))  //catches the last '\n' before EOF, and other possible errors
            {
                c = file.get();
                continue;
            }
            file >> id;
            //take the space
            c = file.get();
            getline(file, username, ' ');
            getline(file, password, ' ');
            file >> priv_id;
            //take the '\n'
            c = file.get();
            //cout << id << ' ' << username << ' ' << password << ' ' << priv_id << endl; //DEBUGGING
            this->add_user(username, password, priv_id, id);
        }
        cout << "Loading complete." << endl;
    }
    return 0;
}

void System::save()
{
    fstream file_fora, file_threads, file_posts, file_users;
    file_fora.open("data/forumhierarchy.save", ios::out);
    file_threads.open("data/thread.save", ios::out);
    file_posts.open("data/post.save", ios::out);
    file_users.open("data/users.save", ios::out);
    cout << "Saving System data..." << endl;
    //save LastIDs
    file_fora << *LastForumID << ' ' << *LastThreadID << ' ' << *LastPostID << ' ' << LastUserID << '\n';

    //save fora, threads, posts
    list<Forum>::iterator it;
    for (it = fora.begin() ; it != fora.end() ; ++it)
        it->save(file_fora, file_threads, file_posts, "", true);

    //save users
    list<user>::iterator it2;
    for (it2 = users.begin() ; it2 != users.end() ; ++it2)
    {
        file_users << it2->GetID() << ' ' << it2->GetName() << ' ' << it2->GetPassword() << ' ' << it2->Getpriv_ID() << '\n';
    }
    cout << "Saving complete." << endl;
}

int System::move_forum(Forum& tobemoved,string path){
            int buff_counter=0,num=0;
            BasicObject *move_ptr = this;
            const char* buff;
            cout << path << endl;
            buff = path.data();
            buff_counter = path.length();
	//MOVING AT THE DESIRED PATH
            for (int i = 0 ; i <= buff_counter ; ++i)
            {
                if (isdigit(buff[i]))
                {
                    num *= 10;
                    num += cton(buff[i]);
                }
                else if (buff[i] == '.')
                {
                    move_ptr = move_ptr->find_forum(num);
                    if(move_ptr==NULL){
                        return -1;
                    }
                    num=0;
                }
                if (i == buff_counter)
                {
                    if(buff[i-1]!='S')
                    {
                        move_ptr = move_ptr->find_forum(num);
                        if(move_ptr==NULL){
                        return -1;
                        }
                    }
                    move_ptr->add_forum(tobemoved);
                    return 0;
                }
            }
}

int System::move_thread(Thread& thr,string path){
    int buff_counter=0,num=0;
    BasicObject *move_ptr = this;
    const char* buff;
    buff = path.data();
    buff_counter = path.length();
    for (int i = 0 ; i <= buff_counter ; ++i)
    {
        if (isdigit(buff[i]))
        {
            num *= 10;
            num += cton(buff[i]);
        }
        else if (buff[i] == '.')
        {
            move_ptr = move_ptr->find_forum(num);
            if(move_ptr==NULL){
                return -1;
            }
            num = 0;
        }
        if (i == buff_counter)
        {
            move_ptr = move_ptr->find_forum(num);
            if(move_ptr==NULL){
                return -1;
            }
            move_ptr->add_thread(thr);
            return 0;
        }
    }
}
int System::move_post(Post& pos,string path){
    int buff_counter=0,num=0;
    BasicObject *move_ptr = this;
    const char* buff;
    buff = path.data();
    buff_counter = path.length();
    for (int i = 0 ; i <= buff_counter ; ++i)
    {
        if (isdigit(buff[i]))
        {
            num *= 10;
            num += cton(buff[i]);
        }
        else if (buff[i] == '.')
        {
            move_ptr = move_ptr->find_forum(num);
            if(move_ptr==NULL){
                return -1;
            }
            num = 0;
        }
        if (i == buff_counter)
        {
            move_ptr = move_ptr->find_thread(num);
            if(move_ptr==NULL){
                return -1;
            }
            move_ptr->add_post(pos);
            return 0;
        }
    }
    return 3;
}
user& System::ret_user(string name){
    list<user>::iterator it;
    bool found;
    for (it = users.begin() ; it != users.end() ; ++it)
    {
        if (it->GetName() == name)
        {
            found = true;
            return (*it);
            break;
        }
    }
    return emptyuser ;
}

int System::operate(int o){
string name;
string passw;
user temp=emptyuser;
if(o==1){
    int state=0;
    while( state==0){
        //show_users();
        cout<<"Give username : ";
        getline(cin,name);
	char ch=0;
        cout<<"Give password : ";
#ifndef OS_WIN
	raw(true);
	ch=getchar();
        while(ch!=13)
	{
		passw.push_back(ch);
		cout<< '*';
		ch=getchar();
	}
	raw(false);
#endif
#ifdef OS_WIN
	getline(cin,passw);
#endif
        if(name!=" "||passw!=" "){
            temp=ret_user(name);
            if(!temp.GetID()==0){
                if(temp.GetPassword()==passw){
                    state=1;
                }
                else{
                    cout<<"\nWrong password!\nTry again with correct password."<<endl;
		    passw="";
                }
            }
            else
                cout<<"\nUser not found!\nTry again with correct username."<<endl;
        }
        else if(name==" "&&passw==" "){
            state=1;
            temp= user("N/a","N/a",1,0);
        }
    }
    bool e=false,r=false,t=false;
    BasicObject* s=this;
    System& sy=*this;
    visit(temp,0,e,s,r,t,sy);
}
if(o==0){
    cout<<"Creating a new user. "<<endl;
    cout<<"_____________________________\n"<<endl;
    string name;
        int state=1;
        while(state==1)
        {
            cout<<"Give a username : ";
            bool stat=true;
            while(stat==true)
            {
                cin>>name;
                if(name.length()<=MAXUSERNAMESIZE&&name.length()>=1)
                    stat=false;
                else
                {
                    cout<<"Username must be 1-"<<MAXUSERNAMESIZE<<" characters!"<<endl;
                    cout<<"Give a username"<<endl;
                }

            }
        user temp=ret_user(name);
        if(!temp.GetID()==0){
        cout<<"Name "<<name <<" is taken."<<endl;
        }
        else
            state=0;
    }
    getchar();
    cout<<"Give a password : ";
    bool stat=true;
                while(stat==true){
                cin>>passw;
                if(passw.length()<=MAXPASSWORDSIZE&&passw.length()>=1)
                    stat=false;
                else{
                    cout<<"Password must be 1-"<<MAXUSERNAMESIZE<<" characters!"<<endl;
                    cout<<"Give a password : "<<endl;}

                }
    add_user(name,passw,1);
    bool e=false,r=false,t=false;
    BasicObject* s=this;
    System& sy=*this;
    visit(ret_user(name),0,e,s,r,t,sy);
}
return 0;
}
#ifndef OS_WIN
void raw( bool b )
  {
  struct termios settings;
  static struct termios initial_settings;
  static bool is_initialized = false;

  if (!is_initialized)
    {
    is_initialized = tcgetattr( STDIN_FILENO, &initial_settings ) == 0;
    if (!is_initialized) return;
    }

  if (b)
    {
    tcgetattr( STDIN_FILENO, &settings );
    settings.c_cc[ VTIME ] = 0;
    settings.c_cc[ VMIN  ] = 1;
    settings.c_iflag &= ~(BRKINT | ICRNL | INLCR | ISTRIP | IXOFF);
    settings.c_iflag |=   IGNBRK;
    settings.c_oflag &= ~(OPOST);
    settings.c_cflag &= ~(CSIZE | PARENB);
    settings.c_cflag |=   CS8;
    settings.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
    }
  else
    settings = initial_settings;

  tcsetattr( STDIN_FILENO, TCSANOW, &settings );
  }
#endif
