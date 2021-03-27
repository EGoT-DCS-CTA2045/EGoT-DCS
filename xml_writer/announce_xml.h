#include <iostream>
#include <string>
//Boost libs
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
/* -------------------------------------------------------------------
 * This class creates xml strings to be sent to the DTM
 * via an http POST. The xml strings are notifications
 * of the CTA-2045 commands that are being sent to the DER.
 * -------------------------------------------------------------------
 */
class CTA2045ToXMLAdapter
{
    protected:
        std::string xml_notification_;
        std::string test_file_name_;
    public:
        CTA2045ToXMLAdapter(): xml_notification_("NO DATA"), test_file_name_("command_adapter_test_file.xml")
        {}
        ~CTA2045ToXMLAdapter();
        void GenerateTestFile();

};
}// namespace dcm_src