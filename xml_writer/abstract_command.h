#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

#ifndef EGOT_DCS_CTA2045_ABSTRACT_COMMAND_H
#define EGOT_DCS_CTA2045_ABSTRACT_COMMAND_H

#endif //EGOT_DCS_CTA2045_ABSTRACT_COMMAND_H

namespace dcm_src
{
namespace xml
{
/* -------------------------------------------------------------------
 * This is an individual command for a DER. It is represented
 * as a class because these commands are used as an abstracted
 * representation of instructions for the DER at multiple points
 * throughout the DCM architecture.
 * -------------------------------------------------------------------
 */
class DERCommand {
    public:
        DERCommand();
        DERCommand(const DERCommand &);
        DERCommand & operator = (const DERCommand &);
        ~DERCommand();
        std::string Str()
        {
            return command_;
        }
        void testing();
        void makeShed();
        void outputTreeToTerminal();
        void appendTreeToTestFile();

    private:
        std::string command_;
        boost::property_tree::ptree tree_;
};


}//namespace xml
}//namespace dcm_src