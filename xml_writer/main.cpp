#include "announce_xml.h"
#include "abstract_command.h"


//namespacing for this file
using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

void DERCommandTest(); // prototypes of testing functions
void XMLAdapterTest();

int main()
{
    //announcer::CTA2045ToXMLAdapter XMLAdapter;
    //cout << "WTF IS GOING ON" << endl;

    cout<<"path test"<<endl;
    XMLAdapterTest();

    //XMLAdapter.GenerateTestFile();
    //XMLAdapter.ReadTestFile();

    announcer::CTA2045ToXMLAdapter XMLAdapter;
    //cout << "WTF IS GOING ON" << endl;
    cout<<"why won't this work"<<endl;

    //XMLAdapter.GenerateTestFile();
    //XMLAdapter.ReadTestFile();
    DERCommandTest();
}
void XMLAdapterTest()
{
    announcer::CTA2045ToXMLAdapter XMLAdapter;
    XMLAdapter.GenerateNamedTestFile("../../msg_logs/dtm_messages_testing.xml");

}
void DERCommandTest()
{
    cout<<"dercommandTest creating command object..."<<endl;
    announcer::DERCommand command;
    cout<<"now testing..."<<endl;
    command.testing();
    command.makeShed();
    cout << " NOW ADD LINES" << endl;
    command.appendTreeToTestFile();
    cout<<"test over"<<endl;
}