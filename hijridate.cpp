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

HijriDate::HijriDate() {
    date_abs = 0, date_y = 0, date_m = 0, date_d = 0;
}
 HijriDate::HijriDate( const Date & mydate) {
    this->date_abs  =  mydate.get_date_abs();
    HijriDate x(absolute_to_hijri(this->date_abs));
    this->date_d = x.date_d;
    this->date_m = x.date_m;
    this->date_y = x.date_y;
}
 HijriDate::HijriDate( const HijriDate & mydate):Date() {
    this->date_abs  =  mydate.date_abs;
    this->date_y = mydate.date_y;
    this->date_m = mydate.date_m;
    this->date_d = mydate.date_d;
}

HijriDate& HijriDate::operator=( HijriDate other) {
    swap(other);
    return *this;
}
HijriDate& HijriDate::operator=(const Date other) {
    HijriDate mydate(other);
    this->date_abs  =  mydate.date_abs;
    this->date_y = mydate.date_y;
    this->date_m = mydate.date_m;
    this->date_d = mydate.date_d;
    return *this;
}

HijriDate::HijriDate(uint32_t _date_abs) {
    this->date_abs = _date_abs;
    if (_date_abs >= __hijri_epoch) {
        HijriDate _temp(absolute_to_hijri(_date_abs));
        this->date_y = _temp.date_y;
        this->date_m = _temp.date_m;
        this->date_d = _temp.date_d;
    } else  {
        this->date_y = 0;
        this->date_m = 0;
        this->date_d = 0;
    }
}
HijriDate::HijriDate(uint32_t year, uint16_t  month, uint16_t day) {
    this->date_abs = hijri_to_absolute(year, month, day);
    this->date_d = day;
    this->date_m = month;
    this->date_y = year;
}
HijriDate::HijriDate(uint32_t year, uint16_t  month
                     , uint16_t day, uint32_t abs) {
    this->date_abs = abs;
    this->date_d = day;
    this->date_m = month;
    this->date_y = year;
}
uint32_t HijriDate::get_epoch() {
    //  Return Hijri epoch,
    //  number of days since gregorian epoch,
    //  (should be Julian 0622-7-16(ie. 227015 days)
    return __hijri_epoch;
}
uint32_t HijriDate::hijri_month_days_(uint32_t year, uint16_t month) {
    //  Return the number of days in
    //  a given hijri month M in a given Y
    return hijri_to_absolute(year+month/12, month%12+1, 1)
            -hijri_to_absolute(year, month, 1);
}
uint32_t HijriDate::hijri_day_of_week(uint32_t year,
                                      uint16_t month,
                                      uint16_t day) {
    //  Return the day-of-the-week index of hijri(Y, M, D) Date
    //  0 for Sunday,  1 for Monday,  etc.
    return hijri_to_absolute(year, month,  day) % 7;
}
uint32_t HijriDate::hijri_days_before_month(uint32_t  year, uint16_t  month) {
    //  Return the number of days before
    //  a given moth M in a given year Y(0 for M = 1)
    uint32_t Mc  = (year - 1) *12 + 1 + __a_const;
    uint32_t McM = Mc * __p_const;
    uint32_t sum = 0;
    for (uint32_t i  = 1 ; i < month ; ++i) {
        if ((McM % __q_const)< __p_const )
            sum+= 30;
        else
            sum += 29;
        McM += __p_const;
    }
    return sum;
}
uint16_t HijriDate::hijri_day_number(uint32_t Y,  uint16_t M,  uint16_t D) {
    // Return the day number within the year of the Islamic date(Y,  M,  D)
    //  1 for 1/1 in any year
    return hijri_days_before_month(Y, M)+D;
}
uint32_t HijriDate::hijri_year_days(uint32_t Y) {
    // Return the number of days in a given year Y
    return hijri_days_before_month(Y, 13);
}
uint16_t HijriDate::hijri_month_days(uint32_t  Y, uint16_t  M) {
    //  Return the number of days in a given hijri month M in a given Y
    uint32_t Mc  = (Y -1) *12 + M;
    if ((((Mc+ __a_const) * __p_const) % __q_const)  < __p_const  )
        return 30;
    else
        return 29;
}
uint32_t  HijriDate::hijri_to_absolute(uint32_t Y,  uint16_t M,  uint16_t D) {
    //  Return absolute date of Hijri(Y, M, D)
    //  eg. ramadan(9), 1, 1427 -> 732578
    uint32_t Mc =(Y-1) * 12;
    // day count = days before hijra plus(...)
    uint32_t dc = __hijri_epoch;
    // plus days in the years before till first multiples of q plus(...)
    Mc-= Mc % __q_const;
    uint32_t y = Y-Mc/12;
    dc+= Mc*29 + Mc*__p_const/__q_const;
    // plus those after the multiples plus(...)
    for ( uint32_t i  = 1 ; i < y; ++i ) dc += hijri_year_days(i);
    // plus days from the begining of that year
    dc+= hijri_day_number(Y,  M,  D) - 1;
    return dc;
}
HijriDate HijriDate::absolute_to_hijri(uint32_t date) {
    //  Return Hijri date(Y, M, D)
    //  corresponding to the given absolute number of days.
    if (date < __hijri_epoch)  {
        Date x;
        return x;  //  before hijra zero values vector
    }
    uint32_t Mc =(date-__hijri_epoch+1)*__q_const/(29*__q_const+__p_const);
    uint32_t Y = Mc/12+1 ,  M =(Mc%12)+1;
    uint32_t d = hijri_to_absolute(Y, M, 1);
    // TODO(ALSADI): ^^
    //             this is an expensive call
    if (date < d)  {
        --M;  //  go one month back if needed
        if ( M == 0 ) {
            Y--;
            M = 12;
        }
        d-= hijri_month_days(Y, M);  //  this call is fast
    }
    uint32_t D = 1 + date - d;
    HijriDate x(Y, M, D, date);
    return x;
}
void  HijriDate::test() {

}
}
