
// Admin_ModuleDlg.h : header file
//

#pragma once
#include "afxwin.h"
#include "afxcmn.h"


// CAdmin_ModuleDlg dialog
class CAdmin_ModuleDlg : public CDialogEx
{
// Construction
public:
	CAdmin_ModuleDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ADMIN_MODULE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	virtual HBRUSH OnCtlColor(CDC * pDC, CWnd * pWnd, UINT nCtlColor);

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
	CEdit m_AdminUserNameCtrl;
	CEdit m_AdminPasswordCtrl;
	afx_msg void OnEnChangeAdminpassword();
	
	CStatic staticUsername;
	CStatic staticPassword;
	afx_msg void OnEnChangeAdminusername();
	afx_msg void OnBnClickedClosebtn();
//	afx_msg void OnDropdownClosebtn(NMHDR* pNMHDR, LRESULT* pResult);
};
