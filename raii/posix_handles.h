/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RAII0X_POSIX_HANDLES_H_INCLUDED_170340e7_4b0b_4b56_bd7b_4fd1e5383963
#define RAII0X_POSIX_HANDLES_H_INCLUDED_170340e7_4b0b_4b56_bd7b_4fd1e5383963

#include <assert.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/mman.h>
#include "raii.h"

namespace raii {
namespace posix {
namespace detail {

struct dirent_handle_config
{
   typedef DIR * underlying_resource_type;
   static DIR * invalid_value() { return NULL; }
   static void dispose(DIR * dir)
   {
      int r = ::closedir(dir);
      assert(r == 0);
   }
};

struct file_descriptor_config
{
   typedef int underlying_resource_type;
   static int invalid_value() { return -1; }
   static void dispose(int fd)
   {
      int r = ::close(fd);
      assert(r == 0);
   }
};

struct map_file_view_handle_config
{
   typedef std::pair<void *, size_t> underlying_resource_type;
   static underlying_resource_type invalid_value() { return underlying_resource_type(MAP_FAILED, 0); }
   static void dispose(underlying_resource_type const & address_length)
   {
      int r = ::munmap(address_length.first, address_length.second);
      assert(r == 0);
   }
};

} // namespace detail

typedef resource<detail::dirent_handle_config>        dirent_handle;
typedef resource<detail::file_descriptor_config>      file_descriptor;
typedef resource<detail::map_file_view_handle_config> map_file_view_handle;

} // namespace posix
} // namespace raii

#endif
