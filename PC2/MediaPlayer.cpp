#include <iostream>
#include <thread>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
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

MediaPlayer::MediaPlayer(void)
{
}


MediaPlayer::~MediaPlayer(void)
{
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
		if (playing_flag) {
			pause_flag = false;
			pause_condition.notify_all();
		} else {
			playing_flag = true;
			thread play_thread(play_video);
			play_thread.detach();
		}

	} else if (current_action == "stop") {
		exit_flag = true;
	} else if (current_action == "pause") {
		pause_flag = true;
	} else if (current_action == "exit") {
		exit_flag = true;
		pause_condition.notify_all();
	}
	return true;
}

void MediaPlayer::play_video()
{
	std::unique_lock<std::mutex> lock(pause_mutex);
	//����Ƶ�ļ�����ʵ���ǽ���һ��VideoCapture�ṹ
    VideoCapture capture("D:/video.avi");
    //����Ƿ�������:�ɹ���ʱ��isOpened����ture
    if(!capture.isOpened())
        cout<<"fail to open!"<<endl;
    //��ȡ����֡��
    long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
    LOG_DEBUG <<"������Ƶ��"<< totalFrameNumber << "֡";


    //���ÿ�ʼ֡()
    long frameToStart = 0;
    capture.set( CAP_PROP_POS_FRAMES,frameToStart);
    LOG_DEBUG << "�ӵ�" << frameToStart << "֡��ʼ��" <<endl;


    //���ý���֡
    int frameToStop = totalFrameNumber;

    if(frameToStop < frameToStart)
    {
        LOG_DEBUG << "����֡С�ڿ�ʼ֡��������󣬼����˳���";
        return ;
    }
    else
    {
        LOG_DEBUG <<"����֡Ϊ����" << frameToStop << "֡";
    }


    //��ȡ֡��
    double rate = capture.get(CAP_PROP_FPS);
    LOG_DEBUG << "֡��Ϊ:" << rate;

    //����һ���������ƶ�ȡ��Ƶѭ�������ı���
    exit_flag = false;
    //����ÿһ֡��ͼ��
    Mat frame;
    //��ʾÿһ֡�Ĵ���
    namedWindow("video");

    double delay = 1000/rate;


    //����whileѭ����ȡ֡
    //currentFrame����ѭ�����п��ƶ�ȡ��ָ����֡��ѭ�������ı���
    long currentFrame = frameToStart;

    while(!exit_flag)
    {
        //��ȡ��һ֡
        if(!capture.read(frame))
        {
            LOG_DEBUG <<"��ȡ��Ƶʧ��";
            return ;    
        }
        
        imshow("video",frame);
        LOG_DEBUG << "���ڶ�ȡ��" << currentFrame << "֡";

        int c = waitKey(delay);
        //����ESC���ߵ���ָ���Ľ���֡���˳���ȡ��Ƶ
        if((char) c == 27 || currentFrame > frameToStop)
        {
            exit_flag = true;
        }
        //���°������ͣ���ڵ�ǰ֡���ȴ���һ�ΰ���
        if( c >= 0)
        {
            waitKey(0);
        }

		if (pause_flag) {
			pause_condition.wait(lock);
		}

        currentFrame++;
    
    }
	playing_flag = false;
	pause_flag = false;
	if (!exit_flag)
		pause_condition.wait(lock);
    //�ر���Ƶ�ļ�
	destroyWindow("video");
    capture.release();
}

}