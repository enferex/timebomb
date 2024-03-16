#ifndef __TIMEBOMB_HH
#define __TIMEBOMB_HH
#include "timebomb_internal.hh"

#define __tb_deprecate_on(_d, _msg) static_assert(!__tbIsDate(_d), _msg)
#define __tb_deprecate_after(_d, _msg) static_assert(!__tbIsAfterDate(_d), _msg)

consteval bool __tbIsDate(const char *a) {
  timebomb::Date aDate = timebomb::getMonDayYear(a);
  return (aDate.day == timebomb::TheCompilerDate.day) &&
         (aDate.month == timebomb::TheCompilerDate.month) &&
         (aDate.year == timebomb::TheCompilerDate.year);
}

// Is the current compiler time after 'd'?
consteval bool __tbIsAfterDate(const char *d) {
  timebomb::Date a = timebomb::getMonDayYear(d);
  timebomb::Date b = timebomb::TheCompilerDate;
  // b > a: "The current compiler date is after the specified date d."
  return b.year > a.year ||
         (b.year == a.year &&
          ((b.month > a.month) || (b.month == a.month && b.day > a.day)));
}

#endif  // __TIMEBOMB_HH
