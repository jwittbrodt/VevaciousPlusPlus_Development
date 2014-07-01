/*
 * GradientMinimizer.hpp
 *
 *  Created on: Jun 30, 2014
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef GRADIENTMINIMIZER_HPP_
#define GRADIENTMINIMIZER_HPP_

#include "CommonIncludes.hpp"
#include "PotentialEvaluation/PotentialFunction.hpp"
#include "PotentialMinimum.hpp"

namespace VevaciousPlusPlus
{

  class GradientMinimizer
  {
  public:
    GradientMinimizer( PotentialFunction const& potentialFunction );
    virtual
    ~GradientMinimizer();


    // This should find the minimum using startingPoint as a starting point,
    // obviously.
    virtual PotentialMinimum
    operator()( std::vector< double > const& startingPoint ) const = 0;

    void SetTemperature( double const minimizationTemperature )
    { this->minimizationTemperature = minimizationTemperature; }


  protected:
    PotentialFunction const& potentialFunction;
    double minimizationTemperature;
  };

} /* namespace VevaciousPlusPlus */
#endif /* GRADIENTMINIMIZER_HPP_ */
