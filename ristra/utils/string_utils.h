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
#include <iomanip>
#include <iterator>
#include <locale>
#include <sstream>
#include <string>
#include <vector>

namespace ristra {
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

////////////////////////////////////////////////////////////////////////////////
//! \brief Remove the extension from a filename
//! \param [in] str  the input string
//! \return the name without extension
////////////////////////////////////////////////////////////////////////////////
inline
std::string remove_extension(const std::string & str) {
    auto lastdot = str.find_last_of(".");
    if (lastdot == std::string::npos) return str;
    return str.substr(0, lastdot); 
}

////////////////////////////////////////////////////////////////////////////////
//! \brief Remove the extension from a filename
//! \param [in] str  the input string
//! \return the name without extension
////////////////////////////////////////////////////////////////////////////////
inline
std::pair<std::string, std::string>
split_extension(const std::string & str) {
  auto lastdot = str.find_last_of(".");
  if (lastdot == std::string::npos)
    return std::make_pair( str, "");
  else
    return std::make_pair( str.substr(0, lastdot), str.substr(lastdot+1) ); 
}


////////////////////////////////////////////////////////////////////////////////
//! \brief split a string using a list of delimeters
//! \param [in] str  the input string
//! \param [in] delim  the list of delimeters
//! \return the list of split strings
////////////////////////////////////////////////////////////////////////////////
inline
std::vector<std::string> split(
  const std::string & str, 
  std::vector<char> delim = {' '}
) {

  if (str.empty()) return {};

  struct tokens_t : std::ctype<char>
  {
    using ctype_base = std::ctype_base;
    using cctype = std::ctype<char>;
    using ccmask = cctype::mask;
    
    tokens_t(const std::vector<char> & delims) 
      : cctype(get_table(delims)) {}

    static ctype_base::mask const * get_table(
      const std::vector<char> & delims
    ) {
      static const ccmask * const_rc = cctype::classic_table();
      static ccmask rc[cctype::table_size];
      std::memcpy(rc, const_rc, cctype::table_size*sizeof(ccmask));
      for (const auto & d : delims) 
        rc[d] = ctype_base::space;
      return &rc[0];
    }
  };

  std::stringstream ss(str);
  ss.imbue(std::locale(std::locale(), new tokens_t(delim)));
  std::istream_iterator<std::string> begin(ss);
  std::istream_iterator<std::string> end;
  std::vector<std::string> vstrings(begin, end);
  return vstrings;
}


///////////////////////////////////////////////////////////////////////////////
//! \brief Tack on an iteration number to a string
///////////////////////////////////////////////////////////////////////////////
inline auto zero_padded( 
  unsigned int n, unsigned int padding = 6 
)
{

  auto number = n;
  unsigned int digits = 0;
  while (number) {
    number /= 10;
    digits++;
  }

  digits = std::max( digits, 1u );
  digits = std::max( padding, digits );

  std::stringstream ss;
  ss << std::setw( digits ) << std::setfill( '0' ) << n;
  return ss.str();
}

} // namespace
} // namespace
