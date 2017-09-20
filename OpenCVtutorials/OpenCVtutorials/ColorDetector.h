#pragma once

#include<opencv2/core/core.hpp>
#include<opencv2/imgproc/imgproc.hpp>

using namespace cv;

class ColorDetector
{
private:
	int maxDist;
	cv::Vec3b target;
	cv::Mat converted;
	bool useLab;

	cv::Mat result;
public:
	ColorDetector() :maxDist(100), target(0, 0, 0), useLab(false) {}
	ColorDetector(bool useBool) :maxDist(100), target(0, 0, 0), useLab(useBool) {}
	ColorDetector(uchar blue, uchar green, uchar red, int dist = 100, bool use = false)
	:maxDist(dist),useLab(use)
	{
		setTargetColor(blue, green, red);
	}

	int getDistanceToTargetColor(const cv::Vec3b &color) const
	{
		return getColorDistance(color, target);
	}

	int getColorDistance(const cv::Vec3b &color1, const cv::Vec3b& color2) const
	{
		return (abs(color1[0] - color2[0]) +
			abs(color1[1] - color2[1])+
			abs(color1[2] - color2[2]));
	}

	cv::Mat process(const cv::Mat &image);

	cv::Mat operator() (const cv::Mat &image)
	{
		cv::Mat input;
		if (useLab)
		{
			cv::cvtColor(image, input, CV_BGR2Lab);
		}
		else
		{
			input = image;
		}

		cv::Mat output;
		cv::absdiff(input, cv::Scalar(target), output);

		std::vector<cv::Mat> images;
		cv::split(output, images);

		output = images[0] + images[1] + images[2];
		cv::threshold(output,
			output, maxDist, 255, cv::THRESH_BINARY_INV);
		return output;
	}

	void setColorDistanceThreshold(int dist)
	{
		if (dist < 0)
			dist = 0;
		maxDist = dist;
	}

	int getColorDistanceThreshold() const
	{
		return maxDist;
	}

	void setTargetColor(uchar blue, uchar green, uchar red)
	{
		target = cv::Vec3b(blue, green, red);

		if (useLab)
		{
			Mat tmp(1, 1, CV_8UC3);
			tmp.at<cv::Vec3b>(0, 0) = cv::Vec3b(blue, green, red);

			cv::cvtColor(tmp, tmp, CV_BGR2Lab);
			
			target = tmp.at<cv::Vec3b>(0, 0);
		}
	}

	void setTargetColor(cv::Vec3b color)
	{
		target = color;
	}

	cv::Vec3b getTargetColor() const
	{
		return target;
	}
};
