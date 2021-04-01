#include "abstract_command.h"


using std::cout;
using std::endl;
using std::string;
namespace pt = boost::property_tree;

namespace dcm_src
{
namespace xml
{
/* --------------------------------------------------------------------
 *            Implementation of DERCommand
 * --------------------------------------------------------------------
 */
DERCommand::DERCommand(): command_(nullptr)
{}
DERCommand::DERCommand(const DERCommand & src)
{
        tree_ = src.tree_; //this is probably sketchy, no idea how = is overloaded for ptree
        command_ = src.command_;
}
DERCommand::~DERCommand()
{}
DERCommand & DERCommand::operator = (const DERCommand & src)
{
    if (this == &src)
    {
        return *this;
    }
    tree_ = src.tree_;
    command_ = src.command_;
    return *this;
}
string DERCommand::testing()
{
    cout<<"DERCOMMAND testing"<<endl;
}

}//namespace xml
}//namespace dcm_src

