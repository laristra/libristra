/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Utilities for string operations.
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <cstring>
#include <sstream>
#include <string>

namespace flecsi {
namespace sp {
namespace utils {


////////////////////////////////////////////////////////////////////////////////
//! \brief replace all occuraces of "from" to "to"
//! \param [in] str  the input string
//! \param [in] from the string to search for
//! \param [in] to   the string to replace "from" with
//! \return the new string
////////////////////////////////////////////////////////////////////////////////
inline
auto replace_all(std::string str, const std::string & from, const std::string & to) {
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
    str.replace(start_pos, from.length(), to);
    start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
  }
  return str;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Convert a value to a string.
//! \param [in] x The value to convert to a string.
//! \return the new string
////////////////////////////////////////////////////////////////////////////////
template < typename T >
auto to_string(const T & x) {
  std::stringstream ss;
  ss << x;
  return ss.str();
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Convert a character array to a wstring.
//! \param [in] text  the input string
//! \return the new string
////////////////////////////////////////////////////////////////////////////////
static std::wstring to_wstring(const char* text)
{
    const size_t size = std::strlen(text);
    std::wstring wstr;
    if (size > 0) {
        wstr.resize(size);
        std::mbstowcs(&wstr[0], text, size);
    }
    return wstr;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Get a file name.
//! \param [in] str  the input string
//! \return the base of the file name
////////////////////////////////////////////////////////////////////////////////
inline
std::string basename(const std::string & str) 
{
#ifdef _WIN32
  char sep = '\\';
#else
  char sep = '/';
#endif

  auto i = str.rfind( sep, str.length() );
  if ( i != std::string::npos )
    return str.substr(i+1, str.length()-1);
  else
    return str;
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Get the extension of a file name.
//! \param [in] str  the input string
//! \return the extension
////////////////////////////////////////////////////////////////////////////////
inline
std::string file_extension(const std::string & str) 
{
  auto base = basename(str);
  auto i = base.rfind( '.', base.length() );

  if ( i != std::string::npos )
    return base.substr(i+1, base.length()-1);
  else
    return "";
 
}

} // namspeace
} // namspeace
} // namspeace
