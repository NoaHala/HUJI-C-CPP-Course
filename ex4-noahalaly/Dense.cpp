#include "Dense.h"

// see full description in header file
Dense::Dense (const Matrix& weights, const Matrix& bias,
Activation_Function
ActivationFunction)
{
  if (bias.get_cols () != 1 || bias.get_rows () != weights.get_rows ())
  {
    throw std::runtime_error ("Invalid input - Cannot construct 'Dense'");
  }
  _weight = weights;
  _bias = bias;
  _activation_function = ActivationFunction;
}

// see full description in header file
Matrix Dense::operator() (const Matrix &m) const
{
  if (_weight.get_cols () != m.get_rows ())
  {
    throw std::runtime_error ("Invalid input - Cannot apply 'Dense'");
  }
  Matrix new_m = (_weight * m) + _bias;
  return _activation_function (new_m);
}
