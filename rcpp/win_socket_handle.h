/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RCPP_WIN_SOCKET_HANDLE_H_INCLUDED_9d4a28d5_beee_4854_b2af_ad4073a6a25f
#define RCPP_WIN_SOCKET_HANDLE_H_INCLUDED_9d4a28d5_beee_4854_b2af_ad4073a6a25f

#include <assert.h>
#include "resource.h"

namespace rcpp {
namespace win {
namespace detail {

struct socket_handle_config
{
   typedef SOCKET underlying_resource_type;
   static SOCKET invalid_value() { return INVALID_SOCKET; }
   static void dispose(SOCKET sock)
   {
      int r = ::closesocket(sock);
      assert(r == 0);
   }
};

} // namespace detail

typedef resource<detail::socket_handle_config> socket_handle;

} // namespace win
} // namespace rcpp

#endif
