//MlpNetwork.h

#ifndef MLPNETWORK_H
#define MLPNETWORK_H

#include "Dense.h"

#define MLP_SIZE 4

/**
 * @struct digit
 * @brief Identified (by Mlp network) digit with
 *        the associated probability.
 * @var value - Identified digit value
 * @var probability - identification probability
 */
typedef struct digit {
	unsigned int value;
	float probability;
} digit;

const matrix_dims img_dims = {28, 28};
const matrix_dims weights_dims[] = {{128, 784},
									{64,  128},
									{20,  64},
									{10,  20}};
const matrix_dims bias_dims[] = {{128, 1},
								 {64,  1},
								 {20,  1},
								 {10,  1}};


/**
 * @class MlpNetwork
 * final integration of this project
 */
class MlpNetwork{
 private:
  Dense _dense1;
  Dense _dense2;
  Dense _dense3;
  Dense _dense4;

 public:

  //constructor
  MlpNetwork(const Matrix weights[], const Matrix biases[]);

  // operator() - from img (as matrix) to the final value calculated
  digit operator()(const Matrix& x) const;
};

#endif // MLPNETWORK_H