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
//----------------------------------------------------------------------------------------------------------
//                         Implementation of CTA2045ToXMLAdapter Class
//----------------------------------------------------------------------------------------------------------
CTA2045ToXMLAdapter::~CTA2045ToXMLAdapter()
{}
void CTA2045ToXMLAdapter::GenerateTestFile()
{
    cout << "Generate Test File" <<endl;
    cout << "Test file name: " << test_file_name_ << endl;
    pt::ptree tree; //create xml tree object

    tree.put("debug.filename", test_file_name_);
    tree.put("debug.level", 3);

    tree.add("debug.modules.module", "here");

    pt::write_xml(test_file_name_, tree);
}


}//namespace dcm_src

