// Patient_RegistrationDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Patient_Module.h"
#include "PatientRegistrationDlg.h"
#include "afxdialogex.h"
#include "Conversion.h"
#include <ctime>
#include <time.h>
#include "./PatientDetails.h"
#include "../Patient_Module/Singleton.h"

#pragma warning(disable : 4996)

IMPLEMENT_DYNAMIC(CPatientRegistrationDlg, CDialog)

CPatientRegistrationDlg::CPatientRegistrationDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_PatientRegistration, pParent)
{
}

CPatientRegistrationDlg::~CPatientRegistrationDlg()
{
}

//****OnInitDialog****
//purpose - this method will create the patient registration window and set the focus on patient first name
//argument - void
//return - boolean
//preconditions - none
//postconditions - none
BOOL CPatientRegistrationDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	CEdit* e = (CEdit*)GetDlgItem(IDC_FirstName);
	e->SetFocus();
	CWnd* pwnd = GetDlgItem(IDC_FN);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
	lf.lfWeight = 5000;
	pfont->CreateFontIndirect(&lf);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_LN);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_DB);
	pwnd->SetFont(pfont);			// TODO: Add extra initialization here
	pwnd = GetDlgItem(IDC_ET);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_SEX);
	pwnd->SetFont(pfont);
	pwnd = GetDlgItem(IDC_STAT);
	pwnd->SetFont(pfont);
	return FALSE;  // return TRUE  unless you set the focus to a control
}




void CPatientRegistrationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_Gender, m_GenderCtrl);
	DDX_Control(pDX, IDC_Encounter, m_EncounterCtrl);
	DDX_Control(pDX, IDC_DATETIMEPICKER1, m_DateOfBirthCtrl);
	DDX_Control(pDX, IDC_Status, m_StatusCtrl);
	DDX_Control(pDX, IDC_FirstName, m_FirstNameCtrl);
	DDX_Control(pDX, IDC_LastName, m_LastNameCtrl);
}


BEGIN_MESSAGE_MAP(CPatientRegistrationDlg, CDialog)
	ON_BN_CLICKED(IDREGISTER, &CPatientRegistrationDlg::OnBnClickedRegister)
	ON_NOTIFY(DTN_DATETIMECHANGE, IDC_DATETIMEPICKER1, &CPatientRegistrationDlg::OnDtnDatePicker)
	ON_EN_CHANGE(IDC_FirstName, &CPatientRegistrationDlg::OnEnChangeFirstname)
	ON_EN_CHANGE(IDC_LastName, &CPatientRegistrationDlg::OnEnChangeLastname)
	ON_CBN_SELCHANGE(IDC_Gender, &CPatientRegistrationDlg::OnCbnSelchangeGender)
	ON_CBN_SELCHANGE(IDC_Encounter, &CPatientRegistrationDlg::OnCbnSelchangeEncounter)
	ON_CBN_SELCHANGE(IDC_Status, &CPatientRegistrationDlg::OnCbnSelchangeStatus)
END_MESSAGE_MAP()


// CPatient_RegistrationDlg message handlers

//****OnBnClickedRegister****
//Purpose- This window will register the patient details
//Arguments - void
//Returns - void
//Preconditions- All the fields are mandatory
//Posiconditions- none
void CPatientRegistrationDlg::OnBnClickedRegister()
{
	// TODO: Add your control notification handler code here
	CSingLeton* st;
	st = CSingLeton::getInstance();

	UpdateData(TRUE);
	CTime tDate = CTime::GetCurrentTime();
	m_DateOfBirthCtrl.GetTime(tDate);
	CString sDate = tDate.Format("%Y-%m-%d");
	time_t Time = time(0);
	struct tm* ti = localtime(&Time);
	int nCuuretnDay = ti->tm_mday;
	int nCurrentMonth = 1 + ti->tm_mon;
	int nCurrentYear = 1900 + ti->tm_year;

	if (m_FirstNameCtrl.GetWindowTextLength() == 0 || m_LastNameCtrl.GetWindowTextLength() == 0 || m_GenderCtrl.GetCurSel() < 0 || m_EncounterCtrl.GetCurSel() < 0 || m_StatusCtrl.GetCurSel() < 0)
	{
		m_sMessage.LoadString(IDS_WARNINGMESSAGE);
		m_sCaption.LoadString(IDS_WARNINGCAPTION);
		::MessageBox(this->GetSafeHwnd(), m_sMessage, m_sCaption, MB_ICONWARNING);
	}
	else
	{
		if (OnValidatePatientFirstName() && OnValidatePatientLastName())
		{
			CString sGender;
			m_GenderCtrl.GetWindowText(sGender);
			CString sEncounterType;
			m_EncounterCtrl.GetWindowText(sEncounterType);
			CString  sStatus;
			m_StatusCtrl.GetWindowText(sStatus);
			CString sLastName;
			m_LastNameCtrl.GetWindowText(sLastName);
			CString sFirstName;
			m_FirstNameCtrl.GetWindowText(sFirstName);
			CString sMrn = OnGetPatientMrn();
			if (!sMrn.IsEmpty())
			{
				try
				{
					std::string sSqlString = "INSERT INTO Person_table VALUES ('" + ConvertCStringToString(sLastName) + "', '" + ConvertCStringToString(sFirstName) + "', '" + ConvertCStringToString(sDate) + "','" + ConvertCStringToString(sGender) + "', '" + ConvertCStringToString(sStatus) + "','" + ConvertCStringToString(sMrn) + "','" + ConvertCStringToString(sEncounterType) + "')";
					st->ExecuteSQL(ConvertStringToCString(sSqlString));
					m_sMessage.LoadString(IDS_PATIENTMRN);
					m_sCaption.LoadString(IDS_MRNNOTE);
					::MessageBox(this->GetSafeHwnd(), m_sMessage + _T(" ") + sMrn, m_sCaption, MB_OK);
					m_FirstNameCtrl.SetWindowText(_T(""));
					m_LastNameCtrl.SetWindowText(_T(""));
					m_StatusCtrl.SetCurSel(-1);
					m_EncounterCtrl.SetCurSel(-1);
					m_GenderCtrl.SetCurSel(-1);
					ResetDate(nCurrentYear, nCurrentMonth, nCuuretnDay);
				}
				catch (CDBException* e)
				{
					OutputDebugString(e->m_strError);
				}
			}
		}
	}
}


//****OnValidatePatientLastName****
//purpose - It will validate the lastname is filled or not and also check in last name should consist of only alphabtes
//arguments - none
//returns - boolean
//preconditions - none
//postconditions - none
BOOL CPatientRegistrationDlg::OnValidatePatientLastName()
{
	int nLastNameLength = m_LastNameCtrl.GetWindowTextLength();
	CString sLastName;
	m_LastNameCtrl.GetWindowText(sLastName);
	BOOL bNameValidation = FALSE;
	if (nLastNameLength > 0)
	{
		for (int i = 0; i < nLastNameLength; i++)
		{
			if (!isalpha(sLastName[i]))
			{
				bNameValidation = TRUE;
				break;
			}
		}
		if (bNameValidation == TRUE)
		{
			m_sMessage.LoadString(IDS_ALPHABETSWARNING);
			m_sCaption.LoadString(IDS_WARNINGCAPTION);
			::MessageBox(this->GetSafeHwnd(), m_sMessage, m_sCaption, MB_ICONWARNING);
			bNameValidation = FALSE;
			return FALSE;
		}
		else
		{
			return TRUE;
		}
	}
	else
	{
		m_sMessage.LoadString(IDS_LASTNAMEWARNING);
		m_sCaption.LoadString(IDS_WARNINGCAPTION);
		::MessageBox(this->GetSafeHwnd(), m_sMessage, m_sCaption, MB_ICONWARNING);
		return FALSE;
	}
}

//****OnValidatePatientFirstName****
//purpose - It will validate the firstname is filled or not and also check in first name should consist of only alphabtes
//arguments - none
//returns - boolean
//preconditions - none
//postconditions - none
BOOL CPatientRegistrationDlg::OnValidatePatientFirstName()
{
	int nFirstNameLength = m_FirstNameCtrl.GetWindowTextLength();
	CString sFirstName;
	m_FirstNameCtrl.GetWindowText(sFirstName);
	BOOL bNameValidation = FALSE;
	if (nFirstNameLength > 0)
	{
		for (int i = 0; i < nFirstNameLength; i++)
		{
			if (!isalpha(sFirstName[i]))
			{
				bNameValidation = TRUE;
				break;
			}
		}
		if (bNameValidation == TRUE)
		{
			m_sMessage.LoadString(IDS_ALPHABETSWARNING);
			m_sCaption.LoadString(IDS_WARNINGCAPTION);
			::MessageBox(this->GetSafeHwnd(), m_sMessage, m_sCaption, MB_ICONWARNING);
			bNameValidation = FALSE;
			return FALSE;
		}
		else
		{
			return TRUE;
		}

	}
	else
	{
		m_sMessage.LoadString(IDS_FIRSTNAMEWARNING);
		m_sCaption.LoadString(IDS_WARNINGCAPTION);
		::MessageBox(this->GetSafeHwnd(), m_sMessage, m_sCaption, MB_ICONWARNING);
		return FALSE;
	}
}

//****OnGetPatientMrn****
//purpose - this method will generate the MRN(Medical Record Number) of patient on the basis of the local date and time.
//arguments - none
//returns - CString MRN
//preconditions - none
//postconditions - none
CString CPatientRegistrationDlg::OnGetPatientMrn()
{
	CString sMrn;
	time_t Time = time(0);
	struct tm* ti = localtime(&Time);
	int nDay = ti->tm_mday;
	CString sDay;
	sDay.Format(_T("%d"), nDay);
	int nMonth = 1 + ti->tm_mon;
	CString sMonth;
	sMonth.Format(_T("%d"), nMonth);
	int nYear = 1900 + ti->tm_year;
	CString sYear;
	sYear.Format(_T("%d"), nYear);
	int nMin = 1 + ti->tm_min;
	CString sMin;
	sMin.Format(_T("%d"), nMin);
	int nHour = 1 + ti->tm_hour;
	CString sHour;
	sHour.Format(_T("%d"), nHour);
	int second = 1 + ti->tm_sec;
	CString sSec;
	sSec.Format(_T("%d"), second);
	sMrn = sDay + sMonth + sYear + sHour + sMin + sSec;
	return sMrn;
}

//****OnDtnDatePicker****
//purpose - this method will restrict the user to select future dates
//arguments - NMHDR, LRESULT
//returns - void
//preconditions - none
//postconditions - none
void CPatientRegistrationDlg::OnDtnDatePicker(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMDATETIMECHANGE pDTChange = reinterpret_cast<LPNMDATETIMECHANGE>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
	CTime tDate = CTime::GetCurrentTime();
	//tDate.operator>
	m_DateOfBirthCtrl.GetTime(tDate);
	CString date = tDate.Format("%Y-%m-%d");
	CString sSelectedDay = tDate.Format("%d");
	int day = _ttoi(sSelectedDay);
	CString sSelectedMonth = tDate.Format("%m");
	int month = _ttoi(sSelectedMonth);
	CString sSelectedYear = tDate.Format("%Y");
	int year = _ttoi(sSelectedYear);

	time_t Time = time(0);
	struct tm* ti = localtime(&Time);
	int nCuuretnDay = ti->tm_mday;
	int nCurrentMonth = 1 + ti->tm_mon;
	int nCurrentYear = 1900 + ti->tm_year;

	CWnd* pwnd = GetDlgItem(IDC_DB);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);
	CString sMessage;
	sMessage.LoadString(IDS_DATEWARNING);
	CString sCaption;
	sCaption.LoadString(IDS_WARNINGCAPTION);
	int nLength = date.GetLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Date Of Birth:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Date Of Birth*:"));
	}
	if (year > nCurrentYear)
	{
		::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
		ResetDate(nCurrentYear, nCurrentMonth, nCuuretnDay);
	}
	else
	{
		if (year == nCurrentYear && month > nCurrentMonth)
		{
			::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
			ResetDate(nCurrentYear, nCurrentMonth, nCuuretnDay);
		}
		else
		{
			if (day > nCuuretnDay && month == nCurrentMonth && year == nCurrentYear)
			{
				::MessageBox(NULL, sMessage, sCaption, MB_ICONWARNING);
				ResetDate(nCurrentYear, nCurrentMonth, nCuuretnDay);
			}
		}
	}
}
//****ResetDate****
//purpose - it will reset the date after patient's successfull registration
//arguments - integer
//returns - void
//precondition - none
//postcondition - none
void CPatientRegistrationDlg::ResetDate(int nCurrentYear, int nCurrentMonth, int nCuuretnDay)
{
	COleDateTime NewDate;
	NewDate.SetDate(nCurrentYear, nCurrentMonth, nCuuretnDay);
	m_DateOfBirthCtrl.SetTime(NewDate);
}

//****OnEnChangeFirstname****
//purpose - It will change the font of the FirstName label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPatientRegistrationDlg::OnEnChangeFirstname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_FN);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_FirstNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("First Name:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("First Name*:"));
	}
}

//****OnEnChangeLastname****
//purpose - It will change the font of the LastName label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPatientRegistrationDlg::OnEnChangeLastname()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_LN);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nLength = m_LastNameCtrl.GetWindowTextLength();
	if (nLength > 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Last Name:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Last Name*:"));
	}
}

//****OnCbnSelchangeGender****
//purpose - It will change the font of the Gender label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPatientRegistrationDlg::OnCbnSelchangeGender()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_SEX);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_GenderCtrl.GetWindowTextLength();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Sex:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Sex*:"));
	}
}

//****OnCbnSelchangeEncounter****
//purpose - It will change the font of the Encounter label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPatientRegistrationDlg::OnCbnSelchangeEncounter()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_ET);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_EncounterCtrl.GetWindowTextLength();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Encounter Type:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Encounter Type*:"));
	}
}

//****OnCbnSelchangeStatus****
//purpose - It will change the font of the status label
//arguments - none
//returns - none
//preconditions - none
//postconditions - none
void CPatientRegistrationDlg::OnCbnSelchangeStatus()
{
	// TODO: Add your control notification handler code here
	CWnd* pwnd = GetDlgItem(IDC_STAT);
	CFont* pfont = pwnd->GetFont();
	LOGFONT lf; pfont->GetLogFont(&lf);

	int nPosition = m_StatusCtrl.GetWindowTextLength();
	if (nPosition >= 0)
	{
		lf.lfWeight = 500;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Status:"));
	}
	else
	{
		lf.lfWeight = 5000;
		pfont->CreateFontIndirect(&lf);
		pwnd->SetFont(pfont);
		pwnd->SetWindowTextW(_T("Status*:"));
	}
}
