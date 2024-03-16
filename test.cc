#include <iostream>
#include <numeric>

#include "example.hh"
#include "timebomb.hh"

constexpr bool tests[] = {
    /* 01 */ true == __tbIsDate2("Jan  1 1980", {1, 1, 1980}),
    /* 02 */ true == __tbIsDate2(" Jan  1 1980", {1, 1, 1980}),
    /* 03 */ true == __tbIsDate2("Jan 1 1980", {1, 1, 1980}),
    /* 04 */ true == __tbIsDate2("Jan 1 1980 ", {1, 1, 1980}),
    /* 05 */ true == __tbIsDate2("Jan  1 1980 ", {1, 1, 1980}),
    /* 06 */ true == __tbIsDate2(" Jan  1 1980 ", {1, 1, 1980}),
    /* 07 */ false == __tbIsDate2("Jan  2 1980", {1, 1, 1980}),
    /* 08 */ false == __tbIsDate2("Jan  1 1981", {1, 1, 1980}),
    /* 09 */ false == __tbIsDate2("Jan  1 1981 ", {1, 1, 1980}),
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
