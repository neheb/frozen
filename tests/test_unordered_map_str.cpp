#include <chrono>
#include <frozen/string.h>
#include <frozen/unordered_map.h>
#include <iostream>
#include <unordered_map>

#include "bench.hpp"
#include "catch.hpp"

TEST_CASE("frozen::unordered_map<str, int> <> std::unordered_map",
          "[unordered_map]") {
#define INIT_SEQ                                                               \
  {"19", 19}, {"1", 1}, {"2", 2}, {"4", 4}, {"5", 5}, {"6", 6},    \
      {"7", 7}, {"8", 8}, {"9", 9}, {"10", 10}, {"11", 11},          \
      {"111", 111}, {"1112", 1112}, {"1115", 1115}, {"1118", 1118},    \
      {"1110", 1110}, {"1977", 1977}, {"177", 177}, {"277", 277},      \
      {"477", 477}, {"577", 577}, {"677", 677}, {"777", 777},          \
      {"877", 877}, {"977", 977}, {"1077", 1077}, {"1177", 1177},      \
      {"11177", 11177}, {"111277", 111277}, {"111577", 111577},          \
      {"111877", 111877}, {"111077", 111077}, {"1999", 1999},            \
      {"199", 199}, {"299", 299}, {"499", 499}, {"599", 599},          \
      {"699", 699}, {"799", 799}, {"899", 899}, {"999", 999},          \
      {"1099", 1099}, {"1199", 1199}, {"11199", 11199},                  \
      {"111299", 111299}, {"111599", 111599}, {"111899", 111899},        \
      {"111099", 111099}, {"197799", 197799}, {"17799", 17799},          \
      {"27799", 27799}, {"47799", 47799}, {"57799", 57799},              \
      {"67799", 67799}, {"77799", 77799}, {"87799", 87799},              \
      {"97799", 97799}, {"107799", 107799}, {"117799", 117799},          \
      {"1117799", 1117799}, {"11127799", 11127799},                        \
      {"11157799", 11157799}, {"11187799", 11187799},                      \
      {"11107799", 11107799}, {"1988", 1988}, {"188", 188},              \
      {"288", 288}, {"488", 488}, {"588", 588}, {"688", 688},          \
      {"788", 788}, {"888", 888}, {"988", 988}, {"1088", 1088},        \
      {"1188", 1188}, {"11188", 11188}, {"111288", 111288},              \
      {"111588", 111588}, {"111888", 111888}, {"111088", 111088},        \
      {"197788", 197788}, {"17788", 17788}, {"27788", 27788},            \
      {"47788", 47788}, {"57788", 57788}, {"67788", 67788},              \
      {"77788", 77788}, {"87788", 87788}, {"97788", 97788},              \
      {"107788", 107788}, {"117788", 117788}, {"1117788", 1117788},      \
      {"11127788", 11127788}, {"11157788", 11157788},                      \
      {"11187788", 11187788}, {"11107788", 11107788},                      \
      {"199988", 199988}, {"19988", 19988}, {"29988", 29988},            \
      {"49988", 49988}, {"59988", 59988}, {"69988", 69988},              \
      {"79988", 79988}, {"89988", 89988}, {"99988", 99988},              \
      {"109988", 109988}, {"119988", 119988}, {"1119988", 1119988},      \
      {"11129988", 11129988}, {"11159988", 11159988},                      \
      {"11189988", 11189988}, {"11109988", 11109988},                      \
      {"19779988", 19779988}, {"1779988", 1779988},                        \
      {"2779988", 2779988}, {"4779988", 4779988}, {"5779988", 5779988},  \
      {"6779988", 6779988}, {"7779988", 7779988}, {"8779988", 8779988},  \
      {"9779988", 9779988}, {"10779988", 10779988},                        \
      {"11779988", 11779988}, {"111779988", 111779988},                    \
      {"1112779988", 1112779988}, {"1115779988", 1115779988},              \
      {"1118779988", 1118779988}, {                                          \
    "1110779988", 1110779988                                                 \
  }

  const std::unordered_map<frozen::string, int> std_map = {INIT_SEQ};
  constexpr frozen::unordered_map<frozen::string, int, 128> frozen_map = {
      INIT_SEQ};
  REQUIRE(std_map.size() == frozen_map.size());

  SECTION("checking size and content") {
    REQUIRE(std_map.size() == frozen_map.size());
    for (auto v : std_map)
      REQUIRE(frozen_map.count(v.first));

    for (auto v : frozen_map)
      REQUIRE(std_map.count(v.first));
  }

  SECTION("checking minimal performance requirements") {
    std::initializer_list<std::pair<frozen::string, int>> data = {INIT_SEQ};
    auto std_start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i)
      for (auto val : data) {
        benchmark::DoNotOptimize(val);
        benchmark::DoNotOptimize(std_map.count(val.first));
      }
    auto std_stop = std::chrono::steady_clock::now();
    auto std_diff = std_stop - std_start;
    auto std_duration =
        std::chrono::duration<double, std::milli>(std_diff).count();
    std::cout << "std::unordered_map<str, int>: " << std_duration << " ms"
              << std::endl;

    auto frozen_start = std::chrono::steady_clock::now();
    for (int i = 0; i < 10000; ++i)
      for (auto val : data) {
        benchmark::DoNotOptimize(val);
        benchmark::DoNotOptimize(frozen_map.count(val.first));
      }
    auto frozen_stop = std::chrono::steady_clock::now();
    auto frozen_diff = frozen_stop - frozen_start;
    auto frozen_duration =
        std::chrono::duration<double, std::milli>(frozen_diff).count();
    std::cout << "frozen::unordered_map<str, int>: " << frozen_duration << " ms"
              << std::endl;

    REQUIRE(std_duration > frozen_duration);
  }
}

TEST_CASE("various frozen::unordered_map config", "[unordered_map]") {
  constexpr frozen::unordered_map<frozen::string, int, 2> olaf0 = {
      {"19", 19},
      {"31", 31},
  };
  constexpr frozen::unordered_map<frozen::string, int, 6> olaf1 = {
      {"19", 19},
      {"31", 31},
      {"coucou", 10},
      {"hello my world!!", 1000},
      {"nice damn shit", 14},
      {"pouet", 11},
  };
}
