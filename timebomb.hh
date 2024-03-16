#ifndef __TIMEBOMB_HH
#define __TIMEBOMB_HH

#define __tb_deprecate_on(_d, _msg) static_assert(__tbIsDate(_d), _msg)
#define __tb_deprecate_after(_d, _msg) static_assert(__tbIsAfterDate(_d), _msg)

namespace timebomb {
static consteval bool cstreq(const char *a, const char *b) {
  if (!a || !b) return false;
  while (*a && *b) {
    bool hasWS = *a == ' ' || *b == ' ';
    while (*a == ' ') ++a;
    while (*b == ' ') ++b;
    if (!hasWS) {
      ++b;
      ++a;
    }
    if (*a != *b) break;
  }

  while (*a == ' ') ++a;
  while (*b == ' ') ++b;
  return *a == '\0' && *b == '\0';
}

struct Date {
  // Jan  1 1970
  int month, day, year;
};

consteval char tolower(char c) {
  return (c >= 'a' && c <= 'z')   ? c
         : (c >= 'A' && c <= 'Z') ? ('a' + ('Z' - c))
                                  : 0;
}

consteval int monthKey(const char mon[3]) {
  return mon[0] + (mon[1] + 26) + (mon[2] + (26 * 2));
}

consteval Date getMonDayYear(const char *date) {
  if (!date) return {0, 0, 0};
  const char *d = (const char *)date;

  // Get the three char month, this is converted to a month number below.
  // Jan  1 1970
  // ^
  int i = 0;
  char month[3]{};
  while (*d == ' ') ++d;
  while ((*d >= 'a' || *d >= 'A') && (*d <= 'z' || *d <= 'Z'))
    month[++i % 3] = tolower(*d), ++d;

  // Advance to start the start of the day value.
  // Jan  1 1970
  // ...--^
  int day = 0;
  while (!(*d >= '0' && *d <= '9')) ++d;
  while ((*d >= '0' && *d <= '9')) day = (10 * day) + (*d - '0'), ++d;

  // Advance to the start of the year value.
  // Jan  1 1970
  // ......-^
  int year = 0;
  while (!(*d >= '0' && *d <= '9')) ++d;
  while ((*d >= '0' && *d <= '9')) year = (10 * year) + (*d - '0'), ++d;

  // Convert the month abbreviation into a numeric value.
  // clang-format off
  int mon = 0;
  switch (monthKey(month)) {
    case monthKey("jan"): mon = 1; break;
    case monthKey("feb"): mon = 2; break;
    case monthKey("mar"): mon = 3; break;
    case monthKey("apr"): mon = 4; break;
    case monthKey("may"): mon = 5; break;
    case monthKey("jun"): mon = 6; break;
    case monthKey("jul"): mon = 7; break;
    case monthKey("aug"): mon = 8; break;
    case monthKey("sep"): mon = 9; break;
    case monthKey("oct"): mon = 10; break;
    case monthKey("nov"): mon = 11; break;
    case monthKey("dec"): mon = 12; break;
  }  // clang-format on

  return {mon, day, year};
}

static constexpr Date TheCompilerDate = getMonDayYear((char *)__DATE__);
};  // namespace timebomb

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
