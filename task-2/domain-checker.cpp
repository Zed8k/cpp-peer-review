#include "domain-checker.hpp"

using namespace std::literals;

//------------------------------------------------------------------------------
// Класс Domain
//------------------------------------------------------------------------------

//--- Публичные методы ---------------------------------------------------------

Domain::Domain()
    : domains_()
    , domain_()
    , top_domain_()
    , level_() {
}

Domain::Domain( std::string domain )
    : domains_()
    , domain_(domain)
    , top_domain_()
    , level_() {
        DomainSplit( std::string(domain.rbegin(), domain.rend()) );
}

bool Domain::operator==( const Domain& domain ) const {
    return domain_ == domain.domain_;
}

bool Domain::operator<( const Domain& domain ) const {
    return domains_ < domain.domains_;
}

bool Domain::IsSubdomain( const Domain& domain ) const {
    if ( domain.domains_.empty() ){
        return false;
    }

    size_t cnt_valid = 0;
    size_t cnt_levels = domain.domains_.size();
    size_t cnt_this_levels = domains_.size();
    size_t delta_level = 0;

    if ( cnt_this_levels < cnt_levels ){
        delta_level = cnt_levels - cnt_this_levels;
    }
    else if ( (cnt_this_levels == cnt_levels)
                || (cnt_this_levels > cnt_levels) ){
        return false;
    }
    for ( size_t n = 0; n < cnt_this_levels; ++n ){
        if ( domains_[n] == domain.domains_[n+delta_level] ){
            ++cnt_valid;
        }
    }

    bool result = (cnt_valid == domains_.size()) ? true : false;

    return result;
}

bool Domain::IsTopdomain( const Domain& domain ) const {
    if ( domain.domains_.empty() ){
        return false;
    }

    size_t cnt_valid = 0;
    size_t cnt_levels = domain.domains_.size();
    size_t cnt_this_levels = domains_.size();

    if ( (cnt_this_levels == cnt_levels)
            || (cnt_this_levels > cnt_levels) ){
                return false;
    }
    for ( size_t n = 0; n < cnt_this_levels; ++n ){
        if ( domains_[n] == domain.domains_[n] ){
            ++cnt_valid;
        }
    }

    bool result = (cnt_valid == cnt_this_levels) ? true : false;

    return result;
}

std::string_view Domain::GetDomainStr() const {
    return domain_;
}

size_t Domain::GetLevel() const {
    return level_;
}

Domain Domain::GetTopDomain() const {
    size_t top_level = (level_ > 0) ? level_ - 1 : 0;
    std::string top_domain = ""s;
    for ( size_t n = 0; n < top_level; ++n ){
        top_domain += domains_[n];
        if ( n < top_level-1 ){
            top_domain += '.';
        }
    }
    return Domain( std::string(top_domain.rbegin(), top_domain.rend()) );
}

Domain Domain::GetRootDomain() const {
    return Domain( std::string( (*domains_.begin()).rbegin(), (*domains_.begin()).rend() ) );
}

Domain Domain::GetDomainLevel( size_t level=1 ) const {
    std::string domain = ""s;
    for ( size_t n = 0; n < level; ++n ){
        domain += domains_[n];
        if ( n < level-1 ){
            domain += '.';
        }
    }
    return Domain( std::string(domain.rbegin(), domain.rend()) );
}

//--- Приватные методы ---------------------------------------------------------

inline void Domain::DomainSplit( std::string domain ){
    bool is_top_domain = true;
    if ( !domain.empty() ){
        std::string cur_level_domain = ""s;
        for ( const char& c : domain ){
            if ( c == '.' ){
                if ( is_top_domain ){
                    top_domain_ = cur_level_domain;
                    is_top_domain = false;
                }
                domains_.push_back( std::move(cur_level_domain) );
                continue;
            }
            cur_level_domain += c;
        }
        domains_.push_back( std::move(cur_level_domain) );
        level_ = domains_.size();
    }
}

//------------------------------------------------------------------------------
// Класс DomainChecker
//------------------------------------------------------------------------------

//--- Публичные методы ---------------------------------------------------------

bool DomainChecker::IsForbidden( const Domain& domain ) const {
    size_t level = domain.GetLevel();
    for ( size_t n = 1; n <= level; ++n ){
        Domain target_domain = domain.GetDomainLevel(n);
        if ( std::binary_search(forbidden_list_.begin(), forbidden_list_.end(), target_domain) ){
            return true;
        }
    }
    return false;
}

size_t DomainChecker::GetListSize() const {
    return forbidden_list_.size();
}

std::vector<std::string> DomainChecker::GetList() const {
    std::vector<std::string> forbidden_list_export;
    forbidden_list_export.reserve( 1000 );
    for ( const Domain& domain : forbidden_list_ ){
        std::string str( domain.GetDomainStr() );
        forbidden_list_export.push_back( std::move(str) );
    }
    return forbidden_list_export;
}
