#include <string>
#include <stdexcept>

using namespace std::literals;

namespace CheckDetail {
void CheckTheDateTimeInSegment( int date, int min_date, int max_date, const std::string& part_msg ){
    if ( date < min_date ){
        throw std::domain_error( part_msg + " is too small"s );
    }
    else if ( date > max_date ){
        throw std::domain_error( part_msg + " is too big"s );
    }
}
} // namespace CheckDetail


void CheckDateTimeValidity(const DateTime& dt) {
    // year
    CheckDetail::CheckTheDateTimeInSegment( dt.year, 1, 9999, "year"s );

    // month
    CheckDetail::CheckTheDateTimeInSegment( dt.month, 1, 12, "month"s );

    const bool is_leap_year = (dt.year % 4 == 0) && !(dt.year % 100 == 0 && dt.year % 400 != 0);
    const array month_lengths = {31, 28 + is_leap_year, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // day
    CheckDetail::CheckTheDateTimeInSegment( dt.day, 1, month_lengths[dt.month - 1], "day"s );

    // hour
    CheckDetail::CheckTheDateTimeInSegment( dt.hour, 0, 23, "hour"s );

    // minute
    CheckDetail::CheckTheDateTimeInSegment( dt.minute, 0, 59, "minute"s );

    // second
    CheckDetail::CheckTheDateTimeInSegment( dt.second, 0, 59, "second"s );
}
