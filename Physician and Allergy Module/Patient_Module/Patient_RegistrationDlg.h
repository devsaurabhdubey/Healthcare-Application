#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CPatient_RegistrationDlg dialog


#define exportRegistration _declspec(dllexport)


class exportRegistration CPatient_RegistrationDlg : public CDialog
{
	DECLARE_DYNAMIC(CPatient_RegistrationDlg)

public:
	CPatient_RegistrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatient_RegistrationDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PatientRegistration };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_GenderCtrl;
	CComboBox m_EncounterCtrl;
	CDateTimeCtrl m_DateOfBirthCtrl;
	CString m_sLastName;
	CString m_sFirstName;
	int m_nGenderType;
	CString m_sGender;
	afx_msg void OnBnClickedRegister();
	BOOL ToGetPatientMrn();
	BOOL ToValidatePatientGender();
	BOOL ToValidatePatientEncounterType();
	BOOL ToValidatePatientStatus();
	BOOL ToValidatePatientName();
	CTime m_tDate;
	CComboBox m_StatusCtrl;
	int m_nEncounterType;
	int m_nStatusType;
	CString m_sEncounterType;
	int m_nStatus;
	int m_nMrn;
	int m_nLastNameLength;
	int m_nFirstNameLength;
	CDatabase m_dataBase;
	CString m_sSqlString;
	CString m_sConnectionString;
	int m_nCount = 0;
	CString m_sMrn;
};
