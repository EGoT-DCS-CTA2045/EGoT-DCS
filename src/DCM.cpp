#include <iostream>
#include <cstring>
#include "CTA2045Translator.h"

using namespace std;

int main(int argc, char * argv[])
{
    char port[20];// used to hold the port
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
    return 0;
}
