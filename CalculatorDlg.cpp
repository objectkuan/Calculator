// CalculatorDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "Calculator.h"
#include "CalculatorDlg.h"
#include "ExpressionHandler.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCalculatorDlg 对话框




CCalculatorDlg::CCalculatorDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCalculatorDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	arc=false;
	hyp=false;
	srand(time(NULL));
}

void CCalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_DISPLAYER, displayer);
}

BEGIN_MESSAGE_MAP(CCalculatorDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_SIN, &CCalculatorDlg::OnBnClickedButtonSin)
	ON_BN_CLICKED(IDC_BUTTON_COS, &CCalculatorDlg::OnBnClickedButtonCos)
	ON_BN_CLICKED(IDC_BUTTON_PREV, &CCalculatorDlg::OnBnClickedButtonPrev)
	ON_BN_CLICKED(IDC_BUTTON_RND, &CCalculatorDlg::OnBnClickedButtonRnd)
	ON_BN_CLICKED(IDC_BUTTON_TAN, &CCalculatorDlg::OnBnClickedButtonTan)
	ON_BN_CLICKED(IDC_BUTTON_COT, &CCalculatorDlg::OnBnClickedButtonCot)
	ON_BN_CLICKED(IDC_BUTTON_NEXT, &CCalculatorDlg::OnBnClickedButtonNext)
	ON_BN_CLICKED(IDC_BUTTON_ARC, &CCalculatorDlg::OnBnClickedButtonArc)
	ON_BN_CLICKED(IDC_BUTTON_SEC, &CCalculatorDlg::OnBnClickedButtonSec)
	ON_BN_CLICKED(IDC_BUTTON_CSC, &CCalculatorDlg::OnBnClickedButtonCsc)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, &CCalculatorDlg::OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_HYP, &CCalculatorDlg::OnBnClickedButtonHyp)
	ON_BN_CLICKED(IDC_BUTTON_7, &CCalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON_8, &CCalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON_9, &CCalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON_0, &CCalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTON_4, &CCalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON_5, &CCalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON_6, &CCalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON_1, &CCalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON_2, &CCalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON_3, &CCalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON_POINT, &CCalculatorDlg::OnBnClickedButtonPoint)
	ON_BN_CLICKED(IDC_BUTTON_CALC, &CCalculatorDlg::OnBnClickedButtonCalc)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CCalculatorDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SUBTRACT, &CCalculatorDlg::OnBnClickedButtonSubtract)
	ON_BN_CLICKED(IDC_BUTTON_MULTIPLY, &CCalculatorDlg::OnBnClickedButtonMultiply)
	ON_BN_CLICKED(IDC_BUTTON_DIVIDE, &CCalculatorDlg::OnBnClickedButtonDivide)
	ON_BN_CLICKED(IDC_BUTTON_POWER, &CCalculatorDlg::OnBnClickedButtonPower)
	ON_BN_CLICKED(IDC_BUTTON_MOD, &CCalculatorDlg::OnBnClickedButtonMod)
	ON_BN_CLICKED(IDC_BUTTON_BRACKET1, &CCalculatorDlg::OnBnClickedButtonBracket1)
	ON_BN_CLICKED(IDC_BUTTON_BRACKET2, &CCalculatorDlg::OnBnClickedButtonBracket2)
END_MESSAGE_MAP()


// CCalculatorDlg 消息处理程序

BOOL CCalculatorDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CCalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCalculatorDlg::OnBnClickedButtonSin()
{
	int nStart,nEnd;
	int selOffset=0;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	if(arc){
		str2.Append(L"arc");
		selOffset=3;
		arc=false;
	}
	str2.Append(L"sin");
	if(hyp){
		str2.Append(L"h");
		selOffset=1;
		hyp=false;
	}
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+4+selOffset,nStart+4+selOffset);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonCos()
{
	int nStart,nEnd;
	int selOffset=0;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	if(arc){
		str2.Append(L"arc");
		selOffset=3;
		arc=false;
	}
	str2.Append(L"cos");
	if(hyp){
		str2.Append(L"h");
		selOffset=1;
		hyp=false;
	}
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+4+selOffset,nStart+4+selOffset);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonTan()
{
	int nStart,nEnd;
	int selOffset=0;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	if(arc){
		str2.Append(L"arc");
		selOffset=3;
		arc=false;
	}
	str2.Append(L"tan");
	if(hyp){
		str2.Append(L"h");
		selOffset=1;
		hyp=false;
	}
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+4+selOffset,nStart+4+selOffset);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonCot()
{
	int nStart,nEnd;
	int selOffset=0;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	arc=false;
	str2.Append(L"cot");
	if(hyp){
		str2.Append(L"h");
		selOffset=1;
		hyp=false;
	}
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+4+selOffset,nStart+4+selOffset);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonSec()
{
	int nStart,nEnd;
	int selOffset=0;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	arc=false;
	str2.Append(L"sec");
	if(hyp){
		str2.Append(L"h");
		selOffset=1;
		hyp=false;
	}
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+4+selOffset,nStart+4+selOffset);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonCsc()
{
	int nStart,nEnd;
	int selOffset=0;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	arc=false;
	str2.Append(L"csc");
	if(hyp){
		str2.Append(L"h");
		selOffset=1;
		hyp=false;
	}
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+4+selOffset,nStart+4+selOffset);
	displayer.SetFocus();
	
}

void CCalculatorDlg::OnBnClickedButtonClear()
{
	displayer.SetWindowText(L"");
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton0()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"0");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton1()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"1");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton2()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"2");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton3()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"3");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton4()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"4");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton5()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"5");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton6()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"6");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton7()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"7");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton8()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"8");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButton9()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"9");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonPoint()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L".");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonAdd()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"+");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonSubtract()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"-");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonMultiply()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"*");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonDivide()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"/");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonPower()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"^");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonMod()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"%");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonBracket1()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"(");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonBracket2()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L")");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+1,nStart+1);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonCalc()
{
	CString expression,result;
	ExpressionHandler ehr;
	displayer.GetWindowText(expression);
	if(expression.Find('\r')>0)
		expression=expression.Mid(0,expression.Find('\r'));
	try {
		result = ehr.calculate(expression);
		displayer.SetWindowText(expression+L"\r\n="+result);
	}catch(StackEmptyException& sex) {
		AfxMessageBox(L"Please check the expression.");
	}catch(ParenthesesException& px) {
		AfxMessageBox(L"Please check the parentheses.");
	}catch(TokenException& tx){
		AfxMessageBox(L"Please check the token.");
	}catch(ArithmeticException& ax){
		AfxMessageBox(L"Some arithmetic error arises.");
	}
}

void CCalculatorDlg::OnBnClickedButtonArc()
{
	if(arc) {
		arc=false;
	}else{
		arc=true;
		hyp=false;
	}
}

void CCalculatorDlg::OnBnClickedButtonHyp()
{
	if(hyp) {
		hyp=false;
	}else{
		hyp=true;
		arc=false;
	}
}

void CCalculatorDlg::OnBnClickedButtonRnd()
{
	int nStart,nEnd;
	CString str1,str2=L"";
	displayer.GetSel(nStart,nEnd);
	displayer.GetWindowText(str1);
	str2.Append(str1.Mid(0,nStart));
	str2.Append(L"RND");
	str2.Append(str1.Mid(nEnd));
	displayer.SetWindowText(str2);
	displayer.SetSel(nStart+3,nStart+3);
	displayer.SetFocus();
}

void CCalculatorDlg::OnBnClickedButtonPrev()
{
}

void CCalculatorDlg::OnBnClickedButtonNext()
{
}

