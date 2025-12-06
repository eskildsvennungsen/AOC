#include <iostream>
#include <sstream>
#include <fstream>
#include <print>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdint>
#include <algorithm>

void calculate(std::vector<std::vector<int>>& data, char operation, int idx, std::uint64_t& ret)
{
   std::uint64_t sum{0};
   for (size_t i{0}; i < data.size(); i++)
   {
      if (operation == '*')
      {
         sum = (sum == 0 ? data[i][idx] : sum * data[i][idx]);
      } else
      {
         sum += data[i][idx];
      }
   }
   ret += sum;
}

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::uint64_t sum{0};
   std::vector<std::vector<int>> data;

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line))
   {
      std::vector<int> row;
      std::stringstream ss(line);
      std::string entry;
      int idx{0};
      while (ss >> entry)
      {
         if (entry[0] == '+' || entry[0] == '*'){
            calculate(data, entry[0], idx++, sum);
            continue;
         }
         row.push_back(std::stoi(entry));
      }
      data.push_back(row);
   }
   std::cout << sum << std::endl;
}
