import random
import sys
import numpy as np
import pygame
import matplotlib.pyplot as plt

# 状态定义
SUSCEPTIBLE = 0  # 易感者
INFECTED = 1  # 感染者
RECOVERED = 2  # 治愈者
EXPOSED = 3  # 潜伏者

# 感染模型参数
k = 0.85  # 上下左右感染概率
l = 0.55  # 其他感染概率
c1 = 0.4  # 变为潜伏者的概率
t1_max = 15  # 潜伏期
t_max = 50  # 感染期
T_max = 75  # 免疫期

RED = (255, 0, 0)
GREY = (127, 127, 127)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)


# 细胞类
class Cell:

    def __init__(self, ix, iy, stage):
        self.ix = ix
        self.iy = iy
        self.stage = stage  # 细胞状态
        self.s1_0 = 0  # 上下左右感染者数量
        self.s1_1 = 0  # 斜对角感染者数量
        self.T_ = 0  # 免疫时间
        self.t_ = 0  # 感染时间
        self.t1_ = 0  # 潜伏时间

    # 计算邻居感染者数量
    def calc_neighboor_count(self):
        count_0 = 0
        count_1 = 0
        pre_x = self.ix - 1 if self.ix > 0 else 0
        for i in range(pre_x, self.ix + 1 + 1):
            pre_y = self.iy - 1 if self.iy > 0 else 0
            for j in range(pre_y, self.iy + 1 + 1):
                if i == self.ix and j == self.iy:
                    continue
                if self.invalidate(i, j):
                    continue
                if (CellGrid.cells[i][j].stage == INFECTED
                        or CellGrid.cells[i][j] == EXPOSED):
                    if ((i == self.ix and j == self.iy - 1)
                            or (i == self.ix and j == self.iy + 1)
                            or (i == self.ix - 1 and j == self.iy)
                            or (i == self.ix + 1 and j == self.iy)):
                        count_0 += 1
                    self.s1_0 = count_0
                    self.s1_1 = count_1

    # 判断是否越界
    def invalidate(self, x, y):
        if x >= CellGrid.cx or y >= CellGrid.cy:
            return True
        if x < 0 or y < 0:
            return True
        return False

    # 更新细胞状态
    def next_iter(self):
        # 规则 1：易感者
        if self.stage == SUSCEPTIBLE:
            probability = random.random()

            s1_01 = self.s1_0 * k + self.s1_1 * l

            if (s1_01 > probability) and (s1_01 != 0):
                p1 = random.random()
                if p1 > c1:
                    self.stage = EXPOSED
                else:
                    self.stage = INFECTED
            else:
                self.stage = SUSCEPTIBLE
        # 规则 2：感染者
        elif self.stage == INFECTED:
            if self.t_ >= t_max:
                self.stage = RECOVERED
            else:
                self.t_ += 1
        # 规则 3：治愈者（永久免疫规则）
        elif self.stage == RECOVERED:
            if self.T_ >= T_max:
                self.stage = SUSCEPTIBLE
            else:
                self.T_ += 1
        # 规则 4：潜伏者
        elif self.stage == EXPOSED:
            if self.t1_ >= t1_max:
                self.stage = INFECTED  # 转变为感染者
            else:
                self.t1_ += 1


# 细胞网格类
class CellGrid:
    cells = []
    cx = 0
    cy = 0

    # 初始化网格
    def __init__(self, cx, cy):
        CellGrid.cx = cx
        CellGrid.cy = cy
        for i in range(cx):
            cell_list = []
            for j in range(cy):
                cell = Cell(i, j, SUSCEPTIBLE)
                if ((i == cx / 2 and j == cy / 2)
                        or (i == cx / 2 + 1 and j == cy / 2)
                        or (i == cx / 2 + 1 and j == cy / 2 + 1)):
                    cell_list.append(Cell(i, j, INFECTED))
                else:
                    cell_list.append(cell)
                CellGrid.cells.append(cell_list)

    # 更新下一次迭代的状态
    def next_iter(self):
        for cell_list in CellGrid.cells:
            for item in cell_list:
                item.next_iter()

    # 计算邻居感染者数量
    def calc_neighbour_count(self):
        for cell_list in CellGrid.cells:
            for item in cell_list:
                item.calc_neighboor_count()

    # 统计各状态细胞数量
    def num_of_nonstage(self):
        count0 = 0
        count1 = 0
        count2 = 0
        count3 = 0
        for i in range(self.cx):
            for j in range(self.cy):
                cell = self.cells[i][j].stage
                if cell == SUSCEPTIBLE:
                    count0 += 1
                elif cell == INFECTED:
                    count1 += 1
                elif cell == RECOVERED:
                    count2 += 1
                elif cell == EXPOSED:
                    count3 += 1
        return count0, count1, count2, count3


# 游戏界面类
class Game:
    screen = None
    count0 = 0
    count1 = 0
    count2 = 0
    count3 = 0

    def __init__(self, width, height, cx, cy):  # 屏幕宽高，细胞生活区域空间大小
        self.width = width
        self.height = height
        self.cx_rate = int(width / cx)
        self.cy_rate = int(height / cy)
        self.screen = pygame.display.set_mode([width, height])
        self.cells = CellGrid(cx, cy)

    # 显示生命状态
    def show_life(self):
        for cell_list in self.cells.cells:
            for item in cell_list:
                x = item.ix
                y = item.iy
                if item.stage == SUSCEPTIBLE:
                    pygame.draw.rect(
                        self.screen,
                        GREY,
                        [
                            x * self.cx_rate,
                            y * self.cy_rate,
                            self.cx_rate,
                            self.cy_rate,
                        ],
                    )
                elif item.stage == RECOVERED:
                    pygame.draw.rect(
                        self.screen,
                        GREEN,
                        [
                            x * self.cx_rate,
                            y * self.cy_rate,
                            self.cx_rate,
                            self.cy_rate,
                        ],
                    )
                elif item.stage == INFECTED:
                    pygame.draw.rect(
                        self.screen,
                        RED,
                        [
                            x * self.cx_rate,
                            y * self.cy_rate,
                            self.cx_rate,
                            self.cy_rate,
                        ],
                    )
                elif item.stage == EXPOSED:
                    pygame.draw.rect(
                        self.screen,
                        BLACK,
                        [
                            x * self.cx_rate,
                            y * self.cy_rate,
                            self.cx_rate,
                            self.cy_rate,
                        ],
                    )


# 主程序
plt.rcParams["font.sans-serif"] = ["FangSong"]
plt.rcParams["axes.unicode_minus"] = False
plt.style.use("ggplot")

if __name__ == "__main__":
    count0_ = []
    count1_ = []
    count2_ = []
    count3_ = []
    pygame.init()
    pygame.display.set_caption("传染病模型")
    game = Game(800, 800, 200, 200)
    clock = pygame.time.Clock()
    k1 = 0
    while True:
        k1 += 1
        print(k1)

        clock.tick(100)
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                sys.exit()
        game.cells.calc_neighbour_count()
        count0, count1, count2, count3 = game.cells.num_of_nonstage()
        count0_.append(count0)
        count1_.append(count1)
        count2_.append(count2)
        count3_.append(count3)
        if count2 > 200 * 190:
            break

        plt.plot(count0_, label="易感者")
        plt.plot(count3_, label="潜伏者")
        plt.plot(count1_, label="感染者")
        plt.plot(count2_, label="治愈者")
        plt.legend()
        plt.xlabel("时间单位")
        plt.ylabel("人数单位")
        plt.pause(0.1)
        plt.clf()

        game.show_life()
        pygame.display.flip()
        game.cells.next_iter()

    plt.show()
