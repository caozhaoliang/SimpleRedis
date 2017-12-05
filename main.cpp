#include <iostream>
#include "multiRedis.hpp"
#include <pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

// void* handle(void* arg) {
// 	multiRedis mRedis;
// 	if(! mRedis.redisInit(string("127.0.0.1"),string("6379"))) {
// 		exit(-1);
// 	}

// 	int i = 0;
// 	char cmd[32] = {0};
// 	while(1){
// 		memset(cmd,0,sizeof(cmd));
// 		snprintf(cmd,sizeof(cmd), "SETEX test_key_%d 60 value_%d ",i,i++);
// 		mRedis.setData(string(cmd));
// 		sleep(1);
// 	}
// 	exit(-1);
// }


int main()
{
	multiRedis mRedis;
	struct timeval _time;
	_time.tv_sec = 2;
	_time.tv_usec = 0;
	if( mRedis.redisInit(string("127.0.0.1"),string("6379"), &_time ) ){
		cout << "init succ"<<endl;
	}else{
		cout << "init err"<<endl;
	}
	if( mRedis.setData("SETEX test_key_1 60 value_1") ){

		cout << "setData succ"<<endl;
	}else{
		cout << "setData err"<<endl;
	}


	// pthread_t pid[1];
	// for (int i = 0; i < 1; ++i){
	// 	pthread_create(&pid[i],NULL, handle, NULL);
	// }

	// for (int i = 0; i < 1; ++i) {
	// 	pthread_join(pid[i],NULL);
	// }



	return 0;

}

