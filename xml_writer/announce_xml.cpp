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
//                         Implementation of CTA2045ToXMLAdapter Class
//----------------------------------------------------------------------------------------------------------
CTA2045ToXMLAdapter::~CTA2045ToXMLAdapter()
{}

void CTA2045ToXMLAdapter::GenerateTestFile()
{
    cout << "Generate Test File" << endl;
    cout << "Test file name: " << test_file_name_ << endl;

    tree_.put("debug.filename", test_file_name_);
    tree_.put("debug.level", 3);

    tree_.add("debug.modules.module", "there");

    pt::write_xml(test_file_name_, tree_);
}

void CTA2045ToXMLAdapter::ReadTestFile()
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

}//namespace xml
}//namespace dcm_src

