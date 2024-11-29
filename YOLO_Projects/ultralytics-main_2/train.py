from ultralytics import YOLO

# 加载模型
model = YOLO('yolov8n.pt')

# 训练模型
model.train(data='yolov8.yaml', workers=1, epochs=25, batch=16)