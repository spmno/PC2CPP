// PC2.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <memory>
#include <json/json.h>
#include <winsock2.h>.
#include <Windows.h>
#include "NetServer.h"
#include "MXLogger.h"
#include "GlobalConfig.h"
#include "SerialPortManager.h"
#include "PartFactory.h"
#include "SerialCommandDisposer.h"
#include "ModeManager.h"

using namespace mxnavi;

extern BOOL RestartWindows();

void updateNetFunction(string& content)
{
	Json::Reader reader;
	Json::Value value;
	PartFactory &part_factory = PartFactory::get_instance();
	
	if (reader.parse(content, value)) {
	
		if (value["type"].asString() == "init") {
			return;
		} else if (value["type"].asString() == "reboot") {
			RestartWindows();
		} else if (value["type"].asString() == "single") {
			std::shared_ptr<Part> &part_ptr = part_factory.createPart(value["part"].asString());
			if (!part_ptr) {
				MessageBox(NULL, L"部件错误", NULL, MB_OK|MB_TOPMOST);
				return;
			}
			part_ptr->make_serial_command(value["action"].asString());
			bool ret = part_ptr->do_command();
			if (!ret) {
				LOG_ERROR << "write " << value["part"].asString() << " command failed!";
			}
		} else {
			ModeManager &mode_manager = ModeManager::get_instance();
			mode_manager.do_mode(value["action"].asString());
		}

	} else {
		LOG_ERROR << "Parse command failed!";
	}
}

void updateSerialFunction(const unsigned char* content)
{
	SerialCommandDisposer disposer;
	disposer.dispose(content);
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	LOG_DEBUG << "App Start!";
	if (!GlobalConfig::get_instance().init()) {
		MessageBox(NULL, L"配置文件错误", NULL, MB_OK|MB_TOPMOST);
		return false;
	}
	//ShowCursor(FALSE);
	SetCursorPos(0, 0);
	NetServer::get_instance().start();
	SerialPortManager::get_instance().init();
	NetServer::get_instance().addUpdateFunction(updateNetFunction);
	SerialPortManager::get_instance().addUpdateFunction(updateSerialFunction);
	HMODULE hInstance= 0;
    hInstance = GetModuleHandle(NULL);
	HWND hWnd; 
	MSG msg;
	//创建一个新的窗口
	hWnd = CreateWindow(L"EDIT",
		L"由main创建的消息",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,NULL,
		hInstance,
		NULL);
	if (!hWnd)
		return (1);

	//ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);
	while (GetMessage(&msg, NULL, NULL, NULL)) {
		TranslateMessage(&msg);
	    DispatchMessage(&msg);
	}
	return 0;
}


