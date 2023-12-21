#pragma once

#include "utest_framework.hpp"
#include "log_duration.hpp"
#include "../domain-checker.hpp"

namespace UTEST {
namespace ClassDomainChecker {

// Тест пустого списка и метода GetListSize
inline void TestGetListSizeDomainChecker();

// Тест метода IsForbidden
inline void TestIsForbiddenDomainChecker();

// Тест с большими данными
inline void TestBigDataEqual();

// Тест с большими данными
inline void TestBigDataDuration();

// Запуск юнит-теста класса DomainChecker
void RunUTestClassDomainChecker();

} // namespace ClassDomainChecker
} // namespace UTEST
