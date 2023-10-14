#ifndef __PROGTEST__
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t {};

struct Path {
  Point from, to;
  unsigned length;

  Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

  friend bool operator == (const Path& a, const Path& b) {
    return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
  }
  
  friend bool operator != (const Path& a, const Path& b) { return !(a == b); }
};

#endif


std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths){

    std::vector<Path> result;
    std::unordered_map<size_t, std::vector<Path>> graph;
    std::unordered_map<size_t, unsigned> in_degree;
    std::queue<size_t> q;
    std::unordered_map<size_t, unsigned> distance;
    std::unordered_map<size_t, std::pair<size_t, unsigned>> parent;

    for (size_t i = 0; i < points; i++){
        in_degree[i] = 0;
    }
    
    for (auto& x : all_paths){
        graph[x.from].push_back(x);
        in_degree[x.to]++;
    }

    for (auto& x : in_degree){
        if (x.second == 0){
            q.push(x.first);
            distance[x.first] = 0;
            parent[x.first] = {-size_t(2), 0};
        }
    }

    unsigned longest = 0;
    size_t to_longest = 0;
    while(!q.empty()){
        auto c = q.front();
        q.pop();

        for (auto& x : graph[c]){
            if (distance.count(x.to) == 0 || distance[x.to] < distance[c] + x.length){
                distance[x.to] = distance[c] + x.length;
                parent[x.to] = {c, x.length};
                q.push(x.to);

                if (longest < distance[x.to]){
                    longest = distance[x.to];
                    to_longest = x.to;
                }
            }
        }
    }
    size_t cur = to_longest;
    while (parent[cur].first != -size_t(2)){
        auto x = parent[cur];
        result.push_back({x.first, cur, x.second});
        cur = x.first;
    }
    std::reverse(result.begin(), result.end());
    return result;
}


#ifndef __PROGTEST__


struct Test {
  unsigned longest_track;
  size_t points;
  std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
  {13, 5, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1} } },
  {11, 5, { {3,2,10}, {3,1,4}, {1,2,3}, {2,4,1} } },
  {16, 8, { {3,2,10}, {3,1,1}, {1,2,3}, {1,4,15} } },
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test& t) {
  auto sol = longest_track(t.points, t.all_paths);

  unsigned length = 0;
  for (auto [ _, __, l ] : sol) length += l;

  CHECK(t.longest_track == length,
    "Wrong length: got %u but expected %u", length, t.longest_track);

  for (size_t i = 0; i < sol.size(); i++) {
    CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
      "Solution contains non-existent path: %zu -> %zu (%u)",
      sol[i].from, sol[i].to, sol[i].length);

    if (i > 0) CHECK(sol[i].from == sol[i-1].to,
      "Paths are not consecutive: %zu != %zu", sol[i-1].to, sol[i].from);
  }

  return true;
}
#undef CHECK

int main() {
  int ok = 0, fail = 0;

  for (auto&& t : TESTS) (run_test(t) ? ok : fail)++;
  
  if (!fail) printf("Passed all %i tests!\n", ok);
  else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif


