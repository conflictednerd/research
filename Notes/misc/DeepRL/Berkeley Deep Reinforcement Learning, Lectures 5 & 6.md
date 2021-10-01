# Berkeley Deep Reinforcement Learning, Lectures 5, 6, 7

## Policy Gradients:

### RL Objective:

Remember that we defined the goal of reinforcement learning as finding the optimal (parametrized) policy:
$$
\theta ^\star = \operatorname{argmax}_\theta \mathbb{E}_{\tau \sim p_\theta(\tau)}\left[ \sum_{t} r(s_t, a_t) \right] = \operatorname{argmax}_\theta J(\theta)
$$
For any policy $\pi_\theta$, we can assign a value $J(\theta)$ to it. For brevity of notation, let $r(\tau) = \sum_t r(s_t, a_t)$. Thus, we have
$$
J(\theta) = \mathbb{E}_{\tau \sim p_\theta(\tau)} \left[r(\tau) \right] = \int p_\theta(\tau)r(\tau)\dd \tau
$$
In order to compute the maximum of $J(\theta)$​ with gradient descent, we need its gradient. Due to linearity of the gradient operator, we can write
$$
\grad_\theta J(\theta) = \int \grad_\theta p_\theta (\tau)r(\tau)\dd \tau
$$
Also, we have the identity below
$$
\grad_\theta p_\theta(\tau) = p_\theta(\tau) \frac{\grad_\theta p_\theta (\tau)}{p_\theta(\tau)} = p_\theta(\tau) \grad_\theta \log p_\theta(\tau)
$$
Using this, we can rewrite the gradient of $J(\theta)$ as
$$
\grad_\theta J(\theta) = \int {p_\theta(\tau) \grad_\theta {\log p_\theta(\tau)} r(\tau) \dd \tau} = \mathbb{E}_{\tau \sim p_\theta(\tau)} \left[\grad_\theta \log {p_\theta(\tau)} r(\tau)\right]
$$
This suggest we are on the right track, because we can estimate the gradient by sampling trajectories $\tau$​. However, we are not done yet! Evaluating $\grad_\theta \log p_\theta(\tau)$​ requires knowing the environment dynamics and state transition distributions. Let us examine this quantity more closely. We know that
$$
p_\theta (\tau) = p(s_1)\prod_{t = 1}^{T} {\pi_\theta(a_t|s_t)p(s_{t+1} | s_t, a_t)}.
$$
Taking the logarithm from both sides we get
$$
\log p_\theta(\tau) = \log {p(s_1)} + \sum_{t=1}^{T} {\log \pi_\theta(a_t|s_t) + p(s_{t+1}|s_t, a_t)}.
$$
Now if we take the gradient of the above formula with respect to $\theta$, all state transition probabilities are independent of $\theta$ and will be omitted after taking the gradient:
$$
\grad_\theta \log p_\theta(\tau) = \sum_{t = 1}^{T} {\grad_\theta \log \pi_\theta (a_t|s_t)}
$$
And notice that this sum is now computable because we can evaluate the gradient of our policy with respect to its parameters.

Putting it all together, we obtain the following formula for the gradient of RL objective with respect to the parameters of our policy:
$$
\grad_\theta J(\theta) = \mathbb{E}_{\tau \sim p_\theta(\tau)} \left[ \left(\sum_{t = 1}^{T} {\grad_\theta \log \pi_\theta (a_t|s_t)}\right) \left( \sum_{t=1}^T {r(s_t, a_t)} \right) \right]
$$
We can estimate this gradient by rolling our policy to obtain a number of trajectories $\tau_i$, and estimate the expectation with sample mean:
$$
\grad_\theta J(\theta) \simeq \frac{1}{N}\sum_i {\left[ \left(\sum_t{\grad_\theta \log {\pi_\theta(a_{i,t}|s_{i,t})}}\right)  \left(\sum_t {r(s_{i,t}, a_{i,t})}\right)\right]}
$$
Intuitively, by updating our policy using $\theta \leftarrow \theta + \alpha\grad_\theta J(\theta)$, we are basically *increasing the (log) probability of trajectories with high rewards and decreasing those with low rewards.*

#### Reducing the variance: Causality

First, rewrite the estimate of $\grad_\theta J(\theta)$ that we obtained above by distributing one of the sums:
$$
\grad_\theta J(\theta) \simeq \frac{1}{N} \sum_{i=1}^{N} \sum_{t=1}^{T} {\grad_\theta \log \pi_\theta (a_{i, t} |s_{i, t}) \left( \sum_{t' = 1}^{T}{r(s_{i, t'}, a_{i, t'})} \right)}
$$
But notice that in this formula, *we are changing the log probability of an action based on rewards that we obtained in the whole trajectory*($t' = 1,\cdots, T$). Due to the principle of causality, our actions at time $t$ do not have an effect on the reward we observed at some time $t' < t$. And in fact, one can prove that those rewards contributions will be zero in expectation. Thus, if we remove these terms, we get a better estimator of the gradient that is still unbiased, but has much lower variance. This estimator can be written as:
$$
\grad_\theta J(\theta) \simeq \frac{1}{N} \sum_{i=1}^{N} \sum_{t=1}^{T} {\grad_\theta \log \pi_\theta (a_{i, t} |s_{i, t}) \left( \sum_{t' = t}^{T}{r(s_{i, t'}, a_{i, t'})} \right)}
$$
Also notice that the sum of rewards from time $t$ onwards, or the reward-to-go, is basically **an estimate of action-value function for the state and action at time $t$ in trajectory $i$**​!! Thus, if we denote this naïve estimate of action value by $\hat{Q}_{i, t}$, we can further simplify our notation and write
$$
\grad_\theta J(\theta) \simeq \frac{1}{N} \sum_{i=1}^{N} \sum_{t=1}^{T} {\grad_\theta \log \pi_\theta (a_{i, t} |s_{i, t}) \hat{Q}_{i, t}}
$$
Replacing this naïve estimate of action-values with a better one will be discussed later.

#### Baselines

Adding a constant to the total reward in the formula for the estimate of policy gradient is known as *using a baseline*. More formally, we rewrite the equation for the gradient as
$$
\grad_\theta J(\theta) \simeq \frac{1}{N} \sum_{i}^{N} \grad_\theta \log p_\theta(\tau_i) [r(\tau_i) - b],
$$
Where $b$ is a constant known as the baseline. 

It can be shown that **adding a baseline does not change the expected value of gradients estimator(so it remains unbiased) but it can change its variance.**

A popular choice for baseline is the average reward, $b = \frac{1}{N} \sum_i r(\tau_i)$.

The optimal baseline can be derived by solving $\frac{ \dd{} \mathrm{Var} }{\dd{} b} = 0$, where $\mathrm{Var} = \mathbb{E}_{\tau\sim p_\theta(\tau)} [(\grad_\theta \log p_\theta(\tau)(r(\tau) - b))^2] - \mathbb{E}_{\tau\sim p_\theta(\tau)} [\grad_\theta \log p_\theta(\tau)(r(\tau) - b)]^2$ is the variance of gradients estimator. Solving this equation will give us the optimal baseline which is
$$
b^\star = \frac{\mathbb{E}[g(\tau)^2r(\tau)]}{\mathbb{E}[g(\tau)^2]},
$$
where $g(\tau) = \grad_\theta \log p_\theta(\tau)$.

#### Off-Policy via importance sampling

#### Actor Critic Algorithms

The critic (estimator of state values) can have help the actor (policy gradient) in two ways. First, it can *replace the Monte Carlo estimate of reward-to-go(action value) with a temporal difference (TD) estimate* which will have much less variance, but at the expense of some bias due to bootstrapping the estimator. Second, it can help *provide a state-dependent baseline* which is an estimate of value function. We know that state-dependent baselines do not create a biased policy gradient estimator, but they can help in lowering the variance. 

Two options for *discounting* policy gradient using Monte Carlo estimates:

**Option 1:** 
$$
\grad_\theta J(\theta) \approx \frac{1}{N} \sum_{i=1}^{N} \sum_{t=1}^{T} {\grad_\theta\log \pi_\theta(a_{i, t}|s_{i, t}) \left( \sum_{t'=t}^{T} \gamma^{t'-t} r(s_{i, t'}, a_{i, t'}) \right)}
$$
**Option 2:**
$$
\grad_\theta J(\theta) \approx \frac{1}{N} \sum_{i=1}^{N} \sum_{t=1}^{T} {\gamma^{t-1}\grad_\theta \log \pi_\theta(a_{i, t}|s_{i, t})) \left( \sum_{t'=t}^{T} \gamma^{t'-t} r(s_{i, t'}, a_{i, t'}) \right)}
$$
The first option is similar to actors estimate of loss when we use a critic:
$$
\grad_\theta J(\theta) \approx \frac{1}{N} \sum_{i=1}^{N} \sum_{t=1}^{T} {\grad_\theta\log \pi_\theta(a_{i, t}|s_{i, t}) \left( r(s_{i, t}, a_{i, t}) + \gamma \hat{V}_\phi^\pi(s_{i, t+1}) - \hat{V}_\phi^\pi(s_{i, t}) \right)}
$$
Basically, option 1 and critic are *time agnostic*, meaning that they do not care when we enter an state and calculate the gradient for actions taken in that state regardless of their place in the trajectory.

Option 2 however is not time agnostic. It puts less weights on actions that were taken further in the trajectory. This way, *actions and rewards that are seen sooner are more impactful in calculating the gradient*.



#### Value Iteration

The full fitted value iteration algorithm is as follows:

1. Dataset $\{s_i, a_i, s_i', r_i\}$ is generated on the fly​ by running policy $\pi_\phi$​
2. Set $y_i \leftarrow r_i + \gamma \max_{a_i} (r(s_i, a_i) + \mathbb{E}[V_\phi(s_i')])$​
3. Update the parameters of V network with $\phi \leftarrow \operatorname{argmax}_\phi \frac{1}{2}\sum_i (y_i - V_\phi(s_i))^2$

#### Q Iteration

The full fitted Q iteration algorithm is as follows:

1. Collect dataset $\{s_i, a_i, s_i', r_i\}$ using some policy
2. Set $y_i \leftarrow r_i + \gamma \max_{a'}Q_\phi(s_i', a_i')$
3. Update parameters of Q network with $\phi \leftarrow \operatorname{argmax}_\phi \frac{1}{2}\sum_i {(y_i - Q_\phi(s_i, a_i))^2}$​

Fitted Q iteration is *off policy*, meaning that generated samples can be from any arbitrary policy.

**Question:** Why is it off policy?

**Answer:** Notice that we do not explicitly represent the policy. Rather, our policy is obtained by taking a maximum over our Q values. The only place where we need to use this implicit policy, is at step 2, where we want to find the future value if we follow this policy from state $s_i'$​​​. But this does not need any roll out of the policy to see what state we will end up in(unlike value iteration). **In short, $Q_\phi(s_i, a_i)$​​​ is the value we expect to get by doing action $a_i$​​​ at state $s_i$​​​ and following the policy $\pi_\phi$​​ ever after. Hence, we get to change our policy only *after* we reach the next state, $s_i'$​​. Therefor, we don't need to see the effect of our policies actions on the environment to update (and improve) $Q_\phi(s_i, a_i)$​​.** This is in contrast to value iteration where we must simulate the environment after taking different actions $a_i$​ to see state $s_i'$​ and estimate $V_\phi(s_i')$​. (Pay attention to backup diagrams!)



TEMP:

Lecture 8 p.4 at the end, it asks about Q-learning with n-step returns and how we can make it off policy. To do so, we must learn $Q^\pi_n(s_1,a_1,\cdots, s_n, a_n) = r(s_1, a_1) + \gamma r(s_2, a_2) + \cdots + \gamma^{n-1} r(s_n, a_n) + \gamma^n \mathbb{E}_{s'\sim p(s_n,a_n), a'\sim \pi}[Q^\pi(s', a')]$.