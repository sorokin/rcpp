/*
Copyright (c) 2010, 2011 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RCPP_WIN_KERNEL_HANDLES_H_INCLUDED_b6edfa01_7d0a_4ecd_90ef_f33c166824ad
#define RCPP_WIN_KERNEL_HANDLES_H_INCLUDED_b6edfa01_7d0a_4ecd_90ef_f33c166824ad

#include <assert.h>
#include "resource.h"

namespace rcpp {
namespace win {
namespace detail {

struct file_handle_config
{
   typedef HANDLE underlying_resource_type;
   static HANDLE invalid_value() { return INVALID_HANDLE_VALUE; }
   static void dispose(HANDLE handle)
   {
      BOOL r = ::CloseHandle(handle);
      r;
      assert(r != FALSE);
   }
};

struct kernel_handle_config
{
   typedef HANDLE underlying_resource_type;
   static HANDLE invalid_value() { return NULL; }
   static void dispose(HANDLE handle)
   {
      BOOL r = ::CloseHandle(handle);
      r;
      assert(r != FALSE);
   }
};

struct find_file_handle_config
{
   typedef HANDLE underlying_resource_type;
   static HANDLE invalid_value() { return NULL; }
   static void dispose(HANDLE handle)
   {
      BOOL r = ::FindClose(handle);
      r;
      assert(r != FALSE);
   }
};

struct module_handle_config
{
   typedef HMODULE underlying_resource_type;
   static HMODULE invalid_value() { return NULL; }
   static void dispose(HMODULE module)
   {
      BOOL r = ::FreeLibrary(module);
      r;
      assert(r != FALSE);
   }
};

struct map_file_view_handle_config
{
   typedef void * underlying_resource_type;
   static void * invalid_value() { return NULL; }
   static void dispose(void * base_address)
   {
      BOOL r = ::UnmapViewOfFile(base_address);
      r;
      assert(r != FALSE);
   }
};

} // namespace detail

typedef resource<detail::file_handle_config>              file_handle;
typedef resource<detail::kernel_handle_config>            kernel_handle;
typedef resource<detail::find_file_handle_config>         find_file_handle;
typedef resource<detail::module_handle_config>            module_handle;
typedef resource<detail::map_file_view_handle_config>     map_file_view_handle;

} // namespace win
} // namespace rcpp

#endif
