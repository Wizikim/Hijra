#ifndef HIJRACPP_HEADERS_HIJRA_H_
#define HIJRACPP_HEADERS_HIJRA_H_
/*
 * Coded by : Muhammad Negm<negm@ravingeek.com>
 * This software is under GNU Lesser General Public License
 * for more information please visit : http://www.gnu.org/licenses/lgpl.html
 *[ a C++ Implementation based on Muyyad Alsadi Hijra
 *for his Algorithm Hijra please visit http://hijra.ojuba.org/
 *Copyright(c) 2006-2008 Muayyad Saleh Alsadi<alsadi@gmail.com>
 */
#include <stdint.h>
#include <ostream>
using std::ostream;

namespace hijra {

class Date {
protected:
    uint16_t date_m, date_d;
    uint32_t date_y, date_abs;
public:
    Date();
    Date(uint32_t someabsDate);
    Date(const Date& c_copy);
    void swap( Date & other);
    Date& operator=(const Date other) ;
    uint32_t get_date_abs()const;
    friend ostream& operator<<(ostream & Ostr, const Date & mydate);
};


class HijriDate : public Date {
private:
    static const  uint8_t __p_const = 191, __a_const = 48;
    static const  uint16_t __q_const = 360;
    static const uint32_t __hijri_epoch = 227015;
public :
    HijriDate();
    HijriDate (const Date & mydate)  ;
    HijriDate(const HijriDate & mydate) ;
    HijriDate& operator=(const HijriDate other) ;
    HijriDate& operator=( const Date other) ;

    HijriDate(uint32_t _date_abs);
    HijriDate(uint32_t year, uint16_t  month, uint16_t day);
    HijriDate(uint32_t year, uint16_t  month , uint16_t day, uint32_t abs);
    uint32_t get_epoch();
    uint32_t hijri_month_days_(uint32_t year, uint16_t month);
    uint32_t hijri_day_of_week(uint32_t year, uint16_t  month, uint16_t day);
    uint32_t hijri_days_before_month(uint32_t  year, uint16_t  month);
    uint16_t hijri_day_number(uint32_t Y,  uint16_t M,  uint16_t D);
    uint32_t hijri_year_days(uint32_t Y);
    uint16_t hijri_month_days(uint32_t  Y, uint16_t  M);
    uint32_t  hijri_to_absolute(uint32_t Y,  uint16_t M,  uint16_t D);
    HijriDate absolute_to_hijri(uint32_t date);
    void test();
};



static const uint16_t  days_in_month[12] =  {31,  28,  31,
                                             30,  31,  30,
                                             31,  31,  30,
                                             31,  30,  31};
class GregorianDate : public Date  {

public:
    GregorianDate();

    GregorianDate(const GregorianDate & mydate);

    GregorianDate(const Date & mydate);

    GregorianDate(const uint32_t & mydateabs);

    GregorianDate(const uint32_t &Y,
                  const uint16_t & M,
                  const uint16_t& D);

    GregorianDate(const uint32_t & Y,
                  const uint16_t & M,
                  const uint16_t & D,
                  const uint32_t & A);
    GregorianDate& operator=(const GregorianDate other) ;
    GregorianDate& operator=(const  Date other) ;


    uint32_t gregorian_month_days(const uint32_t & year,
                                  const uint16_t & month);
    //   The last day in MONTH during YEAR.

    uint32_t gregorian_day_number(const uint32_t & year,
                                  const uint16_t & month,
                                  const uint16_t & day);
    //       Return the day number within the year of the date (year,month, day)

    uint32_t gregorian_to_absolute(const uint32_t & year,
                                   const uint16_t &month,
                                   const uint16_t & day);

    GregorianDate absolute_to_gregorian(const uint32_t & date);
    //    return (year month day) corresponding to the absolute DATE.
    //    The absolute date is the number of days elapsed since the (imaginary)
    //    Gregorian date Sunday, December 31, 1 BC.

    uint32_t gregorian_day_of_week(uint32_t year,
                                   uint16_t month,
                                   uint16_t day);
    //   Return the day-of-the-week index of gregorian (yy, mm, dd) DATE,
    //   0 for Sunday, 1 for Monday, etc.


private:
    bool gregorian_leap_year_p(const uint32_t & year);
    //    Return  (True) if YEAR is a Gregorian leap year.
};
}

#endif  // HIJRACPP_HEADERS_HIJRA_H_
