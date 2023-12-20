//#define LOCAL_TEST
//#undef LOCAL_DEBUG

#include <iostream>
#include <sstream>

#ifdef LOCAL_TEST
#include <fstream>
#endif // LOCAL_TEST

#include "domain-checker.hpp"

std::vector<Domain> ReadDomains( std::istream& input, size_t cnt_domains );

std::vector<Domain> ReadDomains( std::istream& input, size_t cnt_domains ){
    std::vector<Domain> result;
    std::string str_line;

    for ( size_t n_domain = 0; n_domain < cnt_domains; ++n_domain ){
        getline( input, str_line );
        result.push_back( Domain(move(str_line)) );
    }

    return result;
}

template <typename Number>
Number ReadNumberOnLine(std::istream& input) {
    std::string line;
    getline(input, line);

    Number num;
    std::istringstream(line) >> num;

    return num;
}

int main() {
    using namespace std::literals;
    #ifdef LOCAL_DEBUG

    #ifdef LOCAL_J
    if (std::freopen("./utest/input.txt", "r", stdin) == nullptr) {
        std::puts("can't open input.txt");
        return 1;
    }
    if (std::freopen("./utest/output.txt", "w", stdout) == nullptr) {
        std::puts("can't open output.txt");
        return 1;
    }
    #endif // LOCAL_J

    #ifdef LOCAL_H
    if (std::freopen("./utest/input.txt", "r", stdin) == nullptr) {
        std::puts("can't open input.txt");
        return 1;
    }
    if (std::freopen("./utest/output.txt", "w", stdout) == nullptr) {
        std::puts("can't open output.txt");
        return 1;
    }
    #endif // LOCAL_H
    #endif // LOCAL_DEBUG

    const std::vector<Domain> forbidden_domains = ReadDomains(std::cin, ReadNumberOnLine<size_t>(std::cin));

    // Формируем список запрещённых доменов
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    #ifdef LOCAL_TEST
    {
        std::vector<std::string> list_exp = checker.GetList();
        std::ofstream file_out;
        file_out.open( "./utest/forbidden_list.txt", std::ios::out );
        if ( file_out.is_open() ){
            for ( std::string str : list_exp ){
                file_out << str;
            }
        }
        file_out.close();
    }
    #endif // LOCAL_TEST

    // Формируем список проверяемых доменов
    const std::vector<Domain> test_domains = ReadDomains(std::cin, ReadNumberOnLine<size_t>(std::cin));

    #ifdef LOCAL_TEST
    size_t line = 0;
    #endif // LOCAL_TEST

    // Проверяем домены
    for (const Domain& domain : test_domains) {

        #ifdef LOCAL_TEST

        std::string domain_str( domain.GetDomainStr() );
        std::cout << "["sv << ++line << "]["sv << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << "] "sv
                  << domain_str << std::endl;

        #else

        std::cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << std::endl;

        #endif // LOCAL_TEST
    }


}
