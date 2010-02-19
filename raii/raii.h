/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RAII_RAII_H_INCLUDED_a56eb2db_1624_45fd_969a_4ca4f1880455
#define RAII_RAII_H_INCLUDED_a56eb2db_1624_45fd_969a_4ca4f1880455

#include <assert.h>
#include <boost/config.hpp>
#include <boost/noncopyable.hpp>

#include "safe_bool.h"

/*
template <typename T>
struct resource_config
{
   typedef ... underlying_resource_type;
   static underlying_resource_type invalid_value();
   static void dispose(underlying_resource_type const &);
}
*/

namespace raii
{
   template <typename resource_config>
   struct resource : boost::noncopyable
   {
      typedef typename resource_config::underlying_resource_type underlying_resource_type;

      resource()
         : underlying_resource(resource_config::invalid_value())
      {}

      explicit resource(underlying_resource_type const & underlying_resource)
         : underlying_resource(underlying_resource)
      {}

#ifdef BOOST_HAS_RVALUE_REFS
      resource(resource<resource_config> && other)
         : underlying_resource(other.underlying_resource)
      {
         other.underlying_resource = resource_config::invalid_value();
      }

      resource<resource_config> & operator=(resource<resource_config> && other)
      {
         resource<resource_config> tmp(std::move(other));

         using std::swap;
         swap(*this, tmp);
      }
#endif

      ~resource()
      {
         if (underlying_resource != resource_config::invalid_value())
            resource_config::dispose(underlying_resource);
      }

      void reset(underlying_resource_type const & underlying_resource = resource_config::invalid_value())
      {
         resource<resource_config> tmp(underlying_resource);

         using std::swap;
         swap(*this, tmp);
      }

      // underlying_resource_type copy constructor must be nothrow
      // or release() may leak
      underlying_resource_type release()
      {
         underlying_resource_type tmp = underlying_resource;
         underlying_resource = resource_config::invalid_value();
         return tmp;
      }

      underlying_resource_type get() const
      {
         return underlying_resource;
      }

      void swap(resource<resource_config> & other)
      {
         using std::swap;
         swap(underlying_resource, other.underlying_resource);
      }

      RAII_SAFE_BOOL_OPERATOR(underlying_resource != resource_config::invalid_value())

   private:
      underlying_resource_type underlying_resource;
   };
}

namespace std
{
   template <typename resource_config>
   void swap(raii::resource<resource_config> & a, raii::resource<resource_config> & b)
   {
      a.swap(b);
   }
}

#endif
