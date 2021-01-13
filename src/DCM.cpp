#include <iostream>
#include <cstring>
#include "DCMImpl.h"
#include "easylogging++.h"

using namespace std;
INITIALIZE_EASYLOGGINGPP 

int main(int argc, char * argv[])
{
    char port[20];// used to hold the port
    DCMImpl *trans;
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
    trans = new CTA2045Translator(port); // implicit type coercion
    //     
    delete trans;
}
