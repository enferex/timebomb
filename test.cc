#include <iostream>
#include <numeric>

#include "example.hh"
#include "timebomb.hh"

constexpr bool tests[] = {
    /* 01 */ true == timebomb::cstreq("Jan  1 1980", __DATE__),
    /* 02 */ true == timebomb::cstreq(" Jan  1 1980", __DATE__),
    /* 03 */ true == timebomb::cstreq("Jan 1 1980", __DATE__),
    /* 04 */ true == timebomb::cstreq("Jan 1 1980 ", __DATE__),
    /* 05 */ true == timebomb::cstreq("Jan  1 1980 ", __DATE__),
    /* 06 */ true == timebomb::cstreq(" Jan  1 1980 ", __DATE__),
    /* 07 */ false == timebomb::cstreq("Jan  2 1980", __DATE__),
    /* 08 */ false == timebomb::cstreq("Jan  1 1981", __DATE__),
    /* 09 */ false == timebomb::cstreq("Jan  1 1981 ", __DATE__),
    /* 10 */ true == __tbIsDate("Jan  1 1980"),
    /* 11 */ false == __tbIsDate("Jan  2 1980"),
    /* 12 */ false == __tbIsAfterDate(" Jan  2 1980"),
    /* 13 */ false == __tbIsAfterDate("Jan  2 1980 "),
    /* 14 */ false == __tbIsAfterDate("Jan 1 1980"),
    /* 15 */ true == __tbIsAfterDate("Jan 1 1970"),
};
constexpr int NTests = sizeof(tests) / sizeof(tests[0]);

int main(void) {
  constexpr int passing = std::accumulate(&tests[0], &tests[NTests], 0);
  std::cout << "Passing: " << passing << " of " << NTests << std::endl;
  for (int i = 0; i < NTests; ++i)
    std::cout << (i + 1) << ") " << (tests[i] ? "Pass" : "Fail") << std::endl;
}
