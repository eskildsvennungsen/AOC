#include <iostream>
#include <print>
#include <sstream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <filesystem>
#include <cstdint>
#include <algorithm>

template <typename T>
void calculate(std::vector<T>& vec, char op, T& ret){
   std::int64_t s_0{0};
   std::for_each(vec.begin(), vec.end(), [&](std::int64_t x){
      if (op == '+'){
         s_0 += x;
      } else {
         s_0 = (s_0 == 0 ? x : x * s_0);
      }
   });
   ret += s_0;
   vec.clear();
}

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::int64_t sum{0};
   std::vector<std::string> data;
   std::string ops;

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line))
   {
      if (line.find('+')  == std::string::npos)
      {
         data.push_back(line);
      } else
      {
         ops = line;
      }
   }

   int rows = data.size();
   int cols = data[0].length();
   char curr_op;

   std::vector<std::int64_t> d_0;
   for (int i{0}; i < cols; i++)
   {
      std::string num;

      if (ops[i] != ' ')
         curr_op = ops[i];

      for (int j{0}; j < rows; j++)
      {
         char field = data[j][i]; 
         if (!std::isdigit(field)){
            continue;
         }
         num.push_back(field);
      }

      if (num.empty()) {
         calculate(d_0, curr_op, sum);
      } else {
         d_0.push_back(std::stoll(num));
      }
   }
   calculate(d_0, curr_op, sum);
   std::cout << sum << std::endl;
}
