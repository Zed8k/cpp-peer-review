#pragma once

/** \file   domain-checker.hpp
 *  \brief  Класс модуля проверки доменов
 */

/** \defgroup Group_DomainChecker   Средство проверки доменов
 *
 *  @{
 */

#include <string>
#include <vector>
#include <execution>

/** \brief  Класс описывающий сущность Домен
 */
class Domain {
public:

    /// \brief  Конструктор по умолчанию
    Domain();

    /** \brief  Конструктор создающий объект с указанной строкой доменного адреса
     *
     *  \param[in]  domain - Строка адресса
     */
    explicit Domain( std::string domain );

    /** \brief  Оператор ==
     *
     *  \param[in]  domain - Ссылка на сравниваемый адрес домена
     *  \return     \c TRUE если адреса равны, иначе \c FALSE
     */
    bool operator==( const Domain& domain ) const;

    /** \brief  Оператор <
     *
     *  \param[in]  domain - Ссылка на сравниваемый адрес домена
     *  \return     \c TRUE если адрес слева по длине и лесографически меньше чем справа, иначе \c FALSE
     */
    bool operator<( const Domain& domain ) const;

    /** \brief  Проверить является ли объект поддоменом другого
     *
     *  \param[in]  domain - Ссылка на друго адрес домена
     *  \return     \c TRUE если текущий адрес является поддоменом другого, иначе \c FALSE
     */
    bool IsSubdomain( const Domain& domain ) const;

    /** \brief  Проверить является ли объект доменом другого
     *
     *  \param[in]  domain - Ссылка на друго адрес домена
     *  \return     \c TRUE если текущий адрес является доменом для другого, иначе \c FALSE
     */
    bool IsTopdomain( const Domain& domain ) const;

    /** \brief  Получить адресс домена в виде строки
     *
     *  \return Строковое представление адреса домена
     */
    std::string_view GetDomainStr() const;

    /** \brief  Получить уровень домена
     *
     *  \return Номер уровня домена
     */
    size_t GetLevel() const;

    /** \brief  Получить домен уровнем выше текущего
     *
     *  \return Домен верхнего уровня по отношению к текущему. Тип \c Domain
     */
    Domain GetTopDomain() const;

    /** \brief  Получить корневой домен
     *
     *  \return Корневой домен по отношению к текущему
     */
    Domain GetRootDomain() const;

    /** \brief  Получить домен с указанным уровнем для текущего
     *
     *  \param[in]  level - Уровень домена
     *  \return     Домен с указанным уровнем по отношению к текущему
     */
    Domain GetDomainLevel( size_t level ) const;

private:
    // Адрес разложенный на домены
    std::vector<std::string> domains_;
    // Строка текущего адреса домена
    std::string domain_;
    // Срока корневого домена в обратном порядке
    std::string top_domain_;
    // Уровень домена
    size_t level_;

    /** \brief      Разложить строку домена на поддомены
     *
     *  \param[in]  domain - Строка домена
     */
    inline void DomainSplit( std::string domain );
};

/** \brief  Класс проверки доменов
 */
class DomainChecker {
public:
    /** \brief  Конструктор принимающий диапазон контейнера
     *
     *  \param[in]  range_begin - Начальный полу итератор контейнера
     *  \param[in]  range_end - Конечный полу итератор контейнера
     */
    template <typename InputIt>
    DomainChecker( InputIt range_begin, InputIt range_end );

    /** \brief  Проверить запрещён ли указанный домен
     *
     *  \param[in]  domain - Ссылка на домен
     *  \return     \c TRUE если домен запрещён, иначе \c FALSE
     */
    bool IsForbidden( const Domain& domain ) const;

    /** \brief  Получить размер списка запрещённых доменов
     *
     *  \return Размер списка запрещённых доменов
     */
    size_t GetListSize() const;

    /** \brief  Получить список запрещённых доменов
     *
     *  \return Вектор запрещённых доменов
     */
    std::vector<std::string> GetList() const;

private:
    std::vector<Domain> forbidden_list_;
};

//------------------------------------------------------------------------------
// Реализация шаблонов класса DomainChecker
//------------------------------------------------------------------------------

template <typename InputIt>
DomainChecker::DomainChecker( InputIt range_begin, InputIt range_end )
    : forbidden_list_(range_begin, range_end) {
    using namespace std::literals;
    auto comp = []( const Domain& lhs, const Domain& rhs ){
        return lhs == rhs || lhs.IsTopdomain(rhs);
    };
    std::sort( forbidden_list_.begin(), forbidden_list_.end() );
    auto it_end = std::unique( forbidden_list_.begin(), forbidden_list_.end(), comp );
    forbidden_list_.resize( it_end - forbidden_list_.begin() );
}

/** @} Group_DomainChecker */
