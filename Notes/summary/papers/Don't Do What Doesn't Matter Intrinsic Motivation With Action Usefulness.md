## Don't Do What Doesn't Matter: Intrinsic Motivation With Action Usefulness

The paper can be found [here](https://arxiv.org/abs/2105.09992).

### Why?

Designing _sparse rewards_ for RL environments is often easier and better represents the task that is to be solved. However, learning from sparse rewards is much more difficult and is very sample-inefficient. To better guide the exploration of an agent in such environments, _intrinsic motivation_ methods have been proposed. Most of these methods incentivize the agent to explore new states by providing a secondary reward signal. This can be undesirable, specially in environments with large state spaces, because these methods encourage _exhaustive exploration of state space_.

In this paper a new exploration method, DoWhaM, is proposed that shifts the attention from exploring new states, to exploring new states that enable the agent to perform _rare actions_. This will hopefully put the agent in states that are more useful to explore.

### Some Context

Solutions to the problem of exploration can be categorized in two major classes:

1. **Undirected Exploration:** Introduces _stochasticity in agent's policy_ to ensure exploration. Does not use any domain knowledge. This class includes methods such as $\epsilon$-greedy, UCB, Boltzmann exploration and random walks. Require exponentially many number of steps to cover large state spaces.
2. **Directed Exploration:** Incorporates _external priors_ to guide the exploration. Provide a secondary, 'intrinsic' reward signal. This class includes count based methods, curiosity based methods and goal-based methods (which can provide a curriculum), 

### How?

There are some actions that an agent can successfully perform in certain states. Taking Mini-Grid (or BabyAI) environment as our example, an agent can perform _pick up_, _put down_, _open door_, etc when it is next to an object/door. An action is called _effective_ if performing it changes the state. The aforementioned actions are not effective most of the times. DoWhaM tries to detect these rare but effective actions and reward the agent when they are successfully performed.

For an action $a$ let $U^\mathcal{H}(a)$ be the number of times that action has been used in previous trajectories and $E^\mathcal{H}(a)$ be the number of times that action was effective(i.e, $s_{t+1} \neq s_t$). 

The ratio $\frac{E^\mathcal{H}(a)}{U^\mathcal{H}(a)}$ indicates how often the action $a$ has been effective so far. We define the bonus for an action using this ration:
$$
B(a_t) = \frac{\eta^{1 - \frac{E^\mathcal{H}(a_t)}{U^\mathcal{H}(a_t)}}-1}{\eta - 1}
$$
Here, $\eta$ is a hyperparameter. The larger it is, the more we favor rare and efficient actions.

The final DoWhaM reward is defined as
$$
r_{\text {DoWhaM}}^{i}\left(s_{t}, a_{t}, s_{t+1}\right)=\left\{\begin{array}{ll}
\frac{B\left(a_{t}\right)}{\sqrt{N^{\tau}\left(s_{t+1}\right)}} & \text { if } s_{t} \neq s_{t+1} \\
0 & \text { otherwise }
\end{array}\right.
$$
where $N^\tau (s_{t+1})$ is the number of times we have seen state $s_{t+1}$ in the _current_ episode, which can be maintained using a pseudo-count, hash function, etc. If we don't use this, the agent may repeatedly perform effective and rare actions. For instance it may just pick up and put down a box without ever moving it.

### Cons

1. **Noisy Tv problem and stochastic environments:** In these situations all actions will be deemed effective because $s_{t+1} \neq s_t$. But this change of state is because of the stochastic environment, not the agents actions. The paper suggest that using an inverse model similar to [this work](https://arxiv.org/abs/1808.04355) may alleviate this issue. This also seems similar to a signal/noise distinguishing problem.
2. **The ball pit problem:** In situations where there is a room with a lot of objects that can be interacted with, the agent may choose to just stay in that room and doesn't explore other locations.
3. **Complex, multi-step tasks:** Consider the task of opening a locked door. To do this, the agent must pick-up a key, go to a door and then perform the appropriate action to unlock the door. It may be the case that the agent first establishes that _pick up_ and _put down_ are rare and effective actions and repeatedly performs them until the ratio $\frac{E^\mathcal{H}(a)}{U^\mathcal{H}(a)}$ becomes close to 1. Now, the agent knows that unlocking a door is a rare action, but it doesn't know (and the reward signal doesn't indicate this either) that it should use a key to open it. This means that the agent must wander around aimlessly until (by chance) it happens to be next to a locked door with the appropriate key. A curriculum can be very helpful here!

### Future work:
