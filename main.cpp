#include <iostream>
#include "include/BasicObject.h"
#include "include/System.h"
#include "include/Forum.h"
#include <string>
#include <cstdio>

using namespace std;

int main(int argc,char* argv[])
{
    System s("DITLists");
    cout << string( 100, '\n' );
    if(argc==2){
        if(argv[1][0] == '-' && argv[1][1]=='R')
            s.operate(0);
        else
            cout << "Wrong arguments! Please check syntax" << endl;
    }
    else
        s.operate(1);
    return 0;
}


