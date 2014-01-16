#pragma once
#include "afxwin.h"


// COptionDlg �Ի���

class COptionDlg : public CDialogEx
{
	DECLARE_DYNAMIC(COptionDlg)

public:
	COptionDlg(CString strIniName, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~COptionDlg();

// �Ի�������
	enum { IDD = IDD_OPTIONDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	int COptionDlg::SetAutoRun(int bAutoRun);
	int COptionDlg::SetFileRele(int bRele);
	CString m_IniFileName;
	CString m_errStr;
	bool bAutoChng;
	bool bReleChng;
	bool bInitAuto;
	bool bInitRele;
	bool COptionDlg::setFileAssociation(CString ext,  //��׺��.pas��
		CString applicationName,  //�����ַ
		CString progId, // һ������"PK_File"
		CString defaultIcon,  //Ĭ��ͼ��
		CString description); //����
	bool COptionDlg::isAutoRun();
	bool COptionDlg::isReleFile();
	bool COptionDlg::delFileAssociation();

public:
	afx_msg void OnBnClickedOptiondlgCancel();
	afx_msg void OnBnClickedOptiondlgOk();
private:
	CButton m_AutoRun;
	//CButton m_HidePass;
	CButton m_RelePas;
//	virtual void PreInitDialog();
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOptiondlgConn();
	afx_msg void OnBnClickedOptiondlgAutorun();
};
