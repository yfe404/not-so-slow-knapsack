 // Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "io.hpp"
#include "problem.hpp"


using namespace std;

#define N_THREAD 1

std::ostream& operator << (std::ostream& o, const Item& a) {
  o << "(weight: " << a.weight << ", value: " << a.value << ")";
  return o;
}

// Sort by descending order (best value first)
bool sortByDensity(const Item& lhs, const Item& rhs) {
  return (lhs.value/lhs.weight) > (rhs.value/rhs.weight);
}


std::ostream& operator << (std::ostream& o, const Node& a) {
  o << "Optimistic estimation: " << a.estimation << endl;
  o << "Value: " << a.value << endl;
  o << "Capacity left: " << a.room << endl;

  return o;
}


template<typename T>
void printVector(std::vector<T> vect) {
  for (int i = 0; i < vect.size(); ++i)
    std::cout << vect[i] << " ";
  std::cout << std::endl;
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

void optimisticEstimation(Node* node, const std::vector<Item>& sortedItems, int capacity) {
  node->estimation = 0;
  node->value = 0;
  node->room = capacity;
  int room = capacity;

  for(int i : node->local_constraint) {
    room -= sortedItems[i].weight;
  }
  for(int i : node->local_constraint) {
    node->estimation += sortedItems[i].value;
    node->constraints[i] = 0; // prevent from using the item twice
  }
  
  for(int i = 0; i < sortedItems.size(); ++i) {
    if (room == 0) break;

    if (node->constraints[i] != 0) {
	if (sortedItems[i].weight <= room) {
	  room -= sortedItems[i].weight;
	  node->estimation += sortedItems[i].value;
	} else {
	  node->estimation += sortedItems[i].value * (room/sortedItems[i].weight);
	  room = 0;
      } 
    }
  }
  for(int i : node->local_constraint) {
    node->room -= sortedItems[i].weight;
  }
  for(int i : node->local_constraint) {
    node->value += sortedItems[i].value;
    node->constraints[i] = 1; // restoring value
  }
}

void processNode(int th_num, const vector<Node>& treeFront, vector<Node>* dest, const std::vector<Item>& items, int capacity, int best_value, int i) {
}


int main(int argc, char**argv){

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " PROBLEM" << std::endl;
    return 1;
  }

  auto problem = readProblem(argv[1]);
  auto items = problem.items;
  int capacity = problem.capacity;

  vector<int> best_solution(items.size(), 0);
  
  std::sort(items.begin(), items.end(), sortByDensity);

  int best_value = greedy_score(items, capacity);

  // Init
  Node root;
  vector<Node> treeFront;
  vector<Node> newTreeFront;
  
  root.constraints = vector<int>(items.size(), 1);
  optimisticEstimation(&root, items, capacity);

  treeFront.push_back(root);
  
  for(int i = 0; i < items.size(); ++i) {
    if (treeFront.size() == 0) break;
    newTreeFront.clear();

    Node left, right;
    
    for (auto& n : treeFront) {
      if (n.room > 0 && n.estimation > best_value) {
      left.local_constraint = n.local_constraint;
      left.constraints = n.constraints;
      left.local_constraint.push_back(i);
      optimisticEstimation(&left, items, capacity);
      newTreeFront.push_back(left);
    
      right.local_constraint = n.local_constraint;
      right.constraints = n.constraints;
      right.constraints[i] = 0;
      optimisticEstimation(&right, items, capacity);
      newTreeFront.push_back(right);
    }
  }


    treeFront.assign(newTreeFront.begin(), newTreeFront.end());
  
    for (auto  n : treeFront) {
      if (n.room >= 0) {
	if (n.value > best_value) {
	  best_value = n.value;
	  best_solution = n.local_constraint;
	  //	  cout << n; // Uncomment to print intermermediate (valid) solutions
	}
      }
    }
  }
  
  // Build the solution vector
  vector<int> temp(items.size(),0);
  for (int i = 0; i < items.size(); ++i) {
    if(std::find(best_solution.begin(), best_solution.end(), i) != best_solution.end()) {
      temp[i] = 1;
    } else {
      temp[i] = 0;
    }
  }
  
  vector<int> sol(items.size(),0);
  cout << best_value << " " << 1 << endl;
  for (int i = 0; i < items.size(); ++i) {
    sol[items[i].id] = temp[i]; 
  }

  printVector(sol);

}
