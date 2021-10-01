
$$
% Define macros here
\newcommand {\m}{\mathcal{M}}
\newcommand {\e}{\mathcal{E}}
\newcommand {\sym}{\mathrm{Sym}}
\newcommand {\skew}{\mathrm{Skew}}
\newcommand {\u}{\mathcal{U}}
\newcommand {\v}{\mathcal{V}}
\newcommand {\t}{\mathrm{T}}
$$

# Notes on Optimization on Smooth Manifolds

[TOC]

## Embedded submanifolds: first-order geometry

In optimization on manifolds, we aim to solve problems of the form 
$$
\min_{x \in \m} f(x),
$$
where $\m$ is a smooth manifold and $f:\m \to \R$ is a smooth cost function. In this chapter, we will develop tools that would enable us to solve such problems. In particular, we need to formally define the notion of _smooth manifold_ and _smooth function_ on it. Furthermore, we will provide a notion of _differential_ and _inner products_ on such spaces. Defining these notions will enable us to generalize classic first-order optimization methods such as gradient descent to smooth manifolds, which are possibly non-linear.

In this chapter, we will

+ have a quick review on Euclidean spaces and their properties,
+ introduce the concept of (an embedded sub-) manifold,
+ define smooth maps on these manifolds and extend the notion of differential to them,

### Euclidean space

A **linear space** or a **vector space**, denoted by $\e$, is a set equipped with (and closed under) vector addition and scalar multiplication. Examples include $\R^n, \R^{n\times p}, \sym (n), \skew (n)$, with the last two being the spaces of real symmetric matrices of size $n$ and the space of real skew-symmetric matrices of size $n$, respectively.

A **basis** for $\e$ is a maximally large set of (linearly) independent vectors $e_1, \cdots, e_n$. Any vector $x \in \e$ can be expressed as a unique linear combination of the basis vectors: $x = a_1 e_1 + \cdots + a_n e_n$ with $a_i$s being real numbers. 

Each basis induces a one-to-one mapping between $\e$ and $\R^n$: we write $\e \equiv \R^n$. Moreover, $\e$ inherits the usual **topology** of $\R^n$: we can define the **neighborhood** of $x \in \e$ to be an open subset of $\e$ that contains $x$.

For two linear spaces $\e$, $\e'$ of dimensions $d$, $d'$ respectively, using the identification $\e \equiv \R^d$, $\e \equiv \R^{d'}$, a function $F: \e \to \e'$ is **smooth** if and only if it is smooth (infinitely differentiable) in the usual sense for a function from $\R^d$ to $\R^{d'}$.

The **differential** of $F$ at $x$ is a linear map $DF(x): \e \to \e'$ defined by 
$$
DF(x)[v] = \lim_{t \to 0} \frac{F(x + tv) -F(x)}{t} = \frac{\dd}{\dd t} F(x + tv) \Bigg |_{t=0}.
$$
This defines the differential using its relation to the directional derivatives. We can alternatively define the differential to be the (unique) linear map that satisfies 
$$
\lim_{h \to 0} \frac{|F(x + h) - F(x) - DF(x)[h]|}{|h|} = 0.
$$
For a curve $c: \R \to \e$, we write $c'(t)$ to denote its velocity at $t$, $\frac{\dd}{\dd t} c(t)$.

We can also equip a linear space $\e$ with an **inner product**, $\langle \cdot, \cdot \rangle : \e \times \e \to \R$. Any linear space with an inner product is called a **Euclidean space**. Notice that the isomorphism between $\e$ and $\R^n$ induced by a particular basis also induces the standard inner product (and Euclidean norm) of $\R^n$ into $\e$.

To wrap up, we can think of a Euclidean space $\e$ (along with a fixed basis for it) as $\R^n$ where we have standard notions of topology, inner product, norm, differential, etc.

### Embedded submanifolds of Euclidean spaces

In this section, we will

+ define what mean by an _embedded submanifold_ of a linear space,
+ what is the _tangent space_ and how to find it for embedded submanifolds,
+ define the _embedded topology_, which allows us to extend notions such as open/closed set and neighborhoods for embedded submanifolds, and
+ show how to create some _new manifolds_ from existing ones.

#### Smooth embedded submanifold

Let $\m$ be a subset of a linear space $\e$. We say $\m$ is a _(smooth)_ embedded submanifold of $\e$ if either of the following holds:

1. $\m$ is an open subset of $\e$. In this case, we call $\m$ an _open submanifold_. If $\m = \e$ then we also call it a _linear manifold_.

2. For a fixed integer $k\geqslant 1$ and for each $x \in \m$, there exists a neighborhood $\u$ of $x$ in $\e$ and a smooth function $h: \u \to \R^k$ such that 

   ***(i)*** For every $y \in \u$, $h(y) = 0$ if and only if $y \in \m$; and

   ***(ii)*** $\rank Dh (x) = k$.

Such a function $h$ is called a **local defining function for $\m$ at $x$**.

We call $\e$ the embedding space or the ambient space of $\m$. 

#### Tangent space

Let $\m$ be a subset of $\e$. For all $x \in \m$ we define the **tangent space** to $\m$ at $x$ as
$$
\t_x \m = \{c'(0)| c: I \to \m \text{ is smooth around } 0 \text{ and } c(0) = x \}.
$$
Basically, a vector $v \in \e$ is in $\t_x \m$ (is a **tangent vector**) if and only if there exists a smooth curve on $\m$ passing through $x$ with velocity $v$.

Notice that $\t_x \m \subseteq \e$ is not necessarily a linear space. However, the following theorem which characterizes the tangent space of smooth manifolds shows that _the tangent space of a smooth embedded submanifold at any point is indeed a linear space._

**Characterization of $\t_x \m$:** Let $\m$ be an embedded submanifold of $\e$. Consider a point $x$ on $\m$. If $\m$ is an open submanifold, then $\t_x \m = \e$. Otherwise, $\t_x \m = \ker Dh(x)$ with $h$ being any local defining function of $\m$ at $x$.

The above theorem implies that for any embedded submanifold $\m$, and for any point $x \in \m$, the set $\t_x \m$ is a linear subspace of $\e$ of some fixed dimension $\dim \ker Dh(x) = \dim \e - \rank Dh(x) = \dim \e - k$. The dimension of $\t_x\m$ is called the **dimension of $\m$** denoted by $\dim \m$.

#### Topology of an embedded submanifold

A subset $\u$ of $\m$ is _open_ (respectively, _closed_) in $\m$ if $\u$ is the intersection of $\m$ with an open (respectively closed) subset of $\e$. This is called the **subspace topology**.

A **neighborhood** of $x \in \m$ is an open subset of $\m$ that contains $x$. A neighborhood of a subset of $\m$ is an open set of $\m$ that contains that subset.

#### Creating new manifolds

+ Let $\m$ be an embedded submanifold of $\e$. Any open subset of $\m$ is also an embedded submanifold of $\e$ with same dimension and tangent spaces as $\m$.

+ Let $\m$, $\m'$ be embedded submanifolds of $\e$, $\e'$. Then their Cartesian product, $\m \times \m'$ is an embedded submanifold of $\e \times \e'$ of dimension $\dim \m + \dim \m'$ such that 
  $$
  \t_{(x, x')} {\m \times \m'} = \t_x\m \times \t_{x'} \m'.
  $$

### Smooth maps on embedded submanifolds

Let $\m$ and $\m'$ be embedded submanifolds of $\e$ and $\e'$ respectively. A map $F: \m \to \m'$ is smooth at a point $x \in \m$ if there exists a smooth  (in the usual sense) function $\bar F:\u \to \e'$ on a neighborhood $\u$ of $x$ in $\e$ and such that $F$, $\bar F$ coincide on $\m \cap \u$, that is, 
$$
\forall y \in \m \cap \u : \; F(y) = \bar F (y).
$$
Such a function $\bar F$ is called a _smooth extension_ of $F$ around $x$. We say $F$ is smooth if it is smooth at all $x \in \m$.

We can also show that this definition of smoothness of a function defined on a manifold is equivalent to the one presented below:

A map $F : \m \to \m'$ is smooth if and only if it admits a (single) smooth extension $\bar F : \u \to \e'$ on a neighborhood $\u$ of $\m$ in $\e$ such that $F$ is the restriction of $\bar F$ to $\m$: $F = \bar F |_\m$.

A _scalar field on a manifold $\m$_ is a function $f:\m \to \R$. If $f$ is smooth then its called a smooth scalar field. The set of smooth scalar fields on $\m$ is denoted by $\mathfrak{F} (\m)$.

### Differential of a smooth map

Intuitively, the differential of a smooth map $f$ at a certain point $x$ should be a linear operator $Df(x)$ such that $Df(x)[v]$ gives us the change in $f$ if we take an infinitely small step in the direction of $v$. 
$$
t \times Df(x)[v] \approx f(x + tv) - f(x)
$$
When a function is defined on an open subset of a linear space $\e$, at any point $x \in \e$ we can move along any direction $v$ from $x$. This helps us define the differential of that map as the linear function that gives us the change in the value of $f$ as we move along any direction $v$. When we have a function that is defined on a manifold $\m$, we can not move in any arbitrary direction as we may no longer be on $\m$. One way to deal with this is to only consider moving in the directions that are allowed, that is, those directions that are in $T_x\m$.

## References

An introduction to optimization on smooth manifolds by Nicolas Boumal

(By: Saeed Hedayatian)