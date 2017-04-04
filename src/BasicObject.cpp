#include "../include/BasicObject.h"
#include <iostream>
#include <string>
#include "../include/user.h"
#include <cstdio>
#include "../include/System.h"
#include "../include/Thread.h"
#include "../include/Post.h"
#include "../include/Forum.h"

const int MAXTHREADTITLESIZE=30;
const int MAXPOSTSIZE=100;
const int MAXUSERNAMESIZE=12;
const int MAXPASSWORDSIZE=12;

using namespace std;
BasicObject::BasicObject(string name)
{
    this->name = name;
}
//Recursive visit system->forum->forum/thread
void BasicObject::visit(user& visitor,int pos,bool& close, BasicObject* object,bool& home,bool &del,System& syst){
    visitor.Setposition(pos);
    char c;
    int err=0;
    string error_info;
    if(pos==0){//SYSTEM
        int a;
        while(visitor.Getposition()==0)
        {
            if(err==-1){//if there is an error/warning print a message about the error
                cout<<error_info<<endl;
                err=0;
            }
            if(c!='C')
            cout << string( 100, '\n' );
            cout<<"Connected user info : "<<endl;
            cout<<"_____________________"<<endl;
            visitor.print_user_info();//does what it says
            cout<<"++++Forums in System++++\n";
            object->show_forums();
            cout<<"\n";
            c=visitor.print_options( a);//print options based on the privileges the user has
            if(c=='L'){ //save
                syst.save();
                return;
            }
            else if( c=='X'){//dont save
                return;
            }
            else if(c=='N'){
                cout<<"Give a name for the forum "<<endl;
                string n;
                getchar();
                getline(cin,n);//read the name
                object->add_forum(n);
            }
            else if(c=='C'){
                cout << string( 100, '\n' );
                object->show_users();
            }
            else if(c=='M'){
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                    cout<<"Give the ID of the user"<<endl;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                int idp=0;
                while(idp!=1&&idp!=2&&idp!=3)
                {
                    cin.exceptions(ios_base::failbit);
                    try{
                         cout<<"Give the privileges ID (1 or 2 or 3)"<<endl;
                        cin>>idp;
                    }catch(const ios_base::failure& e){
                        cout<<"What are you doing??"<<endl;
                    }
                }
                object->change_user_category(id,idp);
            }
            else if(c=='D'){
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                     cout<<"Give the ID of the user "<<endl;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                if(id!=visitor.GetID())
                object->delete_user(id);
                else{
                    err=-1;
                    error_info="You can't delete yourself!";
                }
            }
            else if(c=='U'){
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                    cout<<"Give the ID of the user"<<endl;

                     cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                cout<<"Give a username"<<endl;
                string n;
                bool state=true;
                while(state==true){
                cin>>n;
                if(n.length()<=MAXUSERNAMESIZE&&n.length()>=1)
                    state=false;
                else{
                    cout<<"Username must be 1-"<<MAXUSERNAMESIZE<<" characters!"<<endl;
                    cout<<"Give a username"<<endl;}

                }
                object->change_user_username(id,n);

            }
            else if(c=='P')
            {
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                     cout<<"Give the ID of the user"<<endl;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                cout<<"Give a password"<<endl;
                string pw;
                bool state=true;
                while(state==true){
                cin>>pw;
                if(pw.length()<=MAXPASSWORDSIZE&&pw.length()>=1)
                    state=false;
                else{
                    cout<<"Password must be 1-"<<MAXPASSWORDSIZE<<" characters!"<<endl;
                    cout<<"Give a password"<<endl;}
                }
                object->change_user_password(id,pw);
            }
            else if(c=='I'){
                BasicObject* ob=object->find_forum(a);
                if(ob!=NULL)
                    object->visit(visitor,1,close,ob,home,del,syst);
                if(!close)//if bool close is not true then don't close the program
                {
                    visitor.Setposition(0);//position of the user must be 0 again
                    if(del)//if delete is true then delete the forum of the id you visited
                    {
                        object->delete_forum(a);
                        del=false;
                    }
                    home=false;// make home false so that in the recursive calls home option can be used again
                }
                else{
                    return;
                }
            }
        }
    }
    else if(pos==1){//in forum
        while(visitor.Getposition()==1){
            cout << string( 100, '\n' );
            if(err==-1){//again if there is an error print it
                cout<<"\n";
                cout<<error_info<<endl;
                err=0;
            }
            cout<<"You are in forum : "<<object->Getname()<<endl;
            cout<<"Available subforums : "<<endl;
            object->show_forums();
            cout<<"Available threads : "<<endl;
            object->show_threads(syst);
            cout<<"\n";
            int p;
            c=visitor.print_options(p);
            if(c=='F'){
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                    cout<<"Give forum ID : "<<endl;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                BasicObject* ob=object->find_forum(id);
                if(ob!=NULL)
                object->visit(visitor,1,close,ob,home,del,syst);//recursive call of visit with a basic object pointer to a forum
                if(!close)
                {
                    visitor.Setposition(1);
                    if(home)
                    {
                        return;
                    }
                    if(del){
                        object->delete_forum(id);
                        del=false;
                    }
                }else{
                    return;
                }
            }
            else if(c=='T'){
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                    cout<<"Give thread ID : "<<endl;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                BasicObject* ob=object->find_thread(id);
                if(ob!=NULL){
                    object->visit(visitor,2,close,ob,home,del,syst);//recursive call of visit with a basic object pointer to a thread
                }
                if(!close)
                {
                    visitor.Setposition(1);
                    if(del){
                        object->delete_thread(id);
                        del=false;
                    }
                    if(home)
                    {
                        return;
                    }

                }
                else{
                    return;
                }
            }
            else if(c=='B'){
                return;
            }
            else if(c=='C'){
                getchar();
                string n,c;
                cout<<"Give thread title : "<<endl;
                bool state=true;
                while(state==true){
                 getline(cin,n);
                if(n.length()<=MAXTHREADTITLESIZE&&n.length()>=1)
                    state=false;
                else{
                    cout<<"Threadtitle must be 1-"<<MAXTHREADTITLESIZE<<" characters!"<<endl;
                    cout<<"Give thread title : "<<endl;}
                }

                cout<<"Give first post : "<<endl;
                state=true;
                while(state==true){
                getline(cin,c);
                cout<<c<<endl;
                if(c.length()<=MAXPOSTSIZE&&c.length()>=1)
                    state=false;
                else{
                    cout<<"Post size must be 1-"<<MAXPOSTSIZE<<" characters!"<<endl;
                    cout<<"Give first post : "<<endl;}
                }
                object->add_thread(n,visitor.GetID(),c);
            }
            else if(c=='H'){
                home=true;
                return;
            }
            else if(c=='L'){
                syst.save();
                 close=true;
                return;
            }
            else if(c=='X'){
                 close=true;
                return;
            }
            else if(c=='N'){
                cout<<"Give a name for the forum"<<endl;
                string n;
                getchar();
                getline(cin,n);
                object->add_forum(n);
            }
            else if(c=='E'){
                cout<<"Give new title : "<<endl;
                string t;
                getchar();
                getline(cin,t);
                object->Setname(t);
            }
            else if(c=='D'){
                del=true;
                return;
            }
            else if(c=='M'){
                cout<<"Give path : "<<endl;
                string path;
                getchar();
                getline(cin,path);
                cout<<path<<endl;
                err=syst.move_forum(object->ret_forum(),path);
                if(err!=-1){
                    del=true;
                    return;
                }
                else
                    error_info="Wrong path!";
            }
        }
    }
    else if(pos==2){//THREAD
        while(visitor.Getposition()==2){
            cout << string( 100, '\n' );
            if(err==-1){
                cout<<error_info<<endl;
                err=0;
            }
            cout<<"You are in thread : "<< object->Getname() <<endl;
            cout<<"Posts : \n"<<endl;
            object->show_posts(syst);
            int p;
            c=visitor.print_options(p);
            getchar();
            if(c=='B'){
                return;
            }
            else if(c=='R'){
                if(!object->is_locked())
                {
                    string c;
                    cout<<"Type post : "<<endl;
                    bool state=true;
                     while(state==true){
                getline(cin,c);
                if(c.length()<=MAXPOSTSIZE&&c.length()>=1)
                    state=false;
                else{
                    cout<<"Post size must be 1-"<<MAXPOSTSIZE<<" characters!"<<endl;
                    cout<<"Type post : "<<endl;}
                }
                    object->add_post(visitor.GetID(),c);
                }
                else{
                    err=-1;
                    error_info="Thread is locked. You can't respond in this thread.";
                }
            }
            else if(c=='H'){
                home=true;
                return;
            }
            else if(c=='L'){
                syst.save();
                close=true;
                return;
            }
            else if(c=='X'){
                //
                close=true;
                return;
            }
            else if(c=='D'){
                del=true;
                return;
            }
            else if(c=='M'){
                //move
                cout<<"Give path "<<endl;
                string path;
                getline(cin,path);
                err=syst.move_thread(object->ret_thread(),path);
                if(err!=-1){
                    del=true;
                    return;
                }
                else{
                    error_info="Wrong path!";
                }
            }
            else if(c=='E'){
                string t;
                cout<<"Give new title : "<<endl;
                getchar();
                bool state=true;
                while(state==true){
                getline(cin,t);
                if(t.length()<=MAXTHREADTITLESIZE&&t.length()>=1)
                    state=false;
                else{
                    cout<<"Thread title size must be 1-"<<MAXTHREADTITLESIZE<<" characters!"<<endl;
                    cout<<"Give new title : "<<endl;}
                }
                object->Setname(t);
            }
            else if(c=='Y'){
                cout<<"S for sticky/N for not sticky"<<endl;
                string t;
                cin>>t;
                if(t=="S")
                    object->set_sticky(true);
                else if(t=="N")
                    object->set_sticky(false);
                else{
                    err=-1;
                    error_info="Wrong input!";
                }
            }
            else if(c=='K'){
                cout<<"L for lock/U for unlock"<<endl;
                string t;
                cin>>t;
                if(t=="L")
                    object->set_locked(true);
                else if(t=="U")
                    object->set_locked(false);
                else{
                    err=-1;
                    error_info="Wrong input!";
                }
            }
            else if(c=='A'){
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                    cout<<"Give post id"<<endl;;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                object->delete_post(id);
            }
            else if(c=='S'){
                cout<<"Give path "<<endl;
                string path;
                getline(cin,path);
                int id;
                cin.exceptions(ios_base::failbit);
                try{
                    cout<<"Give id"<<endl;
                    cin>>id;
                }catch(const ios_base::failure& e){
                    cout<<"What are you doing??"<<endl;
                }
                err=syst.move_post(*object->find_post(id),path);
                if(err!=-1)
                    object->delete_post(id);
                else{
                    error_info="Wrong path!";
                }
            }
        }
    }
}
