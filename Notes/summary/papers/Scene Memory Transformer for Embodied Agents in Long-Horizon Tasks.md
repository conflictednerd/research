## Scene Memory Transformer for Embodied Agents in Long-Horizon Tasks

The paper can be found [here](https://arxiv.org/abs/1903.03878).

### Why?

When applying RL to POMDPs a major challenge arises when we want to condition the policy on past observations. This is conventionally done using LSTMs and other RNN architectures. However, they suffer from two major drawbacks:

1. Training RNN's with backprop through time is not easy and suffers from exploding and vanishing gradients.
2. They have limited capacity because they have to encode all the relevant information from previous timesteps in a fixed-size state vector.

This paper proposes to replace RNNs with transformers.

### How?

The proposed architecture, SMT, stores (an encoded version of) all past observations in a large memory $M$. Then at every time step $t$ when we face a new observation $o_t$, we first apply self attention to all previous observations in $M$ to get an encoded version of them. Then, a transformers decoder will attend to the encoded history, based on the current observation $o_t$.

<img src="images\SMT1.jpg" style="zoom:40%;" />



The encoder part of transformer will require a time complexity of $\mathcal{O}(|M|^2)$. This is quadratic in the length of episodes and is undesirable. To mitigate this, the authors propose a factorization method that uses a (constant length) subset of $M$, named $\tilde{M}$, to attend to $M$ instead of doing the complete self-attention. This will reduce the computational cost to $\mathcal{O}(|M||\tilde{M}|)$ which is linear in $M$.

<img src="images\SMT2.jpg" style="zoom:50%;" />

