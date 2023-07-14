from ultralytics import YOLO
from PIL import Image
import cv2

model = YOLO("yolov8n.pt")
# accepts all formats - image/dir/Path/URL/video/PIL/ndarray. 0 for webcam
# from ndarray
im2 = cv2.imread("image.jpg")
results = model.predict(source=im2, save=True)  # save predictions as labels

# from list of PIL/ndarray
results = model.predict(source=[im2])