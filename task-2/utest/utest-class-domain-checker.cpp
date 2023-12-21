#include "utest-class-domain-checker.hpp"

using namespace std::literals;

// Тест пустого списка и метода GetListSize
inline void UTEST::ClassDomainChecker::TestGetListSizeDomainChecker(){
    std::vector<Domain> forbidden_list;
    //---
    Domain deny1( "aa.aaaa.a.a.a.aaaa.a"s );    //-
    Domain deny2( "aa"s );                      //+ 1
    Domain deny3( "a.aa.aaaa.a.a.a.aaaa.a"s );  //-
    Domain deny4( "a.aa"s );                    //-
    Domain deny5( "a.aa.aaaa.aa.a.aa"s );       //-
    Domain deny6( "aaaa.a.a.aaaa.a"s );         //+ 2
    Domain deny7( "aa"s );                      //-
    Domain deny8( "aaaa.a.a.a.aaaa.a"s );       //+ 3
    Domain deny9( "aa.aaaa.a.a.a.aaaa.a"s );    //-
    Domain deny10( "aaaa.aa.aaa.aaaa.a"s );     //+ 4
    Domain deny11( "edr.dcp"s );                //+ 5
    //--
    forbidden_list.push_back( deny1 );
    forbidden_list.push_back( deny2 );
    forbidden_list.push_back( deny3 );
    forbidden_list.push_back( deny4 );
    forbidden_list.push_back( deny5 );
    forbidden_list.push_back( deny6 );
    forbidden_list.push_back( deny7 );
    forbidden_list.push_back( deny8 );
    forbidden_list.push_back( deny9 );
    forbidden_list.push_back( deny10 );
    forbidden_list.push_back( deny11 );
    //---
    DomainChecker checker( forbidden_list.begin(), forbidden_list.end() );
    //---
    ASSERT( checker.GetListSize() == 5 );
}

// Тест метода IsForbidden
inline void UTEST::ClassDomainChecker::TestIsForbiddenDomainChecker(){
    std::vector<Domain> forbidden_list;
    //---
    Domain deny1( "aa.aaaa.a.a.a.aaaa.a"s );    //-
    Domain deny2( "aa"s );                      //+ 1
    Domain deny3( "a.aa.aaaa.a.a.a.aaaa.a"s );  //-
    Domain deny4( "a.aa"s );                    //-
    Domain deny5( "a.aa.aaaa.aa.a.aa"s );       //-
    Domain deny6( "aaaa.a.a.aaaa.a"s );         //+ 2
    Domain deny7( "aa"s );                      //-
    Domain deny8( "aaaa.a.a.a.aaaa.a"s );       //+ 3
    Domain deny9( "aa.aaaa.a.a.a.aaaa.a"s );    //-
    Domain deny10( "aaaa.aa.aaa.aaaa.a"s );     //+ 4
    Domain deny11( "edr.dcp"s );                //+ 5
    //--
    forbidden_list.push_back( deny1 );
    forbidden_list.push_back( deny2 );
    forbidden_list.push_back( deny3 );
    forbidden_list.push_back( deny4 );
    forbidden_list.push_back( deny5 );
    forbidden_list.push_back( deny6 );
    forbidden_list.push_back( deny7 );
    forbidden_list.push_back( deny8 );
    forbidden_list.push_back( deny9 );
    forbidden_list.push_back( deny10 );
    forbidden_list.push_back( deny11 );
    //---
    DomainChecker checker( forbidden_list.begin(), forbidden_list.end() );
    //---
    Domain test1( "a.aa.aaaa.a.a.a.aaaa.a"s );              // bad
    Domain test2( "aa.aa.aaa.aa.aaaa.aa.aaa.aaaa.a"s );     // bad
    Domain test3( "aaa.aa.aa.aaaa.a.a.a.aaaa.a"s );         // bad
    Domain test4( "aa"s );                                  // bad
    Domain test5( "aaaa.a.a.a.aaaa.a"s );                   // bad
    Domain test6( "aa.aaaa.aaaa.aaa.aaaa.a.aa"s );          // bad
    Domain test7( "a.aaa.aaaa.aaa.a.aa.aa.aa"s );           // bad
    Domain test8( "aaaa.aa.aaaa.a.a.a.aaaa.a"s );           // bad
    Domain test9( "aaaa.aaaa.aa.aa"s );                     // bad
    Domain test10( "aaaa.aaa.aa.a.aaaa.a.a.a.aaaa.a"s );    // bad
    Domain test11( "aaaa.aaaa.a.a.a.aaaa.a"s );             // bad
    Domain test12( "aaa.aaaa"s );                           // good
    Domain test13( "aaa"s );                                // good
    Domain test14( "aaaa.a.a.aaaa.a"s );                    // bad
    Domain test15( "aaa.aa.a.aa.a.aaaa.a.a.aaaa.a"s );      // bad
    Domain test16( "a.aaa.aaaa.a.a.a.aaaa.a"s );            // bad
    Domain test17( "aa.aa.aa.a.aa"s );                      // bad
    Domain test18( "aaa.aaa.aaaa.aaa.aa.a.aaaa.aa.aa"s );   // bad
    Domain test19( "aa.a.aa.aaaa.aa.a.aa"s );               // bad
    Domain test20( "a.aa.a.aa.aaaa.a.a.a.aaaa.a"s );        // bad
    Domain test21( "mjnz.aqvl.rzp.bkny.vjl.edr.dcp"s );     // bad

    ASSERT_HINT( checker.IsForbidden(test1), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test2), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test3), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test4), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test5), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test6), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test7), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test8), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test9), "Домен запрещён!"s );   // bad
    ASSERT_HINT( checker.IsForbidden(test10), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test11), "Домен запрещён!"s );  // bad
    ASSERT_HINT( !checker.IsForbidden(test12), "Домен разрешён!"s ); // good
    ASSERT_HINT( !checker.IsForbidden(test13), "Домен разрешён!"s ); // good
    ASSERT_HINT( checker.IsForbidden(test14), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test15), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test16), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test17), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test18), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test19), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test20), "Домен запрещён!"s );  // bad
    ASSERT_HINT( checker.IsForbidden(test21), "Домен запрещён!"s );  // bad
}

// Тест с большими данными
inline void UTEST::ClassDomainChecker::TestBigDataEqual(){
    const size_t size_reserve = 1000;
    // Образцы: in_deny_test_1.txt, in_domain_test_1.txt, out_check_test_1.txt
    {
        std::vector<std::string> deny_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_deny_test_1.txt" );
        std::vector<std::string> domen_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_domain_test_1.txt" );
        std::vector<std::string> check_list = UTEST::TOOL::BigDataLoad( "./utest/controls/out_check_test_1.txt" );

        ASSERT_HINT( deny_list_sample.size() != 0, "Не найден список запрещённых доменов 'in_deny_test_1.txt'"s );
        ASSERT_HINT( domen_list_sample.size() != 0, "Не найден список обрабатываемых доменов 'in_domain_test_1.txt'"s );
        ASSERT_HINT( check_list.size() != 0, "Не найден контрольный лист 'out_check_test_1.txt'"s );

        std::vector<Domain> deny_domain_list;
        deny_domain_list.reserve( size_reserve );
        for ( std::string str : deny_list_sample ){
            deny_domain_list.push_back( Domain(std::move(str)) );
        }

        std::vector<Domain> domain_list;
        domain_list.reserve( size_reserve );
        for ( std::string str : domen_list_sample ){
            domain_list.push_back( Domain(std::move(str)) );
        }

        DomainChecker checker( deny_domain_list.begin(), deny_domain_list.end() );
        ASSERT_HINT( checker.GetListSize() == 4, "Добавлены не все запрещённые домены!" );

        const size_t number_of_entries = domain_list.size();
        for ( size_t n = 0; n < number_of_entries; ++n ){
            std::string er_line( "Error in in_domen_test_1.txt:"sv );
            er_line += std::to_string(n+1);
            std::string check = check_list[n];
            std::string value = ( checker.IsForbidden(domain_list[n]) ) ? "Bad\r"s : "Good\r"s;
            ASSERT_EQUAL_HINT( check, value, er_line );
        }
    }
    // Образцы: in_deny_test_2.txt, in_domain_test_2.txt, out_check_test_2.txt
    {
        std::vector<std::string> deny_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_deny_test_2.txt" );
        std::vector<std::string> domen_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_domain_test_2.txt" );
        std::vector<std::string> check_list = UTEST::TOOL::BigDataLoad( "./utest/controls/out_check_test_2.txt" );

        ASSERT_HINT( deny_list_sample.size() != 0, "Не найден список запрещённых доменов 'in_deny_test_2.txt'"s );
        ASSERT_HINT( domen_list_sample.size() != 0, "Не найден список обрабатываемых доменов 'in_domain_test_2.txt'"s );
        ASSERT_HINT( check_list.size() != 0, "Не найден контрольный лист 'out_check_test_2.txt'"s );

        std::vector<Domain> deny_domain_list;
        deny_domain_list.reserve( size_reserve );
        for ( std::string str : deny_list_sample ){
            deny_domain_list.push_back( Domain(std::move(str)) );
        }

        std::vector<Domain> domain_list;
        domain_list.reserve( size_reserve );
        for ( std::string str : domen_list_sample ){
            domain_list.push_back( Domain(std::move(str)) );
        }

        DomainChecker checker( deny_domain_list.begin(), deny_domain_list.end() );
        ASSERT_HINT( checker.GetListSize() == 303, "Добавлены не все запрещённые домены!" );

        const size_t number_of_entries = domain_list.size();
        for ( size_t n = 0; n < number_of_entries; ++n ){
            std::string er_line( "Error in in_domain_test_2.txt:"sv );
            er_line += std::to_string(n+1);
            std::string check = check_list[n];
            std::string value = ( checker.IsForbidden(domain_list[n]) ) ? "Bad\r"s : "Good\r"s;
            ASSERT_EQUAL_HINT( check, value, er_line );
        }
    }
    // Образцы: in_deny_test_3.txt, in_domain_test_3.txt, out_check_test_3.txt
    {
        std::vector<std::string> deny_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_deny_test_3.txt" );
        std::vector<std::string> domen_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_domain_test_3.txt" );
        std::vector<std::string> check_list = UTEST::TOOL::BigDataLoad( "./utest/controls/out_check_test_3.txt" );

        ASSERT_HINT( deny_list_sample.size() != 0, "Не найден список запрещённых доменов 'in_deny_test_3.txt'"s );
        ASSERT_HINT( domen_list_sample.size() != 0, "Не найден список обрабатываемых доменов 'in_domain_test_3.txt'"s );
        ASSERT_HINT( check_list.size() != 0, "Не найден контрольный лист 'out_check_test_3.txt'"s );

        std::vector<Domain> deny_domain_list;
        deny_domain_list.reserve( size_reserve );
        for ( std::string str : deny_list_sample ){
            deny_domain_list.push_back( Domain(std::move(str)) );
        }

        std::vector<Domain> domain_list;
        domain_list.reserve( size_reserve );
        for ( std::string str : domen_list_sample ){
            domain_list.push_back( Domain(std::move(str)) );
        }

        DomainChecker checker( deny_domain_list.begin(), deny_domain_list.end() );
        ASSERT_HINT( checker.GetListSize() == 1, "Добавлены не все запрещённые домены!" );

        const size_t number_of_entries = domain_list.size();
        for ( size_t n = 0; n < number_of_entries; ++n ){
            std::string er_line( "Error in in_domain_test_3.txt:"sv );
            er_line += std::to_string(n+1);
            std::string check = check_list[n];
            std::string value = ( checker.IsForbidden(domain_list[n]) ) ? "Bad\r"s : "Good\r"s;
            ASSERT_EQUAL_HINT( check, value, er_line );
        }
    }
}

// Тест производительности с большими данными
inline void UTEST::ClassDomainChecker::TestBigDataDuration(){
    const size_t size_reserve = 1000;
    // Образцы: in_deny_test_2.txt, in_domain_test_2.txt, out_check_test_2.txt
    {
        std::vector<std::string> deny_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_deny_test_2.txt" );
        std::vector<std::string> domen_list_sample = UTEST::TOOL::BigDataLoad( "./utest/samples/in_domain_test_2.txt" );
        std::vector<std::string> check_list = UTEST::TOOL::BigDataLoad( "./utest/controls/out_check_test_2.txt" );

        ASSERT_HINT( deny_list_sample.size() != 0, "Не найден список запрещённых доменов 'in_deny_test_2.txt'"s );
        ASSERT_HINT( domen_list_sample.size() != 0, "Не найден список обрабатываемых доменов 'in_domain_test_2.txt'"s );
        ASSERT_HINT( check_list.size() != 0, "Не найден контрольный лист 'out_check_test_2.txt'"s );

        std::vector<Domain> deny_domain_list;
        deny_domain_list.reserve( size_reserve );
        for ( std::string str : deny_list_sample ){
            deny_domain_list.push_back( Domain(std::move(str)) );
        }

        std::vector<Domain> domain_list;
        domain_list.reserve( size_reserve );
        for ( std::string str : domen_list_sample ){
            domain_list.push_back( Domain(std::move(str)) );
        }

        {
            LOG_DURATION( "Speed class DomainChecker [deny: 10'000; domain: 10'000]"s );
            DomainChecker checker( deny_domain_list.begin(), deny_domain_list.end() );
            const size_t number_of_entries = domain_list.size();

            for ( size_t n = 0; n < number_of_entries; ++n ){
                checker.IsForbidden( domain_list[n] );
            }

        }
    }
}

// Запуск юнит-теста класса DomainChecker
void UTEST::ClassDomainChecker::RunUTestClassDomainChecker(){
    using namespace UTEST::ClassDomainChecker;
    RUN_TEST( TestGetListSizeDomainChecker );
    RUN_TEST( TestIsForbiddenDomainChecker );
    RUN_TEST( TestBigDataEqual );
    RUN_TEST( TestBigDataDuration );
}
