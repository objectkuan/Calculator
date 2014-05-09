// CalculatorDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CCalculatorDlg �Ի���
class CCalculatorDlg : public CDialog
{
// ����
public:
	CCalculatorDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CALCULATOR_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��
	bool arc,hyp;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonSin();
	afx_msg void OnBnClickedButtonCos();
	afx_msg void OnBnClickedButtonPrev();
	afx_msg void OnBnClickedButtonRnd();
	afx_msg void OnBnClickedButtonTan();
	afx_msg void OnBnClickedButtonCot();
	afx_msg void OnBnClickedButtonNext();
	afx_msg void OnBnClickedButtonArc();
	afx_msg void OnBnClickedButtonSec();
	afx_msg void OnBnClickedButtonCsc();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonHyp();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButtonPoint();
	afx_msg void OnBnClickedButtonCalc();
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSubtract();
	afx_msg void OnBnClickedButtonMultiply();
	afx_msg void OnBnClickedButtonDivide();
	afx_msg void OnBnClickedButtonPower();
	afx_msg void OnBnClickedButtonMod();
	afx_msg void OnBnClickedButtonBracket1();
	afx_msg void OnBnClickedButtonBracket2();
	CEdit displayer;
};
