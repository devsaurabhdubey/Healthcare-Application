#include "stdafx.h"
#include "Singleton.h"
#include "odbcinst.h"
#include "afxdb.h"

BOOL CSingleton::bInstanceFlag = FALSE;
CSingleton* CSingleton::instance = NULL;


CSingleton::CSingleton()
{
}


CSingleton * CSingleton::getInstance()
{
	if (!bInstanceFlag)
	{
		instance = new CSingleton();
		bInstanceFlag = TRUE;
		CString sConnectionString = L"AddYourString";
		instance->Open(NULL, false, false, sConnectionString);
		return instance;
	}
	else
	{
		return instance;
	}
}

CSingleton::~CSingleton()
{
	bInstanceFlag = FALSE;
}
