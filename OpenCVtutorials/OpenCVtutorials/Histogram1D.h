#pragma once
#include <opencv2/core.hpp>

class Histogram1D
{
private:
	int histSize[1]; 
	float hranges[2];
	const float *ranges[1];
	int channels[1];
public:
	Histogram1D();
	~Histogram1D();
	cv::Mat getHistogram(const cv::Mat &image);
	cv::Mat getHistogramImage(const cv::Mat &image, int zoom = 1);
	static cv::Mat getImageOfHistogram(const cv::Mat &hist, int zoom);
};

