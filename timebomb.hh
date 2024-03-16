// This is free and unencumbered software released into the public domain.
// 
// Anyone is free to copy, modify, publish, use, compile, sell, or
// distribute this software, either in source code form or as a compiled
// binary, for any purpose, commercial or non-commercial, and by any
// means.
// 
// In jurisdictions that recognize copyright laws, the author or authors
// of this software dedicate any and all copyright interest in the
// software to the public domain. We make this dedication for the benefit
// of the public at large and to the detriment of our heirs and
// successors. We intend this dedication to be an overt act of
// relinquishment in perpetuity of all present and future rights to this
// software under copyright law.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
// OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
// 
// For more information, please refer to <https://unlicense.org>

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
