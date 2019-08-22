/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some functions for computing wall wall times.
////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "ristra-config.h"

//! system includes
#ifdef RISTRA_ENABLE_MPI
#include <mpi.h>
#elif defined( _WIN32 )
#include <Windows.h>
#else
#include <sys/time.h>
#endif

namespace ristra {
namespace utils {


////////////////////////////////////////////////////////////////////////////////
//! \brief Return the wall time counter.
//! \return the wall time
////////////////////////////////////////////////////////////////////////////////
double get_wall_time(void)
{

#ifdef RISTRA_ENABLE_MPI

  // Use mpi to get wall time
  return MPI_Wtime();

#elif defined( _WIN32 )

  // use windows api
  LARGE_INTEGER time,freq;
  if (!QueryPerformanceFrequency(&freq)) 
    THROW_RUNTIME_ERROR( "Error getting clock frequency." );
  if (!QueryPerformanceCounter(&time))
    THROW_RUNTIME_ERROR( "Error getting wall time." );
  return (double)time.QuadPart / freq.QuadPart;

#else

  // Use system time call
  struct timeval tm;
  if (gettimeofday( &tm, 0 )) THROW_RUNTIME_ERROR( "Error getting wall time." );
  return (double)tm.tv_sec + (double)tm.tv_usec * 1.e-6;

#endif
}


////////////////////////////////////////////////////////////////////////////////
//! \brief Convert seconds to days:hours:minutes:seconds.
////////////////////////////////////////////////////////////////////////////////
void daysHoursMinutesSeconds( 
  const long long input_seconds, //!< [in] total number of seconds
  long long & days,              //!< [out] number of days
  int & hours,                   //!< [out] number of hours
  int & minutes,                 //!< [out] number of minuts
  int & seconds                  //!< [out] number of seconds
) {


  const int SecondsPerDay = 86400;
  const int SecondsPerHour = 3600;
  const int SecondsPerMinute = 60;
  const int SecondsPerSecond = 1;

  days = input_seconds / SecondsPerDay;

  long long hours_remainder = input_seconds % SecondsPerDay;
  hours = hours_remainder / SecondsPerHour;

  long long minutes_remainder = hours_remainder % SecondsPerHour;
  minutes = minutes_remainder / SecondsPerMinute;

  long long seconds_remainder = minutes_remainder % SecondsPerMinute;  
  seconds = seconds_remainder / SecondsPerSecond;
}


} // namespace
} // namespace
