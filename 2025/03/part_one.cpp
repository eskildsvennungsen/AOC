#include <iostream>
#include <fstream>
#include <print>
#include <string>
#include <filesystem>
#include <cstdint>
#include <algorithm>


std::pair<std::uint8_t, std::uint8_t> getLargestDigit(const std::string& num, const std::int16_t& start_index = -1)
{
   std::pair<std::uint8_t, std::uint16_t> max;

   std::for_each(num.begin() + start_index + 1, num.end() + (start_index == -1 ? -1 : 0), [&](auto& digit) {
      std::uint8_t n = digit - '0';
      if (n > max.first){
         max.first = n;
         max.second = &digit - &num[0];
      }
   });

   return max;
}

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::uint64_t sum{0};

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line))
   {
      auto first_digit = getLargestDigit(line);
      auto second_digit = getLargestDigit(line, first_digit.second);

      sum += first_digit.first * 10 + second_digit.first;
   }
   std::println("Sum = {}", sum);
}


