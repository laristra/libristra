/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some macros for raising errors.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include<ristra-config.h>

// user includes
#include "here.h"
#include "exceptions.h"

// system includes
#include <iostream>
#include <cstdlib>


//! if exceptions are enabled, set the throw macro
#ifdef RISTRA_ENABLE_EXCEPTIONS
#define THROW_EXCEPTION(e) do { throw e; } while (0)
#else
#define THROW_EXCEPTION(e) do { std::abort(); } while (0)
#endif


////////////////////////////////////////////////////////////////////////////////
//! \brief Raise a runtime error.
//! \param[in] the message to display
////////////////////////////////////////////////////////////////////////////////
#define THROW_RUNTIME_ERROR(msg)                                               \
  do {                                                                         \
    std::cerr << RISTRA_HERE << std::endl;                                     \
    std::cerr << msg << std::endl;                                             \
    THROW_EXCEPTION(ristra::assertions::ExceptionRunTime());                        \
  } while(0)


////////////////////////////////////////////////////////////////////////////////
//! \brief Raise a logic error.
//! \param[in] the message to display
////////////////////////////////////////////////////////////////////////////////
#define THROW_LOGIC_ERROR(msg)                                                 \
  do {                                                                         \
    std::cerr << RISTRA_HERE << std::endl;                                     \
    std::cerr << msg << std::endl;                                             \
    THROW_EXCEPTION(ristra::assertions::ExceptionLogic());                          \
  } while(0)

////////////////////////////////////////////////////////////////////////////////
//! \brief Raise a file-related error.
//! \param[in] the file in question
////////////////////////////////////////////////////////////////////////////////
#define THROW_FILE_ERROR(file)                                          \
  do {                                                                  \
    std::cerr << RISTRA_HERE << std::endl;                                     \
    THROW_EXCEPTION(ristra::assertions::ExceptionFileError(file));              \
  } while(0)


////////////////////////////////////////////////////////////////////////////////
//! \brief Raise a not-implemented error.
//! \param[in] the message to display
////////////////////////////////////////////////////////////////////////////////
#define THROW_IMPLEMENTED_ERROR(msg)                                    \
  do {                                                                  \
    std::cerr << RISTRA_HERE << std::endl;                                     \
    std::cerr << msg << std::endl;                                      \
    THROW_EXCEPTION(ristra::assertions::ExceptionNotImplemented());             \
  } while(0)

////////////////////////////////////////////////////////////////////////////////
//! \brief Assert that something is true.
//! \param[in] cond  the condition to assert evaluates to true
//! \param[in] msg  the message to display
////////////////////////////////////////////////////////////////////////////////
#define assert_true(cond, msg)                                          \
  if ( ! (cond) )                                                       \
    THROW_RUNTIME_ERROR("Assertion falied: " << msg)

////////////////////////////////////////////////////////////////////////////////
//! \brief Display a warning.
//! \param[in] msg  the message to display
////////////////////////////////////////////////////////////////////////////////
#define short_warning(msg)                                              \
    std::cout << "Warning ==> " << msg << std::endl;
