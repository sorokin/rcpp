/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#include "stdio.h"

// rcpp::resource is localed here
#include "rcpp/resource.h"

// this is a resource config, it contains only three things
struct file_handle_config
{
   // create resource wrapper over FILE *
   typedef FILE * underlying_resource_type;
   
   // invalid value is NULL
   static FILE * invalid_value() { return NULL; }
   
   // dispose function is fclose
   static void dispose(FILE * f)
   {
      fclose(f);
   }
};

// give a short name for resource...
typedef rcpp::resource<file_handle_config> file_handle;

int main()
{
   // ... and use it
   file_handle f(fopen("test.txt", "r"));

   // work with file
   // it will be closed automatically

   return EXIT_SUCCESS;
}
