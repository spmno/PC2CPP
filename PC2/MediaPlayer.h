#pragma once
#include "part.h"
#include <string>
#include <condition_variable>
#include <mutex>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <Windows.h>

namespace mxnavi {

class MediaPlayer :
	public Part
{
public:
	MediaPlayer(void);
	~MediaPlayer(void);
	virtual void make_serial_command(const std::string& action);
	virtual void make_net_command(unsigned int command);
	virtual bool make_init_command();
	virtual bool do_command();
private:
	static void onMouse(int event, int x, int y, int flag, void *parma);
	std::string current_action;
	static void play_video();
	static bool exit_flag;
	static bool pause_flag;
	static bool playing_flag;
	static std::condition_variable pause_condition;
	static std::mutex pause_mutex;
	static long total_frame_number;
	static cv::VideoCapture capture;
	static long current_frame;
	static HANDLE event;
};

}