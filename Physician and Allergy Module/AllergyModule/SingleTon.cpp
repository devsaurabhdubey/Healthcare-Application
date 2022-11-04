#include "stdafx.h"
#include "SingleTon.h"


BOOL CSingleTon::bInstanceFlag = FALSE;
CSingleTon* CSingleTon::instance = NULL;


CSingleTon::CSingleTon()
{
}

//****getInstance****
//purpose - it will allow to create only one object of the class to connect the database
//arguments - none
//returns - CSingleTon *
//precondition - none
//postcondition - none
CSingleTon* CSingleTon::getInstance()
{
	if (!bInstanceFlag)
	{
		CString sConnectionString = L"Driver={Microsoft Access Driver (*.mdb)};dbq=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal\\CernerDb.mdb;defaultdir=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal;driverid=25;fil=MS Access;filedsn=C:\\Users\\SD090047\\OneDrive - Cerner Corporation\\Documents\\DevCenterFinal\\CernerDb.mdb.dsn;pagetimeout=5;uid=admin;usercommitsync=Yes";
		instance = new CSingleTon();
		bInstanceFlag = TRUE;
		instance->Open(NULL, false, false, sConnectionString);
		return instance;
	}
	else
	{
		return instance;
	}
}

BOOL CSingleTon::OnConnectAllergyDetails(CString, CString)
{
	return 0;
}


CSingleTon::~CSingleTon()
{
	bInstanceFlag = FALSE;
}
