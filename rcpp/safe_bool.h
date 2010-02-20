/*
Copyright (c) 2010 Ivan Sorokin

Distributed under the Boost Software License, Version 1.0. (See
accompanying file LICENSE_1_0.txt or copy at
http://www.boost.org/LICENSE_1_0.txt)
*/
#ifndef RCPP_SAFE_BOOL_H_INCLUDED_0105a57a_2d21_4feb_a819_a92056f15dc5
#define RCPP_SAFE_BOOL_H_INCLUDED_0105a57a_2d21_4feb_a819_a92056f15dc5

#define RCPP_SAFE_BOOL_OPERATOR(cond)                                         \
   struct _sb_inner_struct                                                    \
   {                                                                          \
      void sb_function()                                                      \
      {}                                                                      \
   };                                                                         \
                                                                              \
   typedef void (_sb_inner_struct::*sb_type) ();                              \
                                                                              \
   operator sb_type() const                                                   \
   {                                                                          \
      return (cond)                                                           \
         ? &_sb_inner_struct::sb_function                                     \
         : sb_type(NULL);                                                     \
   }

#endif
