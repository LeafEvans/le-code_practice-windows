import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision
import torchvision.transforms as transforms
import numpy as np
import matplotlib.pyplot as plt

# 设置中文字体
plt.rcParams['font.sans-serif'] = ['SimHei']
plt.rcParams['axes.unicode_minus'] = False


class SpikingNeuralNetwork(nn.Module):
    """
    脉冲神经网络模型
    """

    def __init__(self,
                 input_size=784,
                 hidden_size=256,
                 output_size=10,
                 threshold=0.5,
                 decay=0.2):
        super(SpikingNeuralNetwork, self).__init__()
        self.fc1 = nn.Linear(input_size, hidden_size)
        self.fc2 = nn.Linear(hidden_size, output_size)
        self.threshold = threshold  # 神经元发放阈值
        self.decay = decay  # 膜电位衰减系数
        self.mem = None  # 膜电位
        self.spike = None  # 脉冲

    def forward(self, x, time_steps=100):
        batch_size = x.size(0)
        self.mem = torch.zeros(batch_size, self.fc2.out_features)
        self.spike = torch.zeros(batch_size, self.fc2.out_features)

        # 时间步仿真
        for t in range(time_steps):
            x = self.fc1(x)
            x = F.relu(x)
            x = self.fc2(x)

            # 更新膜电位和产生脉冲
            self.mem = self.mem * self.decay + x
            spike = (self.mem >= self.threshold).float()
            self.mem = self.mem * (1 - spike)  # 重置膜电位
            self.spike = self.spike + spike

        return self.spike / time_steps


def load_mnist_data():
    """加载MNIST数据集"""
    transform = transforms.Compose(
        [transforms.ToTensor(),
         transforms.Normalize((0.1307, ), (0.3081, ))])

    train_dataset = torchvision.datasets.MNIST(root='./data',
                                               train=True,
                                               download=True,
                                               transform=transform)

    test_dataset = torchvision.datasets.MNIST(root='./data',
                                              train=False,
                                              transform=transform)

    return train_dataset, test_dataset


def visualize_results(model, test_loader):
    """可视化模型识别结果"""
    model.eval()
    fig, axes = plt.subplots(2, 5, figsize=(12, 6))
    axes = axes.ravel()

    with torch.no_grad():
        for idx, (data, target) in enumerate(test_loader):
            if idx >= 10:
                break

            output = model(data)
            pred = output.argmax(dim=1)

            # 显示图像和预测结果
            axes[idx].imshow(data[0][0], cmap='gray')
            axes[idx].set_title(f'预测: {pred.item()}\n实际: {target.item()}')
            axes[idx].axis('off')

    plt.tight_layout()
    plt.show()


# 主程序
def main():
    # 加载数据
    train_dataset, test_dataset = load_mnist_data()
    train_loader = torch.utils.data.DataLoader(train_dataset,
                                               batch_size=64,
                                               shuffle=True)
    test_loader = torch.utils.data.DataLoader(test_dataset,
                                              batch_size=1,
                                              shuffle=True)

    # 创建模型
    model = SpikingNeuralNetwork()
    criterion = nn.MSELoss()
    optimizer = torch.optim.Adam(model.parameters(), lr=0.001)

    # 训练模型
    print("开始训练SNN模型...")
    model.train()
    for epoch in range(5):
        for batch_idx, (data, target) in enumerate(train_loader):
            optimizer.zero_grad()
            output = model(data.view(-1, 784))
            target_one_hot = F.one_hot(target, 10).float()
            loss = criterion(output, target_one_hot)
            loss.backward()
            optimizer.step()

            if batch_idx % 100 == 0:
                print(f'训练轮次: {epoch}, 批次: {batch_idx}, 损失: {loss.item():.6f}')

    # 可视化结果
    visualize_results(model, test_loader)


if __name__ == "__main__":
    main()
