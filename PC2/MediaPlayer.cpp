#include <iostream>
#include <thread>
#include <Windows.h>

#include "MediaPlayer.h"
#include "MXLogger.h"

namespace mxnavi {

using namespace cv;
using namespace std;

bool MediaPlayer::exit_flag;
bool MediaPlayer::pause_flag;
bool MediaPlayer::playing_flag;
std::condition_variable MediaPlayer::pause_condition;
std::mutex MediaPlayer::pause_mutex;
long MediaPlayer::total_frame_number;
VideoCapture MediaPlayer::capture;
long MediaPlayer::current_frame = 0;
HANDLE MediaPlayer::event;

MediaPlayer::MediaPlayer(void)
{
	capture.open("D:/video.avi");
    //检测是否正常打开:成功打开时，isOpened返回ture
    if(!capture.isOpened())
        cout<<"fail to open!"<<endl;
    //获取整个帧数
    total_frame_number = capture.get(CAP_PROP_FRAME_COUNT);
    LOG_DEBUG <<"整个视频共"<< total_frame_number << "帧";
	event = CreateEvent(NULL, TRUE, FALSE, NULL);
}


MediaPlayer::~MediaPlayer(void)
{
	capture.release();
}

bool MediaPlayer::make_init_command()
{
	return true;
}

void MediaPlayer::make_serial_command(const std::string& action)
{
	LOG_DEBUG << __FUNCTION__;
	current_action = action;
}

void MediaPlayer::make_net_command(unsigned int command)
{
	
}

bool MediaPlayer::do_command()
{
	if (current_action == "play") {
		pause_flag = false;
		if (playing_flag) {
			destroyWindow("image");
			return false;
		} else {
			playing_flag = true;
			thread play_thread(play_video);
			play_thread.detach();
		}
	} else if (current_action == "pause") {
		pause_flag = true;
	} else if (current_action == "exit") {
		destroyWindow("image");
		exit_flag = true;
	}
	return true;
}


void MediaPlayer::play_video()
{
    //设置开始帧()
    long frame_to_start = current_frame;
    capture.set( CAP_PROP_POS_FRAMES, frame_to_start);
    LOG_DEBUG << "从第" << frame_to_start << "帧开始读" <<endl;


    //设置结束帧
	int frame_to_stop = total_frame_number;

    if(frame_to_stop < frame_to_start)
    {
        LOG_DEBUG << "结束帧小于开始帧，程序错误，即将退出！";
        return ;
    }
    else
    {
        LOG_DEBUG <<"结束帧为：第" << frame_to_stop << "帧";
    }


    //获取帧率
    double rate = capture.get(CAP_PROP_FPS);
    LOG_DEBUG << "帧率为:" << rate;

    //定义一个用来控制读取视频循环结束的变量
    exit_flag = false;
    //承载每一帧的图像
    Mat frame;
    //显示每一帧的窗口
	string winName = "image";
    namedWindow(winName);

	//setMouseCallback(winName, onMouse, NULL);
    double delay = 1000/rate;

    while(!exit_flag)
    {
        //读取下一帧
        if(!capture.read(frame))
        {
            LOG_DEBUG <<"视频结束";
			current_frame = 0;
			destroyWindow("image");
			exit_flag = false;
			break;
        }
        
        imshow("image",frame);
		//HWND image_handle = FindWindow(L"Main HighGUI class", L"image");
		//if (SetWindowPos(image_handle, HWND_TOP, 0, 0, 1280, 720, SWP_NOSIZE|SWP_NOREDRAW) == FALSE) {
		//	MessageBox(NULL, L"ERROR", NULL, MB_TOPMOST);
		//}
		int c = waitKey(delay);

        //按下ESC或者到达指定的结束帧后退出读取视频
		if(current_frame >= frame_to_stop)
        {
			//waitKey(0);
            exit_flag = true;
        }
 
        current_frame++;

		if (pause_flag) {
			int c = waitKey(0);
			pause_flag = false;
		}

		if (exit_flag) {
			current_frame = 0;
			destroyWindow("image");
			exit_flag = false;
			break;
		}
    }

	playing_flag = false;
	pause_flag = false;
}

}