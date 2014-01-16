// BakDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "BakDlg.h"
#include "afxdialogex.h"


// CBakDlg �Ի���

IMPLEMENT_DYNAMIC(CBakDlg, CDialogEx)

CBakDlg::CBakDlg(doSql * sql, CWnd* pParent /*=NULL*/)
	: CDialogEx(CBakDlg::IDD, pParent)
{
	m_sql = sql;
}

CBakDlg::~CBakDlg()
{
}

void CBakDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BAKDLG_LIST, m_TypeList);
	DDX_Control(pDX, IDC_BAKDLG_PASS, m_DelPass);
}


BEGIN_MESSAGE_MAP(CBakDlg, CDialogEx)
	ON_CBN_SELCHANGE(IDC_BAKDLG_LIST, &CBakDlg::OnCbnSelchangeBakdlgList)
	ON_BN_CLICKED(IDC_BAKDLG_SAVE, &CBakDlg::OnBnClickedBakdlgSave)
	ON_BN_CLICKED(IDC_BAKDLG_PASS, &CBakDlg::OnBnClickedBakdlgPass)
END_MESSAGE_MAP()


// CBakDlg ��Ϣ�������


BOOL CBakDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_TypeList.AddString("���뱾�ļ�(*.pas)");
	m_TypeList.AddString("SQL�ļ�(*.sql)");
	m_TypeList.AddString("CSV�ļ�(*.csv)");
	m_TypeList.SetCurSel(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

//���������
void CBakDlg::OnCbnSelchangeBakdlgList()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int iNow = m_TypeList.GetCurSel(); 
	//iNow ��ʾ������ѡ��ĵڼ���
	if (iNow) //������ǵ�0��
	{
		m_DelPass.SetCheck(BST_CHECKED);
		m_DelPass.EnableWindow(FALSE);
		GetDlgItem(IDC_BAKDLG_INPUT)->EnableWindow(TRUE);
	}else
	{
		m_DelPass.EnableWindow(TRUE);
		int iCheck = m_DelPass.GetCheck();
		if (BST_UNCHECKED == iCheck)
		{
			GetDlgItem(IDC_BAKDLG_INPUT)->EnableWindow(FALSE);
		}
		else
		{
			GetDlgItem(IDC_BAKDLG_INPUT)->EnableWindow(TRUE);
		}
	}
}


void CBakDlg::OnBnClickedBakdlgSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strPath, strPass;
	GetDlgItem(IDC_BAKDLG_INPUT)->GetWindowText(strPass);
	int len = strPass.GetLength();
	char * szPass = new char[len + 1];
	strcpy_s(szPass, len + 1, strPass.GetBuffer());
	strPass.ReleaseBuffer();
	srand(time(0));
	strPath = SelectPath();
	if (strPath.IsEmpty())
	{
		return ;
	}
	int iDel = m_DelPass.GetCheck();
	int iSelect = m_TypeList.GetCurSel();
	bool bDelPass = iDel == BST_CHECKED ? false : true;
	switch (iSelect)
	{
	case 0:
		strPath.Format("%s\\bak_%d.pas", strPath, rand());
		m_sql->bakDatabase(strPath.GetBuffer(), szPass, TYPE_PAS, bDelPass);
		strPath.ReleaseBuffer();
		break;
	case 1:
		strPath.Format("%s\\bak_%d.sql", strPath, rand());
		m_sql->bakDatabase(strPath.GetBuffer(), szPass, TYPE_SQL, bDelPass);
		strPath.ReleaseBuffer();
		break;
	case 2:
		strPath.Format("%s\\bak_%d.csv", strPath, rand());
		m_sql->bakDatabase(strPath.GetBuffer(), szPass, TYPE_CSV, bDelPass);
		strPath.ReleaseBuffer();
		break;
	}
	OnOK();
}

//����ѡ���ļ��жԻ���
CString CBakDlg::SelectPath()
{
	BROWSEINFO Info;
	ITEMIDLIST * pIdl;
	char szPath[MAX_PATH] = {0};
	CString strPath;
	Info.hwndOwner = this->GetSafeHwnd();
	Info.pidlRoot = NULL;
	Info.pszDisplayName = szPath;
	Info.lpszTitle = "ѡ��Ҫ�����Ŀ¼";
	Info.ulFlags = BIF_EDITBOX;   
	Info.lpfn = NULL;
	Info.lParam = 0;   
	Info.iImage = 0;   
	pIdl = SHBrowseForFolder(&Info);
	if (pIdl)
	{
		SHGetPathFromIDList(pIdl, szPath);
		CoTaskMemFree(pIdl);
		strPath = szPath;
		return strPath;
	}else{
		return "";
	}
}

//����ȥ�����븴ѡ��
void CBakDlg::OnBnClickedBakdlgPass()
{
	int iCheck = m_DelPass.GetCheck();
	if (BST_UNCHECKED == iCheck)
	{
		GetDlgItem(IDC_BAKDLG_INPUT)->EnableWindow(FALSE);
	} 
	else
	{
		GetDlgItem(IDC_BAKDLG_INPUT)->EnableWindow(TRUE);
	}
}
