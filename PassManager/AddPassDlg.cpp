// AddPassDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "PassManagerDlg.h"
#include "AddPassDlg.h"
#include "afxdialogex.h"

#include <ctime>

void QuickSort(char * arr,int low,int high);
int FindPos(char * arr,int low,int high);

// CAddPassDlg �Ի���

IMPLEMENT_DYNAMIC(CAddPassDlg, CDialogEx)

CAddPassDlg::CAddPassDlg(doSql * sql, CWnd* pParent /*=NULL*/)
	: CDialogEx(CAddPassDlg::IDD, pParent)
	, m_strPass(_T(""))
	, m_strTag(_T(""))
	, m_strUrl(_T(""))
	, m_strRemark(_T(""))
	, m_strUser(_T(""))
{
	m_sql = sql;
	m_Parent = pParent;
	EditPid = -1;
}

CAddPassDlg::~CAddPassDlg()
{
}

void CAddPassDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ADDDLG_PASS, m_strPass);
	DDX_Text(pDX, IDC_ADDDLG_TAG, m_strTag);
	DDX_Text(pDX, IDC_ADDDLG_URL, m_strUrl);
	DDX_Text(pDX, IDC_ADDDLG_REMARK, m_strRemark);
	DDX_Text(pDX, IDC_ADDDLG_USER, m_strUser);
}


BEGIN_MESSAGE_MAP(CAddPassDlg, CDialogEx)
	ON_BN_CLICKED(IDC_ADDDLG_CANCEL, &CAddPassDlg::OnBnClickedAdddlgCancel)
	ON_BN_CLICKED(IDC_ADDDLG_CHKENGSMALL, &CAddPassDlg::OnBnClickedAdddlgChkengsmall)
	ON_BN_CLICKED(IDC_ADDDLG_CHKENGLARGE, &CAddPassDlg::OnBnClickedAdddlgChkenglarge)
	ON_BN_CLICKED(IDC_ADDDLG_CHKNUM, &CAddPassDlg::OnBnClickedAdddlgChknum)
	ON_BN_CLICKED(IDC_ADDDLG_SIG, &CAddPassDlg::OnBnClickedAdddlgSig)
	ON_WM_MOUSEMOVE()
	ON_STN_DBLCLK(IDC_BMPPASS, &CAddPassDlg::OnStnDblclickBmppass)
	ON_BN_CLICKED(IDC_ADDDLG_OK, &CAddPassDlg::OnBnClickedAdddlgOk)
	ON_WM_CLOSE()
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CAddPassDlg ��Ϣ�������


void CAddPassDlg::OnBnClickedAdddlgCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_strStatus = "�����ʹ�����½�����ʱ��д�ġ���ǩ������������";
	SendMessage(WM_CLOSE);
}


BOOL CAddPassDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SelectBox(IDC_ADDDLG_CHKENGSMALL);
	SelectBox(IDC_ADDDLG_CHKNUM);
	SelectBox(IDC_ADDDLG_CHKENGLARGE);
	SetDlgItemText(IDC_ADDDLG_ALLWORD, "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
	SetDlgItemInt(IDC_ADDDLG_PASSLEN, 12);
	m_pSeed = GetDlgItem(IDC_ADDDLG_SEED);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CAddPassDlg::SelectBox(int name, BOOL select)
{
	CButton * pWin = (CButton *)GetDlgItem(name);
	if (select)
	{
		pWin->SetCheck(BST_CHECKED);
	}else{
		pWin->SetCheck(BST_UNCHECKED);
	}
}

//ȥ���ַ����е��ظ��ַ�
CString CAddPassDlg::DelRepet(TCHAR * szStr, int len)
{
	CString strRe("");
	QuickSort(szStr, 0, len);
	for (int i = 0 ; i <= len ; i++)
	{
		if (i > 0 && szStr[i] == szStr[i - 1])
		{
			continue;
		}
		strRe += szStr[i];
	}
	return strRe;
}

//��������
//highΪ�ַ������� - 1
void QuickSort(TCHAR * arr,int low,int high){
	int pos;
	if(low < high){
		pos = FindPos(arr,low,high);
		QuickSort(arr,low,pos-1);
		QuickSort(arr,pos+1,high);
	}
	return ;
}

int FindPos(TCHAR * arr,int low,int high)
{
	int val = arr[low];
	while(low < high){
		while(arr[high] >= val && low < high)
			high--;
		arr[low] = arr[high];
		while(arr[low] <= val && low < high)
			low++;
		arr[high] = arr[low];
	} //ѭ����ɺ�high == low
	arr[low] = val;
	return(low);
}

//���Сд��ѡ��
void CAddPassDlg::OnBnClickedAdddlgChkengsmall()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * pWin = (CButton *)GetDlgItem(IDC_ADDDLG_CHKENGSMALL);
	int bCheck = pWin->GetCheck();
	TCHAR szChar[192];
	if (bCheck == BST_CHECKED)
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars += "abcdefghijklmnopqrstuvwxyz";
		strChars = DelRepet(strChars.GetBuffer(), strChars.GetLength() - 1);
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
	else
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars.Replace("abcdefghijklmnopqrstuvwxyz", "");
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
}

void CAddPassDlg::OnBnClickedAdddlgChkenglarge()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * pWin = (CButton *)GetDlgItem(IDC_ADDDLG_CHKENGLARGE);
	int bCheck = pWin->GetCheck();
	TCHAR szChar[192];
	if (bCheck == BST_CHECKED)
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
		strChars = DelRepet(strChars.GetBuffer(), strChars.GetLength() - 1);
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
	else
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars.Replace("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "");
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
}


void CAddPassDlg::OnBnClickedAdddlgChknum()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * pWin = (CButton *)GetDlgItem(IDC_ADDDLG_CHKNUM);
	int bCheck = pWin->GetCheck();
	TCHAR szChar[192];
	if (bCheck == BST_CHECKED)
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars += "0123456789";
		strChars = DelRepet(strChars.GetBuffer(), strChars.GetLength() - 1);
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
	else
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars.Replace("0123456789", "");
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
}


void CAddPassDlg::OnBnClickedAdddlgSig()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CButton * pWin = (CButton *)GetDlgItem(IDC_ADDDLG_SIG);
	int bCheck = pWin->GetCheck();
	TCHAR szChar[192];
	if (bCheck == BST_CHECKED)
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars += "!#$%&()*+,-.:;=?@";
		strChars = DelRepet(strChars.GetBuffer(), strChars.GetLength() - 1);
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
	else
	{
		GetDlgItemText(IDC_ADDDLG_ALLWORD, szChar, 96);
		CString strChars(szChar);
		strChars.Replace("!#$%&()*+,-.", "");
		strChars.Replace(":;=?@", "");
		SetDlgItemText(IDC_ADDDLG_ALLWORD, strChars.GetBuffer());
	}
}

//˫��ͼƬ
void CAddPassDlg::OnStnDblclickBmppass()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int len = GetDlgItemInt(IDC_ADDDLG_PASSLEN);
	len = len > 16 ? 16 : len;
	CString strChars, strPass("");
	GetDlgItem(IDC_ADDDLG_ALLWORD)->GetWindowText(strChars);
	if (strChars.IsEmpty())
	{
		MessageBox("Ԥѡ�������Ϊ��");
		return ;
	}
	HINSTANCE hCryptDll = LoadLibrary(TEXT("Cryptdll.dll"));
	if (INVALID_HANDLE_VALUE==hCryptDll||NULL==hCryptDll)
	{
		MessageBox("��ļ������֧����������������������ֶ���������!", "����");
		return ;
	}
	HCRYPTPROV crypt_prov_;
	if( !CryptAcquireContext( &crypt_prov_, NULL, NULL, PROV_RSA_FULL, 0) ) 
	{
		if( !CryptAcquireContext( &crypt_prov_, NULL, NULL, PROV_RSA_FULL, CRYPT_NEWKEYSET) ) 
			MessageBox("��ļ������֧����������������������ֶ���������!", "����");
	}
	BYTE * data = new BYTE[len];
	unsigned long r = 0;
	if( crypt_prov_ ){
		if( CryptGenRandom( crypt_prov_, sizeof(data), data) ) 
		{
			memcpy( &r, data, sizeof(data) );
		}
	}
	CryptReleaseContext(crypt_prov_, 0);
	for (int i = 0 ; i < len ; i++)
	{
		int count = strChars.GetLength();
		strPass += strChars[abs((data[i] ^ (m_seed >> i)) % count)];
	}
	SetDlgItemText(IDC_ADDDLG_PASS, strPass);
	setRandSeed();
}


BOOL CAddPassDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_MOUSEMOVE)
	{
		setRandSeed();
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CAddPassDlg::setRandSeed()
{
	CPoint point;
	GetCursorPos(&point);
	GetDlgItem(IDC_BMPPASS)->GetWindowRect(&m_bmpRect);
	//ScreenToClient(m_bmpRect);
	srand(unsigned(time(0) + GetTickCount()));
	if (m_bmpRect.PtInRect(point))
	{
		int x = point.x - m_bmpRect.left,
			y = point.y - m_bmpRect.top;
		m_seed = (x ^ rand()) * y - (y ^ rand()) * x;
		CString strSeed;
		strSeed.Format("%d", m_seed);
		SetDlgItemText(IDC_ADDDLG_SEED, strSeed);
	}
}

InputInfo CAddPassDlg::getInput()
{
	UpdateData(TRUE);
	InputInfo info(m_strPass, m_strTag, m_strUrl, m_strRemark);
	return info;
}

//�����Ӱ�ť
void CAddPassDlg::OnBnClickedAdddlgOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_strPass.GetLength() > 128 || m_strUser.GetLength() > 32 || m_strUrl.GetLength() > 256 ||
		m_strTag.GetLength() > 256)
	{
		MessageBox("��д����Ϣ����");
		return ;
	}
	if (m_strUser.IsEmpty() || m_strPass.IsEmpty() || m_strTag.IsEmpty())
	{
		MessageBox("�˺š�������ǩ����Ϊ��");
		return ;
	}
	int i = 0;
	TCHAR * token;
	char * strTags[5];
	token = _tcstok(m_strTag.GetBuffer(), "|");
	while (token && i < 5)
	{
		strTags[i++] = token;
		if (strlen(strTags[i - 1]) > 32)
		{
			MessageBox("��д����Ϣ����");
			return ;
		}
		token = _tcstok(NULL, "|");
	}
	bool rc;
	if(m_bEdit){
		rc = m_sql->editPass(EditPid, m_strPass.GetBuffer(), m_strUser.GetBuffer(), m_strUrl.GetBuffer(),
			strTags, i, m_strRemark.GetBuffer());
	}
	else{
		rc = m_sql->addPass(m_strPass.GetBuffer(), m_strUser.GetBuffer(), m_strUrl.GetBuffer(),
		strTags, i, m_strRemark.GetBuffer());
	}
	if (!rc)
	{
		CString str;
		str.Format("�������ݿ�ʧ�ܣ�������룺%d", m_sql->getErrNo());
		MessageBox(str);
		return ;
	}
	m_strStatus.Format("�����ɹ�", m_strUrl);
	SendMessage(WM_CLOSE);
}

void CAddPassDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CPassManagerDlg * p = (CPassManagerDlg *)m_Parent;
	p->OnSonDlgClose(m_strStatus);
	p->OnBnClickedBtnsearch();
	CDialogEx::OnClose();
}

void CAddPassDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()

	if (m_bEdit && EditPid > 0)
	{
		InfoRow info;
		SetWindowText("�޸�����");
		m_sql->getInfoById(EditPid, &info);
		m_strPass = info.szPass;
		m_strUser = info.szUser;
		m_strUrl = info.szUrl;
		m_strRemark = info.szRemark;
		char szTag[256] = {0};
		m_sql->getTagByPid(EditPid, szTag);
		m_strTag = szTag;
		if (m_strTag[0] == '|')
		{
			m_strTag.Delete(0, 1);
		}
		UpdateData(FALSE);
	}
	else
	{
		SetWindowText("��������");
		m_strPass = m_strUrl = m_strTag = m_strUser = m_strRemark = "";
		UpdateData(FALSE);
		CEdit * p = (CEdit *)GetDlgItem(IDC_ADDDLG_USER);
		p->SetSel(0, -1);
	}
}
