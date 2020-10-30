#include <iostream>
#include <fstream>
#include <cmath>
#include <Eigen/Dense>

using namespace std;
using namespace Eigen;

double calc_obj(const VectorXd& x, VectorXd& grad) {

    //
    // 目的関数の値を返し，
    // 勾配（微分値）の値を引数gradに代入する
    //
    // ベクトルuの初期化
    VectorXd u1(2); u1 << -0.7, 0.3;
    VectorXd u2(2); u2 << 0.1, -0.2;
    VectorXd u3(2); u3 << 0.6, 0.7;

    // 4つのシグマ部分の計算
    double sum0=0, sum1=0, sum2=0, sum3=0;
    for(int i=0; i<x.size(); i++) {
        sum0 += x(i) * x(i);
        sum1 += (x(i)-u1(i)) * (x(i)-u1(i));
        sum2 += (x(i)-u2(i)) * (x(i)-u2(i));
        sum3 += (x(i)-u3(i)) * (x(i)-u3(i));
    }
    // 目的関数の値valueを計算
    double value = sum0 - exp(-10*sum1) - exp(-5*sum2) - exp(-10*sum3);

    // 勾配の値の計算
    for(int i=0; i<grad.size(); i++)
        grad(i) = 2*x(i) + 20*(x(i)-u1(i))*exp(-10*sum1) + 10*(x(i)-u2(i))*exp(-5*sum2) + 20*(x(i)-u3(i))*exp(-10*sum3);

    return value;
}

bool minSumExp(VectorXd& x) {

    double alpha;
    double xi = 0.1;
    double tol = 1e-4;
    int maxIter = 100;
    int maxBackTrack = 10;


    for(int iter = 0; iter < maxIter; ++iter) {

        double f;
        VectorXd g(x.size());

        //fの値を計算
        f = calc_obj(x, g);

        // 更新前のxの値を保存
        VectorXd x_old = x;
        alpha = 10;
        bool flg = true;
        for(int btIter = 0; btIter < maxBackTrack; ++btIter) {

            //
            // 現在のステップ幅alphaでx_oldから解を更新
            //
            // x = ...
            x = x_old - alpha * g;

            // 引数に勾配ベクトルが必要なため，使わなくても一応宣言しておく
            VectorXd g_temp;
            double f_temp =  calc_obj(x, g_temp); // 目的関数（ここではg_tempは使わない）

            double armijo_rhs;

            //
            // アルミホのルールの右辺(rhs: right hand side)を計算する
            //
            // rhs_armijo = ...
            //armijo_rhs = f - xi*alpha*g.norm()*g.norm();
            armijo_rhs = f - xi*alpha*(g.transpose()*g).value();

            if(f_temp < armijo_rhs) {
                flg = false;
                break;
            }
            alpha = alpha / 2;
        }
        if (flg) {
            x = x_old;
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
            break;
        }

    }

    return true;
}

int main() {

    VectorXd x(2);
    // 初期解
    x << -0.5, 0.5 ;

    if(minSumExp(x)) {
        cout << "Gradient descent successfully converges" << endl;
    } else {
        cout << "Maximum iteration reaches before convergence" << endl;
    }

    cout << "--------------------------------------------------" << endl;
    cout << "Optimized solution x =" << endl;
    cout << x << endl;

    return 0;
}



