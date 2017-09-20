#include <iostream>
#include <random>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "ColorDetector.h"

using namespace std;
using namespace cv;


void onMouse(int event, int x, int y, int flags, void * param)
{
	Mat *im = reinterpret_cast<Mat *>(param);
	switch (event)
	{
		case cv::EVENT_LBUTTONDOWN:
		{
			cout << "At (" << x << "," << y << ") value is:" <<
				static_cast<int>(im->at<uchar>(Point(x, y))) << endl;
			break;
		}
	}
}
void DrawCircle()
{
	Mat image = imread("output.png");

	if (!image.empty())
	{
		flip(image, image, 1);
		circle(image, Point(155, 110), 65, 0, 3);
		putText(image, "This is a dog.", Point(40, 200), FONT_HERSHEY_PLAIN, 2.0, 255, 2);
		namedWindow("Image");
		imshow("Image", image);
		cout << "No of channels:" << image.channels() << endl;
		setMouseCallback("Image", onMouse, reinterpret_cast<void*>(&image));
		//imshow("Resultwin", result);
		//imwrite("output.png", result);
	}
}

Mat function()
{
	Mat imag(500, 500, CV_8U,50);
	return imag;
}

void ManipulatingImage()
{

	Mat image1(240, 320, CV_8U, 100);
	imshow("Image", image1);
	waitKey(0);
	//change rows n cols
	image1.create(200, 200, CV_8U);
	image1 = 200;
	imshow("Image", image1);
	waitKey(0);
	//CReate a red image
	Mat image2(240, 320, CV_8UC3, Scalar(0, 0, 255));
	imshow("Image", image2);
	waitKey(0);
	//read an image
	Mat image3 = imread("puppy.bmp");
	//point to same image
	Mat image4(image3);
	image1 = image3;

	//point to new copies of source image
	image3.copyTo(image2);
	Mat image5 = image3.clone();

	//flip image for testing
	flip(image3, image3, 1);
	imshow("Image 3", image3);
	imshow("Image 1", image1);
	imshow("Image 2", image2);
	imshow("Image 4", image4);
	imshow("Image 5", image5);
	waitKey(0);

	Mat gray = function();
	imshow("Image", gray);
	waitKey(0);

	image1 = imread("puppy.bmp", CV_LOAD_IMAGE_GRAYSCALE);
	image1.convertTo(image2, CV_32F, 1 / 255.0, 0.0);
	imshow("Image", image2);
	waitKey(0);
}

void ROI()
{
	Mat image = imread("images/puppy.bmp");
	Mat logo = imread("images/smalllogo.png");
	Mat imageROI(image, Rect(image.cols - logo.cols,
		image.rows - logo.rows, logo.cols, logo.rows));

	logo.copyTo(imageROI, logo);
	imshow("Original", image);
	imshow("Image", imageROI);
	waitKey(0);
}

void salt(Mat image, int n)
{
	default_random_engine generator;
	uniform_int_distribution<int> randomRow(0, image.rows - 1);
	uniform_int_distribution<int> randomCol(0, image.cols - 1);

	int i, j;
	for (int k = 0; k < n; k++)
	{
		i = randomRow(generator);
		j = randomCol(generator);

		if (image.type() == CV_8UC1)
		{
			image.at<uchar>(i, j) = 255;
		}
		else if (image.type() == CV_8UC3)
		{
			image.at<Vec3b>(i, j)[0] = 255;
			image.at<Vec3b>(i, j)[1] = 255;
			image.at<Vec3b>(i, j)[2] = 255;
		}
	}
}

void colorReduce(Mat img, int n)
{
	int rows = img.rows;
	int colChannels = img.cols*img.channels();

	for (int i = 0; i < rows; i++)
	{
		uchar *data = img.ptr<uchar>(i);

		for (int j = 0; j < colChannels; j++)
		{
			data[j] = (data[j]/n) *n +(n / 2);
		}
	}
}

void colorReduceUsingIt(Mat img, int n)
{
	Mat_<Vec3b>::iterator it = img.begin<Vec3b>();
	MatIterator_<Vec3b> itend = img.end<Vec3b>();
	int rows = img.rows;
	int colChannels = img.cols*img.channels();
	int n2 = (n / 2);
	for (; it != itend; it++)
	{
		(*it)[0] = ((*it)[0] / n) *n + (n2);
		(*it)[1] = ((*it)[1] / n) *n + (n2);
		(*it)[2] = ((*it)[2] / n) *n + (n2);
	}
	
}

void Sharpen(const Mat &image, Mat &res)
{
	res.create(image.size(), image.type());

	Mat kernel(3, 3, CV_32F, Scalar(0));
	kernel.at<float>(1, 1) = 5.0;
	kernel.at<float>(0, 1) = -1.0;
	kernel.at<float>(1, 0) = -1.0;
	kernel.at<float>(1, 2) = -1.0;
	kernel.at<float>(2, 1) = -1.0;
	
	filter2D(image, res, image.depth(), kernel);
	//int channels = image.channels();

	//for (int i = 1; i < image.rows - 1; i++)
	//{
	//	const uchar* previous = image.ptr<const uchar>(i - 1);
	//	const uchar* current = image.ptr<uchar>(i);
	//	const uchar* next = image.ptr<uchar>(i + 1);

	//	uchar* output = res.ptr<uchar>(i);

	//	for (int j = 1; j < (image.cols - 1)*channels; j++)
	//	{
	//		output[j] = saturate_cast<uchar>(5 * current[j] - current[j - channels] - current[j + channels]
	//			- previous[j] - next[j]);
	//	}
	//}

	////set the unprocessed pixels to 0
	//res.row(0).setTo(Scalar(0));
	//res.row(res.rows - 1).setTo(Scalar(0));
	//res.col(0).setTo(Scalar(0));
	//res.col(res.cols - 1).setTo(Scalar(0));
}

void showRain(Mat image1, Mat image2,Mat &res,float weight)
{
	//image1 = weight*image1+image2;
	//addWeighted(image1, weight, image2, weight, 0, image1);
	//scaleAdd(image1, weight, image2, image1);
	vector<Mat> planes;
	split(image1, planes);
	planes[0] += image2;
	
	merge(planes, res);
}

void wave(Mat image,Mat &res)
{
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			srcX.at<float>(i, j) = j;
			srcY.at<float>(i, j) = i + 5 * sin(j / 10.0);
		}
	}
	remap(image, res, srcX, srcY, INTER_LINEAR);
}

void flipImage(Mat image, Mat &res)
{
	Mat srcX(image.rows, image.cols, CV_32F);
	Mat srcY(image.rows, image.cols, CV_32F);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			srcX.at<float>(i, j) = j;//image.cols - j - 1;
			srcY.at<float>(i, j) = image.rows-i-1;
		}
	}

	remap(image, res, srcX, srcY, INTER_LINEAR);
}

int main()
{
	ColorDetector cdetect;

	Mat image = imread("images/boldt.jpg", 1);
	Mat image2 = imread("images/rain.jpg", 1);
	//Mat res(image.rows, image.cols,CV_32F);

	if (image.empty())
		return 0;
	//DrawCircle();
	//ManipulatingImage();
	//ROI();//colorReduceUsingIt(image, 64);
	//Sharpen(image, image2);
	//salt(image, 3000);
	//showRain(image, image2,res,0.5);
	//wave(image, res);
	//flipImage(image, res);
	
	cdetect.setTargetColor(230, 190, 130);
	Mat result = cdetect.process(image);

	imshow("Original", image);
	imshow("Sharped", result);
	waitKey(0);
	return 0;
}

