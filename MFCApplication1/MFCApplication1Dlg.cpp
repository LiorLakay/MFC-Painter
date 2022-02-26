
// MFCApplication1Dlg.cpp : implementation file
//
//********add includes of rectangle/circle etc. here!********
#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"
#include "myShape.h"
#include "myRectangle.h"
#include "mySegment.h"
#include "myCircle.h"
#include "myTriangle.h"
#include "myHexagon.h"
#include "dragNrefill.h"
#include "myRectCirc.h"
#include "myRectLine.h"

using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplication1Dlg dialog



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, editTextBox(_T("Welcome to my painter"))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	pressed = FALSE;
	whichShape=1;
	currShape = NULL;
	//currMode = Paint;
	currMode = Paint;
	inside = 0;
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, ID_editTextBox, editTextBox);
	DDX_Control(pDX, IDC_REDO_BTN, redoBTN);
	DDX_Control(pDX, IDC_UNDO_BTN, undoBTN);
	DDX_Control(pDX, IDC_SLIDER_CTRL, sliderCtrl);
	DDX_Control(pDX, IDC_BUTTON_DRAG, dragBTN);
	DDX_Control(pDX, IDC_BUTTON_REFILL, refillBTN);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_RADIO_LINE, &CMFCApplication1Dlg::OnBnClickedRadioLine)
	ON_BN_CLICKED(IDC_RADIO_RECT, &CMFCApplication1Dlg::OnBnClickedRadioRect)
	ON_BN_CLICKED(IDC_RADIO_CIRC, &CMFCApplication1Dlg::OnBnClickedRadioCirc)
	ON_BN_CLICKED(IDC_RADIO_TRIANGLE, &CMFCApplication1Dlg::OnBnClickedRadioTriangle)
	ON_COMMAND(ID_MENU_FILE_SAVE, &CMFCApplication1Dlg::OnMenuFileSave)
	ON_COMMAND(ID_MENU_FILE_LOAD, &CMFCApplication1Dlg::OnMenuFileLoad)
	ON_COMMAND(ID_MENU_FILE_NEW, &CMFCApplication1Dlg::OnMenuFileNew)
	ON_BN_CLICKED(IDC_REDO_BTN, &CMFCApplication1Dlg::OnBnClickedRedoBtn)
	ON_BN_CLICKED(IDC_UNDO_BTN, &CMFCApplication1Dlg::OnBnClickedUndoBtn)
	ON_BN_CLICKED(IDC_RADIO_HEXAGON, &CMFCApplication1Dlg::OnBnClickedRadioHexagon)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_CTRL, &CMFCApplication1Dlg::OnNMCustomdrawSliderCtrl)
ON_BN_CLICKED(IDC_BUTTON_FG_COLOR, &CMFCApplication1Dlg::OnBnClickedButtonFgColor)
ON_BN_CLICKED(IDC_BUTTON_BG_COLOR, &CMFCApplication1Dlg::OnBnClickedButtonBgColor)
ON_BN_CLICKED(IDC_BUTTON_DRAG, &CMFCApplication1Dlg::OnBnClickedButtonDrag)
ON_BN_CLICKED(IDC_BUTTON_REFILL, &CMFCApplication1Dlg::OnBnClickedButtonRefill)
ON_BN_CLICKED(IDC_RADIO_RECT_CIRC, &CMFCApplication1Dlg::OnBnClickedRadioRectCirc)
ON_BN_CLICKED(IDC_RADIO_RECT_LINE, &CMFCApplication1Dlg::OnBnClickedRadioRectLine)
END_MESSAGE_MAP()


// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);
	dragBTN.ModifyStyle(0, BS_ICON);
	HICON drag = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON1),
		IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	dragBTN.SetIcon(drag);

	refillBTN.ModifyStyle(0, BS_ICON);
	HICON refill = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON2),
		IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	refillBTN.SetIcon(refill);

	undoBTN.ModifyStyle(0, BS_ICON);
	HICON undo = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON3),
		IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	undoBTN.SetIcon(undo);

	redoBTN.ModifyStyle(0, BS_ICON);
	HICON redo = (HICON)LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON4),
		IMAGE_ICON, 50, 50, LR_DEFAULTCOLOR);
	redoBTN.SetIcon(redo);


	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	CheckRadioButton(IDC_RADIO_LINE, IDC_RADIO_RECT_LINE, IDC_RADIO_LINE);
	redoBTN.EnableWindow(FALSE);
	undoBTN.EnableWindow(FALSE);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC dc(this);
		DrawAllShapes(&dc);
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (pressed) {
		if (currMode == Paint) {
			currShape->setEnd(point);
			Invalidate();
		}
		else if (currMode == Drag && inside) {
			int index = shapes.GetSize() - 1;
			shapes[index]->start.x = point.x - delX;
			shapes[index]->start.y = point.y - delY;
			shapes[index]->end.x = point.x + deldelX;
			shapes[index]->end.y = point.y + deldelY;

			Invalidate();
		}
	}
	
	CDialogEx::OnMouseMove(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	pressed = TRUE;
	//undoBTN.EnableWindow(TRUE);
	//redoBTN.EnableWindow(FALSE);
	
	if (currMode == Paint) {
		undoBTN.EnableWindow(TRUE);

		switch (whichShape)
		{
		case 1:
			shapes.Add(new mySegment(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		case 2:
			shapes.Add(new myRectangle(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		case 3:
			shapes.Add(new myCircle(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		case 4:
			shapes.Add(new myTriangle(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		case 5:
			shapes.Add(new myHexagon(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		case 6:
			shapes.Add(new myRectCirc(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		case 7:
			shapes.Add(new myRectLine(point, point));
			currShape = shapes[shapes.GetSize() - 1];
			break;
		}
	}
	else if (currMode == Drag) {
		
		for (int i = shapes.GetSize() - 1; i >= 0; i--) {
			if (shapes[i]->isInside(point)) {
				inside = 1;
				delX = point.x - shapes[i]->start.x;
				delY = point.y - shapes[i]->start.y;
				deldelX = shapes[i]->end.x - point.x;
				deldelY = shapes[i]->end.y - point.y;
				
				myShape::fColor = shapes[i]->getFColor();
				myShape::bColor = shapes[i]->getBColor();
				myShape::thickness = shapes[i]->getThickness();

				
				if (shapes[i]->getId()==2)
					currShape = new myRectangle(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 3)
					currShape = new myCircle(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 4)
					currShape = new myTriangle(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 5)
					currShape = new myHexagon(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 6)
					currShape = new myRectCirc(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 7)
					currShape = new myRectLine(shapes[i]->getStart(), shapes[i]->getEnd());
				
				dragNrefill drag(shapes, currShape, shapes[i]);
				drag.perform();
				break;
			}
			
		}
			
	}
	else if (currMode == Refill) {
		pressed = FALSE;
		for (int i = shapes.GetSize() - 1; i >= 0; i--) {
			if (shapes[i]->isInside(point)) {

				if (shapes[i]->getId() == 2)
					currShape = new myRectangle(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 3)
					currShape = new myCircle(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 4)
					currShape = new myTriangle(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 5)
					currShape = new myHexagon(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 6)
					currShape = new myRectCirc(shapes[i]->getStart(), shapes[i]->getEnd());
				else if (shapes[i]->getId() == 7)
					currShape = new myRectLine(shapes[i]->getStart(), shapes[i]->getEnd());

				currShape->setBColor(shapes[i]->getFColor());
				currShape->setThickness(shapes[i]->getThickness());
				currShape->setBColor(refillColor);
				dragNrefill refill(shapes, currShape, shapes[i]);
				refill.perform();
				Invalidate();
				break;
			}
		}
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (pressed) {
		pressed = FALSE;
		if (currMode == Paint) {
			currShape->setEnd(point);
			Invalidate();
		}
		else if (currMode == Drag && inside) {
			int index = shapes.GetSize() - 1;
			shapes[index]->start.x = point.x - delX;
			shapes[index]->start.y = point.y - delY;
			shapes[index]->end.x = point.x + deldelX;
			shapes[index]->end.y = point.y + deldelY;
			inside = 0;
			Invalidate();
		}
	}
	CDialogEx::OnLButtonUp(nFlags, point);
}


void CMFCApplication1Dlg::DrawAllShapes(CDC* dc) const
{
	for (int i = 0; i < shapes.GetSize(); i++) {
		shapes[i]->draw(dc);
	}
}

void CMFCApplication1Dlg::OnBnClickedRadioLine()
{
	editTextBox = _T("Line");
	UpdateData(FALSE);
	whichShape = 1;
	currMode = Paint;
}


void CMFCApplication1Dlg::OnBnClickedRadioRect()
{
	editTextBox = _T("Rectangle");
	UpdateData(FALSE);
	whichShape = 2;
	currMode = Paint;
}


void CMFCApplication1Dlg::OnBnClickedRadioCirc()
{
	editTextBox = _T("Circle");
	UpdateData(FALSE);
	whichShape = 3;
	currMode = Paint;
}

void CMFCApplication1Dlg::OnBnClickedRadioTriangle()
{
	editTextBox = _T("Triangle");
	UpdateData(FALSE);
	whichShape = 4;
	currMode = Paint;
}

CMFCApplication1Dlg::~CMFCApplication1Dlg()
{
	for (int i = 0; i < shapes.GetSize(); i++)
	{
		delete shapes[i];
	}
}


void CMFCApplication1Dlg::OnMenuFileSave()
{
	CFileDialog dlg(FALSE, _T(".shapes"), NULL, 0, _T("Shapes (*.shapes)|*.shapes|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		shapes.Serialize(ar);
		ar.Close();
		file.Close();
	}
}


void CMFCApplication1Dlg::OnMenuFileLoad()
{
	CFileDialog dlg(TRUE, _T(".shapes"), NULL, 0, _T("Shapes (*.shapes)|*.shapes|All Files (*.*)|*.*||"));
	CString filename;
	if (dlg.DoModal() == IDOK)
	{
		filename = dlg.GetPathName(); // return full path and filename
		CFile file(filename, CFile::modeRead);
		CArchive ar(&file, CArchive::load);
		shapes.Serialize(ar);
		ar.Close();
		file.Close();
		Invalidate();
	}
}


void CMFCApplication1Dlg::OnMenuFileNew()
{
	shapes.RemoveAll();
	redoBTN.EnableWindow(FALSE);
	undoBTN.EnableWindow(FALSE);
	while(!todo.empty())
		todo.top();
	Invalidate();
}


void CMFCApplication1Dlg::OnBnClickedRedoBtn()
{

	undoBTN.EnableWindow(TRUE);
	
	if (todo.size()<=1) {
		if (todo.empty())
			return;
		else
			redoBTN.EnableWindow(FALSE);
	}
	shapes.Add(todo.top());
	Invalidate();
	todo.pop();
}


void CMFCApplication1Dlg::OnBnClickedUndoBtn()
{


	redoBTN.EnableWindow(TRUE);
	
	int max = shapes.GetCount() - 1;
	
	if (max >= 0) {
		if (max == 0)
			undoBTN.EnableWindow(FALSE);

		todo.push(shapes[max]);
		shapes.RemoveAt(max);
		Invalidate();
	}
	else
		undoBTN.EnableWindow(FALSE);
}


void CMFCApplication1Dlg::OnBnClickedRadioHexagon()
{
	editTextBox = _T("Hexagon");
	UpdateData(FALSE);
	whichShape = 5;
	currMode = Paint;
}


void CMFCApplication1Dlg::OnNMCustomdrawSliderCtrl(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	myShape::thickness = sliderCtrl.GetPos();
	SetIcon(m_hIcon, TRUE);            // Set big icon
	SetIcon(m_hIcon, FALSE);
	//sliderCtrl.SetCapture();
	
	*pResult = 0;
}


void CMFCApplication1Dlg::OnBnClickedButtonFgColor()
{
	CColorDialog dlg;
	if (dlg.DoModal() == IDOK)
	{
		myShape::fColor = dlg.GetColor();
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonBgColor()
{
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		myShape::bColor = dlg.GetColor();
	}
}


void CMFCApplication1Dlg::OnBnClickedButtonDrag()
{
	editTextBox = _T("Drag mode");
	UpdateData(FALSE);
	currMode = Drag;

	((CButton*)GetDlgItem(IDC_RADIO_LINE))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_RECT))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_CIRC))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_TRIANGLE))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_HEXAGON))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_RECT_CIRC))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_RECT_LINE))->SetCheck(BST_UNCHECKED);
}


void CMFCApplication1Dlg::OnBnClickedButtonRefill()
{
	CColorDialog dlg;
	if (dlg.DoModal()==IDOK)
	{
		refillColor = dlg.GetColor();
		currMode = Refill;
		editTextBox = _T("Refill mode");
		UpdateData(FALSE);
	}

	((CButton*)GetDlgItem(IDC_RADIO_LINE))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_RECT))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_CIRC))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_TRIANGLE))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_HEXAGON))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_RECT_CIRC))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_RECT_LINE))->SetCheck(BST_UNCHECKED);
	
}


void CMFCApplication1Dlg::OnBnClickedRadioRectCirc()
{
	editTextBox = _T("Rectangle + Circle");
	UpdateData(FALSE);
	whichShape = 6;
	currMode = Paint;
}


void CMFCApplication1Dlg::OnBnClickedRadioRectLine()
{
	editTextBox = _T("Rectangle + Line");
	UpdateData(FALSE);
	whichShape = 7;
	currMode = Paint;
}
