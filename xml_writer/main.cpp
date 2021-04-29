#include "announce_xml.h"
#include "abstract_command.h"
#include "https/https_client.hpp"


//namespacing for this file
using std::string;
using std::cout;
using std::endl;
namespace announcer = dcm_src::xml;

const string MSG_LOG_PATH = "../../msg_logs/dtm_messages_testing.xml"; //path to msg log

//void InterfaceCommandTest(); // prototypes of testing functions
void XMLAdapterTest();
void ClientTest();

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
    HttpsClient client("host.docker.internal", "8886");
    
    CommandIs.Shed();
    std::string empty = " ";
    std::string command = CommandIs.ReturnCommandAsStr();
    std::cout << client.Post(command) << std::endl;

    //what("http-client-async www.example.com 80 /");
    //std::make_shared<session>(ioc)->run(host, port, target, xml_str, version);
    //ioc.run();

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