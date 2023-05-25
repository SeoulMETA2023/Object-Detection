#include <opencv2/opencv.hpp>
#include <time.h>


using namespace cv;
using namespace std;

int main(int, char**)
{
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
    for (;;)
    {
        cap.read(frame);
                // check if we succeeded
        if (frame.empty()) {
            cerr << "ERROR! blank frame grabbed\n";
            break;
        }

        
        Mat test = imread("img.png");
        if (test.empty())
        {
            cout << "no templ Image!" << endl;
            return -1;
        }
        
        Mat result;
        
        
        
        resize(frame, frame, Size(1080 , 720 ));
        resize(test, test, Size(test.cols / 6, test.rows / 6));
        cvtColor(frame, frame, COLOR_BGR2GRAY);
        cvtColor(test, test, COLOR_BGR2GRAY);
        
        
      
            Mat img_out;
            frame.copyTo(img_out);
            
            int Matching_method = 3;
 
            
            start = clock();
            
            
            matchTemplate(frame, test, result, 3);
            normalize(result, result, 0, 1, NORM_MINMAX, -1, Mat());
            minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, Mat() );
            //minMaxLoc(result, &minVal, NULL, &minLoc, NULL);
            if (Matching_method == 0 || Matching_method == 1)
            {
                matchLoc = minLoc;
            }
            else
                matchLoc = maxLoc;
            
            
            end = clock();
            
            //cout << "Searching time : " << difftime(end, start) / CLOCKS_PER_SEC << endl;
            
            double searching_time = difftime(end, start) / CLOCKS_PER_SEC;
            char mytext[30];
            sprintf(mytext, "searching time : %lf", searching_time);
            
            putText(img_out, mytext, Point(100,100), 1, 2, Scalar(0,0,255),1);
            
            rectangle(img_out, matchLoc, Point(matchLoc.x + test.cols, matchLoc.y + test.rows), Scalar(0, 0, 255), 1);
            
            cvtColor(result, result, COLOR_GRAY2BGR);
            circle(result, matchLoc, 3, Scalar(0, 0, 255), 1);
            
            imshow("src", img_out);
           // imshow("test", test);
            //imshow("result", result);
            
            waitKey(1);
            
        
    }
    return 0;
}
 
 

