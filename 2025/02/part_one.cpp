#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <cstdint>
#include <sstream>

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::uint64_t sum{0};

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line, ','))
   {
      std::uint64_t lower_bound, upper_bound;
      char dash;
      std::stringstream ss(line);

      ss >> lower_bound >> dash >> upper_bound;

      for (std::uint64_t i{lower_bound}; i <= upper_bound; i++)
      {
         std::string number = std::to_string(i);
         std::uint16_t n_digits = number.length();

         if (n_digits % 2 != 0)
            continue;

         if (number.substr(0, n_digits / 2) == number.substr(n_digits / 2))
            sum += i;
      }
   }
   std::cout << sum << std::endl;
}

