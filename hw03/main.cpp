#ifndef __PROGTEST__
#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <random>
#include <type_traits>

using Price = unsigned long long;
using Employee = size_t;
inline constexpr Employee NO_EMPLOYEE = -1;
using Gift = size_t;

#endif

void min_gift_cost(size_t employee, std::vector<std::pair<Price, Gift>>& cheapest_gift, std::vector<std::pair<Price, Gift>>& second_cheapest_gift, const std::vector<std::vector<size_t>>& subordinates, const std::vector<Price>& gift_price){
    size_t num_gifts = gift_price.size();
    std::vector<std::pair<Price, Gift>> gifts(num_gifts);
    for(size_t i = 0; i < num_gifts; ++i)
        gifts[i] = {gift_price[i], i};
    
    for(auto subordinate : subordinates[employee]){
        min_gift_cost(subordinate, cheapest_gift, second_cheapest_gift, subordinates, gift_price);
        for(size_t i = 0; i < num_gifts; ++i)
            gifts[i].first += (cheapest_gift[subordinate].second == i) ? second_cheapest_gift[subordinate].first : cheapest_gift[subordinate].first;
    }

    std::sort(gifts.begin(), gifts.end());
    cheapest_gift[employee] = gifts[0];
    second_cheapest_gift[employee] = gifts[1];
}

void give_gift(size_t employee, size_t parent_gift, std::vector<Gift>& gifts, const std::vector<std::pair<Price, Gift>>& cheapest_gift, const std::vector<std::pair<Price, Gift>>& second_cheapest_gift, Price& total_price, const std::vector<Price>& gift_price, const std::vector<std::vector<size_t>>& subordinates){
    gifts[employee] = (cheapest_gift[employee].second != parent_gift) ? cheapest_gift[employee].second : second_cheapest_gift[employee].second;
    total_price += gift_price[gifts[employee]];

    for(auto subordinate : subordinates[employee])
        give_gift(subordinate, gifts[employee], gifts, cheapest_gift, second_cheapest_gift, total_price, gift_price, subordinates);
}

std::pair<Price, std::vector<Gift>> optimize_gifts(const std::vector<Employee>& boss, const std::vector<Price>& gift_price){
    size_t num_employees = boss.size();
    
    std::vector<std::vector<size_t>> subordinates(num_employees);
    std::vector<size_t> top_level_employees;

    for(size_t i = 0; i < num_employees; ++i){
        if(boss[i] == NO_EMPLOYEE)
            top_level_employees.push_back(i);
        else
            subordinates[boss[i]].push_back(i);
    }

    std::vector<std::pair<Price, Gift>> cheapest_gift(num_employees, {(unsigned long int)-1, (size_t)-1}); 
    std::vector<std::pair<Price, Gift>> second_cheapest_gift(num_employees, {(unsigned long int)-1, (size_t)-1});

    for(auto employee : top_level_employees)
        min_gift_cost(employee, cheapest_gift, second_cheapest_gift, subordinates, gift_price);

    std::vector<Gift> gifts(num_employees);
    Price total_price = 0;
    
    for(auto employee : top_level_employees)
        give_gift(employee, -1, gifts, cheapest_gift, second_cheapest_gift, total_price, gift_price, subordinates);

    return {total_price, gifts};
}

#ifndef __PROGTEST__

const std::tuple<Price, std::vector<Employee>, std::vector<Price>> EXAMPLES[] = {
  { 17, {1,2,3,4,NO_EMPLOYEE}, {25,4,18,3} },
  { 16, {4,4,4,4,NO_EMPLOYEE}, {25,4,18,3} },
  { 17, {4,4,3,4,NO_EMPLOYEE}, {25,4,18,3} },
  { 24, {4,4,3,4,NO_EMPLOYEE,3,3}, {25,4,18,3} },
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Test failed: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool test(Price p, const std::vector<Employee>& boss, const std::vector<Price>& gp) {
  auto&& [ sol_p, sol_g ] = optimize_gifts(boss, gp);
  CHECK(sol_g.size() == boss.size(),
    "Size of the solution: expected %zu but got %zu.", boss.size(), sol_g.size());

  Price real_p = 0;
  for (Gift g : sol_g) real_p += gp[g];
  CHECK(real_p == sol_p, "Sum of gift prices is %llu but reported price is %llu.", real_p, sol_p);

  if (0) {
    for (Employee e = 0; e < boss.size(); e++) printf(" (%zu)%zu", e, sol_g[e]);
    printf("\n");
  }

  for (Employee e = 0; e < boss.size(); e++)
    CHECK(boss[e] == NO_EMPLOYEE || sol_g[boss[e]] != sol_g[e],
      "Employee %zu and their boss %zu has same gift %zu.", e, boss[e], sol_g[e]);

  CHECK(p == sol_p, "Wrong price: expected %llu got %llu.", p, sol_p);

  return true;
}
#undef CHECK

int main() {
  int ok = 0, fail = 0;
  for (auto&& [ p, b, gp ] : EXAMPLES) (test(p, b, gp) ? ok : fail)++;
  
  if (!fail) printf("Passed all %d tests!\n", ok);
  else printf("Failed %d of %d tests.", fail, fail + ok);
}

#endif


