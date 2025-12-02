#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <string>

constexpr int MAX_LOCK_NUM = 100;

int parse_input(const std::string& input)
{
   char rotation_direction = input[0];
   int unsigned_value = std::stoi(input.substr(1));
   return (rotation_direction == 'R') ? unsigned_value : unsigned_value * -1;
}

int task_one(int start_index, std::vector<int>& input)
{
   int index = start_index;
   int pwd = 0;

   for (const auto& value : input)
   {
      index = (index + value + MAX_LOCK_NUM) % MAX_LOCK_NUM;

      if (index == 0)
         pwd++;
   }
   return pwd;
}

int task_two(int start_index, std::vector<int>& input)
{
   int curr_pos = start_index;
   int pwd = 0;

   for (const auto& value : input)
   {
      bool was_zero = curr_pos == 0;
      curr_pos += value;

      if (curr_pos < 0 && !was_zero)
      {
         pwd++;
      }

      pwd += std::abs(curr_pos) / MAX_LOCK_NUM;

      if (curr_pos == 0)
      {
         pwd++;
      }

      curr_pos = ((curr_pos % 100) + 100) % 100;
   }
   return pwd;
}

int main(int argc, char* argv[])
{
   std::string f_name = "rsc/input.txt";

   int index = 0;

   if (argc > 1)
   {
      index = std::stoi(argv[1]);
   }

   std::fstream rsc_file(f_name);
   std::vector<int> parsed_file_input;
   std::string line;
   while(std::getline(rsc_file, line))
   {
      parsed_file_input.push_back(parse_input(line));
   }

   int task_one_pwd = task_one(index, parsed_file_input);
   int task_two_pwd = task_two(index, parsed_file_input);

   std::printf("Task #1 PWD: %d\n", task_one_pwd);
   std::printf("Task #2 PWD: %d\n", task_two_pwd);
}
