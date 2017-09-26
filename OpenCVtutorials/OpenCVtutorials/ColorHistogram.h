#pragma once
#include<opencv2/core.hpp>
class ColorHistogram
{
private:
	int histSize[3];
	float hranges[2];
	const float* ranges[3];
	int channels[3];
public:
	ColorHistogram();
	~ColorHistogram();
	cv::Mat getHistogram(const cv::Mat &image);
	cv::SparseMat getSparseHistogram(const cv::Mat &image);
};

