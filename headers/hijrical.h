#ifndef HIJRACPP_HEADERS_HIJRICAL_H
#define HIJRACPP_HEADERS_HIJRICAL_H
/*
 * Coded by : Muhammad Negm<negm@ravingeek.com>
 * This software is under GNU Lesser General Public License
 * for more information please visit : http://www.gnu.org/licenses/lgpl.html
 *[ a C++ Implementation based on Muyyad Alsadi Hijra
 *for his Algorithm Hijra please visit http://hijra.ojuba.org/
 *Copyright(c) 2006-2008 Muayyad Saleh Alsadi<alsadi@gmail.com>
 */
#include "hijra.h"
#include "timeFunctions.h"
#include <ctime>
#include <string>

using std::string;
namespace hijra{
class HijriCal {
public:
    HijriCal();
    void goto_today();
    bool refresh_today();
    hijra::Date goto_gregorian_day();
    hijra::Date goto_hijri_day();
    bool validate();
private:
    void fill_month_days();
    string ** md;
    string ** gmd;
    int direct,week_start;
    tm * local_time_struct;
    hijra::GregorianDate *current_date_greg;
    hijra::HijriDate *current_date_hijri;
};
}
#endif // HIJRACPP_HEADERS_HIJRICAL_H
