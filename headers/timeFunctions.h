#ifndef HIJRACPP_HEADERS_TIMEFUNCTIONS_H
#define HIJRACPP_HEADERS_TIMEFUNCTIONS_H
/*
 * Coded by : Muhammad Negm<negm@ravingeek.com>
 * This software is under GNU Lesser General Public License
 * for more information please visit : http://www.gnu.org/licenses/lgpl.html
 *[ a C++ Implementation based on Muyyad Alsadi Hijra
 *for his Algorithm Hijra please visit http://hijra.ojuba.org/
 *Copyright(c) 2006-2008 Muayyad Saleh Alsadi<alsadi@gmail.com>
 */
#include "headers/hijra.h"

namespace hijra{
enum Day { SUNDAY , MONDAY , TUESDAY , WEDNESDAY , THURSDAY , FRIDAY , SATURDAY ,NODAY };

tm * get_current_time(){
     tm * x;
    time_t rawtime;
    time(&rawtime);
    x=localtime(&rawtime);
    return x;
}

int get_current_year(){
 return 1900+get_current_time()->tm_year;
}
Day get_current_day(){
return Day(get_current_time()->tm_wday);
}
std::string get_current_day_string(){
    Day today= get_current_day();
    if (today == SUNDAY)
        return "Sunday";
    else if (today == MONDAY)
        return "Monday";
    else if (today == TUESDAY)
        return "Tuesday";
    else if (today == WEDNESDAY)
        return "Wednesday";
    else if (today == THURSDAY)
        return "Thursday";
    else if (today == FRIDAY)
        return "Friday";
    else if (today == SATURDAY)
        return "Saturday";
    else
        return "NOT A DAY";
}
uint32_t get_current_abs_date(){
tm *now =get_current_time();
return GregorianDate(1900+now->tm_year,now->tm_mon+1,now->tm_mday).get_date_abs();;

}

HijriDate get_current_hijri_date(){
    return HijriDate(get_current_abs_date());
}

}
#endif // HIJRACPP_HEADERS_TIMEFUNCTIONS_H
