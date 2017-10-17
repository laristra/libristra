/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some macros for raising errors.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// user includes
#include "here.h"

// system includes
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

//! if exceptions are enabled, set the throw macro
#ifdef ENABLE_EXCEPTIONS
#define THROW_EXCEPTION(e) \
  do {                     \
    throw e;               \
  } while (0)
#else
#define THROW_EXCEPTION(e) \
  do {                     \
    std::abort();          \
  } while (0)
#endif

/////////////////////////////////////////////////////////////////////
//! \brief throw a runtime error.
//! \param[in] the message to display
/////////////////////////////////////////////////////////////////////
#define throw_runtime_error(msg)                          \
  do {                                                    \
    THROW_EXCEPTION((std::runtime_error(HERE_STR(msg)))); \
  } while (0)

/////////////////////////////////////////////////////////////////////
//! \brief throw a logic error.
//! \param[in] the message to display
/////////////////////////////////////////////////////////////////////
#define throw_logic_error(msg)                        \
  do {                                                \
    THROW_EXCEPTION(std::logic_error(HERE_STR(msg))); \
  } while (0)

/////////////////////////////////////////////////////////////////////
//! \brief throw a file-related error.
//! \param[in] the file in question
/////////////////////////////////////////////////////////////////////
#define throw_file_error(file)                                        \
  do {                                                                \
    THROW_EXCEPTION(                                                  \
      std::runtime_error(HERE_STR("error accessing file: " + file))); \
  } while (0)

/////////////////////////////////////////////////////////////////////
//! \brief throw a not-implemented error.
//! \param[in] the message to display
/////////////////////////////////////////////////////////////////////
#define throw_implemented_error(msg)                                     \
  do {                                                                   \
    THROW_EXCEPTION(                                                     \
      std::logic_error(HERE_STR("error: not not implemented: " + msg))); \
  } while (0)

/////////////////////////////////////////////////////////////////////
//! \brief Assert that something is true.
//! \param[in] cond  the condition to assert evaluates to true
//! \param[in] msg  the message to display
/////////////////////////////////////////////////////////////////////
#define assert_true(cond, msg) \
  if (!(cond))                 \
  throw_runtime_error("Assertion falied: " << msg)

/////////////////////////////////////////////////////////////////////
//! \brief Display a warning.
//! \param[in] msg  the message to display
/////////////////////////////////////////////////////////////////////
#define short_warning(msg) std::cout << "Warning ==> " << msg << std::endl;
