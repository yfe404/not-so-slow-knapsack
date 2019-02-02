#ifndef IO_HPP
#define IO_HPP

#include <fstream>
#include "problem.hpp"

Problem readProblem(std::string fp) {
  std::vector<Item> items;
  std::ifstream infile(fp);
  int n, capacity;

  infile >> n >> capacity;
  
  for (int i = 0; i < n; ++i) {
    float v, w;
    infile >> v >> w;
    items.push_back(Item{v,w,i});
  }
  return Problem{n, capacity, items};
}

void printSolution(std::vector<int> solution, int value, int isOptimal) {
  std::cout << value << " " << isOptimal << std::endl;
  for(int item : solution) std::cout << item << " ";
}


#endif
