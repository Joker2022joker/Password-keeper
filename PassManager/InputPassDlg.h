#pragma once


// CInputPassDlg �Ի���

class CInputPassDlg : public CDialog
{
	DECLARE_DYNAMIC(CInputPassDlg)

public:
	CInputPassDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputPassDlg();

// �Ի�������
	enum { IDD = IDD_INPUTPASS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedPasscancel();
	CString CInputPassDlg::getPassword();

private:
	CString m_strPass;
public:
	afx_msg void OnBnClickedPassok();
};
