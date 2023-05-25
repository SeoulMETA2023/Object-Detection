from lib.imageai import VideoObjectDetection
import os
import cv2

execution_path = os.getcwd()

def forFrame(frame_number, output_array, output_count):
    cv2.waitKey(1)

camera = cv2.VideoCapture(0)

detector = VideoObjectDetection()
detector.setModelTypeAsYOLOv3()
detector.setModelPath(os.path.join(execution_path , "yolov3.pt"))
detector.loadModel()

video_path = detector.detectObjectsFromVideo(camera_input=camera,
    output_file_path=os.path.join(execution_path, "camera_detected_video")
    , frames_per_second=20, log_progress=True, per_frame_function=forFrame, minimum_percentage_probability=30)

print(video_path)
