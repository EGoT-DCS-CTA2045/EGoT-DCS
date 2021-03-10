#include <iostream>
#include <string>
#include "CTA2045Translator.h"

using namespace std;

int main(int argc, char * argv[])
{
    int sz = 20;
    char port[sz];// used to hold the port
    int c=-1;
    bool ret = false;
    char prompt[] = "enter:\n0-\texist\n1-\tshed\n2-\tendshed\n3-\tloadup\nINPUT: ";
    // check args length
    if (argc < 2)
    {
        cout<<"INVALID USE"<<endl;
        exit(1);
    }
    // copy to the length of port
    strncpy(port,argv[1],sz-2);
    // add EOX char
    port[sz-1] = '\0'; // translator does that already
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
                ret = tr.shed();
                cout<<"RETURN: "<<ret<<endl;
                break;
            case 2:
                ret = tr.endshed();
                cout<<"RETURN: "<<ret<<endl;
                break;
            case 3:
                ret = tr.loadup();
                cout<<"RETURN: "<<ret<<endl;
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
