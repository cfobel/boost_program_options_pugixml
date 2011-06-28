#include <boost/program_options.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <iostream>
#include "parse_xml_attrs.hpp"
namespace po = boost::program_options;
using namespace boost;
using namespace std;


void print_options(const options_description& desc) {
    set<string> allowed_options = po::get_allowed_options(desc);
    cerr << "Accepted attributes:" << endl;
    BOOST_FOREACH(string const &o, allowed_options) {
        cerr << "    " << o << endl;
    }
}

int main(int argc, char** argv) {
    int a1;
    string a2;
    double a3;

    options_description test;
    test.add_options()
        ("my_int", value<int>(&a1)->default_value(100))
        ("my_double", value<double>(&a3)->default_value(10.5))
        ("my_string", value<string>(&a2)->default_value("Goodbye cruel world!"));
    variables_map vm;

    if(argc != 2) {
        cerr << "Usage: " << endl << "  " << argv[0]
            << " <XML_TAG [attr1=\"value1\" [attr2=\"value2\"]...>" << endl
            << "where attr? is one of the ";
        print_options(test);
        cerr << endl << "Example:" << endl 
            << "  <blah my_int=\"42\" my_double=\"132.39\" />" 
            << endl;
        exit(-1);
    }
    string test_xml(argv[1]); //"<blah my_int=\"42\" my_double=\"132.39\" other=\"blah\" />";
    //string test_xml = "<blah my_int=\"42\" my_double=\"132.39\" other=\"blah\" />";
    pugi::xml_document doc;
    doc.load(test_xml.c_str());
    
    try {
        store(parse_xml_attrs(test, doc.select_single_node("/*").node()), vm);
    } catch(po::unknown_option &e) {
        print_options(test);
        throw e;
    }
    notify(vm);

    cout << a1 << endl;
    cout << a2 << endl;
    cout << a3 << endl;

    return 0;
}
