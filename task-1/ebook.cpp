/** \file   ebook.cpp
 *  \brief  Система стимулирования чтения электронных книг
 */
#include <iostream>
#include <iomanip>
#include <string>
#include <unordered_map>

/** \brief  Прочитать одну строку с потока
 *  \param[in]  input - Входной поток
 *  \return     Строка с входного потока
 */
inline std::string ReadLine( std::istream& input ){
    std::string str_line;
    std::getline( input, str_line );
    return str_line;
}

/** \brief  Получить количество запросов из входного потока
 *  \param[in]  input - Входной поток
 *  \return     Максимум запросов для обработки
 */
inline size_t GetQueryesCount( std::istream& input ){
    size_t count_queryes = 0;
    input >> count_queryes;
    ReadLine(input);
    return count_queryes;
}

/** \brief  Система стимулирования чтения электронных книг
 */
class BookManager {
public:
    /** \brief  Конструктор по умолчанию
     */
    BookManager()
        : stop_on_page_()
        , count_users_() {
    }

    /** \brief  Пользователь прочитал книгу
     *  \param[in]  id - Идентификатор пользователя
     *  \param[in]  page - Номер страницы, до которой пользователь прочитал книгу
     */
    void Read( size_t id, size_t page ){
        if ( stop_on_page_.count(id) ){
            --count_users_[ stop_on_page_[id] ];
            stop_on_page_[id] = page;
            ++count_users_[page];
        }
        else {
            stop_on_page_[id] = page;
            ++count_users_[page];
        }
    }

    /** \brief  Простимулировать пользователя
     *  \param[in]  id - Идентификатор пользователя
     *  \param[out] output - Ссылка на поток вывода
     */
    void Cheer( size_t id, std::ostream& output ){
        if ( !stop_on_page_.count(id) ){
            output << std::setprecision(6) << 0 << std::endl;
        }
        else if ( stop_on_page_.size() == 1 ){
            output << std::setprecision(6) << 1 << std::endl;
        }
        else {
            size_t page_for_id = stop_on_page_[id];
            size_t cnt_users = 0;
            for ( const auto& [page, cnt] : count_users_ ){
                if ( page < page_for_id ){
                    cnt_users += cnt;
                }
            }
            double x = static_cast<double>(cnt_users)/(stop_on_page_.size()-1);
            output << std::setprecision(6) << x << std::endl;
        }
    }

private:
    /** \brief  Номер страницы, на которой остановился пользователь
     *  \b key - id пользователя
     *  \b value - номер страницы, на которой остановился пользователь
     */
    std::unordered_map<size_t, size_t> stop_on_page_;
    
    /** \brief  Количество пользователей, остановившихся на странице
     *  \b key - номер страници, на которой остановился пользователь
     *  \b value - количество пользователей
     */
    std::unordered_map<size_t, size_t> count_users_;
};

int main()
{
    BookManager book_manager;
    const size_t max_queryes = GetMaxQueryes( std::cin );
    
    for ( size_t n_query = 0; n_query < max_queryes; ++n_query ){
        std::string cmd;
        size_t id = 0;
        std::cin >> cmd >> id;
        if ( *cmd.begin() == 'R' ){
            // Запрос READ
            size_t page = 0;
            std::cin >> page;
            book_manager.Read(id, page);
        }
        else if ( *cmd.begin() == 'C' ){
            // Запрос CHEER
            book_manager.Cheer(id, std::cout);
        }
    }

    return 0;
}
