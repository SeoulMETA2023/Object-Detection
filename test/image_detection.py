from imageai.Detection import ObjectDetection
from PIL import Image
import cv2

cap = cv2.VideoCapture(0)

while cv2.waitKey(100) < 0:
    _, cv2_img = cap.read()

    pil_img = Image.fromarray(cv2.cvtColor(cv2_img, cv2.COLOR_BGR2RGB))

    detector = ObjectDetection()
    detector.setModelTypeAsYOLOv3()
    detector.setModelPath("yolov3.pt")
    detector.loadModel()
    detections = detector.detectObjectsFromImage(input_image=pil_img, output_type="array", output_image_path="result.jpg")

    out_image = detections[0]
    detection_objs = detections[1]

    # for detection_obj in detection_objs:
    #     print(detection_obj["name"] , " : " , detection_obj["percentage_probability"] )

    cv2.imshow('PC_camera', out_image)

cap.release()
cv2.destroyAllWindows()