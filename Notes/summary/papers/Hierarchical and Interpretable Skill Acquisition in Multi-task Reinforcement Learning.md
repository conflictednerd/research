## Hierarchical and Interpretable Skill Acquisition in Multi-task Reinforcement Learning

### Why?

The goal of this paper is to train policies that can:

1. execute complex tasks
2. have an interpretable description of their behavior in natural language

### How?

The way to achieve these goal is by training a hierarchy of policies $\pi_1, \pi_2, \cdots, \pi_n$ such that higher level policies build up on lower level ones and are able to perform more sophisticated tasks.

A policy $\pi_n(a|s, g)$ is conditioned on a goal, expressed in natural language, that it tries to achieve.

The interesting idea here, is that higher level policies extend their action space by including lower level policies. If we denote the action space of $\pi_{n-1}$ by $\mathcal{A}_{n-1}$​, then 
$$
\mathcal{A}_{n} = \mathcal{A}_{n-1} \cup \{\pi_{n-1}(g) | g \in \mathcal{G}_{n-1}\},
$$
where $\mathcal{G}_{n-1}$ is the set of goals that $\pi_{n-1}$ is trained for and can accomplish.

Basically, given a goal $g$​, the policy $\pi_n$​ tries to achieve this goal (i.e. maximize cumulative reward) by performing a sequence of actions. At each time $t$​, $\pi_n$​ can either *select a low level action* (that is, from $\mathcal{A}_1$​) or it can generate a goal $g'$ and *ask $\pi_{n-1}$ to accomplish that goal*.

### Cons:

+ The set of goal at each step, $\mathcal{A}_n$, is heavily structured and prespecified by humans.
+ The policies do not use the linguistic relations that are present in NL goals and only use NL as a mean to merely condition a policy on. Intuitively, if we know how to execute *'pick-up blue'* then we should be able to quickly adopt and learn to perform *'put-down red'*, even when we have not seen read previously. However, it seems to me that in order to learn *'put-down red'*, we must again start from $\pi_1$ and build up a skillset required for this task. Hence, I suspect that this model will have **poor generalization to new, novel tasks at test time**. Even more, it **may not exhibit any significant speed-up in training for new tasks when the wording of the goal is changed a little bit**, without changing the overall meaning that much. For instance, if we have never seen the color *'red'* in our pre-training phase, learning to *'pick-up red'* will not use any of the skills that the agent has learned so far, and our pre-training will not be helpful even though this task is very similar to what agent has learned in its pre-training.

### Pros:

+ If the set of goals is chosen carefully and is representative of all possible tasks at test time, this approach can be thought of as a form of curriculum learning that can speed up the training process for learning complex tasks that require multiple steps to complete.
+ The paper uses a *stochastic temporal grammar* (STG) to encode and learn the temporal relation between sub-tasks that a high-level policy can call. For instance, it is usually the case that we want to *'find red'* before *'pick-up red'*.