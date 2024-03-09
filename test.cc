#include <iostream>
#include <numeric>

#include "timebomb.hh"

constexpr bool tests[] = {
    true == cstreq("Jan  1 1980", __DATE__),
    true == cstreq(" Jan  1 1980", __DATE__),
    true == cstreq("Jan 1 1980", __DATE__),
    true == cstreq("Jan 1 1980 ", __DATE__),
    true == cstreq("Jan  1 1980 ", __DATE__),
    true == cstreq(" Jan  1 1980 ", __DATE__),
    false == cstreq("Jan  2 1980", __DATE__),
    false == cstreq("Jan  1 1981", __DATE__),
    false == cstreq("Jan  1 1981 ", __DATE__),
};
constexpr int NTests = sizeof(tests) / sizeof(tests[0]);

int main(void) {
  constexpr int passing = std::accumulate(&tests[0], &tests[NTests], 0);
  std::cout << "Passing: " << passing << " of " << NTests << std::endl;
  for (int i = 0; i < NTests; ++i)
    std::cout << "1) " << (tests[i] ? "Pass" : "Fail") << std::endl;
}
