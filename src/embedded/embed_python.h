/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
////////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Some utilities for using python.
////////////////////////////////////////////////////////////////////////////////
#pragma once

#include "ristra-config.h"

#ifdef RISTRA_ENABLE_PYTHON

// user includes
#include "ristra/utils/string_utils.h"
#include "ristra/assertions/errors.h"

// use python
#include <Python.h>

namespace ristra {
namespace embedded {

//! \brief The python char type.
#if PY_MAJOR_VERSION < 3
using python_char_t = char;
#else
using python_char_t = wchar_t;
#endif

///////////////////////////////////////////////////////////////////////////////
//! \brief Given a character array, return a python string.
///////////////////////////////////////////////////////////////////////////////
auto make_python_string( const char * input ) 
{
#if PY_MAJOR_VERSION < 3
  return std::string(input);
#else
  return utils::to_wstring(input);
#endif
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Given a character array, return a python string.
///////////////////////////////////////////////////////////////////////////////
auto make_python_string( std::string input ) 
{
  return make_python_string(input.c_str());
}

///////////////////////////////////////////////////////////////////////////////
//! \brief Given a python string, return a character array pointer.
///////////////////////////////////////////////////////////////////////////////
template< typename T >
auto as_python_char( T && input ) 
{
  return const_cast<python_char_t*>( std::forward<T>(input).c_str() ) ;
}



void python_free( PyObject * py_obj )
{
  Py_DECREF(py_obj);
}

void python_check( void ) 
{
  if (PyErr_Occurred()) PyErr_Print();
}

void python_set_program_name( std::string name ) 
{
#if PY_MAJOR_VERSION < 3
  Py_SetProgramName( const_cast<char*>(name.c_str()) );
#elif ( PY_MAJOR_VERSION == 3 && PY_MINOR_VERSION < 5 )
  auto name_wstr = utils::to_wstring(name.c_str());
  Py_SetProgramName( const_cast<wchar_t*>(name_wstr.c_str()) );
#else
  auto program = Py_DecodeLocale(name.c_str(), NULL);
  if (!program) 
    THROW_RUNTIME_ERROR("Cannot decode program \"" << name << "\"");
  Py_SetProgramName(program);
  PyMem_RawFree(program);
#endif
}

void python_initialize( void ) 
{
  Py_Initialize();
  if (!Py_IsInitialized()) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot initialize python interpreter.");
  }
}

void python_finalize( void ) 
{
  Py_Finalize();
}

void python_run_string( std::string exec )
{
  PyRun_SimpleString( exec.c_str() );
} 

auto python_import( std::string name ) 
{
#if PY_MAJOR_VERSION < 3
  auto pname = PyString_FromString( const_cast<char*>(name.c_str()) );
#else
  auto pname = PyUnicode_DecodeFSDefault(name.c_str());
#endif
  if (!pname) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot decode module name \"" << name << "\"");
  }
  auto pmodule = PyImport_Import(pname);
  if (!pmodule) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot import module \"" << name << "\"");
  }
  Py_DECREF(pname);
  return pmodule;
}

auto python_add_to_path( std::string path )
{
  auto syspath = PySys_GetObject((char*)"path");
  if (!syspath) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot get system path.");
  }
#if PY_MAJOR_VERSION < 3
  auto pname = PyString_FromString( const_cast<char*>(path.c_str()) );
#else
  auto pname = PyUnicode_DecodeFSDefault(path.c_str());
#endif
  if (!pname) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot decode path \"" << path << "\"");
  }
  if (PyList_Insert(syspath, 0, pname)) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot insert path \"" << path << "\"");
  }
  if (PySys_SetObject((char*)"path", syspath)) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot set new path.");
  }
  Py_DECREF(pname);
  return syspath; 
} 

auto python_get_attribute( PyObject * py_module, std::string attribute )
{
  auto attr = PyObject_GetAttrString(py_module, attribute.c_str());
  if (!attr) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot get attribute \"" << attribute << "\"");
  }
  return attr;
}

inline auto python_as_long( PyObject * py_value )
{
  return PyLong_AsLong( py_value );
}

inline auto python_as_double( PyObject * py_value )
{
  return PyFloat_AsDouble( py_value );
}

auto python_get_value( long arg )
{
  auto pvalue = PyLong_FromLong(arg);
  if (!pvalue) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot set argument.");
  }
  return pvalue;
}

auto python_get_value( int arg )
{
  return python_get_value( static_cast<long>(arg) );
}

auto python_get_value( double arg )
{
  auto pvalue = PyFloat_FromDouble(arg);
  if (!pvalue) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot set argument.");
  }
  return pvalue;
}

auto python_get_tuple_element( PyObject * py_tup, std::size_t i )
{
  auto n = PyTuple_GET_SIZE(py_tup);
  if (i>=n) {
    python_check();
    THROW_RUNTIME_ERROR("Index out of range (i="<<i<<">="<<n<<").");
  }
  auto pitem = PyTuple_GetItem(py_tup, i);
  if (!pitem) {
    python_check();
    THROW_RUNTIME_ERROR("Problem getting item.");
  }
  return pitem;
}


template< typename Arg >
void python_set_tuple_element( PyObject * py_tup, std::size_t i, Arg && arg )
{
  auto n = PyTuple_GET_SIZE(py_tup);
  if (i>=n) {
    python_check();
    THROW_RUNTIME_ERROR("Index out of range (i="<<i<<">="<<n<<").");
  }
  auto pvalue = python_get_value( std::forward<Arg>(arg) );
  // pvalue reference stolen here:
  auto pitem = PyTuple_SetItem(py_tup, i, pvalue);
  if (pitem) {
    python_check();
    THROW_RUNTIME_ERROR("Problem setting item.");
  }
}


namespace detail {

template< typename Arg >
void python_build_args( PyObject * py_args, std::size_t i, Arg&& arg )
{
  python_set_tuple_element( py_args, i, std::forward<Arg>(arg) );
}

template< typename Arg, typename... Args >
void python_build_args( 
  PyObject * py_args, std::size_t i, Arg&& arg, Args&&... args 
) {
  python_set_tuple_element( py_args, i, std::forward<Arg>(arg) );
  // set the remaining arguments
  detail::python_build_args(
    py_args, i+1, std::forward<Args>(args)...
  );
}

} // namespace detail

template< typename... Args >
auto python_build_args( Args&&... args )
{
  auto pargs = PyTuple_New(sizeof...(args));
  if (!pargs) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot initialize arguments.");
  }
  detail::python_build_args(pargs, 0, std::forward<Args>(args)...);
  return pargs;
}

template< typename... Args >
auto python_call_function( PyObject * py_func, Args&&... args )
{
  if (!PyCallable_Check(py_func)) {
    python_check();
    THROW_RUNTIME_ERROR("Function is not callable.");
  }
  auto pargs = python_build_args(std::forward<Args>(args)...);
  if (!pargs) {
    python_check();
    THROW_RUNTIME_ERROR("Cannot initialize arguments.");
  }
  auto pval = PyObject_CallObject(py_func, pargs);
  if (!pval) {
    python_check();
    THROW_RUNTIME_ERROR("Problem calling function.");
  }
  Py_DECREF(pargs);
  return pval;
}


} // namespace embedded
} // namespace ristra

#endif // RISTRA_ENABLE_PYTHON
