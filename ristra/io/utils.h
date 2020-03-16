/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some commonly used utilities.
////////////////////////////////////////////////////////////////////////////////
#pragma once

// system includes
#include <sstream>

namespace ristra {
namespace io {

///////////////////////////////////////////////////////////////////////////////
//! \brief Append information to file
///////////////////////////////////////////////////////////////////////////////
namespace detail {

template <typename T>
void append_to_file( std::ofstream & file, T && t)
{
  file.write((char *) &t, sizeof(T));
}

template <typename T, typename... Args>
void append_to_file( std::ofstream & file, T && t, Args&&... args)
{
  file.write((char *) &t, sizeof(T));
  append_to_file(file, std::forward<Args>(args)...);
}

} // detail


// API: call with this.
template <typename... Args>
void append_to_file( const char * filename, Args&&... args)
{
  std::ofstream file(filename, std::ios::out | std::ios::binary
      | std::ios::app );
  detail::append_to_file(file, std::forward<Args>(args)...);
  file.close();
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Read information from file
///////////////////////////////////////////////////////////////////////////////
namespace detail {

template <typename T>
auto get_length(T && t)
{
  return sizeof(T);
}

template <typename T, typename... Args>
auto get_length(T && t, Args&&... args)
{
  return sizeof(T) + get_length(std::forward<Args>(args)...);
}

  template <typename T>
void read_from_file( std::ifstream & file, T && t)
{
  file.read((char *) &t, sizeof(T));
}

template <typename T, typename... Args>
void read_from_file( std::ifstream & file, T && t, Args&&... args)
{
  file.read((char *) &t, sizeof(T));
  read_from_file(file, std::forward<Args>(args)...);
}

} // detail

// API : call with this.
template <typename... Args>
void read_from_file( const char * filename, Args&&... args)
{
  std::ifstream file(filename, std::ios::in | std::ios::binary );
  // seek to end
  file.seekg(0, std::ios::end);
  // figure out where our data starts
  auto length = file.tellg();
  length -= detail::get_length(std::forward<Args>(args)...);
  file.seekg(length, std::ios::beg);
  // now read data
  detail::read_from_file( file, std::forward<Args>(args)...);
  file.close();
}

} // namespace
} // namespace
