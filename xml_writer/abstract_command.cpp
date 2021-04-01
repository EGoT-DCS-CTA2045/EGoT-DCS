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
DERCommand::DERCommand(): command_("EMPTY"), tree_()
{}
DERCommand::DERCommand(const DERCommand & src)
{
    if(src.command_ != "EMPTY")
    {
        tree_ = src.tree_; // his is probably sketchy, no idea how = is overloaded for ptree
        command_ = src.command_;
    }
}
DERCommand::~DERCommand()
{
    cout<<"DERCommand DESTRUCTOR"<<endl;
}
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
void DERCommand::testing()
{
    cout<<"----------Testing----------------------"<<endl;
    tree_.put("command.type", command_);

    outputTree();
}
void DERCommand::makeShed()
{
    float dur = 3.1415;
    std::time_t t = std::time(0);
    string str_time = ctime(&t);
    //std::tm* gmtm = gmtime(&t);
    //std::string str_time = std::asctime(gmtm);
    cout<<"---------MAKE SHED---------------------"<<endl;
    command_ = "SHED";
    tree_.put("command.type", command_);
    tree_.put("command.start", str_time);
    tree_.put("command.duration", dur);
    tree_.put("command.logged", std::time(0));

    outputTree();
}
void DERCommand::outputTree()
{
    std::stringstream ss;
    pt::write_xml(ss, tree_); //write tree to stringstream
    cout << "TREE: " << endl << endl << ss.str() << endl << endl; //output string created by stringstream
}

}//namespace xml
}//namespace dcm_src

