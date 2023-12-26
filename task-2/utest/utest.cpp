#include "utest.hpp"

void UTEST::RunUTestBoxes(){
    using namespace std::literals;
    RUN_TEST_MODULE( UTEST::ClassDomain::RunUTestClassDomain, "Класс Domain"s );
    RUN_TEST_MODULE( UTEST::ClassDomainChecker::RunUTestClassDomainChecker, "Класс DomainChecker"s );
}
