#include "../include/privileges.h"
#include <iostream>
using namespace std;

privileges::privileges(int val)
{
    if (val == 0){
        read=true;
        crthread=false;
        respond=false;
        thrmanage=false;
        mksticky=false;
        lock=false;
        crforum=false;
        delforum=false;
        mvforum=false;
        rnforum=false;
        mvuser=false;
        chuname=false;
        chuserpassw=false;
    }else if(val == 1){
        read=true;
        crthread=true;
        respond=true;
        thrmanage=false;
        mksticky=false;
        lock=false;
        crforum=false;
        delforum=false;
        mvforum=false;
        rnforum=false;
        mvuser=false;
        chuname=false;
        chuserpassw=false;
    }else if(val == 2){
        read=true;
        crthread=true;
        respond=true;
        thrmanage=false;
        mksticky=true;
        lock=true;
        crforum=false;
        delforum=false;
        mvforum=false;
        rnforum=false;
        mvuser=false;
        chuname=false;
        chuserpassw=false;
    }else {

        read=true;
        crthread=true;
        respond=true;
        thrmanage=true;
        mksticky=true;
        lock=true;
        crforum=true;
        delforum=true;
        mvforum=true;
        rnforum=true;
        mvuser=true;
        chuname=true;
        chuserpassw=true;
    }

}
void privileges::print_system_options(){
    cout<<"I for selecting the ID"<<endl;
    if(crforum){
        cout<<"N for creating a new forum."<<endl;
        cout<<"U for user management."<<endl;
    }
}
void privileges::print_user_management_options(){

    if(mvuser){
        cout<<"C for viewing user's catalog"<<endl;
        cout<<"M for changing a user's privileges"<<endl;
        cout<<"D for deleting a user"<<endl;
    }
    if(chuname){
        cout<<"U for changing a user's name"<<endl;
    }
    if(chuserpassw){
        cout<<"P for changing a user's password"<<endl;
    }
}
void privileges::standard_prints(){
    cout<<"L for closing with saving."<<endl;
    cout<<"X for closing without saving."<<endl;
}
void privileges::print_forum_options(){
    if(read){
        cout<<"F for visiting a forum of the above."<<endl;
        cout<<"T for visiting a thread of the above."<<endl;
        cout<<"B for going a level up in the system."<<endl;
        cout<<"H for going Home"<<endl;
     }
    if(crthread){
        cout<<"C for creating a new thread."<<endl;
    }
    if(crforum)
    {
         cout<<"N for creating a new forum."<<endl;
    }
    if(thrmanage)
    {
        cout<<"E for changing the title of this forum."<<endl;
        cout<<"D for deleting this forum."<<endl;
        cout<<"M fot moving this forum."<<endl;
    }

}
void privileges::print_thread_options(){
    if(read){
        cout<<"B for going up a level in the system."<<endl;
        cout<<"H for returning home."<<endl;
    }
    if(respond){
        cout<<"R for responding in the thread."<<endl;
    }
    if(thrmanage){
        cout<<"D for deleting thread."<<endl;
        cout<<"M for moving this thread."<<endl;
        cout<<"E for changing this thread's title."<<endl;
        cout<<"A for deleting a post."<<endl;
        cout<<"S for moving a post."<<endl;
    }
    if(mksticky){
        cout<<"Y for making this thread sticky/not sticky."<<endl;
    }
    if(lock){
        cout<<"K for locking/unlocking this thread."<<endl;
    }
}
