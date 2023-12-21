#pragma once

#include "utest_framework.hpp"
#include "../domain-checker.hpp"

namespace UTEST {

namespace ClassDomain {

// Тест пустого домена и метода GetLevel
inline void TestZerroAndLevelDomain();

// Тест метода GetTopDomain
inline void TestGetTopDomain();

// Тест метода GetRootDomain
inline void TestGetRootDomain();

// Тест метода GetDomainStr
inline void TestGetDomainStr();

// Тест метода operator==
inline void TestOperatorEquallyDomains();

// Тест метода operator<
inline void TestOperatorLessDomains();

// Тест метода IsSubdomain
inline void TestIsSubdomain();

// Тест метода IsTopdomain
inline void TestIsTopdomain();

// Тест метода GetDomainLevel
inline void TestGetDomainLevel();

// Запуск юнит-теста класса Domain
void RunUTestClassDomain();

} // namespace ClassDomain

} // namespace UTEST
