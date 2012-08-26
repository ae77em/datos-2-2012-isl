#include <iostream>
#include "redsvd/src/redsvd.hpp"

#include "redsvd/src/eigen/Eigen/Dense.h"

using namespace Eigen;

int main()
{
  MatrixXd m(2,2);
  m(0,0) = 19;
  m(1,0) = 321;
  m(0,1) = -1;
  m(1,1) = m(1,0) + m(0,1);
  std::cout << "Here is the matrix m:\n" << m << std::endl;
  VectorXd v(2);
  v(0) = 12;
  v(1) = v(0) - 1;
  std::cout << "Here is the vector v:\n" << v << std::endl;
}

