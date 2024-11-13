from ultralytics import YOLO

# Load a model
model = YOLO('yolov8n.pt')

# Train the model
model.train(data='yolov8-fog.yaml', workers=0, epochs=30, batch=16)
