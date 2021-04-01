#include "announce_xml.h"
#include "abstract_command.h"


//namespacing for this file
using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

const string MSG_LOG_PATH = "../../msg_logs/dtm_messages_testing.txt"; //path to msg log

void InterfaceCommandTest(); // prototypes of testing functions
void XMLAdapterTest();

int main()
{
    cout<<"     TESTING i     "<<endl;
    XMLAdapterTest();
    //InterfaceCommandTest();
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
void InterfaceCommandTest()
{
    cout<<"InterfaceCommandTest creating command object..."<<endl;
    announcer::InterfaceCommand command;
    cout<<"now testing..."<<endl;
    cout << " NOW ADD LINES" << endl;
    cout<<"test over"<<endl;
}