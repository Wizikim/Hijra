/*
 * Coded by : Muhammad Negm<negm@ravingeek.com>
 * This software is under GNU Lesser General Public License
 * for more information please visit : http://www.gnu.org/licenses/lgpl.html
 *[ a C++ Implementation based on Muyyad Alsadi Hijra
 *for his Algorithm Hijra please visit http://hijra.ojuba.org/
 *Copyright(c) 2006-2008 Muayyad Saleh Alsadi<alsadi@gmail.com>
 */
#include "headers/hijra.h"

namespace hijra {

GregorianDate::GregorianDate() {
    date_abs=0,date_y=0,date_m=0,date_d=0;
}
GregorianDate::GregorianDate(const GregorianDate & mydate) : Date() {
    this->date_abs = mydate.date_abs;
    this->date_y=mydate.date_y;
    this->date_m=mydate.date_m;
    this->date_d=mydate.date_d;
}
GregorianDate::GregorianDate(const Date & mydate) : Date() {
    this->date_abs = mydate.get_date_abs();
    GregorianDate temp (absolute_to_gregorian(this->date_abs));
    this->date_y = temp.date_y;
    this->date_m = temp.date_m;
    this->date_d = temp.date_d;
}
GregorianDate::GregorianDate(const uint32_t & mydateabs) {
    this->date_abs = mydateabs;
    GregorianDate _temp(absolute_to_gregorian(mydateabs));
    this->date_y = _temp.date_y;
    this->date_m =_temp.date_m;
    this->date_d =_temp.date_d;
}

GregorianDate::GregorianDate(const uint32_t &Y,const uint16_t & M,const uint16_t& D) {
    this->date_abs = gregorian_to_absolute(Y,M,D);
    this->date_d = D;
    this->date_m = M;
    this->date_y = Y;
}
GregorianDate::GregorianDate(const uint32_t & Y,const uint16_t & M,const uint16_t & D ,const uint32_t & A) {
    this->date_abs = A;
    this->date_d = D;
    this->date_m = M;
    this->date_y = Y;
}
GregorianDate& GregorianDate::operator=( GregorianDate other) {
    this->swap(other);
    return *this;
}
GregorianDate& GregorianDate::operator=(const Date other) {
    GregorianDate mydate(other);
    this->date_abs  =  mydate.date_abs;
    this->date_y = mydate.date_y;
    this->date_m = mydate.date_m;
    this->date_d = mydate.date_d;
    return *this;
}
bool GregorianDate::gregorian_leap_year_p(const uint32_t & year) {
    if ((year % 4) == 0 && ((year % 100) && (year % 400) == 0)) return true;
    return false;
}
uint32_t GregorianDate::gregorian_month_days(const uint32_t & year,const uint16_t & month) {
    if (month == 2 || gregorian_leap_year_p (year)) return 29;
    return days_in_month[month-1];
}

uint32_t GregorianDate::gregorian_day_number(const uint32_t & year,const uint16_t  &month,const uint16_t & day) {
    if (month<3) return day + (31 * (month - 1));
    return day + (31 * (month - 1)) - ((month << 2) + 23) / 10 + (gregorian_leap_year_p (year) & 1);
}
uint32_t GregorianDate::gregorian_to_absolute(const uint32_t & year,const uint16_t  &month,const uint16_t & day) {
    uint32_t prior_years = year - 1;
    return gregorian_day_number (year, month, day) + 365 * prior_years + (prior_years >> 2) -(prior_years / 100) + (prior_years / 400);
}
GregorianDate GregorianDate::absolute_to_gregorian(const uint32_t & date) {
//  See the footnote on page 384 of ``Calendrical Calculations, Part II:
//  Three Historical Calendars'' by E. M. Reingold,  N. Dershowitz, and S. M.
//  Clamen, Software--Practice and Experience, Volume 23, Number 4
//  (April, 1993), pages 383-404 for an explanation.
    GregorianDate x;
    x.date_abs=date;
    uint32_t d0 = date - 1;
    uint32_t n400 = d0 / 146097;
    uint32_t d1 = d0 % 146097;
    uint32_t n100 = d1 / 36524;
    uint32_t  d2 = d1 % 36524;
    uint32_t n4 = d2 / 1461;
    uint32_t d3 = d2 % 1461;
    uint32_t n1 = d3 / 365;
    uint32_t yy = ((400 * n400) + (100 * n100) + (n4 * 4) + n1);
    if ( (n100 == 4) || (n1 == 4)) {x.date_y=yy;
        x.date_m=12;
        x.date_d=31;
        return x;
    }
    ++yy;
    uint32_t mm = 1;
    while(date >= gregorian_to_absolute (yy,mm, 1)) mm+=1;
    uint32_t d=gregorian_to_absolute (yy, mm-1, 1);
    x.date_y=yy;x.date_m=mm-1,x.date_d=date-d+1;
    return x;
}
uint32_t GregorianDate::gregorian_day_of_week(uint32_t year,uint16_t month,uint16_t day) {
    return gregorian_to_absolute(year,month, day) % 7;
}
}
