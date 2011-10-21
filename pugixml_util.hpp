#ifndef ___PUGI_XML_UTIL__HPP___
#define ___PUGI_XML_UTIL__HPP___

inline void insert_node(pugi::xpath_node xp_node, string xml) {
    pugi::xml_document temp;
    temp.load(xml.c_str());
    pugi::xml_node temp_node = temp.select_single_node("/*").node();
    pugi::xml_node result;
    result = xp_node.node().append_copy(temp_node);
    if(!result) {
        throw std::runtime_error("Error inserting node: '" + xml + "'");
    }
}

#endif
