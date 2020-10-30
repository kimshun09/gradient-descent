#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

bool minQuadFunc(const MatrixXd& A, const VectorXd& b, VectorXd& x) {

    double alpha = 0.1;
    double tol = 1e-4;
    int maxIter = 50;

    // 繰り返し上限maxIterまでループを繰り返す
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
        // xで偏微分する
        g = A*x + b;

        //
        // -g方向にステップ幅\alphaで更新
        //
        // x = ...
        //
        // -gは最急降下方向
        x -= alpha * g;

        cout << "--------------------------------------------------" << endl;
        cout << "Gradient descent iteration = " << iter << endl;
        cout << "--------------------------------------------------" << endl;
        cout << "objective function f = " << f << endl;
        cout << "norm of gradient g = " << g.norm() << endl;
        cout << "solution x = " << endl;
        cout << x << endl;

        if (g.norm() < tol) {
            break; // 勾配のノルムが小さくなれば終了
        }
    }

    return true;
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
