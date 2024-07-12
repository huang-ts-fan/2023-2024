
/*
	Provide helper functions for the Date class, such as next_workay() and week_of_year().

	Apologies: I had assumed the the formulas and explanations needed to make date calculations
		simple were more easily available on the web and clearer than I found.
		The mathematical explanations seem to have been drowned in little widgets that will
		calculate for you, but don't explain how.

		The next_workday() and week_of_year() are not very hard, but just about anything further
		gets you into trouble. I did a bit of that below.

		To keep the code simple and comprehensible, the code below has been restricted in
		places (e.g. handling only dates after 1 Jan 1601).

	Warning: Do not try anything non-trivial with date unless you are experienced with either
		data calculations, algorithms in general, or have a good source of algorithms (in some
		language) to guide your work.

	This exercise was meant partly as a motivation for the next exercise: changing the representation
	of a date to "number of days after a designated first date" rather than (day,month,year).
	I think it succeeded all too well at that. To avoid really messy code, I first convert the
	"days after first_date".

*/

#include "std_lib_facilities.h"	

/*
	If you know the day of the week of *any* day (e.g. Jan 16, 2010 is a Saturday) and how to
	calculate leapyear() (exercise 9-10), you can find the day of the week of every day (of the
	current calendar). For example, 7 days after 1/16/2010 is another Saturday, 10 days after
	1/16/2010 is a "Saturday+3"; that is, a Tuesday. 10 days before 1/16/2010 is a "Saturday-3";
	that is, a Wednesday.
	
	Primary school children can do that by counting on their fingers; Our job is to translate
	what those children do into code (formulas) so that we can deal with larger numbers.

	So as not to try to invent everything from scratch, try typing "day of the week" into google (or equivalent).
	For more than you ever wanted to know about calendars, see http://www.tondering.dk/claus/calendar.html
	(e.g. where and when did they have a February 30th?)
*/

//_____________________________________
/*
	for simplicity of distribution on the web, I have copied the code of a Date class into this file.
	Had my aim been realism and proper code organization, I would have used a Date.h and a Date.cpp.
*/

//
// This is example code from Chapter 9.8 "The Date class" of 
// "Programming -- Principles and Practice Using C++" by Bjarne Stroustrup
//

#include <iostream>

using namespace std;

namespace Chrono {

//------------------------------------------------------------------------------

class Date {
public:
    enum Month {
        jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec
    };

	class Invalid { };                 // to throw as exception

    Date(int y, Month m, int d);       // check for valid date and initialize
    Date();                            // default constructor
    // the default copy operations are fine

    // non-modifying operations:
    int   day()   const { return d; }
    Month month() const { return m; }
    int   year()  const { return y; }

    // modifying operations:
    void add_day(int n);        
    void add_month(int n);
    void add_year(int n);
private:
    int   y;
    Month m;
    int   d;
};


bool is_date(int y, Date::Month m, int d); // true for valid date

bool leapyear(int y);                  // true if y is a leap year

bool operator==(const Date& a, const Date& b);
bool operator!=(const Date& a, const Date& b);

ostream& operator<<(ostream& os, const Date& d);
istream& operator>>(istream& is, Date& dd);

const Date& default_date();

} // Date


