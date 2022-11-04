#pragma once
#include "afxwin.h"
#include "afxdtctl.h"


// CPatient_RegistrationDlg dialog


#define exportRegistration _declspec(dllexport)


class exportRegistration CPatientRegistrationDlg : public CDialog
{
	DECLARE_DYNAMIC(CPatientRegistrationDlg)

public:
	CPatientRegistrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPatientRegistrationDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PatientRegistration };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedRegister();
	afx_msg void OnDtnDatePicker(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEnChangeFirstname();
	afx_msg void OnEnChangeLastname();
	afx_msg void OnCbnSelchangeGender();
	afx_msg void OnCbnSelchangeEncounter();
	afx_msg void OnCbnSelchangeStatus();
	void ResetDate(int nCurrentYear, int nCurrentMonth, int nCuuretnDay);
	CString OnGetPatientMrn();
	BOOL OnValidatePatientLastName();
	BOOL OnValidatePatientFirstName();
	CEdit m_FirstNameCtrl;
	CEdit m_LastNameCtrl;
	CString m_sMessage;
	CString m_sCaption;
	CComboBox m_StatusCtrl;
	CComboBox m_GenderCtrl;
	CComboBox m_EncounterCtrl;
	CDateTimeCtrl m_DateOfBirthCtrl;
	int m_nStatus;
};
