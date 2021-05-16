#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2/objdetect.hpp>
#include<iostream>

using namespace std;
using namespace cv;

int main(){

	string path = "http://MY.DROID.CAM.IP:4747/mjpegfeed?640x480";//to use my mobile device as webcam and take live video from it

	VideoCapture cap(path);
	Mat img, imgHSV, mask;


	int hmin = 0, smin = 0, vmin = 0;
	int hmax = 179, smax = 255, vmax = 255;


	namedWindow("Trackbars", (640, 200));//to create a trackbar window

	//our tracking options to decide values according to needed color
	createTrackbar("Hue Min", "Trackbars", &hmin, 179);
	createTrackbar("Hue Max", "Trackbars", &hmax, 179);
	createTrackbar("Saturation Min", "Trackbars", &smin, 255);
	createTrackbar("Saturation Max", "Trackbars", &smax, 255);
	createTrackbar("Value Min", "Trackbars", &vmin, 255);
	createTrackbar("Value Max", "Trackbars", &vmax, 255);

	while (true) {

		cap.read(img);
		cvtColor(img, imgHSV, cv::COLOR_BGR2HSV);//for hue, saturation, value

		Scalar lower(hmin, smin, vmin);
		Scalar upper(hmax, smax, vmax);
		inRange(imgHSV, lower, upper, mask);

		imshow("Image", img);
		imshow("Image Mask", mask);
		waitKey(1);
	}

	return 0;
}
