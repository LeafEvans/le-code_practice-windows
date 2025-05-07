import numpy as np
import torch
import torch.nn as nn
import torch.optim as optim
import gym
import matplotlib.pyplot as plt
from tqdm import tqdm


def trapezoidal_gradient(v, v_th, h, w1, w2):
    """
    梯形近似梯度函数。

    参数:
        v (float 或 np.array): 神经元膜电位。
        v_th (float): 阈值电位。
        h (float): 梯形高度。
        w1 (float): 梯形上底宽度。
        w2 (float): 梯形下底宽度。

    返回:
        np.array: 梯度值。
    """
    gradient = np.zeros_like(v)
    delta_v = np.abs(v - v_th)

    gradient[delta_v < w1] = h

    mask = (delta_v >= w1) & (delta_v < w2)
    gradient[mask] = h * (1 - (delta_v[mask] - w1) / (w2 - w1))

    return gradient


class SNNActorCritic(nn.Module):
    def __init__(
        self, state_dim, action_dim, hidden_dim=128, v_th=1.0, h=1.0, w1=0.1, w2=0.5
    ):
        super(SNNActorCritic, self).__init__()
        self.encoder = nn.Sequential(
            nn.Linear(state_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim),
            nn.ReLU(),
            nn.Linear(hidden_dim, hidden_dim // 2),
            nn.ReLU(),
        )
        self.actor_hidden = nn.Linear(hidden_dim // 2, hidden_dim // 4)
        self.critic_hidden = nn.Linear(hidden_dim // 2, hidden_dim // 4)
        self.actor = nn.Linear(hidden_dim // 4, action_dim)
        self.critic = nn.Linear(hidden_dim // 4, 1)
        self.v_th = v_th
        self.h = h
        self.w1 = w1
        self.w2 = w2

        for m in self.modules():
            if isinstance(m, nn.Linear):
                nn.init.xavier_uniform_(m.weight, gain=0.005)
                if m.bias is not None:
                    nn.init.constant_(m.bias, 0)

    def forward(self, state):
        x = self.encoder(state)
        x = nn.functional.dropout(x, p=0.2, training=self.training)

        actor_features = nn.functional.relu(self.actor_hidden(x))
        critic_features = nn.functional.relu(self.critic_hidden(x))

        action_logits = self.actor(actor_features)
        action_probs = nn.functional.softmax(action_logits / 3.0, dim=-1)
        value = self.critic(critic_features)
        return action_probs, value

    def apply_trapezoidal_gradient(self, v):
        """
        使用梯形梯度更新。
        """
        v_np = v.detach().cpu().numpy()
        gradients = trapezoidal_gradient(v_np, self.v_th, self.h, self.w1, self.w2)
        return torch.tensor(gradients, dtype=torch.float32, device=v.device)


def train_actor_critic(
    env, model, optimizer, num_episodes=200, gamma=0.99, plot_rewards=True
):
    rewards = []
    best_reward = float("-inf")
    patience = 15
    no_improve_count = 0
    epsilon = 0.5
    epsilon_min = 0.01
    epsilon_decay = 0.9

    for episode in tqdm(range(num_episodes)):
        state = env.reset()
        state = torch.tensor(state, dtype=torch.float32)
        episode_reward = 0
        done = False

        while not done:
            try:
                action_probs, value = model(state)

                if np.random.random() < epsilon:
                    action = env.action_space.sample()
                else:
                    action = torch.argmax(action_probs).item()

                next_state, reward, done, _ = env.step(action)
                next_state = torch.tensor(next_state, dtype=torch.float32)

                _, next_value = model(next_state)
                td_target = reward + (1 - done) * gamma * next_value
                td_error = td_target - value

                actor_loss = (
                    -torch.log(action_probs[action] + 1e-10) * td_error.detach()
                )
                critic_loss = td_error.pow(2)
                loss = actor_loss + critic_loss

                optimizer.zero_grad()
                loss.backward()
                optimizer.step()

                state = next_state
                episode_reward += reward

            except Exception as e:
                print(f"训练过程出现错误: {str(e)}")
                continue

        epsilon = max(epsilon_min, epsilon * epsilon_decay)
        rewards.append(episode_reward)

        if episode_reward > best_reward:
            best_reward = episode_reward
            no_improve_count = 0
        else:
            no_improve_count += 1

        if no_improve_count >= patience:
            print(f"训练在第 {episode+1} 轮提前停止")
            break

    return rewards


def compare_gradients(env, num_episodes=500):
    methods = ["rectangular", "triangular", "trapezoidal"]
    rewards_dict = {}

    for method in methods:
        print(f"\n使用 {method} 梯度近似方法训练...")
        state_dim = env.observation_space.shape[0]
        action_dim = env.action_space.n

        torch.manual_seed(42)
        np.random.seed(42)
        env.seed(42)

        model = SNNActorCritic(state_dim, action_dim)
        if method == "rectangular":
            model.w1, model.w2 = 0.0, 0.0
        elif method == "triangular":
            model.w1, model.w2 = 0.1, 0.1
        else:
            model.w1, model.w2 = 0.1, 0.5

        optimizer = optim.Adam(model.parameters(), lr=0.003, weight_decay=0.001)
        rewards = train_actor_critic(
            env, model, optimizer, num_episodes=num_episodes, plot_rewards=False
        )
        rewards_dict[method] = rewards

    plt.figure(figsize=(10, 6))
    for method, rewards in rewards_dict.items():
        rewards = np.array(rewards)
        window_size = 10
        rewards_smooth = np.convolve(
            rewards, np.ones(window_size) / window_size, mode="valid"
        )

        std_rewards = []
        for i in range(len(rewards_smooth)):
            start_idx = max(0, i - window_size)
            end_idx = min(len(rewards), i + window_size)
            std_rewards.append(np.std(rewards[start_idx:end_idx]))
        std_rewards = np.array(std_rewards)

        plt.plot(range(len(rewards_smooth)), rewards_smooth, label=f"{method} gradient")
        plt.fill_between(
            range(len(rewards_smooth)),
            rewards_smooth - std_rewards,
            rewards_smooth + std_rewards,
            alpha=0.2,
        )

    plt.xlabel("Episode")
    plt.ylabel("Reward")
    plt.title("Performance Comparison of Gradient Methods")
    plt.legend()
    plt.grid(True, alpha=0.3)
    plt.show()


if __name__ == "__main__":
    env = gym.make("CartPole-v0")
    compare_gradients(env, num_episodes=200)
