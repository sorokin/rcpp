/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RCPP_WIN_GDI_HANDLES_H_INCLUDED_0075b3b7_1ee9_4b70_910d_853bb6899eca
#define RCPP_WIN_GDI_HANDLES_H_INCLUDED_0075b3b7_1ee9_4b70_910d_853bb6899eca

#include <assert.h>
#include "resource.h"

namespace rcpp {
namespace win {
namespace detail {

struct accelerator_table_handle_config
{
   typedef HACCEL underlying_resource_type;
   static HACCEL invalid_value() { return NULL; }
   static void dispose(HACCEL accel)
   {
      BOOL r = ::DestroyAcceleratorTable(accel);
      r;
      assert(r != FALSE);
   }
};

struct gdiobj_handle_config
{
   typedef HGDIOBJ underlying_resource_type;
   static HGDIOBJ invalid_value() { return NULL; }
   static void dispose(HGDIOBJ gdiobj)
   {
      BOOL r = ::DeleteObject(gdiobj);
      r;
      assert(r != FALSE);
   }
};

struct cursor_handle_config
{
   typedef HCURSOR underlying_resource_type;
   static HCURSOR invalid_value() { return NULL; }
   static void dispose(HCURSOR cursor)
   {
      BOOL r = ::DestroyCursor(cursor);
      r;
      assert(r != FALSE);
   }
};

struct icon_handle_config
{
   typedef HICON underlying_resource_type;
   static HICON invalid_value() { return NULL; }
   static void dispose(HICON icon)
   {
      BOOL r = ::DestroyIcon(icon);
      r;
      assert(r != FALSE);
   }
};

struct menu_handle_config
{
   typedef HMENU underlying_resource_type;
   static HMENU invalid_value() { return NULL; }
   static void dispose(HMENU menu)
   {
      BOOL r = ::DestroyMenu(menu);
      r;
      assert(r != FALSE);
   }
};

struct window_handle_config
{
   typedef HWND underlying_resource_type;
   static HWND invalid_value() { return NULL; }
   static void dispose(HWND window)
   {
      BOOL r = ::DestroyWindow(window);
      r;
      assert(r != FALSE);
   }
};

struct common_dc_handle_config
{
   typedef std::pair<HWND, HDC> underlying_resource_type;
   static underlying_resource_type invalid_value() { return underlying_resource_type(NULL, NULL); }
   static void dispose(underlying_resource_type const & wnd_dc)
   {
      BOOL r = ::ReleaseDC(wnd_dc.first, wnd_dc.second);
      r;
      assert(r != FALSE);
   }
};

struct dc_handle_config
{
   typedef HDC underlying_resource_type;
   static HDC invalid_value() { return NULL; }
   static void dispose(HDC dc)
   {
      BOOL r = ::DeleteDC(dc);
      r;
      assert(r != FALSE);
   }
};

} // namespace detail

typedef resource<detail::accelerator_table_handle_config> accelerator_table_handle;
typedef resource<detail::gdiobj_handle_config>            gdiobj_handle;
typedef resource<detail::cursor_handle_config>            cursor_handle;
typedef resource<detail::icon_handle_config>              icon_handle;
typedef resource<detail::menu_handle_config>              menu_handle;
typedef resource<detail::window_handle_config>            window_handle;
typedef resource<detail::common_dc_handle_config>         common_dc_handle;
typedef resource<detail::dc_handle_config>                dc_handle;

} // namespace win
} // namespace rcpp

#endif
