#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

//Mat image;
//void onMouse(int event, int x, int y, int flags, void *param)
//{
//	Point p1, p2;
//	if (event == EVENT_LBUTTONDOWN)
//	{
//		p1.x = x;
//		p1.y = y;
//		cout << "Drawing lind"<<endl;
//		DrawLine(p1, p1);
//	}
//}
//
//void LoadImage()
//{
//	image = imread("puppy.bmp");
//
//	namedWindow("Image");
//
//	setMouseCallback("Image", onMouse, reinterpret_cast<void*>(&image));
//	imshow("Image", image);
//}
//
//void DrawLine(Point p1,Point p2)
//{
//	cv::line(image, p1, p2, Scalar(255, 255, 255), 8, 0);
//}