from ultralytics import YOLO

# 加载模型并设置任务类型为检测
yolo = YOLO("./yolov8n.pt", task='detect')

# 执行预测
result = yolo(source='./ultralytics/assets/group.jpg', save=True, conf=0.05)
