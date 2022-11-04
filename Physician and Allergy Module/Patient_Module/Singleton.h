#pragma once
#include "afxdb.h"
class CSingLeton :
	public CDatabase
{
private:
	static BOOL bInstanceFlag;
	static CSingLeton* instance;
	CSingLeton();
public:
	static CSingLeton* getInstance();
	BOOL PatientDb(CString, CString);
	~CSingLeton();
};

