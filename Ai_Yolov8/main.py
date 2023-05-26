import cv2
from ultralytics import YOLO
import numpy as np

import torch

cap = cv2.VideoCapture(0)

model = YOLO("yolov8n.pt")

w = round(cap.get(cv2.CAP_PROP_FRAME_WIDTH))
h = round(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv2.CAP_PROP_FPS)

fourcc = cv2.VideoWriter_fourcc(*'DIVX')
delay = round(1000/fps)

out = cv2.VideoWriter('output.mp4', fourcc, fps, (w, h))

while True:
    ret, frame = cap.read()
    if not ret:
        break

    results = model(frame, device = "mps")
    result = results[0]
    annotated_frame = results[0].plot()
    bboxes = np.array(result.boxes.xyxy.cpu(), dtype="int")
    classes = np.array(result.boxes.cls.cpu(), dtype="int")
    for cls, bbox in zip(classes, bboxes):
        (x, y, x2, y2) = bbox
        print(bbox)

    cv2.imshow("Img", annotated_frame)
    #out.write(annotated_frame)
    if cv2.waitKey(1) == 27:
        break


cap.release()
cv2.destroyAllWindows()
