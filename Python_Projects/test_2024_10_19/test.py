from graphviz import Digraph

# 创建一个有向图
dot = Digraph(comment='Policy Iteration Process')

# 添加节点
dot.node('A', '初始化策略 π_0')
dot.node('B', '策略评估: 计算 V^π')
dot.node('C', '策略改进: 更新 π')
dot.node('D', 'π 是否收敛?')
dot.node('E', '输出最优策略 π*')

# 添加边
dot.edges(['AB', 'BC', 'CD'])
dot.edge('D', 'B', label='否')
dot.edge('D', 'E', label='是')

# 保存并渲染图像
dot.render('policy_iteration_process', format='png', cleanup=True)
