#ifndef ___PARSE_XML_ATTRS__HPP___
#define ___PARSE_XML_ATTRS__HPP___

#include <boost/program_options.hpp>
#include <boost/foreach.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>
#include <map>
#include "pugixml/pugixml.hpp"
using namespace std;
using namespace boost::program_options;


namespace boost { namespace program_options {
    typedef map<string, string> attrs_t;

    const attrs_t get_node_attributes(pugi::xml_node const &node);

    set<string> get_allowed_options(const options_description& desc);

    basic_parsed_options<char>
    parse_xml_attrs(const options_description& desc, pugi::xml_node const &node, bool allow_unregistered=true);
}}

#endif
