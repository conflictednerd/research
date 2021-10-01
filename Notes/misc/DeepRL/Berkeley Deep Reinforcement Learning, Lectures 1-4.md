# Berkeley Deep Reinforcement Learning, Lectures 1-4

### Some Notations

$s_t$ : state of the system at time $t$

$o_t$: observation at time $t$

$a_t$: agents action at time $t$

$\pi_\theta (a_t|o_t)$: policy (distribution over actions) parametrized by $\theta$ based on observations at time $t$.

$\pi_\theta (a_t|s_t)$: policy (distribution over actions) parametrized by $\theta$ based on (fully observed Markovian) state at time $t$.



States $s_t$ satisfy the Markov property, that is, $p(s_{t+1}|s_t, a_t)$ is independent of any previous state, $s_{t-1}$.

Observations may contain enough information about the state or not. In general, however, they do not satisfy the Markov property. The relation between these variables is shown in the graphical model below:

<img src="images\mdp_graphical_model.png" alt="MDP graphical model" style="zoom:67%;" />

### Imitation Learning (Behavioral Cloning):

A supervised learning approach to solving the RL problem.

The policy $\pi_\theta (a_t|o_t)$ is directly modeled via a function approximator. In essence, imagine $\pi_\theta$ as a neural network that takes $o_t$ as input and outputs a distribution over possible actions.

Assuming we have access to expert demonstrations, that is, optimal $(o_t, a_t)$ pairs, we can learn to imitate the expert by training $\pi_\theta$ to predict the correct label $a_t$ for each observations, similar to a typical supervised image labeling task.

##### Cons:

1. If we have a trajectory of actions by an expert in the form of $o_1, a_1, o_2, a_2, \cdots, o_n, a_n$, we can't directly use these observation-action pairs to train the network. Why? Because they are not independent of each other (remember, supervised learning requires i.i.d samples). Possible solutions? Experience replay buffer.

2. Every learned model makes some small mistakes. With each mistake, the behavioral cloning policy $\pi_\theta$ diverges a little from expert trajectories that it was trained on, and finds itself in novel situations that has never seen before. This will lead to larger and larger mistakes. The longer the trajectory produced by $\pi_\theta$ becomes, the more likely it is for it to diverge from that of an expert. Possible solutions? Teach the model to correct small mistakes. For instance, teach a self-driving car to return to its original course if it is slightly tilted. Do this by providing $(o_t, a_t)$ samples where $o_t$ is slightly tilted to one side and $a_t$ corrects it.

### DAgger (Dataset Aggregation):

The second problem in behavioral cloning arises because if $\pi_\theta$ is not perfect, then **training distribution $p_{data}(o_t)$ is different from test distribution $p_{\pi_\theta} (o_t)$**. 

DAgger addresses this issue by providing training data from $p_{\pi_\theta} (o_t)$​. This is done by collecting observations by running $\pi_\theta$​ and asking the expert to annotate those.

1. Train $\pi_\theta$ using human data $\mathcal{D} = \{o_1, a_1, \cdots, o_N, a_N\}$​
2. Run $\pi_\theta$ to get dataset $\mathcal{D}_\pi = \{o_1, \cdots, o_M\}$
3. Label $\mathcal{D}_\pi$ with actions $a_t$
4. Aggregate $\mathcal{D} = \mathcal{D} \cup \mathcal{D}_\pi$
5. Repeat

**Question:** DAgger is designed to solve the problem of distributional shift. But can it also solve the causal confusion problem, where the agent misidentifies cause and effect? (see [Causal confusion in imitation learning](https://arxiv.org/abs/1905.11979?context=stat.ML))

**Answer:** I think it can, but it requires a lot of training data for that.

**Idea:** Can we use some kind of attention model that discards extra information in the observation to combat the causal confusion problem?

### Multi-Modal Behavior:

If the expert policy is a continuous multi-modal distribution (as is the case for most human experts), we can not use a simple distribution to model its behavior. Thus, $\pi_\theta$ must be able to model a large family of multi-modal distributions. We have three options here:

1. **Mixture of Gaussians:** One simple solution is to let $\pi_\theta$'s output be the mean and covariances of $N$ Gaussians alongside their respective weights. This way, the policy is modeled as $\pi (a|o) = \sum_{i} w_i \mathcal{N}(\mu_i, \Sigma_i)$.

2. **Latent Variable Models:** Another approach is to use a latent variable model. Essentially, we learn a policy $\pi_\theta (a|o, \varepsilon)$​ which outputs the mean and variance of a simple normal distribution, with the caveat that *it has an additional input $\varepsilon$​*. This is a vector of latent variables which comes from a prior distribution such as $\mathcal{N}(0, \mathbf{I})$​. Training these models is usually hard.

3. **Autoregressive Discretization:** Notice that if our action space is discrete, modeling the multi modal behavior is not an issue. Hence discretizing our action space is a possible solution. The problem with this approach is that *discretizing high dimensional action spaces requires exponentially many categories*. Autoregressive discretization, solves this problem by discretizing one dimension at a time. The way it works is by consecutively sampling from each dimension of the action space. 

   <img src="images\autoregressive_discretization.png" alt="autoregressive_discretization" style="zoom: 50%;" />

   **Question:** How does backprop work in this setting? Do we compute the gradient for each dimension separately, assuming other dimensions are fixed?

   

### Trajectories and Rewards:

If we don't want to just copy the policy of an expert, we need an alternative way of encoding our objective. This is done using the notion of *rewards* which provide a supervisory signal using which we can choose 'good' actions.

Starting from an initial state $s_1$ and following a parametrizes policy $\pi_\theta$, we get a sequence of states and actions $s_1, a_1, \cdots, s_T, a_T$. We call this sequence a *trajectory* and denote it by $\tau$.

We can define a distribution over trajectories as:
$$
p_\theta (s_1, a_1, \cdots, s_T, a_T) = p_\theta(\tau) = p(s_1)\prod_{t=1}^{T} \pi_\theta(a_t|s_t)p(s_{t+1} |s_t, a_t)
$$
Here, $p(s_{t+1} | s_t, a_t)$ is the transition probability of our MDP which we know is (conditionally) independent of previous states and actions.

Now that we have defined a distribution over trajectories, we can define the goal of reinforcement learning as follows:
$$
\theta^\star = \operatorname{argmax}_\theta \mathbb{E}_{\tau \sim p_\theta(\tau)}\left[\sum_{t} r(s_t, a_t) \right],
$$
where $r(s_t, a_t)$ is our (expected) reward function.

Basically, we want to choose a policy following which will produce trajectories with large sum of rewards.

Notice the difference between this, and the behavioral cloning objective, where there is no reward and we are trying to directly model the experts policy given observations:
$$
\theta^\star = \operatorname{argmax}_\theta \mathbb{E}_{s \sim p_\mathrm{expert}}\left[ \log {p(\pi_\theta(a_\mathrm{expert}|s))} \right]
$$

### RL and Stochastic Optimization:

Reinforcement learning is mostly about optimizing expectations. One very important observation is that *expectations can be continuous in the parameters of the corresponding distribution, even though the function we are taking expectation of, may itself be discontinuous*.

For instance, the reward function $r(s, a)$ may be non-smooth. But if $\pi_\theta(a|s)$ is smooth in $\theta$, then $\mathbb{E}_{\pi_\theta}[r(s, a)]$ is also smooth in $\theta$.

### Value and Action-Value Function:

The value function $V^\pi:\mathcal{S} \to \mathbb{R}$ is the expected total reward by following policy $\pi$ assuming we start in an initial state $s$. More formally,
$$
V^\pi (s_t) = \sum_{t'=t}^{T} \mathbb{E}_{\pi_\theta}\left[r(s_{t'}, a_{t'}) | s_t \right]
$$
The action-value function $Q^\pi : \mathcal{S}\times \mathcal{A} \to \R$ is the expected total reward by following policy $\pi$ assuming we start in an initial state $s$ and perform an action $a$. More formally, 
$$
Q^\pi (s_t, a_t) = \sum_{t'=t}^{T} \mathbb{E}_{\pi_\theta}[r(s_{t'}, a_{t'}) | s_t, a_t]
$$
