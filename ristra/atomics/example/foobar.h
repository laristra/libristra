
// -----------------------------------------------------------------------------
// User-defined classes
//    foo
//    bar
// Note: probably sizeof(foo) == sizeof(some integral type), which facilitates
// the use, if we wish, of our type-punning atomicity schemes. I should consider
// having the type-punning constructions automatically fall back on their
// no-pun counterparts in the event that the type's sizeof isn't compatible
// with anything. Or maybe don't do that (it could be misleading), and require
// that the user just avoid strong::pun or weak::pun unless it's going to work.
// -----------------------------------------------------------------------------


// ------------------------
// Classes
// ------------------------

// foo
class foo {
public:
   unsigned char a;
   unsigned char b;
   unsigned char c;
   unsigned char d;
   foo(const int val = 0) : a(val), b(val), c(val), d(val) { }
};

// bar
class bar {
public:
   int i;
   bar(const int val = 0) : i(val) { }

   // Conversion to foo, needed for our library's mineq() and maxeq() functions,
   // which in turn are used by min() and max(). Note that "explicit" is fine.
   inline explicit operator foo() const
   {
      return foo(i);
   }
};


// ------------------------
// foo += bar, etc.
// ------------------------

#define make_binop(op) \
   inline foo &operator op(foo &f, const bar &b) \
   { \
      f.a op b.i; \
      f.b op b.i; \
      f.c op b.i; \
      f.d op b.i; \
      return f; \
   }

make_binop( +=  )
make_binop( -=  )
make_binop( *=  )
make_binop( /=  )
make_binop( %=  )
make_binop( <<= )
make_binop( >>= )
make_binop( &=  )
make_binop( |=  )
make_binop( ^=  )

#undef make_binop


// ------------------------
// ++foo, etc.
// ------------------------

inline foo &operator++(foo &f     ) { return ++f.a, ++f.b, ++f.c, ++f.d, f; }
inline foo &operator++(foo &f, int) { return f.a++, f.b++, f.c++, f.d++, f; }
inline foo &operator--(foo &f     ) { return --f.a, --f.b, --f.c, --f.d, f; }
inline foo &operator--(foo &f, int) { return f.a--, f.b--, f.c--, f.d--, f; }


// ------------------------
// Comparison
// ------------------------

// The following aren't necessarily meaningful definitions, but our goal
// is to illustrate that the atomic min() and max() functions are available
// if we define these.

// foo < bar
inline bool operator<(const foo &f, const bar &b)
{
   return f.a + f.b + f.c + f.d < b.i;
}

// bar < foo
inline bool operator<(const bar &b, const foo &f)
{
   return b.i < f.a + f.b + f.c + f.d;
}


// ------------------------
// Stream output
// ------------------------

// ostream << foo
inline std::ostream &operator<<(std::ostream &os, const foo &f)
{
   return os
      << int(f.a) << ',' << int(f.b) << ','
      << int(f.c) << ',' << int(f.d);
}

// ostream << bar
inline std::ostream &operator<<(std::ostream &os, const bar &b)
{
   return os << b.i;
}
