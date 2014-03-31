/*
 * PotentialFunction.hpp
 *
 *  Created on: Feb 25, 2014
 *      Author: Ben O'Leary (benjamin.oleary@gmail.com)
 */

#ifndef POTENTIALFUNCTION_HPP_
#define POTENTIALFUNCTION_HPP_

#include "../StandardIncludes.hpp"
#include "../PotentialMinimization/PotentialMinimum.hpp"

namespace VevaciousPlusPlus
{
  class PotentialFunction
  {
  public:
    PotentialFunction();
    virtual
    ~PotentialFunction();


    unsigned int NumberOfFieldVariables() const;
    std::string const& FieldName( unsigned int const fieldIndex) const
    { return fieldNames[ fieldIndex ]; }

    // This should return the energy density in GeV^4 of the potential for a
    // state strongly peaked around expectation values (in GeV) for the fields
    // given by the values of fieldConfiguration and temperature in GeV given
    // by temperatureValue.
    virtual double
    operator()( std::vector< double > const& fieldConfiguration,
                double const temperatureValue = 0.0 ) = 0;

    // This should update all the parameters of the potential that are not
    // field values based on the values that appear in blocks in the SLHA
    // format in the file given by slhaFilename.
    virtual void UpdateParameters( std::string const& slhaFilename ) = 0;

    // This returns operator(), but could be over-ridden so that a partial
    // result from a derived class could be returned, such as say the
    // tree-level part of a potential that builds on it with loop
    // corrections.
    virtual double
    QuickApproximation( std::vector< double > const& fieldConfiguration,
                        double const temperatureValue = 0.0 );

    // This should return the square of the scale (in GeV^2) relevant to
    // tunneling between the given minima for this potential.
    virtual double
    ScaleSquaredRelevantToTunneling( PotentialMinimum const& falseVacuum,
                                     PotentialMinimum const& trueVacuum ) = 0;

    // This is for ease of getting the index of a field of a given name. It
    // returns the largest possible unsigned int (-1 should tick over to that)
    // if fieldName was not found.
    unsigned int FieldIndex( std::string const& fieldName ) const;

    std::vector< double > const& DsbFieldValues() const
    { return dsbFieldValueInputs; }

    std::vector< double > const& FieldValuesOrigin() const
    { return fieldOrigin; }


  protected:
    std::vector< std::string > fieldNames;
    unsigned int numberOfFields;
    std::vector< double > dsbFieldValueInputs;
    std::vector< double > fieldOrigin;
  };




  inline unsigned int PotentialFunction::NumberOfFieldVariables() const
  {
    return numberOfFields;
  }

  inline double PotentialFunction::QuickApproximation(
                               std::vector< double > const& fieldConfiguration,
                                                double const temperatureValue )
  {
    return (*this)( fieldConfiguration,
                    temperatureValue );
  }

  // This is for ease of getting the index of a field of a given name. It
  // returns the largest possible unsigned int (-1 should tick over to that) if
  // fieldName was not found.
  inline unsigned int
  PotentialFunction::FieldIndex( std::string const& fieldName ) const
  {
    for( unsigned int fieldIndex( 0 );
         fieldIndex < fieldNames.size();
         ++fieldIndex )
    {
      if( fieldName.compare( fieldNames[ fieldIndex ] ) == 0 )
      {
        return fieldIndex;
      }
    }
    return -1;
  }

} /* namespace VevaciousPlusPlus */
#endif /* POTENTIALFUNCTION_HPP_ */
