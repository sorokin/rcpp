/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RAII0X_WIN_GDI_HANDLES_H_INCLUDED_0075b3b7_1ee9_4b70_910d_853bb6899eca
#define RAII0X_WIN_GDI_HANDLES_H_INCLUDED_0075b3b7_1ee9_4b70_910d_853bb6899eca

#include <assert.h>
#include "raii.h"

namespace raii {
namespace win {
namespace detail {

struct accelerator_table_handle_config
{
   typedef HACCEL underlying_resource_type;
   static HACCEL invalid_value() { return NULL; }
   static void dispose(HACCEL accel)
   {
      BOOL r = ::DestroyAcceleratorTable(accel);
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
      assert(r != FALSE);
   }
};

} // namespace detail

// TODO: ReleaseDC, DeleteDC, wglDeleteContext

typedef resource<detail::accelerator_table_handle_config> accelerator_table_handle;
typedef resource<detail::gdiobj_handle_config>            gdiobj_handle;
typedef resource<detail::cursor_handle_config>            cursor_handle;
typedef resource<detail::icon_handle_config>              icon_handle;
typedef resource<detail::menu_handle_config>              menu_handle;
typedef resource<detail::window_handle_config>            window_handle;

} // namespace win
} // namespace raii

#endif
