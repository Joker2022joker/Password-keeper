// OptionDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "OptionDlg.h"
#include "afxdialogex.h"
#include "PassManagerDlg.h"
#include "Global.h"

// COptionDlg �Ի���

const char * pKeyName = "PassKeeper";

IMPLEMENT_DYNAMIC(COptionDlg, CDialogEx)

COptionDlg::COptionDlg(CString strIniName, CWnd* pParent /*=NULL*/)
	: CDialogEx(COptionDlg::IDD, pParent)
{
	m_IniFileName = strIniName;
	m_errStr = "���óɹ�";
	bReleChng = bAutoChng = false;
}

COptionDlg::~COptionDlg()
{
}

void COptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_OPTIONDLG_CONN, m_RelePas);
	DDX_Control(pDX, IDC_OPTIONDLG_AUTORUN, m_AutoRun);
	//DDX_Control(pDX, IDC_OPTIONDLG_AUTORUN2, m_HidePass);
}


BEGIN_MESSAGE_MAP(COptionDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OPTIONDLG_CANCEL, &COptionDlg::OnBnClickedOptiondlgCancel)
	ON_BN_CLICKED(IDC_OPTIONDLG_OK, &COptionDlg::OnBnClickedOptiondlgOk)
	ON_BN_CLICKED(IDC_OPTIONDLG_CONN, &COptionDlg::OnBnClickedOptiondlgConn)
	ON_BN_CLICKED(IDC_OPTIONDLG_AUTORUN, &COptionDlg::OnBnClickedOptiondlgAutorun)
END_MESSAGE_MAP()


// COptionDlg ��Ϣ�������


void COptionDlg::OnBnClickedOptiondlgCancel()
{
	OnCancel();
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

//�������ü�
void COptionDlg::OnBnClickedOptiondlgOk()
{
	int b1 = m_AutoRun.GetCheck();
	int b2 = m_RelePas.GetCheck();
	bool bAutoRun = b1 == BST_CHECKED ? true : false;
	bool bRele = b2 == BST_CHECKED ? true : false;
	CPassManagerDlg * p = (CPassManagerDlg *)GetParent();
	if (bInitAuto != bAutoRun)
	{
		SetAutoRun(bAutoRun);
		p->OnSonDlgClose(m_errStr);
	}
	if (bInitRele != bRele)
	{
		SetFileRele(bRele);
		p->OnSonDlgClose(m_errStr);
	}	
	OnOK();
}

//���س����Ƿ�������
bool COptionDlg::isAutoRun()
{
	char regname[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkResult;
	LONG ret = RegOpenKey(HKEY_LOCAL_MACHINE, regname, &hkResult);
	if (ERROR_SUCCESS != ret)
	{
		return false;
	}
	TCHAR szValue[MAX_PATH];
	DWORD BufferSize = MAX_PATH;
	ret = RegQueryValueEx(hkResult, pKeyName, NULL, NULL, (LPBYTE)szValue, &BufferSize);
	RegCloseKey(hkResult);
	if (ret != ERROR_SUCCESS)
	{
		return false;
	}
	else
	{
		return true;
	}

}

int COptionDlg::SetAutoRun(int bAutoRun)
{
	char regname[]="Software\\Microsoft\\Windows\\CurrentVersion\\Run";
	HKEY hkResult;
	int ret = RegOpenKey(HKEY_LOCAL_MACHINE, regname, &hkResult);
	if (ERROR_SUCCESS != ret)
	{
		m_errStr = "���ÿ���������ʧ��";
		return -1;
	}
	if (bAutoRun)
	{
		TCHAR szFileName[MAX_PATH];
		GetModuleFileName(NULL, szFileName, MAX_PATH);
		ret = RegSetValueEx(hkResult, pKeyName/* ע������*/, 0, 
			REG_SZ, (const BYTE *)szFileName, sizeof(szFileName));
		if (ret) m_errStr = "���ÿ���������ʧ��";
		RegCloseKey(hkResult);
	}
	else
	{
		ret = RegDeleteValue(hkResult, pKeyName);
		if (ret) m_errStr = "ɾ������������ʧ��";
		RegCloseKey(hkResult);
	}
	return 0;
}

int COptionDlg::SetFileRele(int bRele)
{
	if (bRele)
	{
		TCHAR szFileName[MAX_PATH];
		GetModuleFileName(NULL, szFileName, MAX_PATH);
		CString str = szFileName;
		str = str.Left(str.ReverseFind('\\')) + "\\icon.ico";
		bool rc = setFileAssociation(".pas", szFileName, "PK_File", 
			str, "���뱾�ļ�");
		if (!rc) m_errStr = "���ù���ʧ��";
		return rc ? 0 : -1;
	}else{
		if (!delFileAssociation()){
			m_errStr = "ɾ������ʧ��";
			return -1;
		}
	}
	return 0;
}

//ɾ���ļ�����
bool COptionDlg::delFileAssociation()
{
	HKEY hKey;
	DWORD count;
	LPTSTR data=_T("Software\\Classes\\");
	if (ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, data, &hKey) || 
		ERROR_SUCCESS != RegDeleteKey(hKey, ".pas"))
	{
		return false;
	}
	if(	ERROR_SUCCESS != SHDeleteKey(hKey, "PK_File") || 
		ERROR_SUCCESS != RegCloseKey(hKey))
	{
		return false;
	}
	//֪ͨϵͳ������������Ч 
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL); 
	return true;
}

//�����ļ�����
bool COptionDlg::setFileAssociation(CString ext,  //��׺��.pas��
	CString applicationName,  //�����ַ
	CString progId, // һ������"PK_File"
	CString defaultIcon,  //Ĭ��ͼ��
	CString description) //����
{ 
	bool bRet = false; 
	HKEY hKey;
	CString HKCUPrefix = _T("Software\\Classes\\"); 

	//�����ļ�������ע�⣺��Ҫ����һ��ֵ�������ļ�������չ����
	//������ProgId��Ĭ��ͼ���Windows Shell���������ʽ�� 
	CString fullExt = HKCUPrefix + ext; 
	if(ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, fullExt.GetBuffer(), &hKey) 
		|| ERROR_SUCCESS != RegSetValue(hKey, _T(""), REG_SZ, progId.GetBuffer(), progId.GetLength() + 1) 
		|| ERROR_SUCCESS != RegCloseKey(hKey)) 
	{ 
		return false;
	}
	fullExt.ReleaseBuffer();
	progId.ReleaseBuffer();

	CString fullProgId = HKCUPrefix + progId; 
	if(ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, fullProgId.GetBuffer(), &hKey) 
		|| ERROR_SUCCESS != RegSetValue(hKey, _T(""), REG_SZ, description.GetBuffer(), description.GetLength() + 1)
		|| ERROR_SUCCESS != RegCloseKey(hKey)) 
	{ 
		return false;
	}
	fullProgId.ReleaseBuffer();
	description.ReleaseBuffer();

	CString strIconKey = fullProgId + _T("\\DefaultIcon"); 
	if(ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, strIconKey.GetBuffer(), &hKey) 
		|| ERROR_SUCCESS != RegSetValue(hKey, _T(""), REG_SZ, defaultIcon.GetBuffer(), defaultIcon.GetLength() + 1) 
		|| ERROR_SUCCESS != RegCloseKey(hKey)) 
	{ 
		return false;
	}
	fullProgId.ReleaseBuffer();
	defaultIcon.ReleaseBuffer();

	CString strCommandKey = fullProgId + _T("\\Shell\\Open\\Command"); 
	CString strCommand;
	strCommand.Format("\"%s\" \"%%1\"", applicationName);
	if(ERROR_SUCCESS != RegCreateKey(HKEY_CURRENT_USER, strCommandKey.GetBuffer(), &hKey) 
		|| ERROR_SUCCESS != RegSetValue(hKey, _T(""), REG_SZ, strCommand.GetBuffer(), strCommand.GetLength() + 1) 
		|| ERROR_SUCCESS != RegCloseKey(hKey)) 
	{ 
		return false;
	}
	strCommandKey.ReleaseBuffer();
	strCommand.ReleaseBuffer();

	CString strShellKey = fullProgId + _T("\\Shell"); 
	if(ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, strShellKey.GetBuffer(), &hKey) 
		|| ERROR_SUCCESS != RegSetValue(hKey, _T(""), REG_SZ, _T("Open"), 4 + 1) 
		|| ERROR_SUCCESS != RegCloseKey(hKey)) 
	{ 
		return false;
	} 
	strShellKey.ReleaseBuffer();

	//֪ͨϵͳ������������Ч 
	SHChangeNotify(SHCNE_ASSOCCHANGED, SHCNF_IDLIST, NULL, NULL); 

	bRet = true; 

	return bRet; 
}

bool COptionDlg::isReleFile()
{
	CString HKCUPrefix = _T("Software\\Classes\\.pas");
	HKEY hKey;
	TCHAR szValue[MAX_PATH];
	DWORD dwLen = MAX_PATH;
	if(ERROR_SUCCESS != RegOpenKey(HKEY_CURRENT_USER, HKCUPrefix, &hKey) || 
		ERROR_SUCCESS != RegQueryValueEx(hKey, "", NULL, NULL, (LPBYTE)szValue, &dwLen)) 
	{ 
		return false;
	}
	CString strCommandKey;
	strCommandKey.Format("Software\\Classes\\%s\\Shell\\Open\\Command", szValue);
	int r1,r2;
	dwLen = MAX_PATH;
	if(ERROR_SUCCESS != (r1 = RegOpenKey(HKEY_CURRENT_USER, strCommandKey, &hKey)) || 
		ERROR_SUCCESS != (r2 = RegQueryValueEx(hKey, "", NULL, NULL, (LPBYTE)szValue, &dwLen))) 
	{ 
		return false; 
	}
	CString strExe;
	strExe = szValue;
	GetModuleFileName(NULL, szValue, MAX_PATH);
	if (strExe.Find(szValue, 0) >= 0)
	{
		return true;
	} 
	else
	{
		return false;
	}
}


BOOL COptionDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	bInitRele = isReleFile();
	bInitAuto = isAutoRun();
	if (bInitAuto)
	{
		m_AutoRun.SetCheck(BST_CHECKED);
	}
	if (bInitRele)
	{
		m_RelePas.SetCheck(BST_CHECKED);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void COptionDlg::OnBnClickedOptiondlgConn()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}


void COptionDlg::OnBnClickedOptiondlgAutorun()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
}
