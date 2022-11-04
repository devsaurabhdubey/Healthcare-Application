
// Physician_ModuleDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "PictureWindow.h"

// CPhysician_ModuleDlg dialog
class CPhysicianModuleDlg : public CDialogEx
{
	// Construction
public:
	CPhysicianModuleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHYSICIAN_MODULE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	// Implementation
protected:
	HICON m_hIcon;
	CBrush m_brush;
	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedLogin();
	CString OnEncyrptPassword(CString);
	CEdit m_UsernameCtrl;
	CEdit m_PasswordCtrl;
	afx_msg void OnEnChangeUsername();
	afx_msg void OnEnChangePassword();
};
