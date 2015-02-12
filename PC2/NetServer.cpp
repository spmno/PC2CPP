
#include <stdio.h>

#include <thread>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

#include "NetServer.h"
#include "MXLogger.h"


namespace mxnavi {


NetServer::NetServer(void)
{
 
}


NetServer::~NetServer(void)
{

}

void NetServer::accept() 
{
	using namespace boost::asio;
	io_service iosev;
	ip::tcp::acceptor acceptor(iosev, 
        ip::tcp::endpoint(ip::tcp::v4(), 9876));

	LOG_DEBUG << "NetServer accept.";
	
    // 等待直到客户端连接进来
	while(true) {
		std::unique_ptr<ip::tcp::socket> socket_ptr(new ip::tcp::socket(iosev));
		acceptor.accept(*socket_ptr);
		LOG_DEBUG << (*socket_ptr).remote_endpoint().address();
		socket_container.push_back(std::move(socket_ptr));
		std::thread read_thread(read_wrapper, this);
		read_thread.detach();
	}
    
}

void NetServer::accept_wrapper(NetServer* self)
{
	self->accept();
}

void NetServer::read()
{
	LOG_DEBUG << __FUNCTION__;
	int current_socket_number = socket_container.size() - 1;
	boost::asio::streambuf buffer;
	while(true) {
		boost::asio::read_until(*socket_container[current_socket_number], 
			buffer, '\n');
		std::istream is(&buffer);
		std::string line;
		std::getline(is, line);
		for (auto function : update_function_container) {
			function(line);
		}
		LOG_DEBUG << line;
	}
}

void NetServer::read_wrapper(NetServer *self)
{
	self->read();
}

bool NetServer::start()
{
	using namespace boost::asio;
	using namespace std;

	std::thread accept_thread(accept_wrapper, this);
	accept_thread.detach();
	LOG_DEBUG << "Server started!";
	return true;
}

void NetServer::addUpdateFunction(std::function<void (std::string&)> function)
{
	update_function_container.push_back(function);
}

bool NetServer::write(std::string& command) 
{
	boost::system::error_code ignored_error;
	for(auto socket : socket_container) {
		socket->write_some(boost::asio::buffer(command), ignored_error);
	}
	return true;
}

} // namespace