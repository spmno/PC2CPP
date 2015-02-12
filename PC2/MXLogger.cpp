#include "stdafx.h"
#include "MXLogger.h"

#include <iostream>
#include <string>

#include <boost/filesystem.hpp>


#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/detail/format.hpp>
#include <boost/log/detail/thread_id.hpp>



namespace logging = boost::log;
namespace src = boost::log::sources;
namespace keywords = boost::log::keywords;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;

BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(my_logger, src::logger_mt)
boost::log::sources::severity_logger<boost::log::trivial::severity_level > MXLogger::s_slg;

MXLogger::MXLogger()
{

}

MXLogger::~MXLogger(void)
{
 
}

void MXLogger::Init(const string & dir)
{
  if (boost::filesystem::exists(dir) == false)
  {
    boost::filesystem::create_directories(dir);
  }
  
  auto pSink = logging::add_file_log
  (
      keywords::open_mode = std::ios::app,
      keywords::file_name = dir + "/%Y%m%d.log",
      keywords::rotation_size = 10 * 1024 * 1024,
      keywords::time_based_rotation = sinks::file::rotation_at_time_point(0, 0, 0), 
      //keywords::format = "[%TimeStamp% %ThreadID%]: %Message%"
      keywords::format =
      (
        expr::stream
        << "[" <<expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d %H:%M:%S.%f")
        << " " << expr::attr< boost::log::aux::thread::id >("ThreadID")
        << " " << logging::trivial::severity
        << "] " << expr::smessage
      )
  );
  
  // �����д��� ������ʵʱ�İ���־д��ȥ, ���ǵȴ�����������,���߳��������˳�ʱд��,�������ĺô��Ǽ���IO����.���Ч��,  ���������ﲻ��Ҫ��. ��Ϊ�ҵĳ�����ܻ��쳣�˳�.
  pSink->locked_backend()->auto_flush(true);//ʹ��־ʵʱ����
  //pSink->imbue(std::locale("zh_CN.UTF-8")); // ���ػ� 
  logging::add_common_attributes();
}
