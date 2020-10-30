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
  int maxBackTrack = 10; // バックトラックの最大繰り返し数

  for(int iter = 0; iter < maxIter; ++iter) {

    double f; // 目的関数の値
    VectorXd g(x.size()); // 勾配ベクトル

    //
    // 現在の目的関数の値を計算する
    //
    // f = ...
      f = ((x.transpose()*A*x)/2 + b.transpose()*x).value();


    //
    // 勾配ベクトル
    //
    // g = ...
      g = A*x + b;

    VectorXd x_old = x; // 古い解を保持しておく
    alpha = 10; // ステップ幅初期化
    bool flg = true;
    for(int btIter = 0; btIter < maxBackTrack; ++btIter) { // バックトラックの繰り返し

      //
      // 現在のステップ幅alphaで"x_old"から解を更新
      //
      // x = ...
        x = x_old - alpha * g;

        double f_temp;

      //
      // 目的関数の値を計算する
      //
      // f_temp = ...
        f_temp = ((x.transpose()*A*x)/2 + b.transpose()*x).value();


        double xi = 0.1; // 定数 \xi
        double rhs_armijo;

      //
      // アルミホのルールの右辺(rhs: right hand side)を計算する
      //
      // rhs_armijo = ...
        rhs_armijo = f - xi*alpha*(g.transpose()*g).value();

        if(f_temp < rhs_armijo) {
            flg = false; // 条件が満たされたことを示すフラグ
            break;
        }
        // ステップ幅減衰率=1/2
        alpha = alpha / 2; // ステップ幅を半分に
    }
    if (flg) {
      x = x_old; // 最小のステップ幅でも条件を満たさなかった場合，解を更新せず終了
      return true;
    }

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
    4, -2,
    -2, 3;
  b << -2, -1;

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
