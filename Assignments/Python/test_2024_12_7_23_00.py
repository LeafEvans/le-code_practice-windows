n, m, q = map(int, input().split())
# 初始化每个作品的票数为0
votes = dict.fromkeys(range(1, m + 1), 0)
# 初始化每个投票者的投票意愿为0
voters_will = [0] * n


def event_1(left, right, x):
    # 更新指定范围内投票者的投票意愿，并调整票数
    count = 0
    for i in range(left - 1, right):
        if voters_will[i] > 0:
            votes[voters_will[i]] -= 1
        voters_will[i] = x
        count += 1
    votes[x] = votes.get(x, 0) + count
 

def event_2(x, w):
    # 处理作品 x 退出竞选，将支持者的投票意愿改为 w，并更新票数
    count = votes.get(x, 0)
    if count > 0:
        for i in range(len(voters_will)):
            if voters_will[i] == x:
                voters_will[i] = w
        votes[w] = votes.get(w, 0) + count
    # 将作品 x 的票数设置为 0，而不是删除
    votes[x] = 0


def event_3(x, y):
    # 交换支持作品 x 和 y 的投票者的投票意愿，并调整票数
    count_x_to_y = 0
    count_y_to_x = 0
    for i in range(len(voters_will)):
        if voters_will[i] == x:
            voters_will[i] = y
            count_x_to_y += 1
        elif voters_will[i] == y:
            voters_will[i] = x
            count_y_to_x += 1
    votes[y] = votes.get(y, 0) + count_x_to_y
    votes[x] = votes.get(x, 0) + count_y_to_x - count_x_to_y


def event_4(w):
    # 统计支持作品 w 的投票者数量，如果 w 的票数为 0，返回作品 0 的票数
    count = votes.get(w, votes.get(0, 0))
    print(count)


def event_5():
    # 找到票数最多的作品编号
    max_votes = max(votes.values())  # 找到最高票数

    # 筛选出所有票数等于最高票数的作品编号
    candidates = [work for work, vote in votes.items() if vote == max_votes]

    # 从候选作品中选择编号最小的一个
    winner = min(candidates, default=0)

    # 打印赢家作品编号
    print(winner)


def main():
    # 处理每个事件，根据事件类型调用相应的函数
    for _ in range(q):
        event = list(map(int, input().split()))
        op = event[0]
        if op == 1:
            event_1(event[1], event[2], event[3])
        elif op == 2:
            event_2(event[1], event[2])
        elif op == 3:
            event_3(event[1], event[2])
        elif op == 4:
            event_4(event[1])
        elif op == 5:
            event_5()


if __name__ == "__main__":
    main()
