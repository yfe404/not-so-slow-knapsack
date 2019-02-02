#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include <ostream>
#include <vector>

struct Item {
  float value;
  float weight;
  int id;
} ;

struct Node {
  int room;
  std::vector<int> local_constraint; // indexes of the items to take
  std::vector<int> constraints; // local constraints too but relative to estimation
  int estimation = 0;
  int value = 0;
};

struct Problem {
  int n;
  int capacity;
  std::vector<Item> items;
};


std::ostream& operator << (std::ostream& o, const Item& a) {
  o << "(weight: " << a.weight << ", value: " << a.value << ")";
  return o;
}

std::ostream& operator << (std::ostream& o, const Node& a) {
  o << "Optimistic estimation: " << a.estimation << std::endl;
  o << "Value: " << a.value << std::endl;
  o << "Capacity left: " << a.room << std::endl;

  return o;
}

// Sort by descending order (best value first)
bool sortByDensity(const Item& lhs, const Item& rhs) {
  return (lhs.value/lhs.weight) > (rhs.value/rhs.weight);
}

int greedy_score(const std::vector<Item>& items, int capacity) {
  int value = 0;
  int room = capacity;

  for(auto item : items) {
    if (item.weight > room) continue;
    room -= item.weight;
    value += item.value;
  }

  return value;
}


#endif
