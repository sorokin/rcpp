/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#include <vector>
#include <boost/test/minimal.hpp>

#include "rcpp/resource.h"

namespace
{
   typedef std::vector<int> int_vec;
   int_vec disposed;
   int_vec extract()
   {
      return std::move(disposed);
   }
}

struct moc_config
{
   typedef int underlying_resource_type;
   static underlying_resource_type invalid_value() { return 0; }
   static void dispose(underlying_resource_type const & v)
   {
      disposed.push_back(v);
   }
};

typedef rcpp::resource<moc_config> moc;

int test_main(int, char **)
{
   {
      moc a;
      BOOST_CHECK(extract() == int_vec{});
   }
   BOOST_CHECK(extract() == int_vec{});

   {
      moc a(5);
      BOOST_CHECK(extract() == int_vec{});
   }
   BOOST_CHECK(extract() == int_vec{5});

   {
      moc a(5);
      moc b(6);
      BOOST_CHECK(extract() == int_vec{});
   }
   BOOST_CHECK((extract() == int_vec{6,5}));

   {
      moc a(5);
      moc b(6);
      BOOST_CHECK(b.release() == 6);
      BOOST_CHECK(extract() == int_vec{});
   }
   BOOST_CHECK(extract() == int_vec{5});

   {
      moc a(7);
      BOOST_CHECK(a.get() == 7);
      BOOST_CHECK(extract() == int_vec{});
   }
   BOOST_CHECK(extract() == int_vec{7});

   {
      moc a(7);
      BOOST_CHECK(extract() == int_vec{});
      a.reset();
      BOOST_CHECK(extract() == int_vec{7});
   }
   BOOST_CHECK(extract() == int_vec{});

   {
      moc a(7);
      moc b(std::move(a));
      BOOST_CHECK(extract() == int_vec{});
      BOOST_CHECK(a.get() == 0);
      BOOST_CHECK(b.get() == 7);
   }
   BOOST_CHECK(extract() == int_vec{7});

   {
      moc a(5);
      moc b(6);
      std::swap(a, b);
      BOOST_CHECK(a.get() == 6);
      BOOST_CHECK(b.get() == 5);
      BOOST_CHECK(extract() == int_vec{});
   }
   BOOST_CHECK((extract() == int_vec{5,6}));

   {
      moc a(5);
      moc b(6);
      BOOST_CHECK(a < b);
      BOOST_CHECK(a <= b);
      BOOST_CHECK(a != b);
      BOOST_CHECK(b == b);
      BOOST_CHECK(b >= a);
      BOOST_CHECK(b > a);

      BOOST_CHECK(a >= a);
   }
   BOOST_CHECK((extract() == int_vec{6,5}));

   {
      moc a(5);
      moc b(6);
      a = std::move(b);
      BOOST_CHECK(extract() == int_vec{5});
      BOOST_CHECK(a.get() == 6);
      BOOST_CHECK(b.get() == 0);
   }
   BOOST_CHECK(extract() == int_vec{6});

   {
      moc a(5);
      a = std::move(a);
      BOOST_CHECK(extract() == int_vec{});
      BOOST_CHECK(a.get() == 5);
   }
   BOOST_CHECK(extract() == int_vec{5});

   return 0;
}
