#include "Histogram1D.h"
#include <opencv2/imgproc/imgproc.hpp>


Histogram1D::Histogram1D()
{
	histSize[0] = 256;
	hranges[0] = 0.0;
	hranges[1] = 256.0;
	ranges[0] = hranges;
	channels[0] = 0;
}


Histogram1D::~Histogram1D()
{
}

cv::Mat Histogram1D::getHistogram(const cv::Mat &image)
{
	cv::Mat hist;
	cv::calcHist(&image, 1, channels, cv::Mat(), hist,
		1, histSize, ranges);

	return hist;
}

cv::Mat Histogram1D::getHistogramImage(const cv::Mat &image, int zoom)
{
	cv::Mat hist = getHistogram(image);
	return getImageOfHistogram(hist, zoom);
}

cv::Mat Histogram1D::getImageOfHistogram(const cv::Mat &hist, int zoom)
{
	double maxVal = 0;
	double minVal = 0;
	cv::minMaxLoc(hist, &minVal, &maxVal, 0, 0);

	int histSize = hist.rows;

	cv::Mat histImg(histSize*zoom, histSize*zoom, CV_8U, cv::Scalar(255));

	int hpt = static_cast<int>(0.9*histSize);
	for (int h = 0; h < histSize; h++)
	{
		float binVal = hist.at<float>(h);
		if (binVal > 0)
		{
			int intensity = static_cast<int>(binVal*hpt / maxVal);
			cv::line(histImg, cv::Point(h*zoom, histSize*zoom),
				cv::Point(h*zoom, (histSize - intensity)*zoom),
				cv::Scalar(0), zoom);
		}
	}
	return histImg;
}
