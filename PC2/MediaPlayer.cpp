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
    //����Ƿ�������:�ɹ���ʱ��isOpened����ture
    if(!capture.isOpened())
        cout<<"fail to open!"<<endl;
    //��ȡ����֡��
    total_frame_number = capture.get(CAP_PROP_FRAME_COUNT);
    LOG_DEBUG <<"������Ƶ��"<< total_frame_number << "֡";
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
    //���ÿ�ʼ֡()
    long frame_to_start = current_frame;
    capture.set( CAP_PROP_POS_FRAMES, frame_to_start);
    LOG_DEBUG << "�ӵ�" << frame_to_start << "֡��ʼ��" <<endl;


    //���ý���֡
	int frame_to_stop = total_frame_number;

    if(frame_to_stop < frame_to_start)
    {
        LOG_DEBUG << "����֡С�ڿ�ʼ֡��������󣬼����˳���";
        return ;
    }
    else
    {
        LOG_DEBUG <<"����֡Ϊ����" << frame_to_stop << "֡";
    }


    //��ȡ֡��
    double rate = capture.get(CAP_PROP_FPS);
    LOG_DEBUG << "֡��Ϊ:" << rate;

    //����һ���������ƶ�ȡ��Ƶѭ�������ı���
    exit_flag = false;
    //����ÿһ֡��ͼ��
    Mat frame;
    //��ʾÿһ֡�Ĵ���
	string winName = "image";
    namedWindow(winName);

	//setMouseCallback(winName, onMouse, NULL);
    double delay = 1000/rate;

    while(!exit_flag)
    {
        //��ȡ��һ֡
        if(!capture.read(frame))
        {
            LOG_DEBUG <<"��Ƶ����";
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

        //����ESC���ߵ���ָ���Ľ���֡���˳���ȡ��Ƶ
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