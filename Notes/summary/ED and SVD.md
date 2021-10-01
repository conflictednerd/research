# ED and SVD

### Eigen Decomposition

Suppose that a matrix $\mathbf{A}$ has $n$ eigenvectors $\{\mathbf{v}_{1}, \cdots, \mathbf{v}_n\}$, with corresponding eigenvalues $\{\lambda_1, \cdots, \lambda_n \}$. 
We can put these eigenvectors together, as columns of a matrix $\mathbf{V} = [\mathbf{v}_{1}| \cdots| \mathbf{v}_n]$, and put the eigenvalues together in a vector, $\mathbf{\lambda} = [\lambda_1, \cdots, \lambda_n]^T$. The _eigen-decomposition_ of $\mathbf{A}$ is then given by

$$ \mathbf{A} = \mathbf{V}\text{diag}(\mathbf{\lambda})\mathbf{V}^{-1}.$$

One way to think of the above decomposition is to view $\mathbf{V}$ as a change-of-basis from the eigen-basis to the standard basis:

To compute $\mathbf{A}\mathbf{x}$ for any vector $\mathbf{x} \in \mathbb{R}^n$,

	+ First, perform a change of basis, and obtain the representation of $\mathbf{x}$ in the eigen-basis of $\mathbf{A}$.
	+ Then, stretch $\mathbf{x}$ in each of the directions by the value specified by the eigenvalues.
	+ Finally, perform another change of basis and obtain the representation of $\mathbf{A}\mathbf{x}$ in the standard basis.



Every _real symmetric matrix_ $\mathbf{A}$, has real eigenvalues. Thus, it can be decomposed into

$$ \mathbf{A} = \mathbf{Q}\mathbf{\Lambda}\mathbf{Q}^{T},$$

where $\mathbf{Q}$ is an orthogonal matrix whose columns are eigenvectors of $\mathbf{A}$ and $\mathbf{\Lambda}$ is a diagonal matrix containing the respective eigenvalues.



Some useful information that we can get from the eigen-decomposition of a matrix:

+ A matrix is _singular_ if and only if any of its eigenvalues are zero.
+ It can be used to optimize the quadratic form $f(\mathbf{x}) = \mathbf{x}^T\mathbf{A}\mathbf{x}$ subject to $||\mathbf{x}||_2 = 1$. Notice that $f$ 's maximum(minimum) is equal to the larges(smallest) eigenvalue.
+ A matrix whose eigenvalues are all positive is called _positive definite_. If all eigenvalues are non-negative, it is _positive semidefinite_. For a positive semidefinite matrix, we have $\forall \mathbf{x}, \;\; \mathbf{x}^T\mathbf{A}\mathbf{x} \geq 0$.

### Singular Value Decomposition

The singular value decomposition(SVD) is similar to eigen-decomposition but is more generally applicable. Any $m\times n$ matrix $\mathbf{A}$ can be decomposed as

$$\mathbf{A} = \mathbf{U}\mathbf{D}\mathbf{V}^T$$,

where $\mathbf{U}$ is an $m\times m$ orthogonal matrix, $\mathbf{V}$ is an $n\times n$ orthogonal matrix and $\mathbf{D}$ is a $m \times n$ diagonal matrix. 

+ Diagonal elements of $\mathbf{D}$ are _singular values_ of $\mathbf{A}$.

+ Columns of $\mathbf{U}$ are known as _left-singular vectors_ of $\mathbf{A}$ and columns of $\mathbf{V}$ are known as _right-singular vectors_ of $\mathbf{A}$.

+ Left-singular vectors of $\mathbf{A}$ are the eigenvectors of $\mathbf{A}\mathbf{A}^T$ and right-singular vectors of $\mathbf{A}$ are the eigenvectors of $\mathbf{A}^T\mathbf{A}$.

+ Non-zero *singular values* of $\mathbf{A}$ are the square roots of _eigenvalues_ of $\mathbf{A}\mathbf{A}^T$.

+ The _Moore-Penrose pseudoinverse_ can be defined for any matrix $\mathbf{A}$ using its SVD as

  ​	$$\mathbf{A}^+ = \mathbf{V}\mathbf{D}^+\mathbf{U}^T$$, 

  ​	where $\mathbf{D}^+$ is obtained by taking the reciprocal of $\mathbf{D}$ 's  non-zero elements and transposing the resulting matrix.

+ Moore-Penrose pseudoinverse can be used to efficiently solve systems of linear equations. Given the system $\mathbf{A}\mathbf{x} = \mathbf{y}$, the relation $\mathbf{x} = \mathbf{A}^+\mathbf{y}$ gives us the _solution with minimal Euclidian norm_, $||\mathbf{x}||_2$ among all possible solutions (if there are multiple solutions) or gives us the _$\mathbf{x}$ for which $\mathbf{A}\mathbf{x}$ is as close as possible to $\mathbf{y}$ in terms of Euclidian norm_(if there are no solutions).
