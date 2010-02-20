#include <algorithm>
#include <iostream>
#include <vector>
#include "rcpp/posix_handles.h"

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
   std::vector<rcpp::posix::file_handle> v;

   for (size_t i = 0; i < 10; ++i)
      v.push_back(rcpp::posix::file_handle(::open("test.txt", O_RDONLY)));

   for (auto i = v.cbegin(); i != v.cend(); ++i)
      std::cout << i->get() << ", ";
   std::cout << std::endl;

   std::random_shuffle(v.begin(), v.end());

   for (auto i = v.cbegin(); i != v.cend(); ++i)
      std::cout << i->get() << ", ";
   std::cout << std::endl;

   return EXIT_SUCCESS;
}
