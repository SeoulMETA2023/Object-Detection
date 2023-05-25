from lib.imageai import VideoObjectDetection #자체적인 수정 파일.
import os
import cv2

execution_path = os.getcwd()


def forFrame(frame_number, output_array, output_count, returned_frame):
    cv2.waitKey(1)


video_detector = VideoObjectDetection()
video_detector.setModelTypeAsYOLOv3()
video_detector.setModelPath(os.path.join(execution_path, "yolov3.pt"))
video_detector.loadModel()

video_detector.detectObjectsFromVideo(input_file_path=os.path.join(execution_path, "traffic.mp4"), output_file_path=os.path.join(execution_path, "video_frame_analysis") ,  frames_per_second=20, per_frame_function=forFrame,  minimum_percentage_probability=30, return_detected_frame=True)
