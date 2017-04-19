#~----------------------------------------------------------------------------~#
# Copyright (c) 2014 Los Alamos National Security, LLC
# All rights reserved.
#~----------------------------------------------------------------------------~#

set(common_HEADERS
  array_ref.h
  detail
  errors.h
  exceptions.h
  fixed_vector.h
  string_utils.h
  template_helpers.h  detail/template_helpers_impl.h
  tuple_visit.h       detail/tuple_visit_impl.h
  type_traits.h       detail/type_traits_impl.h
  PARENT_SCOPE
)

set(common_SOURCES
  PARENT_SCOPE
)


#----------------------------------------------------------------------------~-#
# Formatting options for vim.
# vim: set tabstop=2 shiftwidth=2 expandtab :
#----------------------------------------------------------------------------~-#
