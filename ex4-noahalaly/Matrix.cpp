#include "Matrix.h"
#include <cmath>
#define ONE_VAL 1
#define MIN_VAL_FOR_PRINT 0.1
using std::cout;
using std::endl;

/*******************
*   Constructors   *
********************/

// constructor - for full information see header file
Matrix::Matrix (int rows, int cols) : _matrix_dims ({rows, cols})
{
  if (rows <= 0 || cols <= 0)
  {
    throw std::length_error ("matrix dimensions must be positive ints");
  }
  _matrix_array = new float[rows * cols];
  for (int i = 0; i < (rows * cols); i++)
  {
    _matrix_array[i] = 0;
  }
}

// constructor - for full information see header file
Matrix::Matrix () : Matrix (ONE_VAL, ONE_VAL)
{}

// copy constructor - for full information see header file
Matrix::Matrix (const Matrix &m) : _matrix_dims (m._matrix_dims)
{
  int arr_length = _matrix_dims.rows * _matrix_dims.cols;
  _matrix_array = new float[arr_length];
  for (int i = 0; i < arr_length; i++)
  {
    _matrix_array[i] = m._matrix_array[i];
  }
}

// destructor - for full information see header file
Matrix::~Matrix ()
{
  delete[] _matrix_array;
}

/****************
*   Operators   *
*****************/

// see full description in header file
Matrix Matrix::operator+ (const Matrix &m) const
{
  if (get_cols () != m.get_cols () || get_rows () != m.get_rows ())
  {
    throw std::length_error ("Cannot perform addition between matrices with "
                             "different dimensions");
  }
  Matrix addition (*this);
  int arr_len = get_cols () * get_rows ();
  for (int i = 0; i < arr_len; i++)
  {
    addition._matrix_array[i] += m._matrix_array[i];
  }
  return addition;
}

// see full description in header file
Matrix &Matrix::operator= (const Matrix &m)
{
  if (this != &m)
  {
    const float *temp_old_array = _matrix_array;
    const float *temp_new_array = m._matrix_array;
    int arr_length = m._matrix_dims.rows * m._matrix_dims.cols;
    _matrix_array = new float[arr_length];
    _matrix_dims = m._matrix_dims;
    for (int i = 0; i < arr_length; i++)
    {
      _matrix_array[i] = temp_new_array[i];
    }
    delete[] temp_old_array;
  }
  return *this;
}

// see full description in header file
Matrix &Matrix::operator+= (const Matrix &m)
{
  if (get_cols () != m.get_cols () || get_rows () != m.get_rows ())
  {
    throw std::length_error ("Cannot perform addition between matrices with "
                             "different dimensions");
  }
  int arr_length = m._matrix_dims.rows * m._matrix_dims.cols;
  for (int i = 0; i < arr_length; i++)
  {
    _matrix_array[i] += m._matrix_array[i];
  }
  return *this;
}

// see full description in header file
Matrix Matrix::operator* (const Matrix &m) const
{
  if (get_cols () != m.get_rows ())
  {
    throw std::length_error ("Dimensions problem - Cannot perform "
                             "multiplication");
  }
  Matrix mult_matrix (get_rows (), m.get_cols ());
  int n = get_cols (); // the shared dimension , also equal to m.get_rows();
  float temp_cell_val;

  for (int i = 0; i < mult_matrix.get_rows (); i++)
  {
    for (int j = 0; j < mult_matrix.get_cols (); j++)
    {
      temp_cell_val = 0;
      for (int k = 0; k < n; k++)
      {
        temp_cell_val += (*this) (i, k) * m (k, j);
      }
      mult_matrix (i, j) = temp_cell_val;
    }
  }
  return mult_matrix;
}

// see full description in header file
Matrix Matrix::operator* (const float &c) const
{
  Matrix mult_matrix (*this);
  int arr_len = get_cols () * get_rows ();
  for (int i = 0; i < arr_len; i++)
  {
    mult_matrix._matrix_array[i] *= c;
  }
  return mult_matrix;
}

// see full description in header file
Matrix operator* (const float &c, const Matrix &m)
{
  return m * c;
}

// see full description in header file
float Matrix::operator() (const int &i, const int &j) const
{
  if (i >= get_rows () || j >= get_cols ())
  {
    throw std::out_of_range ("Index is out of range");
  }
  return _matrix_array[(i * get_cols ()) + j];
}

// see full description in header file
float &Matrix::operator() (const int &i, const int &j)
{
  if (i >= get_rows () || j >= get_cols ())
  {
    throw std::out_of_range ("Index is out of range");
  }
  return _matrix_array[(i * get_cols ()) + j];
}

// see full description in header file
float Matrix::operator[] (const int &k) const
{
  if (k >= get_cols () * get_rows ())
  {
    throw std::out_of_range ("Index is out of range");
  }
  return _matrix_array[k];
}

// see full description in header file
float &Matrix::operator[] (const int &k)
{
  if (k >= get_cols () * get_rows ())
  {
    throw std::out_of_range ("Index is out of range");
  }
  return _matrix_array[k];
}

// see full description in header file
ostream &operator<< (ostream &os, const Matrix &m)
{
  for (int i = 0; i < m.get_rows (); i++)
  {
    for (int j = 0; j < m.get_cols (); j++)
    {
      if (m (i, j) > MIN_VAL_FOR_PRINT)
      {
        os << "**";
      }
      else
      {
        os << "  ";
      }
    }
    os << std::endl;
  }
  return os;
}

// see full description in header file
istream &operator>> (std::ifstream &is, Matrix &m)
{
  if (!is.is_open ())
  {
    throw std::runtime_error ("file failed to open - cannot read from it");
  }

  // get file size
  is.seekg (0, std::ios::end);
  std::streampos file_size = is.tellg ();
  is.seekg (0, std::ios::beg);

  int arr_len = m.get_cols () * m.get_rows ();
  if (file_size < (long int) (sizeof (float) * arr_len))
  {
    throw std::length_error ("The file is too small for filling the matrix");
  }

  is.read ((char *) m._matrix_array, sizeof (float) * arr_len);
  if (!is)
  {
    throw std::runtime_error ("Failed to read the file");
  }

  return is;
}

/****************
*    Methods    *
*****************/

// see full description in header file
float Matrix::sum () const
{
  float sum = 0;
  for (int i = 0; i < get_rows (); i++)
  {
    for (int j = 0; j < get_cols (); j++)
    {
      sum += (*this) (i, j);
    }
  }
  return sum;
}

// see full description in header file
Matrix &Matrix::transpose ()
{
  Matrix helper_matrix (*this);

  int temp = get_cols ();
  _matrix_dims.cols = _matrix_dims.rows;
  _matrix_dims.rows = temp;

  for (int i = 0; i < get_rows (); i++)
  {
    for (int j = 0; j < get_cols (); j++)
    {
      (*this) (i, j) = helper_matrix (j, i);
    }
  }

  return (*this);
}

// see full description in header file
Matrix &Matrix::vectorize ()
{
  _matrix_dims.rows = get_cols () * get_rows ();
  _matrix_dims.cols = ONE_VAL;
  return (*this);
}

// see full description in header file
void Matrix::plain_print () const
{
  for (int i = 0; i < get_rows (); i++)
  {
    for (int j = 0; j < get_cols (); j++)
    {
      std::cout << (*this) (i, j) << " ";
    }
    std::cout << std::endl;
  }
}

// see full description in header file
Matrix Matrix::dot (const Matrix &m) const
{
  if (get_cols () != m.get_cols () || get_rows () != m.get_rows ())
  {
    throw std::length_error ("Cannot perform addition between matrices with "
                             "different dimensions");
  }
  Matrix dot_mult_matrix (*this);
  for (int i = 0; i < get_rows (); i++)
  {
    for (int j = 0; j < get_cols (); j++)
    {
      dot_mult_matrix (i, j) = dot_mult_matrix (i, j) * m (i, j);
    }
  }
  return dot_mult_matrix;
}

// see full description in header file
float Matrix::norm () const
{
  float norm = 0;
  for (int i = 0; i < get_rows (); i++)
  {
    for (int j = 0; j < get_cols (); j++)
    {
      norm += ((*this) (i, j) * (*this) (i, j));
    }
  }
  return (float) (sqrt ((double) norm));
}

// see full description in header file
// todo - bonus rref


// see full description in header file
int Matrix::argmax () const
{
  int max_val_index = 0;
  int arr_len = get_rows () * get_cols ();
  for (int i = 0; i < arr_len; i++)
  {
    if ((*this)[i] > (*this)[max_val_index])
    {
      max_val_index = i;
    }
  }
  return max_val_index;
}
