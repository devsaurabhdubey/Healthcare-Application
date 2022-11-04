
// Physician_ModuleDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Physician_Module.h"
#include "Physician_ModuleDlg.h"
#include "afxdialogex.h"
#include "odbcinst.h"
#include "afxdb.h"
#include "../Patient_Module/Connection.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPhysician_ModuleDlg dialog



CPhysician_ModuleDlg::CPhysician_ModuleDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_PHYSICIAN_MODULE_DIALOG, pParent)
	, m_sUsername(_T(""))
	, m_sPassword(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhysician_ModuleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_sUsername);
	DDX_Text(pDX, IDC_EDIT2, m_sPassword);
	DDX_Control(pDX, IDC_EDIT1, m_sUserEdit);
	DDX_Control(pDX, IDC_EDIT2, m_sPasswordClean);
}

BEGIN_MESSAGE_MAP(CPhysician_ModuleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDLOGIN, &CPhysician_ModuleDlg::OnBnClickedLogin)
END_MESSAGE_MAP()


// CPhysician_ModuleDlg message handlers

BOOL CPhysician_ModuleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhysician_ModuleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPhysician_ModuleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPhysician_ModuleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CPhysician_ModuleDlg::OnBnClickedLogin()
{
	// TODO: Add your control notification handler code here
	CDatabase dataBase;
	CString sSqlString;
	CString sConnectionString = L"ODBC;DSN=localdb;Integrated Security=True;Connect Timeout=15";
	dataBase.Open(NULL, TRUE, TRUE, sConnectionString);
	UpdateData(TRUE);
	try
	{
		CRecordset recest(&dataBase);
		sSqlString = L"SELECT * from PRSNL_table where UserName='" + m_sUsername + L"' AND Password='" + m_sPassword + L"'";
		recest.Open(CRecordset::forwardOnly, sSqlString, CRecordset::readOnly);
		while (!recest.IsEOF())
		{
			m_nRowCount++;
			recest.MoveNext();
		}
		if (m_nRowCount > 0)
		{
			::MessageBox(NULL, _T("Authorized"), _T("Success"), MB_OK);
			m_nRowCount = 0;
			dataBase.Close();
			m_sUserEdit.SetWindowTextW(_T(""));
			m_sPasswordClean.SetWindowTextW(_T(""));
			CConnection con;
			con.Create();
			EndDialog(0);
		}
		else
		{
			::MessageBox(NULL, _T("Unauthorized"), _T("Error"), MB_ICONWARNING);
		}
	}
	catch (CDBException* e)
	{
		OutputDebugString(e->m_strError);
	}
}
