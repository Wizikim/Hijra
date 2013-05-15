/*
 * Coded by : Muhammad Negm<negm@ravingeek.com>
 * This software is under GNU Lesser General Public License
 * for more information please visit : http://www.gnu.org/licenses/lgpl.html
 *[ a C++ Implementation based on Muyyad Alsadi Hijra
 *for his Algorithm Hijra please visit http://hijra.ojuba.org/
 *Copyright(c) 2006-2008 Muayyad Saleh Alsadi<alsadi@gmail.com>
 */
#include <ostream>
#include "headers/hijra.h"

using std::ostream;

namespace hijra {

Date::Date() {
    this->date_abs = 0;
    this->date_m = 0, this->date_d = 0, this->date_y = 0;
}
Date::Date(unsigned someabsDate) {
    Date();
    this->date_abs = someabsDate;
}
Date::Date(const Date& c_copy) {
    this->date_m = c_copy.date_m;
    this->date_d = c_copy.date_d;
    this->date_y = c_copy.date_y;
    this->date_abs = c_copy.date_abs;
}
void Date::swap(Date & other)
{
    std::swap(this->date_abs , other.date_abs);
    std::swap(this->date_y , other.date_y);
    std::swap(this->date_m , other.date_m);
    std::swap(this->date_d , other.date_d);
}
Date & Date::operator=(Date other) {
    this->swap(other);
    return *this;
}
unsigned Date::get_date_abs()const {
    return this->date_abs;
}
ostream& operator << (ostream & Ostr, const Date & mydate) {
    Ostr << mydate.date_d << "-" << mydate.date_m << "-" << mydate.date_y;
    return Ostr;
}
}
