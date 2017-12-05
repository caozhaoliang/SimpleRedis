#include <iostream>
#include <hiredis/hiredis.h>
#include <stdlib.h>
#include <sys/time.h>


using namespace std;


int main()
{
	struct timeval _time;
	_time.tv_sec = 2;
	_time.tv_usec = 0;

	redisContext* c;
	c = redisConnectWithTimeout("127.0.0.1",6379,_time);
	if( NULL == c ) {
		cout << " redisConnectWithTimeout err "<< endl;
		return -1;
	}
	redisReply* reply = NULL;
	reply = (redisReply*)redisCommand(c,"SETEX test_key_1 60 value_1");
	if( NULL == reply ) {
		cout << "redisCommand err" <<endl;
		return -1;
	}
	cout << "reply->type:"<< reply->type <<",reply->str:" << reply->str<<endl;
	redisFree(c);
	freeReplyObject(reply);

	return 0; 

}



