#ifndef PROBLEM_HPP
#define PROBLEM_HPP

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


#endif
