## Representation Learning with Contrastive Predictive Coding

The paper can be found [here](https://arxiv.org/abs/1807.03748).

### Why?

Having access to informative features and representations of data is essential for almost all ML tasks. In many scenarios, we have access to large datasets without any labels. It is therefore desirable to be able to use this data and learn how to come up with useful representations of our data and use these for various downstream tasks.

In this paper the authors propose an unsupervised learning approach to extract features from unlabeled data. They show that this method can learn useful representations for multiple modalities of data, such as audio, image and RL. 

### How?

In order to learn useful representations from unlabeled data, the proposed approach is to first compress the high dimensional inputs into a compact latent embedding space. Then an autoregressive model is used to make predictions about (distant) future in this latent space. A key element in this approach is the loss function, we don't try to directly predict the future data point (or its embedding). Instead, we train the model to be able to correctly discriminate the future embedding from a set of embeddings.

<img src="images\CPC-audio.png" alt="CPC-audio" style="zoom: 33%;" />

Lets say we have a sequence of high-dimensional data $\{x_t\}$. These can be patches in an image, consecutive segments of an audio, observations of an RL agent, etc. We have an encoder model $g_\mathrm{enc}$ that takes an $x_t$ as input and produces a latent embedding $z_t = g_\mathrm{enc}(x_t)$. We have an autoregressive model, $g_\mathrm{ar}$ (e.g., an LSTM) that takes these latent representations and produces a _context vector_ $c_t = g_\mathrm{ar}(z_t, c_{t-1})$. Ideally, we would like this context vectors to contain information about future embeddings, $x_{t+k}$. More formally, we would like to maximize the mutual information between $c_t$ and $x_{t+k}$.

**What is the loss that we are trying to minimize?** Given a set $X = \{x_1, \cdots, x_N\}$ of $N$ random samples containing one positive sample $x^+ \sim p(x_{t+k}|c_t)$ and $N-1$ negative samples $x_{j} \sim p(x_{t+k})$, we optimize 
$$
\mathcal{L}_N = -\mathbb{E}_X[\log \frac{f_k(x^+, c_t)}{\sum_{x_j\in X} f_k(x_j, c_t)}],
$$
where $f_k$ is a scoring function that outputs logits. In the paper, the authors use a simple, log-bilinear scoring function $f_k(x_j, c_t) = \exp \left( z_{j}^T W_k c_t \right)$ where $W_k$ is a different matrix for each value of $k$.

It is shown that the optimal value for $f_k(x^+, c_t)$ in this loss is proportional to $\frac{p(x_{t+k} | c_t)}{p(x_{t+k})}$, independent of $N$. It is further proved that minimizing this loss corresponds to maximizing the mutual information between $x_{t+k}$, $c_t$.

### Future work:

Midway through writing, I came across [this post](https://lilianweng.github.io/lil-log/2019/11/10/self-supervised-learning.html) by Lilian Weng, and it is so beautiful and well written that I feel like I have nothing more to add! Just read her blog!