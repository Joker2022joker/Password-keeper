
// PassManagerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "PassManagerDlg.h"
#include "afxdialogex.h"
#include "InputPassDlg.h"
#include "BakDlg.h"
#include "OptionDlg.h"
#include "DetailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

static UINT indicators[] = {
	IDS_STRBAR
};

const char * Author = "http://www.leavesongs.com";
const char * HelpSite = "http://pk.leavesongs.com";

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CPassManagerDlg �Ի���

CPassManagerDlg::CPassManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPassManagerDlg::IDD, pParent)
	, m_strSearch(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_MAINICON);
	m_sql = NULL;
	m_addPassDlg = NULL;
	m_fastDlg = NULL;
	m_SearchDlg = NULL;
	m_bEdit = false;
}

void CPassManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RELIST, m_listShow);
	DDX_Text(pDX, IDC_EDITWORD, m_strSearch);
	DDX_Control(pDX, IDC_EDITWORD, m_EditSearch);
}

BEGIN_MESSAGE_MAP(CPassManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(MENU_NEWBOOK, &CPassManagerDlg::OnNewbook)
	ON_COMMAND(MENU_OPENBOOK, &CPassManagerDlg::OnOpenbook)
//	ON_WM_SIZE()
	ON_COMMAND(MENU_QUIT, &CPassManagerDlg::OnQuit)
	ON_NOTIFY(NM_RCLICK, IDC_RELIST, &CPassManagerDlg::OnNMRClickRelist)
	ON_COMMAND(MENU_ADD, &CPassManagerDlg::OnAdd)
	ON_BN_CLICKED(IDC_BTNSEARCH, &CPassManagerDlg::OnBnClickedBtnsearch)
	ON_COMMAND(ID_POPCREATE, &CPassManagerDlg::OnPopcreate)
	ON_COMMAND(ID_POPOPEN, &CPassManagerDlg::OnPopopen)
	ON_COMMAND(ID_MPOPADD, &CPassManagerDlg::OnMpopadd)
	ON_COMMAND(ID_MPOPCOPY, &CPassManagerDlg::OnMpopcopy)
	ON_COMMAND(ID_CLOSEBOOK, &CPassManagerDlg::OnClosebook)
	ON_MESSAGE(WM_TRAYICON_MOUSEOVER, OnTrayCallBackMsg)
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_COMMAND(MENU_FAST, &CPassManagerDlg::OnFast)
	ON_COMMAND(ID_TRAY_QUIT, &CPassManagerDlg::OnTrayQuit)
	ON_COMMAND(MENU_QUERY, &CPassManagerDlg::OnQuery)
	ON_COMMAND(ID_TRAY_SEARCH, &CPassManagerDlg::OnTraySearch)
	ON_COMMAND(ID_TRAY_OPEN, &CPassManagerDlg::OnTrayOpen)
	ON_COMMAND(MENU_REPASS, &CPassManagerDlg::OnRepass)
	ON_COMMAND(MENU_BAK, &CPassManagerDlg::OnBak)
	ON_COMMAND(ID_MPOPEDIT, &CPassManagerDlg::OnMpopedit)
	ON_COMMAND(ID_MPOPDEL, &CPassManagerDlg::OnMpopdel)
	ON_COMMAND(MENU_ABOUT, &CPassManagerDlg::OnAbout)
	ON_WM_DROPFILES()
	ON_COMMAND(MENU_OPTION, &CPassManagerDlg::OnOption)
	ON_NOTIFY(NM_DBLCLK, IDC_RELIST, &CPassManagerDlg::OnNMDblclkRelist)
	ON_COMMAND(MENU_HELP, &CPassManagerDlg::OnHelp)
	ON_COMMAND(MENU_LEAVESONGS, &CPassManagerDlg::OnLeavesongs)
END_MESSAGE_MAP()


// CPassManagerDlg ��Ϣ�������

BOOL CPassManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	//SetWindowSkin( this->m_hWnd, "Dialog" ); 
	//SetDialogSkin( "Dialog" );
	mainMenu = LoadMenu(NULL, MAKEINTRESOURCE(IDR_MENUMAIN));
	::SetMenu(this->m_hWnd, mainMenu);
	::DrawMenuBar(this->m_hWnd);

	CRect rect;
	m_bar.Create(this); //We create the status bar  
	m_bar.SetIndicators(indicators,1);
	GetClientRect(&rect); 
	m_bar.SetPaneInfo(0,IDS_STRBAR,SBPS_NORMAL,rect.Width());
	RepositionBars(AFX_IDW_CONTROLBAR_FIRST,AFX_IDW_CONTROLBAR_LAST,IDS_STRBAR);

	//��ʼ���б�
	InitList();

	//��������ͼ��
	TrayMyIcon(true);
	m_bShow = true;

	//��ʼ�������ļ���ע���ȼ�
	CreateDefaultIniFile();

	//�Ƿ�����ʾ���������Ի���
	m_bSearchShow = false;

	//��������в���������в����Ļ�����ò���������Ҫ�򿪵����뱾�ļ�
	CString strCmd = GetCommandLine();
	//MessageBox(strCmd);
	BOOL isExists = AfxExtractSubString(m_dbPath, strCmd, 1, ' ');
	m_dbPath.Remove('"');
	if (isExists && !m_dbPath.IsEmpty() && PathFileExists(m_dbPath))
	{
		CInputPassDlg passDlg(this);
		INT_PTR rt = passDlg.DoModal();
		if (!rt)
		{
			return TRUE;
		}
		CString strPass = passDlg.getPassword();
		OpenPassBook(m_dbPath, strPass);
	}

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CPassManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CPassManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CPassManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//������½����뱾���󴥷�
void CPassManagerDlg::OnNewbook()
{
	if (m_sql)
	{
		if (MessageBox("�رյ�ǰ���뱾�����½�һ���µ����뱾��", "����", MB_OKCANCEL) == IDCANCEL)
		{
			return ;
		}else{
			OnClosebook();
		}
	}
	TCHAR szNowDir[MAX_PATH + 10];
	GetCurrentDirectory(MAX_PATH + 10, szNowDir);
	_tcscat_s(szNowDir, MAX_PATH + 9, "\\me.pas");
	CString strEditName, strPass;
	CFileDialog dlg(FALSE, "pas", szNowDir, OFN_EXPLORER | OFN_OVERWRITEPROMPT, "Password Book (*.pas)|*.pas||", this, 0, FALSE);
	CInputPassDlg passDlg(this);
	INT_PTR rt = dlg.DoModal();
	if (IDOK != rt)
	{
		return ;
	}
	rt = passDlg.DoModal();
	if (!rt)
	{
		return ;
	}
	m_dbPath = dlg.GetPathName();
	strPass = passDlg.getPassword();
	m_sql = new doSql();
	if(! m_sql->InitCreate(m_dbPath.GetBuffer(), strPass.GetBuffer(), strPass.GetLength())){
		int errNo;
		CString str;
		errNo = m_sql->getErrNo();
		str.Format("����������룺%d", errNo);
		MessageBox(str);
	}else{
		setStatusBar("�½����뱾�ɹ�");
		EnableMenus();
		clearListEdit();
	}
	m_dbPath.ReleaseBuffer();
	strPass.ReleaseBuffer();
}

//����������뱾��ʱ����
void CPassManagerDlg::OnOpenbook()
{
	if (m_sql)
	{
		if (MessageBox("�رյ�ǰ���뱾��������һ��һ�����뱾��", "����", MB_OKCANCEL) == IDCANCEL)
		{
			return ;
		}else{
			OnClosebook();
		}
	}
	// TODO: �ڴ���������������
	TCHAR szNowDir[MAX_PATH + 10];
	CString strEditName, strPass, strNowDir;
	GetModuleFileName(NULL, szNowDir, MAX_PATH + 10);
	strNowDir = szNowDir;
	strNowDir = strNowDir.Left(strNowDir.ReverseFind('\\'));
	strNowDir += "\\me.pas";
	CFileDialog dlg(TRUE, "pas", strNowDir, OFN_EXPLORER | OFN_OVERWRITEPROMPT, "Password Book (*.pas)|*.pas||", this, 0, FALSE);
	CInputPassDlg passDlg(this);
	INT_PTR rt = dlg.DoModal();
	if (IDOK != rt)
	{
		return ;
	}
	rt = passDlg.DoModal();
	if (!rt)
	{
		return ;
	}
	m_dbPath = dlg.GetPathName();
	strPass = passDlg.getPassword();
	OpenPassBook(m_dbPath, strPass);
}

void CPassManagerDlg::InitList()
{
	CRect rect;
	GetWindowRect(&rect);
	int Width = rect.Width() - 2;
	int Height = rect.Height();
	m_listShow.InsertColumn(0, "username", LVCFMT_LEFT, Width / 6);
	m_listShow.InsertColumn(1, "password", LVCFMT_LEFT, Width / 6);
	m_listShow.InsertColumn(2, "remarks", LVCFMT_LEFT, int(Width / 2.5));
	m_listShow.InsertColumn(3, "url", LVCFMT_LEFT, Width - int(Width/3) - int(Width / 2.5) - 10);
	m_listShow.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	//��ʼ���Ҽ��˵�
	m_PopMenu.LoadMenu(IDR_MENUPASSPOP);
}

void CPassManagerDlg::setStatusBar(CString str)
{
	m_bar.SetPaneText(0, str);

}

//����˳�ʱ����
void CPassManagerDlg::OnQuit()
{
	// TODO: �ڴ���������������
	SendMessage(WM_CLOSE);
}

//�û����б����Ҽ�
void CPassManagerDlg::OnNMRClickRelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CPoint mousept;
	GetCursorPos(&mousept);
	CMenu * pMenu = NULL;
	pMenu = m_PopMenu.GetSubMenu(0);
	if (m_listShow.GetSelectedCount() > 0)
	{
		EnableMenu(&m_PopMenu, 0, ID_MPOPCOPY);
		EnableMenu(&m_PopMenu, 0, ID_MPOPDEL);
		EnableMenu(&m_PopMenu, 0, ID_MPOPEDIT);
	}
	else
	{
		EnableMenu(&m_PopMenu, 0, ID_MPOPCOPY, FALSE);
		EnableMenu(&m_PopMenu, 0, ID_MPOPDEL, FALSE);
		EnableMenu(&m_PopMenu, 0, ID_MPOPEDIT, FALSE);
	}
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, mousept.x, mousept.y, this);
	*pResult = 0;
}

void CPassManagerDlg::EnableMenus()
{
	CMenu * pMenu = GetMenu();
	EnableMenu(pMenu, 0, ID_CLOSEBOOK);
	EnableMenu(pMenu, 1, MENU_ADD);
	EnableMenu(pMenu, 1, MENU_QUERY);
	EnableDlg(IDC_BTNSEARCH);
	EnableMenu(&m_PopMenu, 0, ID_MPOPADD);
	EnableMenu(&m_PopMenu, 0, MENU_REPASS);
	EnableMenu(pMenu, 2, MENU_REPASS);
	EnableMenu(pMenu, 1, MENU_BAK);
}

void CPassManagerDlg::DisableMenus()
{
	CMenu * pMenu = GetMenu();
	EnableMenu(pMenu, 0, ID_CLOSEBOOK, FALSE);
	EnableMenu(pMenu, 1, MENU_ADD, FALSE);
	EnableMenu(pMenu, 1, MENU_QUERY, FALSE);
	EnableDlg(IDC_BTNSEARCH, FALSE);
	EnableMenu(&m_PopMenu, 0, ID_MPOPADD, FALSE);
	EnableMenu(&m_PopMenu, 0, MENU_REPASS, FALSE);
	EnableMenu(pMenu, 2, MENU_REPASS, FALSE);
	EnableMenu(pMenu, 1, MENU_BAK, FALSE);
}

void CPassManagerDlg::EnableDlg(int name, BOOL bEnable)
{
	CWnd * pWin = GetDlgItem(name);
	pWin->EnableWindow(bEnable);
}

void CPassManagerDlg::EnableMenu(CMenu * pMenu, int refer, UINT name, BOOL bEnable)
{
	if (bEnable)
	{
		pMenu->GetSubMenu(refer)->EnableMenuItem(name, MF_BYCOMMAND | MF_ENABLED);
	}else{
		pMenu->GetSubMenu(refer)->EnableMenuItem(name, MF_BYCOMMAND | MF_DISABLED);
	}
}

//���ӻ��޸�һ������ʱ����
//����֮ǰ����
void CPassManagerDlg::OnAdd()
{
	// TODO: �ڴ���������������
	if (!m_addPassDlg || !m_addPassDlg->m_hWnd)
	{
		m_addPassDlg = new CAddPassDlg(m_sql, this);
		m_addPassDlg->Create(IDD_DLGADD);
	}
	m_addPassDlg->m_bEdit = m_bEdit;
	if (m_bEdit) m_addPassDlg->EditPid = m_IdArr.GetAt(m_listShow.GetSelectionMark());
	m_addPassDlg->ShowWindow(SW_SHOWNORMAL);
}

void CPassManagerDlg::OnSonDlgClose(CString strStatus)
{
	setStatusBar(strStatus);

}

//���������ť
void CPassManagerDlg::OnBnClickedBtnsearch()
{
	m_listShow.DeleteAllItems();
	m_IdArr.RemoveAll();
	InfoRow * info = NULL;
	UpdateData(TRUE);
	int count = m_sql->SearchPass(m_strSearch.GetBuffer(), &info);
	for (int i = 0 ; i < count ; i++)
	{
		m_listShow.InsertItem(i,info[i].szUser);
		m_listShow.SetItemText(i, 1, info[i].szPass);
		m_listShow.SetItemText(i, 2, info[i].szRemark);
		m_listShow.SetItemText(i, 3, info[i].szUrl);
		m_IdArr.Add(info[i].pid);
	}
	delete [] info;
	m_EditSearch.SetSel(0, -1);
}

//����Ҽ������˵��Ĵ�����ť
void CPassManagerDlg::OnPopcreate()
{
	// TODO: �ڴ���������������
	OnNewbook();
}

//����Ҽ������˵��Ĵ򿪰�ť
void CPassManagerDlg::OnPopopen()
{
	// TODO: �ڴ���������������
	OnOpenbook();
}

//����Ҽ������˵����������밴ť
void CPassManagerDlg::OnMpopadd()
{
	// TODO: �ڴ���������������
	OnAdd();
}

//����Ҽ������˵��ĸ������밴ť
void CPassManagerDlg::OnMpopcopy()
{
	// TODO: �ڴ���������������
	CString strCopy;
	if(!OpenClipboard())
	{
		setStatusBar("���Ƴ���");
		return ;
	}
	EmptyClipboard();
	int nowPos = m_listShow.GetSelectionMark();
	strCopy = m_listShow.GetItemText(nowPos, 1);
	HANDLE hClip;
	hClip=GlobalAlloc(GMEM_MOVEABLE,strCopy.GetLength()+1);
	char *pBuf;
	pBuf=(char *)GlobalLock(hClip);
	strcpy(pBuf,strCopy.GetBuffer());
	GlobalUnlock(hClip);
	SetClipboardData(CF_TEXT,hClip);
	CloseClipboard();
	setStatusBar("ѡ��������Ѹ���");
}

//�ر����뱾
void CPassManagerDlg::OnClosebook()
{
	// TODO: �ڴ���������������
	delete m_sql;
	m_sql = NULL;
	DisableMenus();
	clearListEdit();
	setStatusBar("���뱾�ѹرգ������´���������뱾");
}

//����༭����б���
void CPassManagerDlg::clearListEdit()
{
	m_EditSearch.SetWindowText("");
	m_listShow.DeleteAllItems();
}

//��ʾ����������ͼ�꣬�ڳ����������ر�ʱ�ֱ����һ��
BOOL CPassManagerDlg::TrayMyIcon(bool bShow)
{
	BOOL bRet = FALSE;
	NOTIFYICONDATA tnd;
	tnd.cbSize = sizeof(NOTIFYICONDATA);
	tnd.hWnd = this->m_hWnd;
	tnd.uID = IDR_MENU_NOTIFY;
	if (bShow)
	{
		tnd.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
		tnd.uCallbackMessage = WM_TRAYICON_MOUSEOVER;
		tnd.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDI_MAINICON));
		_tcscpy_s(tnd.szTip, sizeof(tnd.szTip), _T("����ʥ�� V1.0"));
		bRet = Shell_NotifyIcon(NIM_ADD, &tnd);
	} 
	else
	{
		SetForegroundWindow();
		bRet = Shell_NotifyIcon(NIM_DELETE, &tnd);
	}
	return bRet;
}

//��Ӧ����ƶ��������ϵ���Ϣ
LRESULT CPassManagerDlg::OnTrayCallBackMsg(WPARAM wparam, LPARAM lparam)
{
	switch (lparam)
	{
	case WM_RBUTTONUP:
		{
			PopNotifyMenu();
			SetForegroundWindow();
			break;
		}
	case WM_LBUTTONDBLCLK:
		{
			DoShowWindow(!m_bShow);
			break;
		}
	default:
		{
			break;
		}
	}
	return NULL;
}

//�������̲˵�
VOID CPassManagerDlg::PopNotifyMenu()
{
	CPoint pt;
	GetCursorPos(&pt);
	CMenu mMenu, * pMenu = NULL;
	mMenu.LoadMenu(IDR_MENU_NOTIFY);
	pMenu = mMenu.GetSubMenu(0);
	SetForegroundWindow();
	pMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, pt.x, pt.y, this);
}

//�����ڴ�С�ñ�ʱ����
void CPassManagerDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// ����Ϣ����С������ʱ
	if (SIZE_MINIMIZED == nType)
	{
		DoShowWindow(false);
		return ;
	}
}

void CPassManagerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	TrayMyIcon(false);
	CDialogEx::OnClose();
}

//��ʾ�����ش���
void CPassManagerDlg::DoShowWindow(bool bShow)
{
	if (bShow)
	{
		ShowWindow(SW_RESTORE);
		ShowWindow(SW_SHOWNA);
		SetForegroundWindow();
	}else
	{
		ShowWindow(SW_HIDE);
	}
	this->m_bShow = bShow;
	return ;
}

void CPassManagerDlg::OnFast()
{
	// TODO: �ڴ���������������
	if (!m_fastDlg || !m_fastDlg->m_hWnd)
	{
		m_fastDlg = new CFastKeyDlg(m_iniFilePath, this);
		m_fastDlg->Create(IDD_DLGFAST);
	}
	m_fastDlg->ShowWindow(SW_SHOWNORMAL);
}

//�����ʱ����һ��Ĭ�ϵ�INI�ļ�
bool CPassManagerDlg::CreateDefaultIniFile()
{
	TCHAR szFilePathName[MAX_PATH];
	GetModuleFileName(NULL, szFilePathName, MAX_PATH);
	m_iniFilePath = szFilePathName;
	m_iniFilePath = m_iniFilePath.Left(m_iniFilePath.ReverseFind('\\'));
	m_iniFilePath += "\\Setting.ini";
	CFileFind finder;
	BOOL ifFind = finder.FindFile(m_iniFilePath);
	if( !ifFind )
	{
		CString strHotKey;
		DWORD hotKey;
		hotKey = (MOD_ALT << 16) | ('Q');
		strHotKey.Format("%ld", hotKey);
		WritePrivateProfileString(_T("HOTKEY"),_T("SHOW"),
			strHotKey, m_iniFilePath);
		hotKey = (MOD_ALT << 16) | ('E');
		strHotKey.Format("%ld", hotKey);
		WritePrivateProfileString(_T("HOTKEY"),_T("SEARCH"),
			strHotKey, m_iniFilePath);
		BOOL rc = RegisterHotKey(this->GetSafeHwnd(), WM_HOTKEY_SHOW, MOD_ALT, 'Q');
		rc = RegisterHotKey(this->GetSafeHwnd(), WM_HOTKEY_SEARCH, MOD_ALT, 'E');
		if (!rc)
		{
			setStatusBar("�ȼ�ע��ʧ��");
		}
	}else
	{
		UINT showHotKey = GetPrivateProfileInt("HOTKEY", "SHOW", 0, m_iniFilePath);
		UINT searchHotKey = GetPrivateProfileInt("HOTKEY", "SEARCH", 0, m_iniFilePath);
		if (showHotKey && searchHotKey)
		{
			BOOL rc = RegisterHotKey(this->GetSafeHwnd(), WM_HOTKEY_SHOW, showHotKey >> 16, showHotKey & 0x0000FFFF);
			rc = RegisterHotKey(this->GetSafeHwnd(), WM_HOTKEY_SEARCH, searchHotKey >> 16, searchHotKey & 0x0000FFFF);
			if (!rc)
			{
				setStatusBar("�ȼ�ע��ʧ��");
			}
		}	
	}
	
	return true;
}

//������̲˵����˳���ť
void CPassManagerDlg::OnTrayQuit()
{
	// TODO: �ڴ���������������
	OnQuit();
}

BOOL CPassManagerDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_HOTKEY)
	{
		switch (pMsg->wParam)
		{
		case WM_HOTKEY_SHOW:
			DoShowWindow(!m_bShow);
			break;
		case WM_HOTKEY_SEARCH:
			if (m_sql) ShowSearchDlg(!m_bSearchShow);
			break;
		}
	}

	return CDialogEx::PreTranslateMessage(pMsg);
}

//��ʾ���������Ի���
void CPassManagerDlg::ShowSearchDlg(bool bShow)
{
	if (!m_SearchDlg || !m_SearchDlg->m_hWnd)
	{
		m_SearchDlg = new CSearchDlg(m_sql, this);
		m_SearchDlg->Create(IDD_SEARCHDLG);
	}
	if (bShow)
	{
		m_SearchDlg->ShowWindow(SW_SHOWNORMAL);
	} 
	else
	{
		m_SearchDlg->ShowWindow(SW_HIDE);
	}
	m_bSearchShow = bShow;
	CRect rect;
	m_SearchDlg->GetWindowRect(&rect);
	m_SearchDlg->MoveWindow(rect.left, rect.top, 150, 50);
	m_SearchDlg->SetFocus();
}

void CPassManagerDlg::OnQuery()
{
	// TODO: �ڴ���������������
	if (m_sql) ShowSearchDlg(true);
}


void CPassManagerDlg::OnTraySearch()
{
	OnQuery();
	// TODO: �ڴ���������������
}


void CPassManagerDlg::OnTrayOpen()
{
	DoShowWindow(TRUE);
	// TODO: �ڴ���������������
}


void CPassManagerDlg::OnRepass()
{
	// TODO: �ڴ���������������
	CRepassDlg repDlg(m_sql, this);
	repDlg.DoModal();
}


void CPassManagerDlg::OnBak()
{
	// TODO: �ڴ���������������
	CBakDlg bakDlg(m_sql, this);
	bakDlg.DoModal();
}

//����޸����밴ť
void CPassManagerDlg::OnMpopedit()
{
	// TODO: �ڴ���������������
	m_bEdit = true;
	OnAdd();
	m_bEdit = false;
}

//���ɾ�����밴ť
void CPassManagerDlg::OnMpopdel()
{
	if (IDCANCEL == MessageBox("�Ƿ�Ҫɾ����������", "��ʾ", MB_OKCANCEL))
	{
		return ;
	}
	int at = m_IdArr.GetAt(m_listShow.GetSelectionMark());
	bool bOk = m_sql->delPass(at);
	if (!bOk)
	{
		setStatusBar("ɾ������ʧ��");
	}else{
		setStatusBar("ɾ������ɹ�");
		OnBnClickedBtnsearch();
	}
}


void CPassManagerDlg::OnAbout()
{
	// TODO: �ڴ���������������
	static CAboutDlg m_abt;
	if (!m_abt.m_hWnd)
	{
		m_abt.Create(IDD_ABOUTBOX);
	}
	m_abt.ShowWindow(SW_SHOWNORMAL);
}


void CPassManagerDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (m_sql)
	{
		if (MessageBox("�رյ�ǰ���뱾��������һ��һ�����뱾��", "����", MB_OKCANCEL) == IDCANCEL)
		{
			return ;
		}else{
			OnClosebook();
		}
	}
	char pFilePathName[MAX_PATH];
	::DragQueryFile(hDropInfo, 0, pFilePathName, MAX_PATH);  // ��ȡ�Ϸ��ļ��������ļ���
	m_dbPath = pFilePathName;
	::DragFinish(hDropInfo);   // ע����������٣��������ͷ�Windows Ϊ�����ļ��ϷŶ�������ڴ�

	CInputPassDlg passDlg(this);
	INT_PTR rt = passDlg.DoModal();
	if (!rt)
	{
		return ;
	}
	CString strPass = passDlg.getPassword();
	OpenPassBook(m_dbPath, strPass);

	CDialogEx::OnDropFiles(hDropInfo);
}

void CPassManagerDlg::OpenPassBook(CString strFile, CString strPass)
{
	m_sql = new doSql();
	if( ! m_sql->InitOpen((LPCTSTR)strFile, (LPCTSTR)strPass, strPass.GetLength())){
		int errNo;
		CString str;
		errNo = m_sql->getErrNo();
		str.Format("����������룺%d", errNo);
		MessageBox(str);
		delete m_sql;
		m_sql = NULL;
		return ;
	}else{
		setStatusBar("�����뱾�ɹ�");
		EnableMenus();
		clearListEdit();
		m_sql->delMoreTag();
	}
}

void CPassManagerDlg::OnOption()
{
	// TODO: �ڴ���������������
	COptionDlg dlg(m_iniFilePath, this);
	dlg.DoModal();
}

//˫��ĳһ����������鴰��
void CPassManagerDlg::OnNMDblclkRelist(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (m_listShow.GetSelectedCount() > 0)
	{
		int nSelect = m_listShow.GetSelectionMark();
		CString strPass, strUser, strUrl, strMak;
		strUser = m_listShow.GetItemText(nSelect, 0);
		strPass = m_listShow.GetItemText(nSelect, 1);
		strUrl = m_listShow.GetItemText(nSelect, 3);
		strMak = m_listShow.GetItemText(nSelect, 2);
		CDetailDlg dlg(strUser, strPass, strUrl, strMak, this);
		dlg.DoModal();
	}
	*pResult = 0;
}

//����˵��ϵİ�����ť
void CPassManagerDlg::OnHelp()
{
	// TODO: �ڴ���������������
	ShellExecute(0, _T("open"), HelpSite, NULL, NULL, SW_SHOWMAXIMIZED);
}

//����˵��ϵ����谴ť�������ҵ���ҳ
void CPassManagerDlg::OnLeavesongs()
{
	// TODO: �ڴ���������������
	ShellExecute(0, _T("open"), Author, NULL, NULL, SW_SHOWMAXIMIZED);
}
