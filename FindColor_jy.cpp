#include "FindColor_jy.h"
#define _CRT_NONSTDC_NO_DEPRECATE

FindColor_jy::FindColor_jy()
{
	edge = 0;
	
}

FindColor_jy::~FindColor_jy()
{
	
}

FindColor_jy::FindColor_jy(string color) {
	Mouse_Point.x = -1;
	Mouse_Point.y = -1;
	if (color.compare("RED") == 0 || color.compare("red") == 0)
	{
		LowH = 0;
		HighH = 10;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color.compare("BLUE") == 0 || color.compare("blue") == 0)
	{
		LowH = 100;
		HighH = 115;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color.compare("YELLOW") == 0 || color.compare("yellow") == 0)
	{
		LowH = 25;
		HighH = 40;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color.compare("BLACK") == 0 || color.compare("black") == 0)
	{
		LowH = 41;
		HighH = 60;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 33;
	}
}

void FindColor_jy::set_color(string color)
{
	if (color.compare("RED") == 0 || color.compare("red") == 0)
	{
		LowH = 0;
		HighH = 10;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color.compare("BLUE") == 0 || color.compare("blue") == 0)
	{
		LowH = 100;
		HighH = 115;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color.compare("YELLOW") == 0 || color.compare("yellow") == 0)
	{
		LowH = 25;
		HighH = 40;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 255;
	}
	else if (color.compare("BLACK") == 0 || color.compare("black") == 0)
	{
		LowH = 41;
		HighH = 60;

		LowS = 50;
		HighS = 255;

		LowV = 0;
		HighV = 33;
	}
}
void FindColor_jy::divide_color(cv::Mat Captured_img) {
	img_input = Captured_img;
	//imshow("원본 영상", img_input);
	/*cv::VideoCapture cam1 = &inputcam(0);
	bool ret = cam1.read(img_input);
	if (!ret)
	{
		std::cout << "카메라로부터 이미지를 가져올 수 없습니다.\n";
		exit(-1);
	}*/
	cvtColor(img_input, img_hsv, cv::COLOR_BGR2HSV);

	inRange(img_hsv, cv::Scalar(LowH, LowS, LowV), cv::Scalar(HighH, HighS, HighV), img_binary);

	//morphological opening 작은 점들을 제거 
	erode(img_binary, img_binary, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	dilate(img_binary, img_binary, cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));

	//morphological closing 영역의 구멍 메우기 
	dilate(img_binary, img_binary, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
	erode(img_binary, img_binary, getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(5, 5)));
}
void FindColor_jy::labeling_(int i) {

	//라벨링 
	cv::Mat img_labels, stats, centroids;
	int numOfLables = connectedComponentsWithStats(img_binary, img_labels,
		stats, centroids, 8, CV_32S);

	//영역박스 그리기
	int max = -1, idx = 0;
	for (int j = 1; j < numOfLables; j++) {
		int area = stats.at<int>(j, cv::CC_STAT_AREA);
		if (max < area)
		{
			max = area;
			idx = j;
		}
	}

	int left = stats.at<int>(idx, cv::CC_STAT_LEFT);
	int top = stats.at<int>(idx, cv::CC_STAT_TOP);
	int width = stats.at<int>(idx, cv::CC_STAT_WIDTH);
	int height = stats.at<int>(idx, cv::CC_STAT_HEIGHT);
	radius_range = width > height? width / 2:height/2;
	rectangle(img_input, cv::Point(left, top), cv::Point(left + width, top + height),cv::Scalar(0, 0, 255), 1);


	CenterPoint = cv::Point((left + radius_range), (top + radius_range));
	cv::Rect object_region(left, top, width, height);
	//cv::circle(img_input, CenterPoint, radius_range, CV_RGB(255, 0, 0), 1, 8, 0);
	getObjectHistogram(img_hsv, object_region);
	prev_rect = object_region;
	cv::circle(img_input, CenterPoint, 3, CV_RGB(0, 255, 0), -1, 8, 0);
	cv::circle(img_input, CenterPoint, radius_range, CV_RGB(255, 0, 0), 1, 8, 0);
	char *temp;
	str = "";
	str += to_string((int)CenterPoint.x);
	str += ",";
	str += to_string((int)CenterPoint.y);
	cv::putText(img_input, str, CenterPoint, 1, 1, CV_RGB(0, 0, 0), 1);
	



/*

	temp_str = "";
	check_mouse_point(img_input);
	if (Mouse_Point.x > 0 && Mouse_Point.y > 0) {
		temp_str += to_string((int)Mouse_Point.x);
		temp_str += ",";
		temp_str += to_string((int)Mouse_Point.y);
		cv::putText(img_input, temp_str, Mouse_Point, 1, 1, CV_RGB(0, 0, 0), 1);
	}

*/



	imshow("이진화 영상", img_binary);
	imshow("Original", img_input);
}


void FindColor_jy::getObjectHistogram(cv::Mat &frame, cv::Rect object_region)
{
	const int channels[] = { 0, 1 };
	const int histSize[] = { 64, 64 };
	float range[] = { 0, 256 };
	const float *ranges[] = { range, range };

	// Histogram in object region
	cv::Mat objectROI = frame(object_region);
	calcHist(&objectROI, 1, channels, cv::noArray(), objectHistogram, 2, histSize, ranges, true, false);


	// A priori color distribution with cumulative histogram
	calcHist(&frame, 1, channels, cv::noArray(), globalHistogram, 2, histSize, ranges, true, true);


	// Boosting: Divide conditional probabilities in object area by a priori probabilities of colors
	for (int y = 0; y < objectHistogram.rows; y++) {
		for (int x = 0; x < objectHistogram.cols; x++) {
			objectHistogram.at<float>(y, x) /= globalHistogram.at<float>(y, x);
		}
	}
	normalize(objectHistogram, objectHistogram, 0, 255, cv::NORM_MINMAX);

}
void FindColor_jy::backProjection(const cv::Mat &frame, const cv::Mat &histogram, cv::Mat &bp) {
	const int channels[] = { 0, 1 };
	float range[] = { 0, 256 };
	const float *ranges[] = { range, range };
	calcBackProject(&frame, 1, channels, objectHistogram, bp, ranges);
}

char FindColor_jy::set_position(cv::Point inputpoint)
{
	cv::Point defaultPoint = cv::Point(320,320);
	cv::Point calPoint = cv::Point( (int)defaultPoint.x - (int)CenterPoint.x , (int)defaultPoint.y - (int)CenterPoint.y ); // 목표위치 - 현위치
	cout << "calPoint 값 = " << (int)calPoint.x << (int)calPoint.y << '\n';
	//변위값을 조절하여 원하는 위치와의 위치관계를 표시하자
	if ((int)calPoint.x ==0) { //두 낫띵
		return ' ';
	}
	else if ((int)calPoint.x < 0) {  // ㅁ목표위치가 왼쪽임 왼쪽으로가자
		return 'a';
	}
	else if ((int)calPoint.x > 0) {		//목표위치가 오른쪽임 오른쪽으로가자
		return 'd';
	}
	else {
		return ' ';
	}
}




//
//void FindColor_jy::onMouseStatic(int event, int x, int y, int flags, void* that)
//{	
//	FindColor_jy* thiz = static_cast<FindColor_jy*>(that);
//	thiz->onMouseEvent(event, x, y, flags, &that);
//}
//
//void FindColor_jy::onMouseEvent(int event, int x, int y, int flags, void * dstImage)
//{
//	cv::Mat MoutsImage = *(cv::Mat*)dstImage;
//
//	switch (event) {
//	case (cv::EVENT_LBUTTONDOWN):
//		Mouse_Point.x = x;
//		Mouse_Point.y = y;
//		break;
//	}
//}
//
//
//void FindColor_jy::check_mouse_point(cv::Mat image)
//{
//	cv::setMouseCallback("Original", onMouseStatic, (void*)&img_input);
//}
//
