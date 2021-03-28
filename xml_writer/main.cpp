#include "announce_xml.h"
//
// Created by whits on 3/26/2021.
//

//namespace pt_lib = boost::property_tree;

using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

int main()
{
    announcer::CTA2045ToXMLAdapter XMLAdapter;
    cout << "WTF IS GOING ON" << endl;

    //XMLAdapter.GenerateTestFile();
    XMLAdapter.ReadTestFile();
}