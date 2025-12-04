#include <iostream>
#include <fstream>
#include <print>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdint>
#include <algorithm>

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::uint64_t sum{0};

   char roll = '@';
   char accessable = 'X';

   std::vector<std::string> storage;

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line))
   {
      storage.push_back(line);
   }

   int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
   int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

   int rows = storage.size();
   int cols = storage[0].size();

   while (true)
   {
      int t_sum{0};

      for (int i{0}; i < rows; i++)
      {
         std::for_each(storage.begin(), storage.end(), [&](std::string& s){ 
            std::for_each(s.begin(), s.end(), [&](char& c){ if (c == accessable) c = '.'; });
         });

         for (int j{0}; j < cols; j++)
         {
            if (storage[i][j] != roll)
               continue;

            int adjacent{0};

            for (int k{0}; k < 8; k++)
            {
               int y = i + dy[k];
               int x = j + dx[k];

               if (x >= cols || x < 0 || y >= rows || y < 0)
                  continue;

               char neighbour = storage[y][x];
               if (neighbour == accessable || neighbour == roll)
                  adjacent++;
            }

            if (adjacent < 4){
               storage[i][j] = accessable;
               t_sum++;
            }
         }
      }

      if (sum == sum + t_sum)
         break;

      sum += t_sum;
   }
   std::cout << sum << std::endl;
}
