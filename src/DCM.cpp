#include <iostream>
#include <cstring>
#include "CTA2045Translator.h"

using namespace std;

int main(int argc, char * argv[])
{
    char port[20];// used to hold the port
    int c=-1;
    char prompt[] = "enter:\n0-\texist\n1-\tshed\n2-\tendshed\n3-\tloadup\nINPUT: ";
    // check args length
    if (argc < 2)
    {
        cout<<"INVALID USE"<<endl;
        exit(1);
    }
    // copy to the length of port
    strncpy(port,argv[1],sizeof(port)-1);
    // add EOX char
    port[sizeof(port)-1] = '\0'; // translator does that already
    cout<<port<<endl;
    CTA2045Translator tr(port);
    tr.connect();
    while(c!=0){
        cout<<prompt;
        cin>>c;
        switch(c){
            case 0:
                c = 0;
                continue;
            case 1:
                tr.shed();
                break;
            case 2:
                tr.endshed();
                break;
            case 3:
                tr.loadup();
                break;
            default:
                cout<<"INCORRECT choice\n";
                cin.clear();
                break;
        }
        c = -1;
    }
    
    return 0;
}
