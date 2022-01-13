#include "Date.h"
#include <iostream>
#include <stdexcept>
#include <array>

using namespace std;

////////////////////////////////////////////////
Date::Date(int dy,int mn, int yr)
{
    if (mn>0 && mn<=month_per_year) //Check the number of months.
        month=mn;
    else
        throw invalid_argument("month must be 1-12");
    year = yr; // could validate yr
    day = checkDay( dy );   //call checkday

}
////////////////////////////////////////////////
Date::~Date()
{

}
////////////////////////////////////////////////
void Date::set_year(int y)
 {
    year=y;
 }
////////////////////////////////////////////////
unsigned int Date::get_year()const
{
    return year;

}
////////////////////////////////////////////////
void Date::print() const
{
    cout << day << '/' << month << '/' << year; //Prints the contents of the date object.
}
////////////////////////////////////////////////

unsigned int Date::checkDay(int testDay) const
{
   static const array< int, month_per_year + 1 > daysPerMonth =
    { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

// determine whether testDay is valid for specified month
    if ( testDay > 0 && testDay <= daysPerMonth[ month ] )      //Checks 31-day and 30-day months.
    return testDay;


    if ( month == 2 && testDay == 29 && ( year % 400 == 0 ||
    ( year % 4 == 0 && year % 100 != 0 ) ) )
    return testDay;

    throw invalid_argument( "Invalid day for current month and year" );

}
