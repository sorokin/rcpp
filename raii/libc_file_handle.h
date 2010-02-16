/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RAII0X_LIBC_FILE_HANDLE_H_INCLUDED_b3b7c9e6_aec1_400c_85ba_8cfad4e8c3b7
#define RAII0X_LIBC_FILE_HANDLE_H_INCLUDED_b3b7c9e6_aec1_400c_85ba_8cfad4e8c3b7

#include <assert.h>
#include <stdio.h>
#include "raii.h"

namespace raii {
namespace libc {
namespace detail {

struct file_handle_config
{
   typedef FILE * underlying_resource_type;
   static FILE * invalid_value() { return NULL; }
   static void dispose(FILE * file)
   {
      int r = ::fclose(file);
      assert(r == 0);
   }
};

} // namespace detail

typedef resource<detail::file_handle_config> file_handle;

} // namespace libc
} // namespace raii

#endif
