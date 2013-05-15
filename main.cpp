/*
 * Coded by : Muhammad Negm<negm@ravingeek.com>
 * This software is under GNU Lesser General Public License
 * for more information please visit : http://www.gnu.org/licenses/lgpl.html
 *[ a C++ Implementation based on Muyyad Alsadi Hijra
 *for his Algorithm Hijra please visit http://hijra.ojuba.org/
 *Copyright(c) 2006-2008 Muayyad Saleh Alsadi<alsadi@gmail.com>
 */

#include "headers/hijrical.h"
#include <ctime>
#include <iostream>
using namespace hijra;
int main(void) {
    hijra::HijriDate x;
    hijra::GregorianDate y(1993,10,12);
    x=y;
    std::cout<<y<<std::endl<<x;
     return 0;
}
