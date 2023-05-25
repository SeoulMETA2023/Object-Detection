#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    vector <Rect> found;
    int i;
    char ch;
    Mat frame;
    VideoCapture cap;
    clock_t start, end;
    int deviceID = 0;             // 0 = open default camera
    int apiID = 0;      // 0 = autodetect default API
        // open selected camera using selected API
    cap.open(deviceID, apiID);
    double minVal, maxVal;
    Point minLoc, maxLoc;
    Point matchLoc;
    if (!cap.isOpened()) {
            cerr << "ERROR! Unable to open camera\n";
            return -1;
        }
    cout << "Start grabbing" << endl
            << "Press any key to terminate" << endl;

    HOGDescriptor hog(
        Size(48,96),
        Size(16,16),
        Size(8,8),
        Size(8,8),
        9
    );

    while(1){
        cap >> frame;
        if(frame.empty()) break;
      resize(frame, frame, Size(720 , 480 ));
        hog.detectMultiScale(
            frame,
            found,
            1.2,
            Size(8,8),
            Size(32,32),
            1.05,
            6
        );

        hog.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());

        for(i=0; i<(int)found.size();i++){
            rectangle(frame,found[i],Scalar(0,255,0),2);
        }

        imshow("pedestrian detection",frame);
        ch = waitKey(1);
        if(ch ==27) break;
        else if(ch ==32){
            while((ch = waitKey(1) !=32 && ch!=27));
            if(ch==27) break;
        }
    }
}
