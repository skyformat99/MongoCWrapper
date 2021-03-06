#ifndef MongoClient_h__
#define MongoClient_h__

#ifdef _MSC_VER
#pragma warning(disable: 4324)
#endif // _MSC_VER

#include <string>
#include <mongoc.h>
#include "MongoAuto.h"

namespace MongoClib
{	
	// !! ONLY TryPopClient & PushClient are THREAD-SAFE

	// init mongo c driver. NOT thread safe. call this in single-threaded phase
	// locname is used in UNICODE <-> ANSI convention, "" to ignore, but conversion may fail.
	// unsigned toXXXMS is time-out milliseconds for xxx, <= 0 is for default
	// default: toConnectMS 10secs, toSelectMS 30secs, toSocketMS mins
	// remember to create index after init if necessary.
	int Init(const std::wstring& srv, const std::wstring& db, const std::string& locname,
		int toConnectMS = 0, int toSelectMS = 0, int toSocketMS = 0,
		unsigned short port = 27017);
	void Cleanup(void);

	const char* GetDbName(void);

	// CAUTION: this will remove entire database from server.
	bool DropDataBase(void);
	
	// thread safe. DO NOT destroy client from PopClient, push-back when used.
	// return NULL when no client available.
	mongoc_client_t* TryPopClient(void);
	void PushClient(mongoc_client_t* client);

	
} // MongoClib

#endif // MongoClient_h__
