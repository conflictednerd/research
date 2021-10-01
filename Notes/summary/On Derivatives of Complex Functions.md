# On Derivatives of Complex Functions

Any complex function $f: \C \to \C$ can also be thought of as a function $F: \R^2 \to \R^2$. But the notion of derivative for these two functions are different. Noticeably, $\frac{\dd f}{\\d z}(z_0)$ is a single complex number (equivalently, a point in $\R^2$) while $DF(x_1, x_2)$ is a linear transformation from $\R^2$ into itself, which can be represented as a $2 \times 2$ matrix. Although they seem to be completely different mathematical objects, these two are related to each other in a subtle and beautiful way. In this note I try to explore the connections between these two notions.

## Holomorphic functions

Let $\Omega$ be an open set in $\C$ and $f$ a complex-valued function on it. The function $f$ is said to be **holomorphic at point $z_0 \in \Omega$** if the following limit converges: 
$$
\lim_{h \to 0} \frac{f(z_0+h) - f(z_0)}{h}.
$$
When this limit exists, we denote it by $f'(z_0)$ and call it the (complex) **derivative of $f$ at $z_0$**.

A function $f$ is said to be **holomorphic on $\Omega$** if it is holomorphic at every point of $\Omega$. 

Notice that in this definition, $h$ is a complex number and can approach $0$ from any direction(side-note: check out the $\varepsilon-\delta$ definition of limit as well as the the one using convergence of sequences to see what we mean by _approach_). 


Although the definition of holomorphic functions is very similar to a real, one-variable, differentiable function, there are important distinctions between the two. Here are some examples without proof:

+ A holomorphic function is **infinitely many times complex-differentiable**.
+ Every holomorphic function is **analytic**, in the sense that it has a power series expansion near every point. For this reason, holomorphic functions are sometimes called analytic.

## Real-differentiable functions

Now consider a function $f: U \to \R^2$, where $U\subseteq \R^2$ is an open set. This function is said to be differentiable at a point $a \in U$ if there exists a linear transformation $Df(a): \R^2 \to \R^2$ such that 
$$
\lim_{h \to 0} \frac{\norm{f(x + h) - f(x) - Df(a)[h]}}{\norm{h}} = 0.
$$
The linear map $Df(a)$ is called the (total) **differential or derivative** of $f$ at $a$.

This linear mapping is described in the standard basis of $\R^2$ by the **Jacobian matrix**: 
$$
Df(a) = J_f(a) = J(a) = 
\begin{bmatrix}
\frac{\partial f_1}{\partial x_1}(a) & \frac{\partial f_1}{\partial x_2}(a) \\
\frac{\partial f_2}{\partial x_1}(a) & \frac{\partial f_2}{\partial x_2}(a)
\end{bmatrix}
$$


## Complex-valued functions as mappings

We will now consider both interpretations of a complex-valued function simultaneously and investigate the relation between the two.

Let $f: \C \to \C$ be defined as 
$$
f(z) = f(x + iy) = u(x, y) + iv(x, y),
$$
where $x, y \in \R$ and $u, v$ are functions from $\R^2$ to $\R$. We can associate a mapping $F:\R^2 \to \R^2$ to this complex-valued function by letting
$$
F(x, y) = (u(x, y), v(x, y)).
$$
I call this the *real representation* of the complex-valued function $f$ (I use this terminology because it sounds intuitive to me. I don't know if it is standard or not).

At the first glance, we see that the (complex) derivative of $f$ at a point $z_0$ is a single complex number, $f'(z_0)$, whereas the (total) derivative of $F$ at a point $(x_0, y_0)$ is a $2 \times 2$ real matrix. However on a closer look, we can see that these two derivatives are related to each other.

To see this, let $f: \C \to \C$ be a holomorphic function. Consider the definition of complex derivative when $h$ is real, that is, $h = h_1 +ih_2$ with $h_2 = 0$. If we write $z = x + iy$ and $z_0 = x_0 + iy_0$, we find that 
$$
f'(z_0) = \lim_{h_1 \to 0} \frac{f(x_0+h_1 + iy_0) - f(x_0 + iy_0)}{h_1} = \frac{\partial f}{\partial x}(z_0),
$$
where $\frac{\partial}{\partial x}$ denotes the usual partial derivative with respect to variable $x$. To see how the limit of a complex function reduced to a (real) partial derivative, notice that we fixed $y_0$ and thought of $f$ as a complex-valued function of a single, real variable $x$.

Now taking $h$ to be a purely imaginary number and a similar argument yields 
$$
f'(z_0) = \lim_{h_2 \to 0} \frac{f(x_0 + i(y_0 + h_2)) - f(x_0, iy_0)}{ih_2} = \frac{1}{i}\frac{\partial f}{\partial y}(z_0),
$$
where $\frac{\partial}{\partial y}$ is the usual partial differentiation with respect to $y$ variable.

From the two equations above, we get 
$$
f'(z_0) = \frac{\partial f}{\partial x}(z_0) = \frac{1}{i}\frac{\partial f}{\partial y}(z_0).
$$
If we write $f$ as $f = u + iv$ and separate the real and imaginary parts, we see that the partial derivatives of $u, v$ with respect to $x, y$ exist and satisfy the following relations 
$$
\frac{\partial u}{\partial x} = \frac{\partial v}{\partial y}, \\
\frac{\partial v}{\partial x} = -\frac{\partial u}{\partial y}.
$$
These are the **Cauchy-Riemann** equations and they link complex and real analysis.

To summarize, if $f(x + iy) = u(x, y) + iv(x, y)$ is holomorphic and $F(x, y) = (u(x, y), v(x, y))$ is the associated multivariable function, then we can write 
$$
DF(x, y) =
\begin{bmatrix}
\frac{\partial u}{\partial x} & \frac{\partial u}{\partial y} \\
\frac{\partial v}{\partial x} & \frac{\partial v}{\partial y}
\end{bmatrix} =
\begin{bmatrix}
\frac{\partial u}{\partial x} & \frac{\partial u}{\partial y} \\
-\frac{\partial u}{\partial y} & \frac{\partial u}{\partial x}
\end{bmatrix} =
\begin{bmatrix}
\frac{\partial v}{\partial y} & -\frac{\partial v}{\partial x} \\
\frac{\partial v}{\partial x} & \frac{\partial v}{\partial y}
\end{bmatrix}
$$
The converse of the above is also true:

Let $f = u + iv$ be a complex-valued function defined on an open set $\Omega$. If $u$ and $v$ are *continuously differentiable* and satisfy the Cauchy-Riemann equations on $\Omega$, then $f$ is holomorphic on $\Omega$ and $f'(z) = \frac{\partial f}{\partial z}$. (see the definition of $\frac{\partial f}{\partial z}$ in the last section)

## Geometric Interpretation

Why is it the case that when we represent a holomorphic function as a mapping from $\R^2$ to itself, the Jacobian has a special form? Geometrically speaking, how can we justify the special form of the Jacobian?

First, let's look closely into the Jacobian matrix of the real representation of a holomorphic function $f(z)$. Cauchy-Riemann equations assert that it must be of the following form: 
$$
J =
\begin{bmatrix}
a & -b \\
b & a
\end{bmatrix}
$$
Assuming $J \neq 0$, this matrix is orthogonal, meaning that it can be viewed as a (real) scalar times a rotation matrix: 
$$
J =
\sqrt{a^2 + b^2}
\begin{bmatrix}
\frac{a}{\sqrt{a^2 + b^2}} & -\frac{b}{\sqrt{a^2 + b^2}} \\
\frac{b}{\sqrt{a^2 + b^2}} & \frac{a}{\sqrt{a^2 + b^2}}
\end{bmatrix}
=
\sqrt{a^2 + b^2}
\begin{bmatrix}
\cos \theta & -\sin \theta \\
\sin \theta & \cos \theta
\end{bmatrix}
$$
Hence, the mapping identified with $J$ performs a *rotation* and a *uniform scaling*.

Now, let's look at the complex derivative, $f'(z_0)$. This is a single complex number which can be represented as $r_0e^{i\theta_0}$. Multiplying it by an arbitrary complex number $z = re^{i\theta}$ will give us 
$$
z_0z = r_0re^{i(\theta_0 + \theta)},
$$
which is again, a rotation and a uniform scaling!

## Taking a further step

Here are two side-notes.

### Partial derivative with respect to complex variable

It is convenient to define two differential operators for complex-valued functions: 
$$
\frac{\partial}{\partial z} = \frac{1}{2}(\frac{\partial}{\partial x} + \frac{1}{i}\frac{\partial}{\partial y}) \\
\frac{\partial}{\partial \bar{z}} = \frac{1}{2}(\frac{\partial}{\partial x} - \frac{1}{i}\frac{\partial}{\partial y})
$$
Using this new notation, we can write the following theorem:

If a function $f$ is holomorphic at $z_0$, then 
$$
\frac{\partial f}{\partial \bar{z}}(z_0) = 0, \;\; \frac{\partial f}{\partial z}(z_0) = f'(z_0) = 2\frac{\partial u}{\partial z}(z_0).
$$
Also, if write $F(x, y) = f(z)$, then $F$ is differentiable in the sense of real variables, and 
$$
\det J_F(x_0, y_0) = |f'(z_0)|^2.
$$

### Going from $\R^2$ to $\C$

In this note, we mostly considered complex-variable functions $f:\C \to \C$ and associated with each of them a function $F: \R^2 \to \R^2$ in a natural way.  Here we want to discuss the opposite direction, given a function $F: \R^2 \to \R^2$, can we create a natural *complex representation* for it? Meaning a function $f:\C \to \C$ defined by $f(z) = f(x + iy) = u(x, y) + iv(x, y)$ such that $u = F_1$ and $v = F_2$.

The answer is positive. Given $F(x, y) = (F_1(x, y), F_2(x, y))$, let $z = x + iy$. Then it is easy to see that 
$$
x = \frac{z + \bar z}{2}, \\
y = \frac{z - \bar z}{2}.
$$
Now we can define $f$ as a function of $z$ to be 
$$
f(z) = F_1(\frac{z + \bar z}{2}, \frac{z - \bar z}{2}) + iF_2 (\frac{z + \bar z}{2}, \frac{z - \bar z}{2}).
$$
As we can see, the complex representation depends on both $z$ and $\bar z$.

Remember that Cauchy-Riemann condition asserts that $f$ is holomorphic, if $\frac{\partial f}{\partial \bar z} = 0$, which means that $f$ <u>does not</u> depend on $\bar z$.

## Conclusion

We knew intuitively that any complex valued function $f$ can also be seen (in a natural way) as a mapping $F$ from $\R^2$ into itself. Here we showed that the complex derivative of $f$ is related to the normal (total) derivative of $F$ through Cauchy-Riemann equations. Therefore, if a function is complex-differentiable (holomorphic) then the Jacobian matrix of it's real representation is orthogonal.

## References

*Complex Analysis* by Stein and Shakarchi

