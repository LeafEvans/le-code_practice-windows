import gym
import numpy as np

env = gym.make('MountainCar-v0')
print(f'观测空间 = {env.observation_space}')
print(f'动作空间 = {env.action_space}')
print(f'观测范围 = {env.observation_space.low} ~ {env.observation_space.high}')
print(f'动作数 = {env.action_space.n}')


class SimpleAgent:
    def __init__(self, env):
        pass

    def decide(self, observation):
        position, velocity = observation
        lb = min(-0.09 * (position + 0.25)**2 + 0.03,
                 0.3 * (position + 0.9)**4 - 0.008)
        ub = -0.07 * (position + 0.38)**2 + 0.07
        if lb < velocity < ub:
            action = 2
        else:
            action = 0
        return action

    def learn(self, *args):
        pass


agent = SimpleAgent(env)


def play(env, agent, render=False, train=False):
    episode_reward = 0.  # 记录回合总奖励，初始值为0
    observation = env.reset()  # 重置游戏环境，开始新回合
    while True:  # 不断循环，直到回合结束
        if render:  # 判断是否显示
            env.render()  # 显示图形界面
        action = agent.decide(observation)
        next_observation, reward, done, _ = env.step(action)  # 执行动作
        episode_reward += reward  # 收集回合奖励
        if train:  # 判断是否训练智能体
            agent.learn(observation, action, reward, done)  # 学习
        if done:  # 回合结束，跳出循环
            break
        observation = next_observation
    return episode_reward  # 返回回合总奖励


env.seed(3)  # 设置随机种子，让结果可复现
episode_reward = play(env, agent, render=True)
print(f'回合奖励 = {episode_reward}')
env.close()  # 关闭图形界面

episode_rewards = [play(env, agent) for _ in range(100)]
print(f'平均回合奖励 = {np.mean(episode_rewards)}')
