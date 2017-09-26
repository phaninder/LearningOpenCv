#include "ColorHistogram.h"
#include<opencv2/imgproc.hpp>


ColorHistogram::ColorHistogram()
{
	histSize[0] = histSize[1] = histSize[2] = 256;
	hranges[0] = 0.0;
	hranges[1] = 256.0;
	ranges[0] = hranges;
	ranges[1] = hranges;
	ranges[2] = hranges;
	channels[0] = 0;
	channels[1] = 1;
	channels[2] = 2;
}


ColorHistogram::~ColorHistogram()
{
}


cv::Mat ColorHistogram::getHistogram(const cv::Mat &image)
{
	cv::Mat hist;
	cv::calcHist(&image, 1, channels, cv::Mat(), hist, 3, histSize, ranges);
	return hist;
}


cv::SparseMat ColorHistogram::getSparseHistogram(const cv::Mat &image)
{
	cv::SparseMat hist(3, histSize, CV_32F);
	cv::calcHist(&image, 1, channels, cv::Mat(), hist, 3, histSize, ranges);
	return hist;

}
