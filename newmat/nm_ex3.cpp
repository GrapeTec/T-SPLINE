/// \ingroup newmat
///@{

/// \file nm_ex3.cpp
/// Print out values from precisio.h

#define WANT_STREAM
#define WANT_MATH

#include "newmatio.h"
#include "precisio.h"

#ifdef use_namespace
using namespace RBD_LIBRARIES;
#endif


int my_main()                  // called by main()
{
   Tracer tr("my_main ");      // for tracking exceptions

   cout << "Values from precisio.h" << endl;
   cout << "printed as individual numbers - no special formatting"
      << endl << endl;
   cout << "Epsilon      " << FloatingPointPrecision::Epsilon() << endl;
   cout << "Maximum      " << FloatingPointPrecision::Maximum() << endl;
   cout << "LnMaximum    " << FloatingPointPrecision::LnMaximum() << endl;
   cout << "Minimum      " << FloatingPointPrecision::Minimum() << endl;
   cout << "LnMinimum    " << FloatingPointPrecision::LnMinimum() << endl;
   cout << endl;
   
   ColumnVector values(5), sel_values(4);
   
   values(1) = sel_values(1) = FloatingPointPrecision::Epsilon();
   values(2) = FloatingPointPrecision::Maximum();
   values(3) = sel_values(2) = FloatingPointPrecision::LnMaximum();
   values(4) = sel_values(3) = FloatingPointPrecision::Minimum();
   values(5) = sel_values(4) = FloatingPointPrecision::LnMinimum();
  
   cout << "Load values into a ColumnVector and print in scientific format"
      << endl << endl;
   cout << "Values in scientific format" << endl;
   cout << setw(15) << setprecision(5) << scientific << values << endl;
  
   cout << "Print in fixed format" << endl << endl;
   cout << "Selected values in fixed format (omit Maximum)" << endl;
   cout << setw(15) << setprecision(5) << fixed << sel_values << endl;
   
   cout << "Test Epsilon" << endl << endl;
   Real x = 1.0 + FloatingPointPrecision::Epsilon();
   cout << "This value should be non-zero" << endl;
   cout << "(1.0 + Epsilon) - 1.0    " << setw(15) << setprecision(5) <<
      scientific << (Real)(x - 1.0) << endl;
   x = 1.0 + FloatingPointPrecision::Epsilon() / 2.0;
   cout << "This value should be zero" << endl;
   cout << "(1.0 + Epsilon / 2) - 1.0" << setw(15) << setprecision(5) <<
      scientific << (Real)(x - 1.0) << endl;
   cout << endl;
   
   cout << "Test Minimum" << endl << endl;
   cout << "This value should be non-zero" << endl;
   cout << "Minimum                  " << setw(15) << setprecision(5) <<
      scientific << FloatingPointPrecision::Minimum() << endl;
   x = FloatingPointPrecision::Minimum() * FloatingPointPrecision::Epsilon();
   cout << "Not clear whether this should be zero" << endl;
   cout << "Minimum  * Epsilon       " << setw(15) << setprecision(5) <<
      scientific << x << endl;
   x /= 2.0;
   cout << "This value should be zero" << endl;
   cout << "Minimum  * Epsilon / 2.0 " << setw(15) << setprecision(5) <<
      scientific << x << endl;
   cout << endl;
   
   cout << "Test LnMaximum and LnMinimum" << endl << endl;
   x = exp(FloatingPointPrecision::LnMaximum());
   cout << "This should print a value close to Maximum" << endl;
   cout << "Fails with some compilers - needs fixing" << endl; 
   cout << "exp(LnMaximum)           " << setw(15) << setprecision(5) <<
      scientific << x << endl;
   x = exp(FloatingPointPrecision::LnMinimum());
   cout << "This should print a value close to Minimum, not zero" << endl;
   cout << "exp(LnMinimum)           " << setw(15) << setprecision(5) <<
      scientific << x << endl;
   cout << endl;
   
   
   
   return 0;
}


// call my_main() - use this to catch exceptions
// use macros for exception names for compatibility with simulated exceptions
int main()
{
   Try  { return my_main(); }
   Catch(BaseException) { cout << BaseException::what() << "\n"; }
   CatchAll { cout << "\nProgram fails - exception generated\n\n"; }
   return 0;
}

///@}

