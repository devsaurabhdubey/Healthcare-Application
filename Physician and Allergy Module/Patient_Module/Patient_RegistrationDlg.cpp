// Patient_RegistrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Patient_Module.h"
#include "Patient_RegistrationDlg.h"
#include "afxdialogex.h"
#include "Conversion.h"
#include <ctime>
#include <time.h>


// CPatient_RegistrationDlg dialog

IMPLEMENT_DYNAMIC(CPatient_RegistrationDlg, CDialog)

CPatient_RegistrationDlg::CPatient_RegistrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PatientRegistration, pParent)
	, m_sLastName(_T(""))
	, m_sFirstName(_T(""))
{
	m_sConnectionString = L"ODBC;DSN=localdb;Integrated Security=True;Connect Timeout=15";
	m_dataBase.Open(NULL, TRUE, TRUE, m_sConnectionString);
}

CPatient_RegistrationDlg::~CPatient_RegistrationDlg()
{
}

void CPatient_RegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_GenderCtrl);
	DDX_Control(pDX, IDC_COMBO2, m_EncounterCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateOfBirthCtrl);
	DDX_Text(pDX, IDC_EDIT2, m_sLastName);
	DDX_Text(pDX, IDC_FirstName, m_sFirstName);
	DDX_Control(pDX, IDC_Status, m_StatusCtrl);
}


BEGIN_MESSAGE_MAP(CPatient_RegistrationDlg, CDialog)
	ON_BN_CLICKED(IDREGISTER, &CPatient_RegistrationDlg::OnBnClickedRegister)
END_MESSAGE_MAP()


// CPatient_RegistrationDlg message handlers




void CPatient_RegistrationDlg::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	
	UpdateData(TRUE);
	m_tDate = CTime::GetCurrentTime();
	m_DateOfBirthCtrl.GetTime(m_tDate);
	CString sDate = m_tDate.Format("%Y-%m-%d");
	m_nGenderType = m_GenderCtrl.GetCurSel();
	m_nEncounterType = m_EncounterCtrl.GetCurSel();
	m_nStatusType = m_StatusCtrl.GetCurSel();
	if (m_nFirstNameLength == 0 && m_nLastNameLength == 0 && m_nEncounterType < 0 && m_nGenderType < 0 && m_nStatusType < 0)
	{
		::MessageBox(NULL, _T("Enter the details"), _T("Warning"), MB_ICONWARNING);
	}
	else
	{
		BOOL bValidateGender = ToValidatePatientGender();
		BOOL bValidateEncounterType = ToValidatePatientEncounterType();
		BOOL bValidateStatus = ToValidatePatientStatus();
		BOOL bValidateName = ToValidatePatientName();
		if (bValidateGender && bValidateEncounterType && bValidateStatus && bValidateName)
		{
			bool bMrn = ToGetPatientMrn();
			if (bMrn)
			{
				try
				{

					std::string sSqlString = "INSERT INTO Person_table VALUES ('" + ConvertCStringToString(m_sLastName) + "', '" + ConvertCStringToString(m_sFirstName) + "', '" + ConvertCStringToString(sDate) + "','" + ConvertCStringToString(m_sGender) + "', " + std::to_string(m_nStatusType) + ",'" + ConvertCStringToString(m_sMrn) + "','" + ConvertCStringToString(m_sEncounterType) + "')";
					m_dataBase.ExecuteSQL(ConvertStringToCString(sSqlString));
					::MessageBox(NULL, _T("Your MRN Number is ") + m_sMrn, _T("Please note the number"), MB_OK);
					EndDialog(0);
				}
				catch (CDBException* e)
				{
					OutputDebugString(e->m_strError);
				}
				m_dataBase.Close();
			}
		}
		else
		{
			::MessageBox(NULL, _T("Enter the details Properly"), _T("Warning"), MB_ICONWARNING);
		}
	}
}


BOOL CPatient_RegistrationDlg :: ToValidatePatientGender()
{
	if (m_nGenderType < 0)
	{
		::MessageBox(NULL, _T("Please Select Gender"), _T("Warning"), MB_ICONWARNING);
	}
	else if (m_nGenderType == 0)
	{
		m_sGender = _T("FEMALE");
	}
	else
	{
		m_sGender = _T("MALE");
	}
	return TRUE;
}

BOOL CPatient_RegistrationDlg::ToValidatePatientEncounterType()
{
	if (m_nEncounterType < 0)
	{
		::MessageBox(NULL, _T("Please Select Encounter type"), _T("Warning"), MB_ICONWARNING);
	}
	else if (m_nEncounterType == 0)
	{
		m_sEncounterType = _T("Inpatient");
	}
	else
	{
		m_sEncounterType = _T("Outpatient");
	}
	return TRUE;
}

BOOL CPatient_RegistrationDlg::ToValidatePatientStatus()
{
	if (m_nStatusType < 0)
	{
		::MessageBox(NULL, _T("Please Select Status"), _T("Warning"), MB_ICONWARNING);
	}
	else if (m_nStatusType == 0)
	{
		m_nStatusType = 1;
	}
	return TRUE;
}

BOOL CPatient_RegistrationDlg::ToValidatePatientName()
{
	bool bNameValidation = FALSE;
	m_nLastNameLength = m_sLastName.GetLength();
	if (m_nLastNameLength > 0)
	{
		for (int i = 0; i < m_nLastNameLength; i++)
		{
			if (!isalpha(m_sLastName[i]))
			{
				bNameValidation = TRUE;
				break;
			}
		}
		if (bNameValidation == TRUE)
		{
			::MessageBox(NULL, _T("Enter the characters only"), _T("Warning"), MB_ICONWARNING);
			bNameValidation = FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		::MessageBox(NULL, _T("Enter the Last Name Properly"), _T("Warning"), MB_ICONWARNING);
		return FALSE;
	}

	m_nFirstNameLength = m_sFirstName.GetLength();
	if (m_nFirstNameLength > 0)
	{
		for (int i = 0; i < m_nFirstNameLength; i++)
		{
			if (!isalpha(m_sFirstName[i]))
			{
				bNameValidation = TRUE;
				break;
			}
		}
		if (bNameValidation == TRUE)
		{
			::MessageBox(NULL, _T("Enter the characters only"), _T("Warning"), MB_ICONWARNING);
			bNameValidation = FALSE;
		}
		else
		{
			return TRUE;
		}

	}
	else
	{
		::MessageBox(NULL, _T("Enter the First Name Properly"), _T("Warning"), MB_ICONWARNING);
		return FALSE;

	}
}

BOOL CPatient_RegistrationDlg::ToGetPatientMrn()
{
	time_t Time = time(0);
	struct tm *ti = localtime(&Time);
	int nDay = ti->tm_mday;
	CString sDay;
	sDay.Format(_T("%d"), nDay);
	int nMonth = 1+ti->tm_mon;
	CString sMonth;
	sMonth.Format(_T("%d"), nMonth);
	int nYear = 1900+ti->tm_year;
	CString sYear;
	sYear.Format(_T("%d"), nYear);
	int nMin = 1 + ti->tm_min;
	CString sMin;
	sMin.Format(_T("%d"), nMin);
	int nHour = 1 + ti->tm_hour;
	CString sHour;
	sHour.Format(_T("%d"), nHour);
	int second = 1+ti->tm_sec;
	CString sSec;
	sSec.Format(_T("%d"), second);
	m_sMrn = sDay + sMonth + sYear + sHour + sMin + sSec;
	m_nMrn = _ttoi(m_sMrn);
	return TRUE;
}
