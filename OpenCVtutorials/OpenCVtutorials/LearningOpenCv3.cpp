#include <iostream>
#include <fstream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

int g_slider_position = 0;
int g_run = 1, g_dontset = 0;
cv::VideoCapture g_cap;

void onTrackbarSlide(int pos, void *)
{
	g_cap.set(cv::CAP_PROP_POS_FRAMES, pos);

	if (!g_dontset)
		g_run = 1;
	g_dontset = 0;
}

void PlayVideo()
{
	cv::namedWindow("Example2_4", cv::WINDOW_AUTOSIZE);

	g_cap.open("Video.mp4");

	int frames = (int)g_cap.get(cv::CAP_PROP_FRAME_COUNT);
	int tmpw = (int)g_cap.get(cv::CAP_PROP_FRAME_WIDTH);
	int tmph = (int)g_cap.get(cv::CAP_PROP_FRAME_HEIGHT);

	cout << "Video has " << frames << " frames of dimensions(" << tmpw << " ," << tmph << ")." << endl;

	cv::createTrackbar("Position", "Example2_4", &g_slider_position, frames, onTrackbarSlide);
	cv::Mat frame;
	for (;;)
	{
		if (g_run != 0)
		{
			g_cap >> frame;
			if (frame.empty())
			{
				std::cout << "Frame is empty" << std::endl;
				break;
			}
			int current_pos = (int)g_cap.get(cv::CAP_PROP_POS_FRAMES);
			g_dontset = 1;
			cv::setTrackbarPos("Position", "Example2_4", current_pos);
			cv::imshow("Example2_4", frame);

			g_run -= 1;
		}
		char c = (char)cv::waitKey(1);

		if (c == 's')
		{
			g_run = 1;
			cout << "Single step,run" << g_run << endl;
		}
		if (c == 'r')
		{
			g_run = -1;
			cout << "Run mode,run" << g_run << endl;
		}
		if (c == 27)
			break;
	}
}

void ApplySmoothing()
{
	Mat image = imread("puppy.bmp");
	cv::namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5-out", WINDOW_AUTOSIZE);

	if (image.empty())
		return ;
	
	imshow("Example2_5-in", image);
	Mat out;
	GaussianBlur(image, out, Size(5, 5), 3, 3);
	GaussianBlur(out, out, Size(5, 5), 3, 3);

	imshow("Example2_5-out", out);
}

void PyrDown()
{
	Mat image = imread("puppy.bmp");
	cv::namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5-out", WINDOW_AUTOSIZE);

	if (image.empty())
		return;

	imshow("Example2_5-in", image);
	Mat out;
	//GaussianBlur(image, out, Size(5, 5), 3, 3);
	//GaussianBlur(out, out, Size(5, 5), 3, 3);
	
	pyrDown(image, out);

	imshow("Example2_5-out", out);
}

void CannyEdgeDect()
{
	Mat image = imread("images/chessboards/chessboard01.jpg");
	
	cv::namedWindow("Example2_5-in", WINDOW_AUTOSIZE);
	namedWindow("Example2_5-out", WINDOW_AUTOSIZE);

	if (image.empty())
		return;

	imshow("Example2_5-in", image);
	Mat gray,canny;
	
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("Example2_5-out", gray);

	Canny(gray, canny, 10, 100, 3, true);
	imshow("Canny", canny);
}

int main()
{
	//PlayVideo();
	//ApplySmoothing();
	//PyrDown();
	CannyEdgeDect();
	cv::waitKey(0);
	cv::destroyAllWindows();
	return 0;
}