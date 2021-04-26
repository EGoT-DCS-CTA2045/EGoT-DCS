#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

//
// Created by Whitman on 3/25/2021.
//

#ifndef EGOT_DCS_CTA2045_ANNOUNCE_XML_H
#define EGOT_DCS_CTA2045_ANNOUNCE_XML_H

#endif //EGOT_DCS_CTA2045_ANNOUNCE_XML_H

namespace dcm_src
{
namespace xml
{
/* -------------------------------------------------------------------
 * This class creates xml strings to be sent to the DTM
 * via an http POST. The xml strings are notifications
 * of the CTA-2045 commands that are being sent to the DER.
 * -------------------------------------------------------------------
 */
const std::string testing_file_name = "test_file.xml";

class XMLCommandAdapter
{
    public:
        XMLCommandAdapter() : xml_notification_("NO DATA"), test_file_name_(testing_file_name)
        {}
        ~XMLCommandAdapter();
        void GenerateTestFile();
        void GenerateNamedTestFile(std::string src);
        void ReadTestFile();
        void AppendTreeToTestLog(std::string log_path);
        void OutputTreeToTerminal();
        void OutputTreeToTerminal(boost::property_tree::ptree & src_tree);
        void Load();
        void Shed();
        void MakeCommand(std::string type);
        std::string ReturnCommandAsStr()
        {
            std::stringstream ss;
            pt::write_xml(ss, tree_, boost::property_tree::xml_writer_make_settings<std::string>(' ', 4));
            return ss.str();
        }

    private:
        std::string xml_notification_;
        std::string test_file_name_;
        boost::property_tree::ptree tree_;
};

}//namespace xml
}// namespace dcm_src