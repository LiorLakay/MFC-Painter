
// MFCApplication1Dlg.h : header file
//

#pragma once
#include "myShape.h"
#include "mySegment.h"
#include "myRectangle.h"
#include "myCircle.h"
#include "myTriangle.h"
#include "myHexagon.h"
#include "dragNrefill.h"
#include "myRectCirc.h"
#include "myRectLine.h"
#include <stack>

using namespace std;


// CMFCApplication1Dlg dialog
class CMFCApplication1Dlg : public CDialogEx
{

	CTypedPtrArray<CObArray, myShape*> shapes;
	myShape* currShape;
	bool pressed;
	int whichShape;
	stack <myShape*> todo;
public:
	~CMFCApplication1Dlg();
// Construction
public:
	CMFCApplication1Dlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION1_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString editTextBox;	
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void DrawAllShapes(CDC*)const;
	afx_msg void OnBnClickedRadioLine();
	afx_msg void OnBnClickedRadioRect();
	afx_msg void OnBnClickedRadioCirc();
	afx_msg void OnBnClickedRadioTriangle();
	afx_msg void OnBnClickedRadioHexagon();
	afx_msg void OnBnClickedRadioRectCirc();
	afx_msg void OnBnClickedRadioRectLine();
	afx_msg void OnMenuFileSave();
	afx_msg void OnMenuFileLoad();
	afx_msg void OnMenuFileNew();
	afx_msg void OnBnClickedRedoBtn();
	afx_msg void OnBnClickedUndoBtn();
	CButton redoBTN;
	CButton undoBTN;
	CSliderCtrl sliderCtrl;
	afx_msg void OnNMCustomdrawSliderCtrl(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBnClickedButtonFgColor();
	afx_msg void OnBnClickedButtonBgColor();
	enum myMode{Paint,Refill,Drag};
	myMode currMode;
	afx_msg void OnBnClickedButtonDrag();
	int index;
	double delX, delY, deldelX, deldelY;
	afx_msg void OnBnClickedButtonRefill();
	COLORREF refillColor;
	int inside;
	CButton dragBTN;
	CButton refillBTN;
};
