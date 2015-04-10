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
	//打开视频文件：其实就是建立一个VideoCapture结构
    VideoCapture capture("D:/video.avi");
    //检测是否正常打开:成功打开时，isOpened返回ture
    if(!capture.isOpened())
        cout<<"fail to open!"<<endl;
    //获取整个帧数
    long totalFrameNumber = capture.get(CAP_PROP_FRAME_COUNT);
    LOG_DEBUG <<"整个视频共"<< totalFrameNumber << "帧";


    //设置开始帧()
    long frameToStart = 0;
    capture.set( CAP_PROP_POS_FRAMES,frameToStart);
    LOG_DEBUG << "从第" << frameToStart << "帧开始读" <<endl;


    //设置结束帧
    int frameToStop = totalFrameNumber;

    if(frameToStop < frameToStart)
    {
        LOG_DEBUG << "结束帧小于开始帧，程序错误，即将退出！";
        return ;
    }
    else
    {
        LOG_DEBUG <<"结束帧为：第" << frameToStop << "帧";
    }


    //获取帧率
    double rate = capture.get(CAP_PROP_FPS);
    LOG_DEBUG << "帧率为:" << rate;

    //定义一个用来控制读取视频循环结束的变量
    exit_flag = false;
    //承载每一帧的图像
    Mat frame;
    //显示每一帧的窗口
    namedWindow("video");

    double delay = 1000/rate;


    //利用while循环读取帧
    //currentFrame是在循环体中控制读取到指定的帧后循环结束的变量
    long currentFrame = frameToStart;

    while(!exit_flag)
    {
        //读取下一帧
        if(!capture.read(frame))
        {
            LOG_DEBUG <<"读取视频失败";
            return ;    
        }
        
        imshow("video",frame);
        LOG_DEBUG << "正在读取第" << currentFrame << "帧";

        int c = waitKey(delay);
        //按下ESC或者到达指定的结束帧后退出读取视频
        if((char) c == 27 || currentFrame > frameToStop)
        {
            exit_flag = true;
        }
        //按下按键后会停留在当前帧，等待下一次按键
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
    //关闭视频文件
	destroyWindow("video");
    capture.release();
}

}