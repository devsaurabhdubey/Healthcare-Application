#pragma once
#include "afxwin.h"


// CPhysicianRegistrationDlg dialog

class CPhysicianRegistrationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPhysicianRegistrationDlg)

public:
	CPhysicianRegistrationDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~CPhysicianRegistrationDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHYSICIANREGISTREATION };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);

	BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg	void OnBnClickedRegister();
	CString ToValidatePhysicianPosition();
	CString ToValidatePhysicianLastName();
	CString ToValidatePhysicianFirstName();
	CString ToValidatePhysicianUserName();
	CString ToValidatePhysicianPassword();
	CString ToEncyrptPassword();
	CComboBox m_PositionCtrl;
	CBrush m_brush;
	CEdit m_LastNameCtrl;
	CEdit m_FirstNameCtrl;
	CEdit m_UserNameCtrl;
	CEdit m_PasswordCtrl;
	CEdit m_ConfirmPasswordCtrl;
	afx_msg void OnCbnSelchangePosition();
	CStatic m_Position;
	afx_msg void OnEnChangePhysicianlastname();
	CStatic m_LastName;
	afx_msg void OnEnChangeFirstname();
	afx_msg void OnEnChangePhysicianusername();
	afx_msg void OnEnChangePassword();
	CStatic m_FirstName;
	CStatic m_Username;
	CStatic m_Password;
	CStatic m_ConfmPassword;
	afx_msg void OnEnChangeConfirmpassword();
};
