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

class CTA2045ToXMLAdapter
{
    public:
        CTA2045ToXMLAdapter() : xml_notification_("NO DATA"), test_file_name_(testing_file_name)
        {}
        ~CTA2045ToXMLAdapter();
        void GenerateTestFile();
        void GenerateNamedTestFile(std::string src);
        void ReadTestFile();

    private:
        std::string xml_notification_;
        std::string test_file_name_;
        boost::property_tree::ptree tree_;
};

}//namespace xml
}// namespace dcm_src