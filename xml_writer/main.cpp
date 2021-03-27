#include "announce_xml.h"
//
// Created by whits on 3/26/2021.
//

//namespace pt_lib = boost::property_tree;

using std::string;
using std::cout;
using std::endl;

int main()
{
    dcm_src::CTA2045ToXMLAdapter XMLVersionOfCommand;
    cout << "HELLO WORLD" << endl;

    XMLVersionOfCommand.GenerateTestFile();
}