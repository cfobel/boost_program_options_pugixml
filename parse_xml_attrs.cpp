#include "parse_xml_attrs.hpp"

namespace boost { namespace program_options {

const attrs_t get_node_attributes(pugi::xml_node const &node) {
    attrs_t attrs;

    pugi::xml_node::attribute_iterator b = node.attributes_begin();
    pugi::xml_node::attribute_iterator e = node.attributes_end();
    for(; b != e; b++) {
        attrs[b->name()] = b->value();
    }
    return attrs;
}

set<string> get_allowed_options(const options_description& desc) {
    using boost::shared_ptr;
    set<string> allowed_options;

    const vector<shared_ptr<option_description> >& options = desc.options();
    for (unsigned i = 0; i < options.size(); ++i) {
        const option_description& d = *options[i];

        if (d.long_name().empty())
            boost::throw_exception(
                error("long name required for config file"));

        allowed_options.insert(d.long_name());
    }
    return allowed_options;
}

basic_parsed_options<char>
parse_xml_attrs(const options_description& desc, pugi::xml_node const &node, bool allow_unregistered) {
    set<string> allowed_options = get_allowed_options(desc);

    // Parser return char strings
    parsed_options result(&desc);
    const attrs_t attrs = get_node_attributes(node);
    BOOST_FOREACH(attrs_t::value_type const &item, attrs) {
        if(allow_unregistered && allowed_options.count(item.first) == 0) continue;
        result.options.push_back(basic_option<char>(item.first, vector<string>(1, item.second)));
    }
    return basic_parsed_options<char>(result);
}

}}
