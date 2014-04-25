/*
 * BinaryOperationFunctionoid.hpp
 *
 *  Created on: Mar 4, 2014
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef PLUSMINUSFUNCTIONOID_HPP_
#define PLUSMINUSFUNCTIONOID_HPP_

#include "../../CommonIncludes.hpp"
#include "ParameterFunctionoid.hpp"


namespace VevaciousPlusPlus
{

  class BinaryOperationFunctionoid : public ParameterFunctionoid
  {
  public:
    static double PlusFunction( double firstValue,
                                double secondValue )
    { return ( firstValue + secondValue ); }
    static double MinusFunction( double firstValue,
                                 double secondValue )
    { return ( firstValue - secondValue ); }
    static double MultiplyFunction( double firstValue,
                                    double secondValue )
    { return ( firstValue * secondValue ); }
    static double DivideFunction( double firstValue,
                                  double secondValue )
    { return ( firstValue / secondValue ); }
    static double IfNonZeroFunction( double firstValue,
                                     double secondValue )
    { return ( ( firstValue != 0.0 ) ? firstValue : secondValue ); }

    BinaryOperationFunctionoid( double (*binaryOperation)( double,
                                                           double ),
                                ParameterFunctionoid* const firstFunctionoid,
                                ParameterFunctionoid* const secondFunctionoid,
                                std::string const& creationString,
                                std::string const& pythonParameterName );
    virtual
    ~BinaryOperationFunctionoid();


    // This returns the value of the functionoid for the given logarithm of the
    // scale.
    virtual double operator()( double const logarithmOfScale ) const
    { return (*binaryOperation)( (*firstFunctionoid)( logarithmOfScale ),
                                 (*secondFunctionoid)( logarithmOfScale ) ); }

    // This re-calculates the coefficients of the polynomial of the logarithm
    // of the scale used in evaluating the functionoid.
    virtual void UpdateForNewLogarithmOfScale( double const logarithmOfScale );

    // This is mainly for debugging.
    virtual std::string AsString();

    // This is for creating a Python version of the potential.
    virtual std::string PythonParameterEvaluation() const;


  protected:
    double (*binaryOperation)( double,
                               double );
    ParameterFunctionoid* firstFunctionoid;
    ParameterFunctionoid* secondFunctionoid;
  };




  // This updates currentValue based on logarithmOfScale.
  inline void BinaryOperationFunctionoid::UpdateForNewLogarithmOfScale(
                                                double const logarithmOfScale )
  {
    currentValue = (*binaryOperation)( (*firstFunctionoid)(),
                                       (*secondFunctionoid)() );

    // debugging:
    /*std::cout << std::endl << "debugging:"
    << std::endl
    << "[" << this->AsString()
    << "].UpdateForNewLogarithmOfScale( " << logarithmOfScale
    << " ) called. currentValue = " << currentValue;
    std::cout << std::endl;*/
  }

  // This is mainly for debugging.
  inline std::string BinaryOperationFunctionoid::AsString()
  {
    std::stringstream returnStream;
    returnStream
    << "[BINARYOPERATION " << this << ": " << firstFunctionoid->AsString()
    << ", " << secondFunctionoid->AsString() << "]";
    return returnStream.str();
  }

} /* namespace VevaciousPlusPlus */
#endif /* PLUSMINUSFUNCTIONOID_HPP_ */