#pragma once

#include <cassert>
#include <iostream>
#include <string>

// Фреймворк юнит-теста

void AssertImpl(bool value, const std::string& expr_str, const std::string& file, const std::string& func, unsigned line,
                const std::string& hint);

#define ASSERT(expr) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_HINT(expr, hint) AssertImpl(!!(expr), #expr, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename T, typename U>
void AssertEqualImpl(const T& t, const U& u, const std::string& t_str, const std::string& u_str, const std::string& file,
                     const std::string& func, unsigned line, const std::string& hint) {
    using namespace std;
    if (t != u) {
        cerr << boolalpha;
        cerr << file << "("s << line << "): "s << func << ": "s;
        cerr << "ASSERT_EQUAL("s << t_str << ", "s << u_str << ") failed: "s;
        cerr << t << " != "s << u << "."s;
        if (!hint.empty()) {
            cerr << " Hint: "s << hint;
        }
        cerr << endl;
        abort();
    }
}

#define ASSERT_EQUAL(a, b) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, ""s)

#define ASSERT_EQUAL_HINT(a, b, hint) AssertEqualImpl((a), (b), #a, #b, __FILE__, __FUNCTION__, __LINE__, (hint))

template <typename T>
void RunTestImpl( const T& t, const std::string& func_name ){
    using namespace std;
    t();
    cerr << func_name << " OK"s << endl;
}

#define RUN_TEST(func) RunTestImpl((func), (#func))

template <typename T>
void RunUTestImpl( const T& t, const std::string& func_brief ){
    using namespace std;
    cerr << "Запуск теста: \""s << func_brief << "\""s << endl;
    t();
}

#define RUN_TEST_MODULE(module, brief) RunUTestImpl((module), (brief))

#include <vector>
#include <fstream>

namespace UTEST {
namespace TOOL {

std::vector<std::string> BigDataLoad( const char* filename );

} // namespace TOOL
} // namespace UTEST
