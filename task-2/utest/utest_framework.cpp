#include "utest_framework.hpp"

using namespace std;

void AssertImpl(bool value, const string& expr_str, const string& file, const string& func, unsigned line,
                const string& hint) {
    if (!value) {
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT("s << expr_str << ") failed."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

std::vector<std::string> UTEST::TOOL::BigDataLoad( const char* filename ){
    std::vector<std::string> data_list;
    std::ifstream data_hndl( filename, std::ios::in ) ;
    if ( data_hndl.is_open() ){
        std::string line;
        while ( std::getline(data_hndl, line) ){
            data_list.push_back( std::move(line) );
        }
    }
    return data_list;
}
