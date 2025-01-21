#ifndef DENSE_H
#define DENSE_H

#include "Activation.h"
using activation::Activation_Function;

/**
 * @class Dense
 * each object in this clss represent a layer in the neurons network
 */
class Dense
{
 private:
  Matrix _weight;
  Matrix _bias;
  Activation_Function _activation_function;

 public:

 /**
  * Constructor
  */
  Dense (const Matrix &weights, const Matrix &bias, Activation_Function
  ActivationFunction);


 /**
 * getters
 */
  Matrix get_weights () const
  { return _weight; }

  Matrix get_bias () const
  { return _bias; }

  Activation_Function get_activation () const
  { return _activation_function; }

 /**
 * operator()
 */
  Matrix operator() (const Matrix &m) const;

};

#endif //DENSE_H
