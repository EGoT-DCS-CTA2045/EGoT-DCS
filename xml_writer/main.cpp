#include "announce_xml.h"
#include "abstract_command.h"
#include "https/include/https/https_client.hpp"

//namespacing for this file
using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

const string MSG_LOG_PATH = "../../msg_logs/dtm_messages_testing.xml"; //path to msg log

//void InterfaceCommandTest(); // prototypes of testing functions
void XMLAdapterTest();

int main()
{
    cout<<"     TESTING X     "<<endl;
    //XMLAdapterTest();
    //InterfaceCommandTest();
    ClientTest();
}
void ClientTest()
{
    announcer::XMLCommandAdapter CommandIs;
    std::cout << "http Client test" << std::endl;
    HttpsClient client("localhost", "8886");
    
    CommandIs.Shed();
    std::cout << client.POST("", CommandIs.ReturnCommandAsStr()) << std::endl;

}
void XMLAdapterTest()
{
    cout << "XMLADAPTER TEST " << endl;
    announcer::XMLCommandAdapter CommandIs;
    //CommandIs.GenerateNamedTestFile(MSG_LOG_PATH);
    //CommandIs.Load();
    CommandIs.Shed();
    //CommandIs.OutputTreeToTerminal();
    CommandIs.AppendTreeToTestLog(MSG_LOG_PATH);

}
/*
void InterfaceCommandTest()
{
    cout<<"InterfaceCommandTest creating command object..."<<endl;
    announcer::InterfaceCommand command;
    cout<<"now testing..."<<endl;
    cout << " NOW ADD LINES" << endl;
    cout<<"test over"<<endl;
}
 */