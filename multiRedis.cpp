# include "multiRedis.hpp"
# include <string> 
#include <sys/time.h>

int strIcmp(const char* p1, const char* p2 ){
	while (*p1) 
    { 
        char c1 = *p1; 
        char c2 = *p2; 

        if (c1 >= 'A' && c1 <= 'Z') 
        { 
            c1 += 'a' - 'A'; 
        } 
        if (c2 >= 'A' && c2 <= 'Z') 
        { 
            c2 += 'a' - 'A'; 
        } 
        if (c1 != c2) 
        { 
            return c1 - c2; 
        } 
        p1++; 
        p2++; 
    } 
    return *p1 - *p2; 
}

multiRedis::multiRedis(){

}

multiRedis::multiRedis(string _ip,string _port){
	m_ip = _ip;
	m_port = _port;
}

multiRedis::~multiRedis(){
	if( m_redisCon != NULL ) {
		redisFree(m_redisCon);
		m_redisCon = NULL;
	}
}


/*
 * 建立连接
 * 私有成员函数，仅在类内部使用
 */
bool multiRedis::connectRedis(){
	if( m_redisCon ) {
		return true;
	}

	m_redisCon = redisConnectWithTimeout(m_ip.c_str(),atoi(m_port.c_str()),*m_timeOut );
	if( m_redisCon == NULL || m_redisCon->err ) {
		if( m_redisCon ) {
			redisFree(m_redisCon);
			m_redisCon = NULL;
		}
		return false;
	}
	return true;
}
/*
 * 初始化redis并建立连接
 */
bool multiRedis::redisInit(string _ip,string _port,struct timeval* _time){
	m_ip = _ip;
	m_port = _port;
	m_timeOut = _time;
	// m_timeOut = { DEFAULT_TIME_OUT_REDIS_CONNECT_SEC,DEFAULT_TIME_OUT_REDIS_CONNECT_USEC};
	return connectRedis();
}


/*
 * 执行命令 返回结果
 */
bool multiRedis::execRedis(string strcmd, string& result){

	bool bRet = false;
	if( m_redisCon == NULL) {
		return bRet;
	}

	redisReply *reply = NULL;
	cout << "execRedis 11 " << m_redisCon <<" strcmd :" << strcmd <<endl;
	reply = (redisReply*)redisCommand(m_redisCon,strcmd.c_str());
	if( NULL == reply) {
		// redisFree(m_redisCon);
		// m_redisCon = NULL;
		cout << "execRedis 22"<<endl;
		// connectRedis();
		return bRet;
	}
	if( REDIS_REPLY_STRING == reply->type ) {
		result = reply->str;
		bRet = true;
	}else if(REDIS_REPLY_ARRAY == reply->type) {
		
	}else if(REDIS_REPLY_NIL == reply->type){

    }else if(REDIS_REPLY_ERROR == reply->type) {

    }else if(REDIS_REPLY_STATUS == reply->type ) {
		// if( strIcmp(reply->str, "OK") == 0 ) {
			bRet = true;
		// }
	}else if(REDIS_REPLY_INTEGER == reply->type) {
		if(reply->integer == 1) {
			bRet = true;
		}
	}
	cout << "execRedis 33"<<endl;
	freeReplyObject(reply);
	return bRet;
}

/*
 * 执行查询命令获取数据
 */
bool multiRedis::getData(string strcmd, string& result ){
	if( strcmd.empty() || strcmd.length() < 5 ) {
		return false;
	}
	bool err = execRedis(strcmd, result);
	return err;
}

/*
 * 插入数据
 */
bool multiRedis::setData(string strcmd) {
	if( strcmd.empty() || strcmd.length() < 5 ) {
		return false;
	}
	string result;
	bool err = execRedis(strcmd, result);
	return err ;
}

