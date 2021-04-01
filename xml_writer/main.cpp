#include "announce_xml.h"
#include "abstract_command.h"
//
// Created by whits on 3/26/2021.
//

//namespace pt_lib = boost::property_tree;

using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

void DERCommandTest(); // prototypes of testing functions
void XMLAdapterTest();

int main()
{
    announcer::CTA2045ToXMLAdapter XMLAdapter;
    //cout << "WTF IS GOING ON" << endl;
    cout<<"why won't this work"<<endl;

    //XMLAdapter.GenerateTestFile();
    //XMLAdapter.ReadTestFile();
    DERCommandTest();
}
void XMLAdapterTest()
{

}
void DERCommandTest()
{
    cout<<"dercommandTest creating command object..."<<endl;
    announcer::DERCommand command;
    cout<<"now testing..."<<endl;
    command.testing();
    command.makeShed();
    cout<<"test over"<<endl;
}