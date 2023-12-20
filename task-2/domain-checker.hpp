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

#define DomainChecker_Constructor_Rev_4
#define DomainChecker_IsForbidden_Rev_3

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

    /** \brief  Развернуть порядок строки адреса домена
     *
     *  \param[in]  domain - Ссылка на строку адреса доменя
     *  \return     Развёрнутую строку в обратном порядке адрес домена
     */
    inline std::string Reverse( const std::string& domain );

    /** \brief  Развернуть порядок строки адреса домена
     *
     *  \param[in]  domain - Ссылка на строку адреса доменя
     *  \return     Развёрнутую строку в обратном порядке адрес домена
     */
    inline std::string Reverse( const std::string& domain ) const;

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
    const size_t level_to_parallel_mode_ = 1000;
};

//------------------------------------------------------------------------------
// Реализация шаблонов класса DomainChecker
//------------------------------------------------------------------------------

template <typename InputIt>
DomainChecker::DomainChecker( InputIt range_begin, InputIt range_end )
    : forbidden_list_() {
    using namespace std::literals;
    forbidden_list_.reserve( 1000 );

    for ( auto it = range_begin; it != range_end; ++it ){
        // Если список пустой - сразу добавляем
        if ( forbidden_list_.empty() ){
            forbidden_list_.push_back( *it );
            continue;
        }
        // Ищем домен начиная с корневого в глубь
        size_t it_level = it->GetLevel();
        bool is_finded = false;
        for ( size_t n = 1; n <= it_level; ++n ){
            Domain target_domain = it->GetDomainLevel( n );
            if ( std::binary_search(forbidden_list_.begin(), forbidden_list_.end(), target_domain) ){
                is_finded = true;
                break;
            }
        }
        // Если не нашли, то добавляем
        if ( !is_finded ){
            forbidden_list_.push_back( *it );
            // Сортируем
            if ( forbidden_list_.size() > level_to_parallel_mode_ ){
                // В параллельном режиме
                std::sort( std::execution::par, forbidden_list_.begin(), forbidden_list_.end() );
            }
            else {
                // Иначе в последовательном режиме
                std::sort( forbidden_list_.begin(), forbidden_list_.end() );
            }
            // Удаляем поддомены
            auto it_last = (forbidden_list_.size() > level_to_parallel_mode_)
                ? std::unique( std::execution::par, forbidden_list_.begin(), forbidden_list_.end(),
                    [](const Domain& lhs, const Domain& rhs){
                        return lhs.IsTopdomain(rhs);
                    } )
                : std::unique( forbidden_list_.begin(), forbidden_list_.end(),
                    [](const Domain& lhs, const Domain& rhs){
                        return lhs.IsTopdomain(rhs);
                } );
            forbidden_list_.erase( it_last, forbidden_list_.end() );
            continue;
        }
    }
}

/** @} Group_DomainChecker */
