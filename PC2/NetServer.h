#ifndef _PC2_NETSERVER_H_
#define _PC2_NETSERVER_H_

#include <vector>
#include <thread>
#include <functional>
#include <memory>
#include <string>
#include <boost/asio.hpp>
#include <boost/noncopyable.hpp>
#include "Util.h"


namespace mxnavi {

class NetServer : boost::noncopyable
{
public:
	~NetServer(void);
	bool start();
	void accept();
	static void accept_wrapper(NetServer* self);
	void read();
	static void read_wrapper(NetServer *self);
	bool write(std::string& command);
	void addUpdateFunction(std::function<void (std::string&)> function);
	static NetServer& get_instance()
	{
		static NetServer net_server;
		return net_server;
	}
private:
	NetServer(void);
	std::vector<std::shared_ptr<boost::asio::ip::tcp::socket> > socket_container;
	std::thread accept_thread;
	std::vector<std::thread> read_thread_container;
	std::vector<std::function<void (std::string&)> > update_function_container; 
};

}

#endif
