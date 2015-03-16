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

bool MediaPlayer::play_flag;

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
		thread play_thread(play_video);
		play_thread.detach();
	} else if (current_action == "stop") {
		play_flag = false;
	} else if (current_action == "pause") {

	}
	return true;
}

void MediaPlayer::play_video()
{
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
    play_flag = true;
    //����ÿһ֡��ͼ��
    Mat frame;
    //��ʾÿһ֡�Ĵ���
    namedWindow("video");

    double delay = 1000/rate;


    //����whileѭ����ȡ֡
    //currentFrame����ѭ�����п��ƶ�ȡ��ָ����֡��ѭ�������ı���
    long currentFrame = frameToStart;

    while(play_flag)
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
            play_flag = false;
        }
        //���°������ͣ���ڵ�ǰ֡���ȴ���һ�ΰ���
        if( c >= 0)
        {
            waitKey(0);
        }
        currentFrame++;
    
    }
    //�ر���Ƶ�ļ�
	destroyWindow("video");
    capture.release();
}

}