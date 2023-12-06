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

void post_order(size_t start_employee, const std::vector<std::vector<size_t>>& subordinates, std::vector<size_t>& post_order){
    std::vector<bool> visited(subordinates.size(), false);
    std::stack<size_t> s;
    s.push(start_employee);
    while (!s.empty()){
        auto employee = s.top();
        s.pop();
        post_order.push_back(employee);
        for (auto subordinate : subordinates[employee])
            if (!visited[subordinate]){
                s.push(subordinate);
                visited[subordinate] = true;
            }
    }
    std::reverse(post_order.begin(), post_order.end());
}

void min_gift_cost(const std::vector<size_t>& post_order, const std::vector<std::vector<size_t>>& subordinates, const std::vector<Price>& gift_price, std::vector<std::pair<Price, Gift>>& cheapest_gift, std::vector<std::pair<Price, Gift>>& second_cheapest_gift){
    size_t num_gifts = gift_price.size();

    for (auto employee : post_order){
        std::pair<Price, Gift> min1 = {(unsigned long long)-1, 0};
        std::pair<Price, Gift> min2 = {(unsigned long long)-1, 0};

        for(size_t i = 0; i < num_gifts; ++i){
            Price price = gift_price[i];
            for(auto subordinate : subordinates[employee])
                price += (cheapest_gift[subordinate].second == i) ? second_cheapest_gift[subordinate].first : cheapest_gift[subordinate].first;
            
            if (price < min1.first){
                min2 = min1;
                min1 = {price, i};
            }
            else if (price < min2.first)
                min2 = {price, i};
        }

        cheapest_gift[employee] = min1;
        second_cheapest_gift[employee] = min2;
    }
}

void give_gift(size_t start_employee, const std::vector<std::vector<size_t>>& subordinates, const std::vector<Price>& gift_price, const std::vector<std::pair<Price, Gift>>& cheapest_gift, const std::vector<std::pair<Price, Gift>>& second_cheapest_gift, std::vector<Gift>& gifts, Price& total_price){
    std::stack<std::pair<size_t, size_t>> stack;
    stack.push({start_employee, -1});

    while(!stack.empty()){
        auto [employee, superior_gift] = stack.top();
        stack.pop();

        gifts[employee] = (cheapest_gift[employee].second != superior_gift) ? cheapest_gift[employee].second : second_cheapest_gift[employee].second;
        total_price += gift_price[gifts[employee]];

        for(auto subordinate : subordinates[employee])
            stack.push({subordinate, gifts[employee]});
    }
}

std::pair<Price, std::vector<Gift>> optimize_gifts(const std::vector<Employee>& boss, const std::vector<Price>& gift_price){
    size_t num_employees = boss.size();
    Price total_price = 0;

    std::vector<std::vector<size_t>> subordinates(num_employees);
    std::vector<size_t> top_level_employees;

    std::vector<std::pair<Price, Gift>> cheapest_gift(num_employees, {(unsigned long int)-1, (size_t)-1});
    std::vector<std::pair<Price, Gift>> second_cheapest_gift(num_employees, {(unsigned long int)-1, (size_t)-1});

    std::vector<Gift> gifts(num_employees);

    for(size_t i = 0; i < num_employees; ++i)
        if(boss[i] == NO_EMPLOYEE)
            top_level_employees.push_back(i);
        else
            subordinates[boss[i]].push_back(i);

    for(auto employee : top_level_employees){
        std::vector<size_t> post_ord;
        post_order(employee, subordinates, post_ord);
        min_gift_cost(post_ord, subordinates, gift_price, cheapest_gift, second_cheapest_gift);
    }
    
    for(auto employee : top_level_employees)
        give_gift(employee, subordinates, gift_price, cheapest_gift, second_cheapest_gift, gifts, total_price);

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


