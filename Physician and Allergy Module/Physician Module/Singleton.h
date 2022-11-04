#pragma once
#include "afxdb.h"
#define exportSingleton _declspec(dllexport)
class exportSingleton CSingleton :
	public CDatabase
{
private:
	static BOOL bInstanceFlag;
	static CSingleton* instance;
	CSingleton();
public:
	static CSingleton* getInstance();
	BOOL PhysicianDb(CString, CString);
	~CSingleton();
};

