#include <iostream>
#include <print>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdint>
#include <stack>
#include <cmath>
#include <vector>

int getBattery(std::string& i)
{
   int value= i[0] - '0';
   i.erase(0,1);
   return value;
}

std::int64_t getJoltage(std::string battery_bank)
{
   std::stack<int> enabled_batteries;
   enabled_batteries.push(getBattery(battery_bank));

   int batteries_left = battery_bank.length();
   while (batteries_left > 0)
   {
      int battery = getBattery(battery_bank);

      while (enabled_batteries.size() > 0 && battery > enabled_batteries.top() && enabled_batteries.size() + batteries_left > 12)
         enabled_batteries.pop();

      if (enabled_batteries.size() < 12)
         enabled_batteries.push(battery);

      batteries_left--;
   }

   std::int64_t joltage{0};
   int idx{0};
   while (enabled_batteries.empty() == false)
   {
      auto battery = enabled_batteries.top();
      joltage += battery * std::pow(10, idx);
      enabled_batteries.pop();
      idx++;
   }

   return joltage;
}

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::int64_t sum{0};

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line))
   {
      sum += getJoltage(line);
   }
   std::cout << sum << std::endl;
}

