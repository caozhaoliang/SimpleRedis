#ifndef __MULTIREDIS_HPP__
#define __MULTIREDIS_HPP__
#include <vector>
#include <hiredis/hiredis.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define DEFAULT_TIME_OUT_REDIS_CONNECT_SEC 		2
#define DEFAULT_TIME_OUT_REDIS_CONNECT_USEC 	0

using namespace std;


class multiRedis
{
public:
	multiRedis();
	multiRedis(string _ip,string _port);
	~multiRedis();
	bool redisInit(string _ip,string _port,struct timeval* _time);
	bool reconnect();
	bool getData(string strcmd, string& result );
	bool setData(string strcmd );
	bool execRedis(string strcmd, string& result);
private:
	bool connectRedis();
private:
	redisContext* 			m_redisCon;
	string 					m_ip;
	string					m_port;
	struct timeval*			m_timeOut;
};




#endif