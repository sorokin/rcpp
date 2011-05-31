/*
Copyright (c) 2010, 2011 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#include <assert.h>
#include <sysexits.h>
#include "rcpp/libc_file_handle.h"

size_t const READ_BUFFER_SIZE = 32 * 1024;

int main(int argc, char ** argv)
{
   if (argc == 1)
   {
      printf("usage: %s [files]\n", argv[0]);
      return EX_USAGE;
   }

   for (int i = 1; i < argc; ++i)
   {
      rcpp::libc::file_handle file(::fopen(argv[i], "rb"));
      if (!file)
      {
         printf("failed to open \"%s\"\n", argv[i]);
         return EX_NOINPUT;
      }

      for (;;)
      {
         if (::feof(file.get()))
            break;

         char buf[READ_BUFFER_SIZE];
         size_t read = ::fread(buf, 1, READ_BUFFER_SIZE, file.get());
         if (read != READ_BUFFER_SIZE)
         {
            if (::ferror(file.get()))
               return EX_IOERR;

            assert(::feof(file.get()));
         }

         size_t written = ::fwrite(buf, 1, read, stdout);
         if (written != read)
            return EX_IOERR;
      }
   }

   return EXIT_SUCCESS;
}

