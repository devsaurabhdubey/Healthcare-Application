
// Physician_ModuleDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CPhysician_ModuleDlg dialog
class CPhysician_ModuleDlg : public CDialogEx
{
// Construction
public:
	CPhysician_ModuleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHYSICIAN_MODULE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_sUsername;
	CString m_sPassword;
	int m_nRowCount;
	afx_msg void OnBnClickedLogin();
	CEdit m_sUserEdit;
	CEdit m_sPasswordClean;
};
