import cv2
import numpy as np

def generate_snow_overlay(image, num_flakes=500):
    h, w, _ = image.shape

    # 创建空白图层
    snow_layer = np.zeros((h, w, 3), dtype=np.uint8)

    # 随机生成雪花位置和大小
    for _ in range(num_flakes):
        x = np.random.randint(0, w)
        y = np.random.randint(0, h)
        radius = np.random.randint(2, 5)
        cv2.circle(snow_layer, (x, y), radius, (255, 255, 255), -1)

    # 添加运动模糊模拟飘落
    kernel = np.zeros((15, 15), dtype=np.float32)
    kernel[:, 7] = np.linspace(0.1, 1, 15)
    snow_layer = cv2.filter2D(snow_layer, -1, kernel)

    # 混合图像
    snowy_image = cv2.addWeighted(image, 0.8, snow_layer, 0.2, 0)
    return snowy_image

img = cv2.imread("C:\\Users\\31866\\Pictures\\下载图片\\头像-9.jpeg")
snowy_img = generate_snow_overlay(img)
cv2.imwrite("snowy_output.jpg", snowy_img)

