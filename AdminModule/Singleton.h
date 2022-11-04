#pragma once
#include "afxdb.h"
class CSingleton :
	public CDatabase
{
private:
	static BOOL bInstanceFlag;
	static CSingleton *instance;
	CSingleton();
public:
	static CSingleton* getInstance();
	~CSingleton();
};

