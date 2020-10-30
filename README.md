# Gradient descent

最急降下法をやってみた

### `asg01/main.cpp`

2次最適化問題を最急降下法で解く例．

勾配のノルムが一定の条件を下回れば終了．

以下は実行例

```
--------------------------------------------------
Gradient descent iteration = 0
--------------------------------------------------
objective function f = 0
norm of gradient g = 2.23607
solution x = 
0.2
0.1
--------------------------------------------------
.
.
.
--------------------------------------------------
Gradient descent iteration = 49
--------------------------------------------------
objective function f = -1.5
norm of gradient g = 0.0010005
solution x = 
0.999634
0.999531
Gradient descent successfully converges
--------------------------------------------------
Optimized solution x =
0.999634
0.999531


```



### `asg02/main.cpp`

2次最適化問題をバックトラック直線探索を用いた最急降下法で解く例．

直線探索の停止判定にはアルミホの条件を用いる．

以下は実行例

```
--------------------------------------------------
Gradient descent iteration = 0
--------------------------------------------------
objective function f = 0
norm of gradient g = 2.23607
solution x = 
1.25
0.625
--------------------------------------------------
.
.
.
--------------------------------------------------
Gradient descent iteration = 35
--------------------------------------------------
objective function f = -1.5
norm of gradient g = 7.76407e-05
solution x = 
0.999992
1.00001
Gradient descent successfully converges
--------------------------------------------------
Optimized solution x =
0.999992
1.00001
```

アルミホの条件のおかげで`asg01`よりループ回数が減っている．



### `asg03/main.cpp`

2次最適化問題を最適なステップ幅を用いた最急降下法で解く例．

以下は実行例

```
--------------------------------------------------
Gradient descent iteration = 0
--------------------------------------------------
objective function f = 0
norm of gradient g = 2.23607
solution x = 
0.909091
0.454545
--------------------------------------------------
.
.
.
--------------------------------------------------
Gradient descent iteration = 15
--------------------------------------------------
objective function f = -1.5
norm of gradient g = 8.0023e-05
solution x = 
0.999988
0.999988
Gradient descent successfully converges
--------------------------------------------------
Optimized solution x =
0.999988
0.999988

```

よりループ回数が少なくなっている．



### `asg04/main.cpp`

以下の最適化問題を最急降下法とアルミホの条件による直線探索で解く例．

```html
<img src=
"https://render.githubusercontent.com/render/math?math=%5Cbegin%7Balign%2A%7D%0AR%28g%29+%26%3D+%5Cfrac%7B1%7D%7Bn%7D+%5Csum_%7Bi%3D1%7D%5E%7Bn%7D+%5Cell%28y_i%2Cg%28x_i%29%29%5C%5C%0A%26%3D%5Cfrac%7B1%7D%7B2n%7D+%28%5Cmathbf%7BX%7D%5Cboldsymbol%7Bw%7D-%5Cmathbf%7By%7D%29%5ET+%28%5Cmathbf%7BX%7D%5Cboldsymbol%7Bw%7D-%5Cmathbf%7By%7D%29%0A%5Cend%7Balign%2A%7D%0A" 
alt="\begin{align*}
R(g) &= \frac{1}{n} \sum_{i=1}^{n} \ell(y_i,g(x_i))\\
&=\frac{1}{2n} (\mathbf{X}\boldsymbol{w}-\mathbf{y})^T (\mathbf{X}\boldsymbol{w}-\mathbf{y})
\end{align*}
">
```

