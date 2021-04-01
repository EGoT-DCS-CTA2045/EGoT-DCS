#include "announce_xml.h"
#include "abstract_command.h"
<<<<<<< HEAD
=======
//
// Created by whits on 3/26/2021.
//

//namespace pt_lib = boost::property_tree;
>>>>>>> dc481bf655327a3fb8c47186775278b609baca32

//namespacing for this file
using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

void DERCommandTest(); // prototypes of testing functions
void XMLAdapterTest();

int main()
{
<<<<<<< HEAD
    //announcer::CTA2045ToXMLAdapter XMLAdapter;
    //cout << "WTF IS GOING ON" << endl;

    cout<<"path test"<<endl;
    XMLAdapterTest();

    //XMLAdapter.GenerateTestFile();
    //XMLAdapter.ReadTestFile();

=======
    announcer::CTA2045ToXMLAdapter XMLAdapter;
    //cout << "WTF IS GOING ON" << endl;
    cout<<"why won't this work"<<endl;

    //XMLAdapter.GenerateTestFile();
    //XMLAdapter.ReadTestFile();
>>>>>>> dc481bf655327a3fb8c47186775278b609baca32
    DERCommandTest();
}
void XMLAdapterTest()
{
<<<<<<< HEAD
    announcer::CTA2045ToXMLAdapter XMLAdapter;
    XMLAdapter.GenerateNamedTestFile("../../msg_logs/dtm_messages_testing.xml");
=======

>>>>>>> dc481bf655327a3fb8c47186775278b609baca32
}
void DERCommandTest()
{
    cout<<"dercommandTest creating command object..."<<endl;
    announcer::DERCommand command;
    cout<<"now testing..."<<endl;
    command.testing();
    command.makeShed();
<<<<<<< HEAD
    cout << " NOW ADD LINES" << endl;
    command.appendTreeToTestFile();
=======
>>>>>>> dc481bf655327a3fb8c47186775278b609baca32
    cout<<"test over"<<endl;
}