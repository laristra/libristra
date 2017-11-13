/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Classes for raising exceptions.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <stdexcept>
#include <string>



namespace flecsi {
namespace sp {
namespace utils {


///////////////////////////////////////////////////////////////////
//! \brief Raised when a general runtime error occurs.
///////////////////////////////////////////////////////////////////
class ExceptionRunTime : public std::runtime_error
{
public:
  ExceptionRunTime() : std::runtime_error( "general runtime error" ) {}
};

///////////////////////////////////////////////////////////////////
//! \brief  Raised when something happens that shouldn't have.
///////////////////////////////////////////////////////////////////
class ExceptionLogic : public std::logic_error
{
public:
  ExceptionLogic() : std::logic_error( "error in internal logic" ) {}
};

///////////////////////////////////////////////////////////////////
//! \brief  Raised when an unimplemented feature is accessed.
///////////////////////////////////////////////////////////////////
class ExceptionNotImplemented : public std::logic_error
{
public:
  ExceptionNotImplemented() : std::logic_error( "error, not implemented" ) {}
};


///////////////////////////////////////////////////////////////////
//! \brief  Raised when an error occurs accessing files.
///////////////////////////////////////////////////////////////////
class ExceptionFileError : public std::runtime_error
{
public:
  ExceptionFileError(const std::string& filename) : std::runtime_error( "error accessing file: " + filename ) {}
};


///////////////////////////////////////////////////////////////////
//! \brief  Raised when some convergence error occurs.
///////////////////////////////////////////////////////////////////
class ExceptionConvergenceFailure : public std::runtime_error
{
public:
  ExceptionConvergenceFailure() : std::runtime_error( "error trying to converge" ) {}
};

///////////////////////////////////////////////////////////////////
//! \brief  Raised when a floating point error occurs.
///////////////////////////////////////////////////////////////////
class ExceptionFloatingPoint: public std::runtime_error
{
public:
  ExceptionFloatingPoint() : std::runtime_error( "FPE occured" ) {}
};


} // namespace
} // namespace
} // namespace
