$$
% Define macros here
\newcommand\bf{\mathbf{f}}
\newcommand\bx{\mathbf{x}}
\newcommand\bh{\mathbf{h}}
\newcommand\br{\mathbf{r}}
\newcommand\bg{\mathbf{g}}
\newcommand\be{\mathbf{e}}
\newcommand\bu{\mathbf{u}}
\newcommand\bv{\mathbf{v}}
\newcommand\pard[2]{\frac{\partial #1}{\partial #2}}
$$

# Notes on Topology and Analysis

[TOC]

## Topology



A **topology** on  a set $X$ is a collection $\tau$ of subsets of $X$ having the following properties:

1. $\varnothing$ and $X$ are in $\tau$.

2. The union of the elements of any subcollection of $\tau$ is in $\tau$.
   $$
   \{U_i: i\in I\} \subseteq \tau \implies \bigcup_{i\in I}{U_i} \in \tau
   $$
   
3. The intersection of the elements of any finite subcollection of $\tau$ is in $\tau$.
   $$
   U_1, \cdots, U_n \in \tau \implies U_1 \cap \cdots \cap U_n \in \tau
   $$

A set $X$ for which a topology $\tau$ has been specified is called a **topological space**.

If $(X, \tau)$ is a topological space, a subset $U$ of $X$ is an **open set** of $X$ if $U\in \tau$.

If $X$ is a set, a **basis** for a topology on $X$ is a collection $\mathfrak{B}$ of subsets of $X$ (called **basis elements**) such that

1. For each $x \in X$, there is at least one basis element $B$ containing $x$.
2. If $x$ belongs to the intersection of two basis elements $B_1$ and $B_2$, then there is a basis element $B_3$ containing $x$ such that $B_3 \subset B_1 \cap B_2$.

If $\mathfrak{B}$ is a basis for a topology on $X$, the **topology $\tau$ generated by $\mathfrak{B}$** is described as follows: A subset $U$ of $X$ is said to be open in $X$ (that is, $U \in \tau$) if for each $x \in U$, there is a basis element $B \in \mathfrak{B}$ such that $x \in B$ and $B \subset U$.

A subset $A$ of a topological space $(X, \tau)$ is said to be **closed** if $X - A$ is open. It can be shown that:

1. $\varnothing$ and $X$ are closed.
2. Arbitrary intersection of closed sets are closed.
3. Finite unions of closed sets are closed.

If $(X, \tau)$ is a topological space and $p$ is a point in $X$, a **neighborhood** of $p$ is a subset $V$ of $X$ that includes an open set $U$ containing $p$, $p \in U \subseteq V \subseteq X$.

## Metric Spaces

A **metric space** is an ordered pair $(M, d)$ where $M$ is a set and $d$ is a **metric** defined on $M$, that is, $d: M\times M \to \mathbb{R}$ is a function such that for any $x, y, z \in M$, the following holds:

1. $d(x, y) = 0 \iff x = y$
2. $d(x, y) = d(y, x)$
3. $d(x, z) \leqslant d(x, y) + d(y, z)$

It can also be shown that any metric must also satisfy $d(x, y) \geqslant 0$.

Some examples of metric spaces are given below:

1. $\mathbb{R}^n$ along with the Euclidean distance $d(x, y) = \sqrt{(x-y)^T(x-y)}$ is a _complete_ metric space.
2. Any **normed vector space** is a metric space by defining $d(x, y) = \Vert y-x \Vert$

About any point $x$ in a metric space $M$ we define the **open ball** of radius $r>0$ (where $r$ is a real number) about $x$ as the set $B(x;r) = \{y\in M: d(x, y) < r\}$

The collection of these open balls form a basis for a topology on $M$, making every metric space a topological space as well in a natural manner.

A subset $U$ of $M$ is called **open** if for every $x \in U$, there exists a real number $r>0$ such that $B(x;r)$ is contained in $U$.

A **neighborhood** of a point $x$ is any subset of $M$ that contains an open ball about $x$ as a subset.

A sequence $\{x_n\}$ in a metric space $M$ is said to _converge_ to the limit $x \in M$ if and only if for every $\varepsilon>0$ there exists a natural number $N$ such that $d(x_n, x) < \varepsilon$ for all $n>N$.

If $U$ is an open set in $\mathbb{R}^n$ and we _remove a finite number of points_ from it, the resulting set is still open.

## Multivariable Calculus

**Derivative:** Suppose $E$ is an open set in $\R^n$, $\bf$ maps $E$ into $\R^m$, and $\bx \in E$. If there exists a _linear transformation_ $A$ of $\R^n$ into $\R^m$ such that
$$
\lim_{\bh \to \mathbf{0}} \frac{\vert \bf(\bx + \bh) - \bf(\bx) - A\bh \vert}{\vert \bh \vert} = 0,
$$
then we say that $\bf$ is **differentiable** at $\bx$, and we write $\bf' (\bx) = A$. If $\bf$ is differentiable at every $\bx \in E$, we say that $\bf$ is *differentiable in $E$*.

Here are a few remarks on the definition presented above:

1. Note that since $E$ is open, if $|\bh|$ is small enough, then $\bx + \bh \in E$. Hence, $\bf(\bx + \bh) \in \R^m$ is defined.

2. It can be shown that if $\bf$ is differentiable at $\bx$, then $\bf'(\bx) = A$ is unique.

3. The aforementioned relation can be rewritten as
   $$
   \bf (\bx + \bh) - \bf(\bx) = \bf'(\bx)\bh + \br(\bh)\label{eq:mv2}\tag{1}
   $$
   where the remainder $\br(\bh)$ satisfies
   $$
   \lim_{\bh \to \mathbf{0}} \frac{|\br(\bh)|}{|\bh|} = 0.
   $$
   This may be interpreted by saying that _for fixed $\bx$ and small $\bh$, the left side of ($\ref{eq:mv2}$) is approximately equal to $\bf'(x)\bh$_, that is, to the value of a linear transformation applied to $\bh$.

4. If $\bf$ is differentiable in $E$, then for every $\bx \in E$, $\bf'(\bx)$ is a function, namely, a linear transformation of $\R^n$ into $\R^m$. But _$\bf'$ itself is also a function_: it maps $E$ into the space of linear transformation from $\R^n$ to $\R^m$, denoted by $L(\R^n, \R^m)$.

5. $\bf$ is continuous at any point at which it is differentiable.

6. The derivative that is defined here is often called the **differential** or the **total derivative** of $\bf$ at $\bx$, to distinguish it from partial derivatives that will come later.

**Chain rule:** Suppose $E$ is an open set in $\R^n$, $\bf$ maps $E$ into $\R^m$ and is differentiable at $\bx_0 \in E$, $\bg$ maps an open set containing $\bf(E)$ into $\R^k$ and is differentiable at $\bf(\bx_0)$. Then the mapping $\mathbf{F}$ of $E$ into $\R^k$ defined by $\mathbf{F}(\bx) = \bg(\bf(\bx))$ is differentiable at $\bx_0$, and 
$$
\mathbf{F}'(\bx_0) = \bg'(\bf(\bx_0))\bf'(\bx_0),
$$
where on the right side, we have the product of two linear transformations.

**Partial Derivatives:** Consider a function $\bf: E \to \R^m$, where $E\subset \R^n$ is an open set. Let $\{\be_1, \cdots, \be_n\}$ and $\{\bu_1, \cdots, \bu_m\}$ be the standard basis of $\R^n$ and $\R^m$. The _components of_ $\bf$ are the real functions $f_1, \cdots f_m$ defined by
$$
\bf(\bx) = \sum_{i=1}^{m}f_i(\bx)\bu_i \;\;\;\;\;\;\;\; (\bx \in E),
$$
or, equivalently, by $f_i(\bx) = \bf(\bx) \cdot \bu_i, \; 1\leqslant i \leqslant m$.

For $\bx \in E$, $1\leqslant i \leqslant m$, $1 \leqslant j \leqslant n$, we define
$$
(D_j f_i)(\bx) = \lim_{t \to 0}\frac{f_i(\bx + t\be_j) - f_i(\bx)}{t},
$$
provided the limit exists. It can be seen that $D_jf_i$ is the derivative of $f_i$ with respect to $x_j$, keeping other variables fixed. The notation
$$
\frac{\partial f_i}{\partial x_j}
$$
is therefore often used in place of $D_jf_i$, which is called a _partial derivative_.

It must be noted that even for continuous functions, the existence of all partial derivatives <u>does not</u> imply differentiability. However, if $\bf$ is known to be differentiable at a point $\bx$, then its partial derivatives exist at $\bx$, and they completely determine the linear transformation $\bf'(\bx)$. See the following theorem for more details.

Suppose $\bf$ maps an open set $E\subset \R^n$ into $\R^m$, and $\bf$ is differentiable at a point $\bx \in E$. Then the partial derivatives $\pard{f_i}{x_j}$ exist, and
$$
\bf'(\bx) \be_j = \sum_{i = 1}^{m}(\pard{f_i}{x_j})(\bx)\bu_i \;\;\;\; (1\leqslant j \leqslant n),
$$
where $\{\be_1, \cdots, \be_n\}$ and $\{\bu_1, \cdots, \bu_m\}$ are the standard bases of $\R^n$ and $\R^m$ respectively.

As a consequence of the above theorem, if $[\bf'(\bx)]$ is the matrix that represents $\bf'(\bx)$ with respect to our standard bases, then $\bf'(\bx) \be_j$ is the $j$th column of that matrix. Therefore, $\pard{f_i}{x_j}$ is the number at $i$th row and $j$th column of $[\bf'(\bx)]$:
$$
[\bf'(\bx)] = 
\begin{bmatrix}
(D_1f_1)(\bx) & \cdots & (D_nf_1)(\bx) \\
\vdots & \ddots & \vdots \\
(D_1f_m)(\bx) & \cdots & (D_nf_m)(\bx)
\end{bmatrix}
$$
This matrix is often regarded as the **Jacobian** matrix.

**Gradient:** Let $f$ be a <u>real valued</u> differentiable function with its domain $E \subseteq \R^n$ being an open set. Associate with each $\bx \in E$ a vector, the so-called _gradient_ of $f$ at $\bx$, defined by 
$$
(\grad f)(\bx) = \sum_{i=1}^n {(D_if)(\bx)\be_i}
$$
One can represent this vector (with respect to the standard basis) as $[\pard{f}{x_1}(\bx), \cdots, \pard{f}{x_n}(\bx)]^T$.

Some points regarding the gradient:

1. The gradient defines a vector field, over the domain of a real valued function, that is, if $f:\R^n \to \R$ then the gradient $\grad f:\R^n \to \R^n$ assigns a vector to each point in $\R^n$.

2. The gradient vector can be interpreted as _the direction and rate of fastest increase_. If the gradient of a function is non-zero at a point $\bx$, its direction is the one moving along which and away from $\bx$ increases the function most quickly. The magnitude of gradient is the _rate of change_ in that direction.

3. The gradient is the **dual to the total derivative** $D f$: The value of the gradient at any point is a **tangent vector**, while the value of the derivaitve at any point is a **cotangent vector**[^fn1], that is, a linear function on vectors.

4. If $f:\R^n \to \R$ [^fn2] is differentiable at a point $\bx$ and $\mathbf{v}$ is a vector, then the dot product of the gradient of $f$ at $\bx$ with $\mathbf{v}$ is equal to the directional derivative of $f$ at $\bx$ along $\mathbf{v}$. Thus, 
   $$
   (\grad f)(\bx) \cdot \bv = \pard{f}{\bv} (\bx) = D_\bv f(\bx)
   $$

5. TODO: Gradient of a vector field is the transpose of Jacobian, Einstien notaion

**TODO: Directional derivative**

**TODO: Multi variable Taylor expansion**

**TODO: Manifolds**



[^fn1]: For any smooth manifold $\mathcal{M}$​ and a point $x$​ on it, the _cotangent space_ is a vector space denoted by $T_x^*\mathcal{M}$​ and defined to be the dual space of the tangent space at $x$​, $T_x\mathcal{M}$​. The elements of this space are called _cotangent vectors_ or _tangent covectors_.
[^fn2]: More generally, the domain of $f$ can be any smooth manifold. In this case, the vector $\bv$ must be a tangent vector at point $\bx$.



## References 

Topology, a first course by Munkres

Principles of mathematical analysis by Rudin

Wikipedia

(By: Saeed Hedayatian)