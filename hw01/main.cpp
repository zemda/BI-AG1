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
    std::vector<std::vector<std::pair<size_t, int>>> graph(points, std::vector<std::pair<size_t, int>>());
    std::vector<int> distance(points, 0); //distance to the vertice from the starting point, -1 when they have indegrees at the start
    std::vector<std::pair<size_t, unsigned>> parent(points, {-size_t(2), 0}); //parent and distance between the two vertices
    std::queue<size_t> q;
    
    for (const auto& x : all_paths){ //count indegs of all vertices
        graph[x.from].push_back({x.to, x.length});
        distance[x.to] = -1; //distance vect is here used to mark vertices with indegs > 0, but since we dont need that info, we can overwrite it later with distance
    }

    for (size_t i = 0; i < points; i++) //when has indeg 0, then the possible path will be as long as possible, so we need to start our bfs from these vertices
        if (distance[i] == 0)
            q.push(i);
    
    int longest = 0;
    size_t end_point = 0;
    while(!q.empty()){
        auto c = q.front();
        q.pop();

        for (const auto& x : graph[c]){
            if (distance[x.first] < distance[c] + x.second){
                distance[x.first] = distance[c] + x.second;
                parent[x.first] = {c, x.second};
                q.push(x.first);
                
                if (longest < distance[x.first])
                    longest = distance[end_point = x.first];
            }
        }
    }
    while (parent[end_point].first != -size_t(2)){ //-size_t(2) = no vertex = we are at the start
        result.push_back({parent[end_point].first, end_point, parent[end_point].second});
        end_point = parent[end_point].first;
    }
    return std::vector<Path>(result.rbegin(), result.rend());
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