import gym

env = gym.make("MountainCar-v0")
print(f'观测空间 = {env.observation_space}')
print(f'动作空间 = {env.action_space}')
print(f'观测范围 = {env.observation_space.low} ~ {env.observation_space.high}')
print(f'动作数 = {env.action_space.n}')
