#pragma once

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/highgui.hpp>
#include <vector>
#include <cstdio>
#include <opencv2/features2d/features2d.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/core/mat.hpp>  
#include <opencv2/imgcodecs.hpp>  
#include <opencv2/imgproc.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>


#include <string>
using namespace std; 
//using namespace cv;


class FindColor_jy
{
private:
	int LowH ;
	int HighH;
	int LowS;
	int HighS;
	int LowV;
	int HighV;
	float *p;
	CvMemStorage *storage;
	CvSeq *circles = 0;
	
	int radius_range;
	string str;
	string temp_str;



	static void onMouseStatic(int event, int x, int y, int flags, void* that);
public:
	cv::Point CenterPoint;
	IplImage *edge;
	IplImage *frame;
	IplImage *trans;
	cv::Rect prev_rect;
	cv::Mat objectHistogram;
	cv::Mat globalHistogram;
	cv::Mat bp;
	cv::Mat img_input, img_hsv, img_binary;
	FindColor_jy();
	~FindColor_jy();

	cv::Point Mouse_Point;
	FindColor_jy(string color);

	void set_color(string color);
	void divide_color(cv::Mat Captured_img);
	void labeling_(int i);
	void getObjectHistogram(cv::Mat &frame, cv::Rect object_region);

	void backProjection(const cv::Mat &frame, const cv::Mat &histogram, cv::Mat &bp);

	char set_position(cv::Point inputpoint);
	
	void onMouseEvent(int event, int x, int y, int flags, void* dstImage);
	void check_mouse_point(cv::Mat image);
};

