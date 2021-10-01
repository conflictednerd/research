## ELLA: Exploration Through Learned Language Abstraction

The paper can be found [here](https://arxiv.org/abs/2103.05825).

### Why?

Language-conditioned RL often involves learning tasks in _long-horizon, sparse reward_ environments. This paper proposes a _reward shaping_ method that doesn't affect the optimal policy, but encourages exploration by rewarding the agent upon completing a useful low-level instructions. This will provide the agent with a stronger feedback from the environment and will increase sample efficiency.

### How?

#### Termination Classifier

First, a low-level termination dataset is produces with the help of human annotators. This dataset contains positive and negative pairs of $(\mathrm{state}, \; \mathrm{low-level \; instruction})$. In positive pairs, $\mathrm{state}$ is a successful termination state for $\mathrm{low-level \; instruction}$. This dataset is used to train a binary classifier $h^\phi : \mathcal{S} \times \mathcal{G}_l \to \{0, 1\}$ to predict if a low-level task $g_l \in \mathcal{G}_l$ is completed in a state $s \in \mathcal{S}$ or not. In this work, low-level instructions are simple _go to_, _pick up_ and _open_ instructions.

<img src="images\ELLA3.jpg" style="zoom:50%;" />

($h^\phi$ has an architecture like the one above except that it has a binary classifier instead of the actor and the critic heads)

#### Relevance Classifier

Ella also learns a relevance classifier $f^\rho: \mathcal{G} \times \mathcal{G}_l \to \{0, 1\}$ that predicts whether a low-level instruction $g_l \in \mathcal{G}_l$ is relevant to high level task $g \in \mathcal{G}$ or not. This classifier is learned online using successful trajectories of agents and contrastive learning methods.

<img src="images\ELLA1.jpg" style="zoom:67%;" />

#### ELLA

ELLA uses the aforementioned classifiers to reshape the reward function. Basically, each time the agent completes a relevant low-level instruction, it gains a $+\lambda$ reward. The value of $\lambda$ is set such that it won't change the optimal policy.

<img src="images\ELLA2.jpg" style="zoom:60%;" />



### Future work:

1. The termination classifier uses a single observation to determine if a particular low-level instruction is completed or not. For more complex low-level instructions and in POMDPs, a single observation may not be enough (e.g, if the instruction is 'put the red ball in room 1 and the green ball in room 2' and we can't observe both rooms at the same time, then we can't know if the instruction is completed from a single observation). Alternatively, one can use an LSTM or a transformer to use all previous observations, but then the data collection becomes a bit harder...
2. We can come up with better schemes for maintaining the relevance dataset $\mathcal{D}$. The one that is proposed is not really robust to mistakes(considers the intersection). Also, it maybe better to reward subtask completions proportional to how strongly the classifier believes it is relevant. In the paper, a subtask is treated as either relative or not but we can consider a spectrum of relativity.
3. It may be better to replace the GRUs in relevance classifier with transformers. Transformers can probably generalize better to unseen situations by (for instance) learning to attend to colors in an instruction.
4. The order in which low-level instructions are executed is not considered in this work. It may be beneficial to also consider the order in which they are completed and make that influential in our reward shaping strategy.