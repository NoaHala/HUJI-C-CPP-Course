#include "MlpNetwork.h"
using activation::relu;
using activation::softmax;
#define DIGITS_NUM 10

// see full description in header file
MlpNetwork::MlpNetwork (const Matrix weights[], const Matrix biases[]) :
    _dense1 (weights[0], biases[0], relu),
    _dense2 (weights[1], biases[1], relu),
    _dense3 (weights[2], biases[2], relu),
    _dense4 (weights[3], biases[3], softmax)
{}

// see full description in header file
digit MlpNetwork::operator() (const Matrix &x) const
{
  Matrix new_m(x);
  new_m = _dense4 (_dense3 (_dense2 (_dense1 (new_m.vectorize()))));
  digit output_digit{0, 0};
  for (int i = 0; i < DIGITS_NUM; i++)
  {
    if (new_m[i] > output_digit.probability)
    {
      output_digit.value = i;
      output_digit.probability = new_m[i];
    }
  }
  return output_digit;
}