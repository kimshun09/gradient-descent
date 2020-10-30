#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

bool minQuadFunc(const MatrixXd& A, const VectorXd& b, VectorXd& x) {

  double alpha;
  double tol = 1e-4;
  int maxIter = 50;
  int maxBackTrack = 10;

  for(int iter = 0; iter < maxIter; ++iter) {

    double f = ((x.transpose() * (A * x))/2.0 + b.transpose() * x).value();
    VectorXd g(x.size());

    //
    // 現在の目的関数の値を計算する
    //
    // f = ...
      f = ((x.transpose() * (A * x))/2.0 + b.transpose() * x).value();




    //
    // 勾配ベクトル
    //
    // g = ...
      g = A*x + b;

    //
    // 最適なステップ幅を設定
    //
    // alpha = ..
      alpha = (g.transpose()*g / (g.transpose()*A*g)).value();
      x -= alpha * g;

    cout << "--------------------------------------------------" << endl;
    cout << "Gradient descent iteration = " << iter << endl;
    cout << "--------------------------------------------------" << endl;
    cout << "objective function f = " << f << endl;
    cout << "norm of gradient g = " << g.norm() << endl;
    cout << "solution x = " << endl;
    cout << x << endl;

    if (g.norm() < tol) {
      return true;
    }
  }
  return false;
}

int main() {

  MatrixXd A(2,2);
  VectorXd b(2);
  VectorXd x(2);

  // 最適化問題を定義するパラメータ
  A <<
    2, 1,
    1, 4;
  b << 3, 1;

  // 初期解
  x << 0, 0;

  if(minQuadFunc(A, b, x)) {
    cout << "Gradient descent successfully converges" << endl;
  } else {
    cout << "Maximum iteration reaches before convergence" << endl;
  }

  cout << "--------------------------------------------------" << endl;
  cout << "Optimized solution x =" << endl;
  cout << x << endl;

  return 0;
}
