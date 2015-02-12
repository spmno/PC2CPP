#pragma once
#include <memory>
#include <boost/asio.hpp>


namespace mxnavi {

namespace bip = boost::asio::ip;

class NetReader
{
public:
	NetReader(void);
	~NetReader(void);
	void operator()(const bip::tcp::socket& reader);
private:
	//std::unique_ptr<const bip::tcp::socket> socket_pointer;
};

}