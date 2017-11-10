/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
///
/// \file
///
/// \brief Utilities for writing binary files.
///
////////////////////////////////////////////////////////////////////////////////

#pragma once

// system includes
#include <iostream>
#include <fstream>

namespace flecsi {
namespace sp {
namespace io {

// data types
using int32 = int;
using int64 = long;
using float32 = float;
using float64 = double;

////////////////////////////////////////////////////////////////////////////////
/// \brief Determine endienness.
/// \return Return true if machine is big endian.
////////////////////////////////////////////////////////////////////////////////
inline bool isBigEndian(void) {
  static unsigned long x(1);
  static bool result(reinterpret_cast<unsigned char*>(&x)[0] == 0);
  return result;
}

////////////////////////////////////////////////////////////////////////////////
/// \brief Write data in binary to a stream.
/// \param [in,out] file  The file stream.
/// \param [in]  buffer  The buffer to write.
/// \tparam T  The type of the buffer.
////////////////////////////////////////////////////////////////////////////////
template <class T> 
inline void WriteBinary(std::ostream &file, T buffer) {
  file.write(reinterpret_cast<char*>(&buffer), sizeof(T));
}


////////////////////////////////////////////////////////////////////////////////
/// \defgroup WriteBinarySwap A group of functions to write binary data.
/// \brief Write data in binary to a stream, swapping endienness.
/// \param [in,out] file  The file stream.
/// \param [in]  buffer  The buffer to write.
/// \tparam T  The type of the buffer.
////////////////////////////////////////////////////////////////////////////////
///@{

/// \brief This is the base template.
template <class T> 
inline void WriteBinarySwap(std::ofstream &file, T buffer) {};

/// \brief This is a specialization for 32-bit integers.
template <>
inline void WriteBinarySwap(std::ofstream &file, int32 buffer) 
{ 
  union temp {
    int32  value;
    char   c[4];
  } in, out;

  in.value = buffer;

  out.c[0] = in.c[3];
  out.c[1] = in.c[2];
  out.c[2] = in.c[1];
  out.c[3] = in.c[0];
  
  file.write(out.c, sizeof(int32));
}

/// \brief This is a specialization for 64-bit integers.
template<>
inline void WriteBinarySwap(std::ofstream &file, int64 buffer) 
{ 
  union temp {
    float64  value;
    char     c[8];
  } in, out;

  in.value = buffer;

  out.c[0] = in.c[7];
  out.c[1] = in.c[6];
  out.c[2] = in.c[5];
  out.c[3] = in.c[4];
  out.c[4] = in.c[3];
  out.c[5] = in.c[2];
  out.c[6] = in.c[1];
  out.c[7] = in.c[0];
  
  file.write(out.c, sizeof(int64));
}

/// \brief This is a specialization for 32-bit floats.
template<>
inline void WriteBinarySwap(std::ofstream &file, float32 buffer) 
{ 
  union temp {
    float32  value;
    char     c[4];
  } in, out;

  in.value = buffer;

  out.c[0] = in.c[3];
  out.c[1] = in.c[2];
  out.c[2] = in.c[1];
  out.c[3] = in.c[0];
  
  file.write(out.c, sizeof(float32));
}

/// \brief This is a specialization for 64-bit floats.
template<>
inline void WriteBinarySwap(std::ofstream &file, float64 buffer) 
{ 
  union temp {
    float64  value;
    char     c[8];
  } in, out;

  in.value = buffer;

  out.c[0] = in.c[7];
  out.c[1] = in.c[6];
  out.c[2] = in.c[5];
  out.c[3] = in.c[4];
  out.c[4] = in.c[3];
  out.c[5] = in.c[2];
  out.c[6] = in.c[1];
  out.c[7] = in.c[0];
  
  file.write(out.c, sizeof(float64));
}
///@}


////////////////////////////////////////////////////////////////////////////////
/// \brief Write string data in binary to a stream.
/// \param [in,out] file  The file stream.
/// \param [in]  S  The buffer to write.
////////////////////////////////////////////////////////////////////////////////
inline void WriteString(std::ofstream &file, const char *S) {
  int L = 0;
  while (S[L] != '\0')
    WriteBinary<int32>(file,int(S[L++]));
  WriteBinary<int32>(file,0);
}

} // namspace
} // namspace
} // namspace
