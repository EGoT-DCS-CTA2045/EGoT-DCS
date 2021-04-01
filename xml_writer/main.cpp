#include "announce_xml.h"
#include "abstract_command.h"


//namespacing for this file
using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

const string MSG_LOG_PATH = "../../msg_logs/dtm_messages_testing.txt"; //path to msg log

void DERCommandTest(); // prototypes of testing functions
void XMLAdapterTest();

int main()
{
    cout<<"     TESTING      "<<endl;
    XMLAdapterTest();
    //DERCommandTest();
}
void XMLAdapterTest()
{
    announcer::XMLCommandAdapter CommandIs;
    //CommandIs.GenerateNamedTestFile(MSG_LOG_PATH);
    CommandIs.Load();
    CommandIs.Shed();
    CommandIs.OutputTreeToTerminal();
    CommandIs.AppendTreeToTestLog(MSG_LOG_PATH);

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