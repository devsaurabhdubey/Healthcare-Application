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
		CString sConnectionString = L"Driver={Microsoft Access Driver (*.mdb)};dbq=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal\\CernerDb.mdb;defaultdir=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal;driverid=25;fil=MS Access;filedsn=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal\\CernerDb.mdb.dsn;pagetimeout=5;uid=admin;usercommitsync=Yes";
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
