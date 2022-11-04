#pragma once
#include "afxdb.h"
class CSingleTon :
	public CDatabase
{
	static BOOL bInstanceFlag;
	static CSingleTon* instance;
	CSingleTon();
public:
	static CSingleTon* getInstance();
	BOOL OnConnectAllergyDetails(CString, CString);
	~CSingleTon();
};

