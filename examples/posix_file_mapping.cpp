/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sysexits.h>
#include "rcpp/posix_handles.h"

#include <stdexcept>
#include <iostream>

namespace
{
   rcpp::posix::map_file_view_handle create_file_view(size_t length, int prot, int flags, rcpp::posix::file_handle const & fd, off_t offset)
   {
      void * address = ::mmap(NULL, length, prot, flags, fd.get(), offset);
      if (address == MAP_FAILED)
         throw std::runtime_error("failed to mmap file");

      return rcpp::posix::map_file_view_handle(rcpp::posix::map_file_view_handle::underlying_resource_type(address, length));
   }
}

int main(int argc, char ** argv)
{
   if (argc != 2)
      return EX_USAGE;

   try
   {
      rcpp::posix::file_handle fd(::open(argv[1], O_RDONLY));
      if (!fd)
         return EX_NOINPUT;

      size_t file_size = lseek(fd.get(), 0, SEEK_END);

      rcpp::posix::map_file_view_handle file_view = create_file_view(file_size, PROT_READ, MAP_PRIVATE, fd, 0);

      ::fwrite(file_view.get().first, 1, file_view.get().second, stdout);
   }
   catch (std::exception const & e)
   {
      std::cerr << "error: " << e.what() << std::endl;
      return EXIT_FAILURE;
   }

   return EXIT_SUCCESS;
}
