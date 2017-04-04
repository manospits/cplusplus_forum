#include "../include/user.h"
#include <iostream>
#include "../include/privileges.h"
#include <string>
using namespace std;

user::user( string N="", string P="", int I=0, int PR=0 ):Name(N),ID(I),priv_ID(PR),priv(PR),position(0),Password(P)
{}
char user::print_options(int& id){
    char c;
    id=-1;
    while(true){
        if(position==0){//in system
            cout<<"Give the ID of the forum you want to visit"<<endl;
            cout<<"Press : "<<endl;
            priv.standard_prints();
            priv.print_system_options();
            cin>>c;
            if(c ==  'L' || c == 'X'|| c == 'N'|| c == 'U'|| c == 'C'|| c == 'M'|| c == 'D'|| c == 'P'||c=='I')
            {
                if( (c == 'N'|| c == 'U'|| c == 'C'|| c == 'M'|| c == 'D'|| c == 'P')&&priv_ID!=3){
                    cout<<"Wrong input!"<<endl;
                }
                else
                {
                    if( c == 'U' ){
                        priv.print_user_management_options();
                        priv.standard_prints();
                        cin>>c;
                        }
                    if(c=='I')
                    {
                        cin.exceptions(ios_base::failbit);
                        try{
                        cout<<"Give the ID : ";
                        cin>>id;
                        }
                        catch(const ios_base::failure& e) {
                            cout << "What?"<<endl;
                            break;
                        }
                    }
                        return c;
                }
            }
                //cout<<"Wrong input!"<<endl;
        }
        if(position==1){//in a forum
            priv.print_forum_options();
            priv.standard_prints();
            cin>>c;
            if(c == 'F'|| c == 'T'||c == 'B'||c == 'H'||c == 'L'||c == 'C'||c == 'X'||c == 'N'||c == 'E'||c == 'D'||c == 'M' ){
                if((c == 'N'||c == 'E'||c == 'D'||c == 'M')&&priv_ID!=3)
                    cout<<"Wrong inputs!"<<endl;
                else
                    return c;
            }
            else
                cout<<"Wrong input!"<<endl;
        }
        if(position==2){//in a thread
                priv.standard_prints();
                priv.print_thread_options();
                cin>>c;
                if(c == 'B'||c == 'R'||c == 'H'||c == 'L'||c == 'X'||c == 'D'||c == 'M'||c == 'E'||c == 'Y'||c == 'K'||c == 'A'||c == 'S'){
                    if((c == 'D'||c == 'M'||c == 'E'||c == 'Y'||c == 'K'||c == 'A'||c == 'S')&&(priv_ID=!2&&priv_ID!=3)){
                        cout<<"Wrong inputs! "<< c<<endl;
                    }
                    else
                        return c;
                }
                else
                cout<<"Wrong input!"<<endl;
        }
    }
}
void user::change_user_cat(int a){
    priv_ID=a;
    privileges temp(a);
    priv=temp;
}
void user::print_user_info(){
    cout<<"Username: "<< Name <<"\nID : "<< ID/*<<" password : "<<Password<<*/;
    cout<< "\nPrivileges : ";
    if (priv_ID==0){
        cout<<"Visitor"<<endl;
    }else if(priv_ID==1){
        cout<<"Registered user\n"<<endl;
    }
    else if(priv_ID==2){
        cout<<"Global moderator\n"<<endl;
    }
    else{
        cout<<"Administrator\n"<<endl;
    }
}
