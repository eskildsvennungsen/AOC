#include <fstream>
#include <print>
#include <string>
#include <vector>
#include <filesystem>
#include <cstdint>
#include <algorithm>

template <typename T>
void merge(std::vector<std::pair<T,T>>& range)
{
   std::sort(range.begin(), range.end());

   std::vector<std::pair<T,T>> merged = {range[0]};

   for (auto i{range.begin() + 1}; i < range.end(); i++)
   {
      auto* l_m = &merged.back();
      if (i->first >= l_m->first && i->first <= l_m->second){
         l_m->second = std::max(i->second, l_m->second);
      } else {
         merged.push_back(*i);
      }
   } 

   range = merged;
}

int main(int argc, char* argv[])
{
   std::string file_name = "rsc/input.txt";
   std::filesystem::path path = std::filesystem::absolute(argv[0]).parent_path() / file_name;

   std::uint64_t sum{0};

   std::vector<std::pair<std::uint64_t, std::uint64_t>> id_range;
   std::vector<std::uint64_t> id;

   std::fstream file(path);
   std::string line;
   while(std::getline(file, line))
   {
      if (line.empty())
         break;

      std::uint16_t idx = line.find('-');
      std::uint64_t l_b = std::stoull(line.substr(0, idx));
      std::uint64_t u_b = std::stoull(line.substr(idx + 1));
      std::pair<std::uint64_t, std::uint64_t> candidate(l_b, u_b);

      id_range.push_back(candidate);
   }
   merge(id_range);

   while(std::getline(file, line))
   {
      id.push_back(std::stoull(line));
   }

   for (const auto& i : id)
   {
      for (const auto range : id_range)
      {
         if (i < range.first || i > range.second)
            continue;

         sum++;
         break;
      }
   }

   std::println("{}", sum);
}
