// FileDialogEx.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PassManager.h"
#include "FileDialogEx.h"


// CFileDialogEx

IMPLEMENT_DYNAMIC(CFileDialogEx, CFileDialog)

CFileDialogEx::CFileDialogEx(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{

}

CFileDialogEx::~CFileDialogEx()
{
}


BEGIN_MESSAGE_MAP(CFileDialogEx, CFileDialog)
END_MESSAGE_MAP()



// CFileDialogEx ��Ϣ�������




BOOL CFileDialogEx::OnFileNameOK()
{
	// TODO: �ڴ����ר�ô����/����û���

	return CFileDialog::OnFileNameOK();
}
