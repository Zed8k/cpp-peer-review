//#undef LOCAL_DEBUG

#include <iostream>
#include <sstream>

#ifdef LOCAL_DEBUG
#include "utest/utest.hpp"
#endif // LOCAL_DEBUG

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

    UTEST::RunUTestBoxes();

    #else

    const std::vector<Domain> forbidden_domains = ReadDomains(std::cin, ReadNumberOnLine<size_t>(std::cin));

    // Формируем список запрещённых доменов
    DomainChecker checker(forbidden_domains.begin(), forbidden_domains.end());

    // Формируем список проверяемых доменов
    const std::vector<Domain> test_domains = ReadDomains(std::cin, ReadNumberOnLine<size_t>(std::cin));

    // Проверяем домены
    for (const Domain& domain : test_domains){
        std::cout << (checker.IsForbidden(domain) ? "Bad"sv : "Good"sv) << std::endl;
    }

    #endif // LOCAL_DEBUG

}
