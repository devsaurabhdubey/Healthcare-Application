#pragma once
#include "afxwin.h"


// CPhysician_RegistrationDlg dialog

class CPhysician_RegistrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPhysician_RegistrationDlg)

public:
	CPhysician_RegistrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPhysician_RegistrationDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Physician_Registration };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
public:
	void OnBnClickedRegister();
	CComboBox m_Position_control;
	CString m_sLastName;
	CString m_sFirstName;
	CString m_sUserName;
	CString m_sPassword;
	CString m_sConfirmPassword;
	BOOL ToValidatePhysicianPosition(int);
	BOOL ToValidatePhysicianLastName(int);
	BOOL ToValidatePhysicianUserName(int);
	BOOL ToValidatePhysicianFirstName(int);
	BOOL ToValidatePhysicianPassword();
	int m_nPosition;
	bool m_bValidation = FALSE;
	int m_nLastNameLength;
	int m_nFirstNameLength;
	int m_nUserNameLength;
	CString m_sPosition;
	CButton m_buttonCtrl;
	bool m_ToCheckValidate = FALSE;
	afx_msg void OnEnChangeConfirmPassword();
	CEdit m_ConfirmPasswordctrl;
	BOOL ToEncyrptPassword();
	CEdit m_PasswordCtrl;
	CEdit m_LastNameCtrl;
	CEdit m_FirstnameCtrl;
	CEdit m_UserNameCtrl;
};
