#pragma once


// CDetailDlg �Ի���

class CDetailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CDetailDlg)

public:
	CDetailDlg(CString strUser, CString strPass, CString strUrl, CString strMak, CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDetailDlg();

// �Ի�������
	enum { IDD = IDD_DETAILDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

private:
	CString m_strUser;
	CString m_strPass;
	CString m_strUrl;
	CString m_strMak;
	CWnd * pPar;

	void CDetailDlg::CopyStr(CString str);

public:
	afx_msg void OnBnClickedDetailReturn();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtndetailUser();
	afx_msg void OnBnClickedBtndetailPass();
	afx_msg void OnBnClickedBtndetailUrl();
	afx_msg void OnBnClickedBtndetailMak();
};
