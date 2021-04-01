#include "announce_xml.h"
//
// Created by Whitman on 3/25/2021.
//
using std::cout;
using std::endl;
using std::string;
namespace pt = boost::property_tree;

namespace dcm_src //in dcm_src namespace, covering code meant to run on dcm
{
namespace xml
{
//----------------------------------------------------------------------------------------------------------
//                         Implementation of XMLCommandAdapter Class
//----------------------------------------------------------------------------------------------------------
XMLCommandAdapter::~XMLCommandAdapter()
{}

void XMLCommandAdapter::GenerateTestFile()
{
    cout << "Generate Test File" << endl;
    cout << "Test file name: " << test_file_name_ << endl;

    tree_.put("debug.filename", test_file_name_);
    tree_.put("debug.level", 3);
    tree_.add("debug.modules.module", "there");

    pt::write_xml(test_file_name_, tree_);
}
void XMLCommandAdapter::GenerateNamedTestFile(string src)
{
    cout << "Generate Named Testfile" << endl;
    cout << "Test file name: " << src << endl;

    tree_.put("CREATED.date", "4/1/2021");
    pt::write_xml(src, tree_);
}

void XMLCommandAdapter::ReadTestFile()
{
    cout<<"read"<<endl;
    std::stringstream string_xml; //stringstream
    pt::read_xml(test_file_name_, tree_); //read

    pt::write_xml(string_xml, tree_); //write to stream
    cout << string_xml.str() <<endl; //output string version of stream
     /*
    std::ifstream f("test_file.xml");
    std::stringstream buffer;
    buffer << f.rdbuf();
    cout << "string: " << buffer.str() <<endl;
     */
}
void XMLCommandAdapter::AppendTreeToTestLog(std::string log_path)
{
    std::stringstream ss; //string stream
    std::ofstream file(log_path, std::ios::app); //open file stream in append mode
    pt::write_xml(ss, tree_); //write xml tree to string stream
    file << endl << endl; //add line breaks after prev entry
    file << ss.str(); //write stringstream (containing xml tree) to file
    file.close(); //close file
}
void XMLCommandAdapter::OutputTreeToTerminal()
{
    std::stringstream ss;
    pt::write_xml(ss, tree_); //write tree to stringstream
    cout << "TREE: " << endl << endl << ss.str() << endl << endl; //output string created by stringstream
}
void XMLCommandAdapter::Load()
{
    MakeCommand("LOAD");
}
void XMLCommandAdapter::Shed()
{
    MakeCommand("SHED");
}
void XMLCommandAdapter::MakeCommand(string type)
{
    float dur = 3.1415;
    std::time_t t = std::time(0);
    string str_time = ctime(&t);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);

    tree_.put("command.type", type);
    tree_.put("command.start", t);
    tree_.put("command.duration", dur);
    tree_.put("command.logged", std::time(0));
}

}//namespace xml
}//namespace dcm_src

