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
    cout << "Append Tree" << endl;
    std::stringstream ss;
    pt::ptree file_tree;
    pt::read_xml(log_path, file_tree);
    OutputTreeToTerminal(file_tree);
    file_tree.push_back( std::make_pair("message_log", tree_ ) );
    cout << "Now Re-display" << endl;
    OutputTreeToTerminal(file_tree);
    /*
    std::stringstream ss; //string stream
    std::ofstream file(log_path, std::ios::app); //open file stream in append mode
    pt::write_xml(ss, tree_); //write xml tree to string stream
    file << endl << endl; //add line breaks after prev entry
    file << ss.str(); //write stringstream (containing xml tree) to file
    file.close(); //close file
     */

}
void XMLCommandAdapter::OutputTreeToTerminal()
{
    std::stringstream ss;
    //pt::write_xml(ss, tree_); //write tree to stringstream
    pt::write_xml(ss, tree_, pt::xml_writer_make_settings<std::string>(' ', 4)); //<- this works to format the tree nicely
    cout << "TREE: " << endl << endl << ss.str() << endl << endl; //output string created by stringstream
}
void XMLCommandAdapter::OutputTreeToTerminal(pt::ptree & src_tree)
{
    std::stringstream ss;
    //pt::write_xml(ss, tree_); //write tree to stringstream
    pt::write_xml(ss, src_tree, pt::xml_writer_make_settings<std::string>(' ', 4)); //<- this works to format the tree nicely
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
    float dur = 3.1415; //duration for testing
    std::time_t start_time = std::time(0);
    string str_time = ctime(&start_time);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);
    tree_.put("message.from", "DCM");
    tree_.put("message.to", "DER");
    tree_.put("message.content.command.type", type);
    tree_.put("message.content.command.start", start_time);
    tree_.put("message.content.command.duration", dur);
    tree_.put("message.content.expect_response", 1);
    tree_.put("message.logged", std::time(0));
}

}//namespace xml
}//namespace dcm_src

