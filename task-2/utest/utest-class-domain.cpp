#include "utest-class-domain.hpp"

using namespace std::literals;

// Тест пустого домена и метода GetLevel
inline void UTEST::ClassDomain::TestZerroAndLevelDomain(){
    {
        Domain test_zerro;
        ASSERT( test_zerro.GetLevel() == 0 );
    }
    {
        Domain test( "ru"s );
        ASSERT( test.GetLevel() == 1 ); // true
    }
    {
        Domain test( "test.ru"s );
        ASSERT( test.GetLevel() == 2 ); // true
    }
}

// Тест метода GetTopDomain
inline void UTEST::ClassDomain::TestGetTopDomain(){
    Domain test1( "test.ru"s );
    Domain test2( "my.test.ru"s );

    ASSERT( test1.GetTopDomain() == Domain("ru"s) );        // true
    ASSERT( test2.GetTopDomain() == Domain("test.ru"s) );   // true
}

// Тест метода GetRootDomain
inline void UTEST::ClassDomain::TestGetRootDomain(){
    Domain test1( "test.ru"s );
    Domain test2( "my.test.ru"s );

    ASSERT( test1.GetRootDomain() == Domain("ru"s) );   // true
    ASSERT( test2.GetRootDomain() == Domain("ru"s) );   // true
}

// Тест метода GetDomainStr
inline void UTEST::ClassDomain::TestGetDomainStr(){
    Domain test( "test.ru"s );
    ASSERT( test.GetDomainStr() == "test.ru"sv );   // true
}

// Тест метода operator==
inline void UTEST::ClassDomain::TestOperatorEquallyDomains(){
    Domain test1( "test.ru"s );
    Domain test2( "test.ru"s );
    Domain test3( "test.uk"s );

    ASSERT( test1 == test2 );   // true
    ASSERT( !(test1 == test3) );// false
}

// Тест метода operator<
inline void UTEST::ClassDomain::TestOperatorLessDomains(){
    Domain test1( "test.ru"s );
    Domain test2( "test.ru"s );
    Domain test3( "test.uk"s );
    Domain test4( "test.com"s );

    ASSERT( !(test1 < test2) ); // false
    ASSERT( !(test1 < test3) ); // false
    ASSERT( test4 < test1 );    // true
}

// Тест метода IsSubdomain
inline void UTEST::ClassDomain::TestIsSubdomain(){
    Domain test1( "test.ru"s );
    Domain test2( "test.ru.com"s );
    Domain test3( "test.uk.com"s );

    ASSERT( test1.IsSubdomain(test2) ); // true
    ASSERT( !test1.IsSubdomain(test3) );// false
}

// Тест метода IsTopdomain
inline void UTEST::ClassDomain::TestIsTopdomain(){
    Domain test1( "test.ru"s );
    Domain test2( "part1.test.ru"s );
    Domain test3( "part1.test.uk"s );

    ASSERT( test1.IsTopdomain(test2) ); // true
    ASSERT( !test1.IsTopdomain(test3) );// false
}

// Тест метода GetDomainLevel
inline void UTEST::ClassDomain::TestGetDomainLevel(){
    Domain test1( "part1.test.ru"s );

    ASSERT( test1.GetDomainLevel(1) == Domain("ru"s) );
    ASSERT( test1.GetDomainLevel(2) == Domain("test.ru"s) );
    ASSERT( test1.GetDomainLevel(3) == Domain("part1.test.ru"s) );
}

// Запуск юнит-теста класса Domain
void UTEST::ClassDomain::RunUTestClassDomain(){
    using namespace UTEST::ClassDomain;
    RUN_TEST( TestZerroAndLevelDomain );
    RUN_TEST( TestGetTopDomain );
    RUN_TEST( TestGetRootDomain );
    RUN_TEST( TestGetDomainStr );
    RUN_TEST( TestOperatorEquallyDomains );
    RUN_TEST( TestOperatorLessDomains );
    RUN_TEST( TestIsSubdomain );
    RUN_TEST( TestIsTopdomain );
    RUN_TEST( TestGetDomainLevel );
}
