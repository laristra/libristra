/*~-------------------------------------------------------------------------~~*
 * Copyright (c) 2016 Los Alamos National Laboratory, LLC
 * All rights reserved
 *~-------------------------------------------------------------------------~~*/
///////////////////////////////////////////////////////////////////////////////
/// \file
/// \brief Defines a struct that contains all the inputs.
///////////////////////////////////////////////////////////////////////////////
#pragma once 

// user includes
#include <ristra/utils/string_utils.h>
#include <ristra/embedded/embed_lua.h>

// system includes
#include <iomanip>
#include <string>

namespace ristra {
namespace initialization {

#define inputs_try_access_as(state, key, ...)                                  \
  (!state[key].empty()) ?                                                      \
    state[key].template as<__VA_ARGS__>() :                                             \
    throw std::runtime_error(                                                  \
      "\'" + state[key].name() +                                               \
      "\' does not exist in the input state you are accessing."                \
    )

#define inputs_try_access(state, key)                                          \
  (!state[key].empty()) ?                                                      \
    state[key] :                                                               \
    throw std::runtime_error(                                                  \
      "\'" + state[key].name() +                                               \
      "\' does not exist in the input state you are accessing."                \
    )


///////////////////////////////////////////////////////////////////////////////
//! \brief A struct that contains all the inputs for a 2d case.
///////////////////////////////////////////////////////////////////////////////
class input_t {

  //===========================================================================
  // Private data
  //===========================================================================

  using byte_t = unsigned char;

  enum class types_t {
    size_t,
    float_t,
    double_t,
    string
  };
  
  //! \brief the lua state
  ristra::embedded::lua_t state_;

  std::string filename_;
  
  std::map< std::string, std::string > descriptions_;
  
  // keep track of 
  std::map< 
    std::string,
    std::tuple<std::string, std::vector<byte_t>, types_t >
  > inputs_;


public:

  using result_t = ristra::embedded::lua_result_t;
  
  static input_t& instance()
  {
    static input_t s;
    return s;
  };

  //===========================================================================
  //! \brief Load the lua input file
  //! \param [in] file  The name of the lua file to load.
  //===========================================================================
  void load(const std::string & file) 
  {
    state_.loadfile( file );
    filename_ = file;
  }

  auto filename() const {
    return filename_;
  }

  //===========================================================================
  /// \brief Access an object in the global table.
  /// \param [in] key  The key to access.
  /// \return A lua_result_t object which points to the value of the table
  ///         lookup.
  //===========================================================================
  auto operator[](const std::string & key) const &
  {
    auto result = lua_try_access(this->state_, key);
    return result;
  }
  
  //===========================================================================
  //! register an argument group
  //===========================================================================
  bool register_group( std::string key, std::string title ) {

    // try to add it
    auto res = descriptions_.emplace(key, title);
    return true;

  }
  
  //===========================================================================
  //! register the arguments
  //===========================================================================
  template<typename T>
  bool register_parameter(
    std::string key,
    std::string var_name,
    std::string message,
    const T & default_value
  )
  {
      
    std::vector<byte_t> val;
    types_t type;

    // utility function to cast integral types
    auto cast_integral = [](auto & bytes, auto x)
    {
      auto n = sizeof(decltype(x));
      bytes.resize(n);
      std::memcpy( bytes.data(), &x, n );
    };
          
    // convert default to byte arrays
    if constexpr (std::is_same_v<T, std::string> ) {
      type = types_t::string;
      auto n = default_value.size() * sizeof(char);
      val.resize(n);
      std::memcpy( val.data(), default_value.c_str(), n );
    }
    else if constexpr (std::is_same_v<T, size_t> ) {
      type = types_t::size_t;
      cast_integral(val, default_value);
    }
    else if constexpr (std::is_same_v<T, float> ) {
      type = types_t::float_t;
      cast_integral(val, default_value);
    }
    else if constexpr (std::is_same_v<T, double> ) {
      type = types_t::double_t;
      cast_integral(val, default_value);
    }

    // try to add it
    inputs_.emplace(
        key + "?" + var_name,
        std::forward_as_tuple(message, val, type) ); 

    return true;
  }


};

} // namespace ristra
} // namespace utils
