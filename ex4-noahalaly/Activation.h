#ifndef ACTIVATION_H
#define ACTIVATION_H

#include "Matrix.h"

/**
 * @namespace activation
 * activation function for the network layers
 */
namespace activation
{
    /**
     * relu activation function as described in 1.2.3.1 in the task's
     * instruction
     */
    Matrix relu (Matrix &m);

    /**
     * softmax activation function as described in 1.2.3.1 in the task's
     * instruction
     */
    Matrix softmax (Matrix &m);

    // typedef for easier access to the activation function
    typedef Matrix (*Activation_Function) (Matrix &m);
}

#endif //ACTIVATION_H