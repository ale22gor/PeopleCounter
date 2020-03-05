#include <iostream>
#include <sstream>

#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>

#include "FilterMovementFrame.h"
#include "FindPersonСontour.h"
#include "CheckPeopleInOut.h"
#include "center.h"
#include "path.h"


using namespace std;
using namespace cv;


int main()
{

    VideoCapture cap("videoplayback.mp4");
    if(!cap.isOpened()){
        cout << "Error opening video stream or file" << endl;
        return -1;
    }

    //create Background Subtractor object
    Ptr<BackgroundSubtractor> pBackSub{createBackgroundSubtractorMOG2(500,15,true)};

    Mat frame,fgMask, grayFrame;

    vector<Rect> countors;
    vector<Center> centers;
    std::vector<Path> inputPaths;

    int inCount{0};
    int outCount{0};
    while(true){

        // Capture frame
        cap >> frame;

        // If the frame is empty, break
        if (frame.empty())
            break;
        //convert to b&w
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);

        //update the background model
        pBackSub->apply(grayFrame, fgMask, 0.001);


        filterMovementFrame(fgMask,fgMask);
        //find people contours
        findPersonContour(fgMask,countors,centers);
        //updtae in and Out counter
        checkPeopleInOut(inputPaths,centers,frame.size(),inCount,outCount);

        // Display the result
        for(auto &countor:countors)
            rectangle(frame,countor,Scalar(0,255,255));
        for(auto &path:inputPaths)
            path.DrawPath(frame);

        stringstream resultText;
        resultText <<"<- MY OUT:"<<outCount<<" MY IN:"<<inCount<<" ->";

        putText(frame, resultText.str(), Point(100,410),
            FONT_HERSHEY_PLAIN, 2, Scalar(0,0,255),3);
        imshow( "Frame", frame );

        // Press  ESC to exit
        char c=static_cast<char>(waitKey(30));
        if(c==27)
            break;
    }

    //release the video capture object
    cap.release();

    // close all the frames
    destroyAllWindows();

    return 0;
}
