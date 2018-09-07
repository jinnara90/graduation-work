#pragma warning(disable:4996)

#include "FindColor_jy.h"
#include "Arduino_jy.h"

using namespace cv;
using namespace std;

int main() {
	//통신부부터시작
	int inputport;
	string inputstring;
	cin >> inputport >> inputstring;
	Arduino_jy ardu1(inputport,inputstring);
	//아두이노 연결
	ardu1.Arduino_connet();


	// 호버링을 위한 임시변수 flag
	int temp_for_hover = 0;

	//


	//영상처리부 시작
	VideoCapture cap(0);
	cap.set(CAP_PROP_FRAME_WIDTH, 640);
	cap.set(CAP_PROP_FRAME_HEIGHT, 480);
	FindColor_jy find_red("RED");

	int start_flag = 0;
	if (!cap.isOpened())
	{
		cout << "웹캠을 열 수 없습니다." << endl;
		return -1;
	}
	else {
		cout << "웹캡을 열었습니다.\n";
	}
	int i = 0;
	while (TRUE) {
		i++;
		Mat captured_img;
		cap.read(captured_img);
		flip(captured_img, captured_img, -1);
		//find_red.divide_color(captured_img);
		//find_red.labeling_(i);
		
		ardu1.MyColor.divide_color(captured_img);
		ardu1.MyColor.labeling_(i);
		//while문에서 시리얼통신
		//		ardu1.Arduino_jy_st(drone_flag);
		if (_kbhit()) {
			ardu1.getch_jy = _getch();
			if (ardu1.getch_jy == 'o') {
				temp_for_hover = 1;
			}
			else if (ardu1.getch_jy == 'i') {
				temp_for_hover = 0;
			}
			else{
				ardu1.drone_flag.comst_write(ardu1.getch_jy);
				//cout << ardu1.getch_jy;
				start_flag = 1; 
			}
		}
		else if (!kbhit() && start_flag > 0 && temp_for_hover == 0) {
			ardu1.drone_flag.Comst_write_void();
		}
		if (temp_for_hover == 1) {
			ardu1.drone_flag.comst_write(ardu1.MyColor.set_position(cv::Point(320, 320)));
		}
		//while에서 시리얼통신끝
		//cout << i;
		if (waitKey(30) >= 0)
			break;
	}
	return 0;

}