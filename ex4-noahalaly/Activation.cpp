#include "Matrix.h"
#include "Activation.h"
#include <cmath>

// see full description in header file
Matrix activation::relu (Matrix &m)
{
  Matrix new_m (m);
  for (int i = 0; i < (m.get_cols () * m.get_rows ()); i++)
  {
    if (m[i] >= 0)
    {
      new_m[i] = m[i];
    }
    else
    {
      new_m[i] = 0;
    }
  }
  return new_m;
}

// see full description in header file
Matrix activation::softmax (Matrix &m)
{
  Matrix new_m (m.get_rows(),m.get_cols());
  float sum = 0;
  for (int i = 0; i < (m.get_cols () * m.get_rows ()); i++)
  {
    new_m[i] = std::exp(m[i]);
    sum += new_m[i];
  }
  return  new_m * (1/sum);
}