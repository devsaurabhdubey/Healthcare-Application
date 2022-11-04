
#pragma once
#include "afxwin.h"

#define exportConnection _declspec(dllexport)
class exportConnection CConnection
{
public:
	CConnection();
	~CConnection();
	BOOL Create();
};

