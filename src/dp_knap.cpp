 // Example program
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>

struct item {
  int value;
  int weight;
} ;

struct Problem {
  int n;
  int capacity;
  std::vector<item> items;
};

Problem read_problem(std::string fp) {
  std::vector<item> items;
  std::ifstream infile(fp);
  int n, capacity;

  infile >> n >> capacity;
  
  for (int i = 0; i < n; ++i) {
    int v, w;
    infile >> v >> w;
    items.push_back(item{v,w});
  }
  return Problem{n, capacity, items};
 
}


void print_table(std::vector<std::vector<int> > table) {
  for(int i = 0; i < table.size(); ++i) {
      for(int j = 0; j < table[0].size(); ++j)
	std::cout << table[i][j] << " ";
      std::cout << std::endl;
    }
}

void print_solution(std::vector<int> sol) {
  for (int i = 0; i < sol.size(); ++i)
    std::cout << sol[i] << " ";
  std::cout << std::endl;
}

std::vector<std::vector<int> > get_table(int nrows, int ncols) {
  std::vector<std::vector<int> > table;
  for(int i = 0; i <= nrows; ++i) {
    table.push_back(std::vector<int>(ncols, 0));
  }

  return table;
}


int main(int argc, char const *argv[])
{

  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " PROBLEM" << std::endl;
    return 1;
  }

  auto problem = read_problem(argv[1]);
  auto items = problem.items;
  int capacity = problem.capacity;
  auto table = get_table(capacity, items.size()+1); 

  for (int idx = 0; idx < items.size(); ++idx) {
    int col = idx + 1;

    for (int row = 0; row < capacity+1; ++row) {
       
      if (items[idx].weight <= row) {
	int with_this_item = items[idx].value + table[
						      std::max(0, row-items[idx].weight)][col-1];
	int without_this_item = table[row][col-1];
	table[row][col] = std::max(with_this_item, without_this_item);
      } else {
	table[row][col] = table[row][col-1];
      }
    }
  }

  // Trace back
  std::vector<int> solution(items.size(), 0);
  int curr_line = capacity;
  int obj = 0;
  const int opt = 1;
  
  for(int i = items.size(); i > 0; --i) {
    if (table[curr_line][i] == table[curr_line][i-1]) {
      solution[i-1] = 0;
    } else {
      curr_line = curr_line - items[i-1].weight;
      solution[i-1] = 1;
      obj += items[i-1].value;
    }
  }
  
  //  print_table(table);
  std::cout << obj << " " << opt << std::endl;
  print_solution(solution);
}
