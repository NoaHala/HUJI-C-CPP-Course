#ifndef MATRIX_H
#define MATRIX_H
#include <iostream>
#include <fstream>
using std::ostream;
using std::istream;

/**
 * @struct matrix_dims
 * @brief Matrix dimensions container. Used in MlpNetwork.h and main.cpp
 */
typedef struct matrix_dims
{
    int rows, cols;
} matrix_dims;

/**
 * @class Matrix
 * Notice the headlines, here and in the cpp implementation file,
 * they're helpful for finding faster the constructors, operators or methods:)
 */
class Matrix
{
 private:
  float *_matrix_array;
  matrix_dims _matrix_dims;

 public:

  /*******************
  *   Constructors   *
  ********************/

  /**
  * Default constructor
  * Constructs Matrix of size 1 × 1. Inits the single element to 0.
  */
  Matrix ();

  /**
  * Constructor
  * Constructs Matrix of size 𝑟𝑜𝑤𝑠 × 𝑐𝑜𝑙𝑠. Inits all elements to 0
  */
  Matrix (int rows, int cols);

  /**
  * Copy Constructor
  * Constructs a matrix from another Matrix m.
  */
  Matrix (const Matrix &m);

  /**
  * Destructor
  */
  ~Matrix ();

  /**************
  *   Getters   *
  ***************/

  /**
  * returns the amount of rows as int.
  */
  int get_rows () const
  { return _matrix_dims.rows; }

  /**
  * returns the amount of columns as int.
  */
  int get_cols () const
  { return _matrix_dims.cols; }

  /****************
  *   Operators   *
  *****************/

  // Matrix a, b; → a + b
  Matrix operator+ (const Matrix &m) const;

  // Matrix a, b; → a = b
  Matrix &operator= (const Matrix &m);

  // Matrix a, b; → a += b
  Matrix &operator+= (const Matrix &m);

  // Matrix a, b; → a * b
  Matrix operator* (const Matrix &m) const;

  // Matrix m; float c; → m * c
  Matrix operator* (const float &c) const;

  // Matrix m; float c; → c * m
  friend Matrix operator* (const float &c, const Matrix &m);

  // For cell (i,j) in matrix m:
  // m(i,j) will return the element in cell (i,j) in m
  float operator() (const int &i, const int &j) const;

  // assigning operator fot For cell (i,j) in matrix m
  float &operator() (const int &i, const int &j);

  // m[k] will return the k'th element as if m is represented as a vector
  float operator[] (const int &k) const;

  // assigning operator fot For cell [k] in matrix m
  float &operator[] (const int &k);

  // print of matrix as described in section 3.1.1 of the task instructions
  friend ostream& operator<<(ostream& os, const Matrix& m);

  // fills matrix elements.
  friend istream& operator>>(std::ifstream& is, Matrix& m);


  /****************
  *    Methods    *
  *****************/

  /**
  * Returns the sum of all the elements in the matrix
  */
  float sum() const;

  // Transforms a matrix into its transpose matrix,
  // Supports function call chaining/concatenation
  Matrix& transpose();

  // Transforms a matrix into a column vector (as described in section 3.1.2
  // of the task instructions). Supports function call chaining/concatenation.
  Matrix& vectorize();

  // Prints matrix elements, no return value.
  // Prints space after each element (including last element in row).
  // Prints newline after each row (including last row).
  void plain_print() const;

  // Returns a matrix which is the element-wise multiplication (Hadamard
  //product) of this matrix with another matrix m.
  Matrix dot(const Matrix& m) const;

  // Returns the Frobenius norm of the given matrix
  float norm() const;

  // todo - bonus rref

  // Returns index of the largest number in the matrix
  int argmax() const;

  // Print the matrix
  void print () const
  {
    for (int i = 0; i < _matrix_dims.rows; i++)
    {
      for (int j = 0; j < _matrix_dims.cols; j++)
      {
        std::cout << _matrix_array[i * _matrix_dims.cols + j] << " ";
      }
      std::cout << std::endl;
    }
  }

};

#endif //MATRIX_H