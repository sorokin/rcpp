/*
Copyright (c) 2010, 2011 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RCPP_WIN_GLRC_HANDLE_H_INCLUDED_ed2e4afe_c6b6_4d33_96ae_e2ae2d1975b4
#define RCPP_WIN_GLRC_HANDLE_H_INCLUDED_ed2e4afe_c6b6_4d33_96ae_e2ae2d1975b4

#include <assert.h>
#include "resource.h"

namespace rcpp {
namespace win {
namespace detail {

struct glrc_handle_config
{
   typedef HGLRC underlying_resource_type;
   static HGLRC invalid_value() { return NULL; }
   static void dispose(HGLRC glrc)
   {
      BOOL r = ::wglDeleteContext(glrc);
      r;
      assert(r != FALSE);
   }
};

} // namespace detail

typedef resource<detail::glrc_handle_config> glrc_handle;

} // namespace win
} // namespace rcpp

#endif
