#include <iostream>
#include "parse_xml_attrs.hpp"
using namespace std;

int main() {
    int a1;
    string a2;
    double a3;

    options_description test;
    test.add_options()
        ("my_int", value<int>(&a1)->default_value(100))
        ("my_double", value<double>(&a3)->default_value(10.5))
        ("my_string", value<string>(&a2)->default_value("Goodbye cruel world!"));
    variables_map vm;

    string test_xml = "<blah my_int=\"42\" my_double=\"132.39\" />";
    pugi::xml_document doc;
    doc.load(test_xml.c_str());
    
    store(parse_xml_attrs(test, doc.select_single_node("/blah").node()), vm);
    notify(vm);

    cout << a1 << endl;
    cout << a2 << endl;
    cout << a3 << endl;

    return 0;
}
