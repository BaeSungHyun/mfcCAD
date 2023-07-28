
// mfcproject1View.cpp : implementation of the Cmfcproject1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "mfcproject1.h"
#endif

#include "mfcproject1Doc.h"
#include "mfcproject1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cmfcproject1View

IMPLEMENT_DYNCREATE(Cmfcproject1View, CView)

BEGIN_MESSAGE_MAP(Cmfcproject1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_GEO_POINT, &Cmfcproject1View::OnGeoPoint)
	ON_COMMAND(ID_GEO_LINE, &Cmfcproject1View::OnGeoLine)
END_MESSAGE_MAP()

// Cmfcproject1View construction/destruction

Cmfcproject1View::Cmfcproject1View() noexcept
	:m_hRC(0), m_pDC(0), sceneRotate(0), aspect_ratio(0), cx{ 0 }, cy{ 0 }, mouseStart(0, 0)
{
	// TODO: add construction code here
	pLinedlg = NULL;
	// Initialize rotationMatrix to Identity Matrix

}

Cmfcproject1View::~Cmfcproject1View() {
	delete pLinedlg;
}


BOOL Cmfcproject1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Cmfcproject1View drawing

void Cmfcproject1View::OnDraw(CDC* /*pDC*/)
{
	Cmfcproject1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
	::glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	PreRenderScene();

	::glPushMatrix();
	ThreeDimAxis();
	::glPopMatrix();

	::glPushMatrix();
	::glColor3f(0.0f, 0.0f, 0.0f);
	::glPointSize(1.0f);
	::glBegin(GL_POINTS);
	for (int i = 0; i < pDoc->pointCapacity; ++i)
		::glVertex3f(pDoc->points[i].getPointX(), pDoc->points[i].getPointY(), pDoc->points[i].getPointZ());
	::glEnd();
	::glPopMatrix();

	::glPushMatrix();
	::glColor3f(0.0f, 0.0f, 0.0f);
	::glLineWidth(1.0f);
	for (int j = 0; j < pDoc->lineCapacity; ++j) {
		pDoc->lines[j].createList();
	}
	::glPopMatrix();


	::glFinish();

	if (FALSE == ::SwapBuffers(m_pDC->GetSafeHdc()))
		return;
}


// Cmfcproject1View printing

BOOL Cmfcproject1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void Cmfcproject1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void Cmfcproject1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// Cmfcproject1View diagnostics

#ifdef _DEBUG
void Cmfcproject1View::AssertValid() const
{
	CView::AssertValid();
}

void Cmfcproject1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

Cmfcproject1Doc* Cmfcproject1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(Cmfcproject1Doc)));
	return (Cmfcproject1Doc*)m_pDocument;
}
#endif //_DEBUG

BOOL Cmfcproject1View::InitializeOpenGL() {
	m_pDC = new CClientDC(this);

	if (NULL == m_pDC) {
		return FALSE;
	}

	if (!SetupPixelFormat())
		return FALSE;

	if (0 == (m_hRC = ::wglCreateContext(m_pDC->GetSafeHdc()))) {
		return FALSE;
	}

	if (FALSE == ::wglMakeCurrent(m_pDC->GetSafeHdc(), m_hRC)) {
		return FALSE;
	}

	::glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	::glClearDepth(1.0f);
	::glEnable(GL_DEPTH_TEST);

	sceneRotate = 30.0f;

	return TRUE;
}

BOOL Cmfcproject1View::SetupPixelFormat() {
	static PIXELFORMATDESCRIPTOR pfd = {
		sizeof(PIXELFORMATDESCRIPTOR), // size of this pfd
		1, // version number
		PFD_DRAW_TO_WINDOW | // support window
		PFD_SUPPORT_OPENGL | // support Opengl
		PFD_DOUBLEBUFFER, // double buffered
		PFD_TYPE_RGBA, // RGBA type
		24, // 24-bit color depth
		0, 0, 0, 0, 0, 0, // color bits ignored
		0, // no alpha buffer
		0, // shift bit ignored
		0, // no accumulation buffer
		0, 0, 0, 0, // accum bits ignored
		// 32,      // 32-bit z-buffer
		16, // NOTE: better preformance with 16-bit z-buffer
		0, // no stencil buffer
		0, // no auxiliary buffer
		PFD_MAIN_PLANE, // main layer
		0, // reserved
		0, 0, 0 // layer masks ignored
	};

	int pixelformat;

	if (0 == (pixelformat = ::ChoosePixelFormat(m_pDC->GetSafeHdc(), &pfd))) {
		return FALSE;
	}

	if (FALSE == ::SetPixelFormat(m_pDC->GetSafeHdc(), pixelformat, &pfd)) {
		return FALSE;
	}

	return TRUE;
}

// Viewport Transformation
BOOL Cmfcproject1View::SetupViewport(int cx, int cy) {
	::glViewport(0, 0, cx, cy);

	return TRUE;
}

// Viewing Transform - chages the position and orientation of the viewpoint
// must be called before Modeling Transform
BOOL Cmfcproject1View::SetupViewingTranform() {
	::glRotated(tempRotation[2], tempRotation[0], tempRotation[1], 0.0f);
	::glMultMatrixd(rotationMatrix);
	::glTranslated( tempTranslate[0] + translate[0], tempTranslate[1] + translate[1], zoom);
	::glTranslatef(0.0f, 0.0f, -cameraBack);
	::glRotated(tempRotate[2], tempRotate[0], tempRotate[1], 0.0f);
	::glMultMatrixd(rotateMatrix);
	::glRotatef(sceneRotate, 1.0f, 0.0f, 0.0f);
	::glRotatef(-45, 0.0f, 1.0f, 0.0f);
	// normal 을 어떻게 보관할 수 있을까?
	return TRUE;
}

// Projection Transform - choosing a lens for the camera
BOOL Cmfcproject1View::SetupViewingFrustum(GLdouble fovy, GLdouble aspect_ratio,
	GLdouble zNear, GLdouble zFar) {
	// maybe need to change this based on zoom too
	::gluPerspective(fovy, aspect_ratio, zNear, zFar);
	return TRUE;
}


// Cmfcproject1View message handlers
int Cmfcproject1View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	InitializeOpenGL();
	
	return 0;
}


BOOL Cmfcproject1View::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default

	return CView::OnEraseBkgnd(pDC);
}


void Cmfcproject1View::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	if (m_pDC)
		delete m_pDC;

	if (FALSE == ::wglDeleteContext(m_hRC))
		return;
}

void Cmfcproject1View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	cx = cx;
	cy = cy;

	if (0 >= cx || 0 >= cy)
		return;

	SetupViewport(cx, cy);

	::glMatrixMode(GL_PROJECTION);
	::glLoadIdentity();

	// compute the aspect ratio 
	aspect_ratio = (GLdouble)cx / (GLdouble)cy;

	SetupViewingFrustum(40.0f, aspect_ratio, zNear, zFar);

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();

	SetupViewingTranform();
}

void Cmfcproject1View::ThreeDimAxis() {
	GLfloat origin[4]{ 0.0f, 0.0f, 0.0f, 1 };
	GLfloat x2[4]{100.0f, 0.0f, 0.0f, 1}, y2[4]{ 0.0f, 100.0f, 0.0f, 1 }, z2[4]{ 0.0f, 0.0f, 100.0f, 1 };
	GLfloat xColor[3] = { 1.0f, 0.0f, 0.0f };
	GLfloat yColor[3] = { 0.0f, 1.0f, 0.0f };
	GLfloat zColor[3] = { 0.0f, 0.0f, 1.0f };

	::glBegin(GL_LINES);
	
	::glColor3fv(xColor);
	::glVertex4fv(origin);
	::glVertex3fv(x2);

	::glColor3fv(yColor);
	::glVertex4fv(origin);
	::glVertex4fv(y2);

	::glColor3fv(zColor);
	::glVertex4fv(origin);
	::glVertex4fv(z2);

	::glEnd();
}

BOOL Cmfcproject1View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default 
	
	// controlled Viewing Volume


	// zoom max limit
	if (zoom >= cameraBack) {
		zoom = cameraBack;
		if (zDelta < 0) {
			zoom += (GLfloat)(zDelta / 120 - 0.5);
		}
		return TRUE;
	}
	// zoom betweein max and min - phase 1
	else if (zoom < cameraBack && zoom >= cameraBack * 0.666) {
		zoom += (GLfloat)(zDelta / 120) * 0.5f;
	}
	// zoom between max and min - phase 2
	else if (zoom < cameraBack * 0.666f && zoom >= cameraBack - zFar) {
		zoom += (GLfloat)(zDelta / 120);
	}
	// zoom min limit
	else {
		zoom = cameraBack - zFar;
		if (zDelta > 0) {
			zoom += (GLfloat)(zDelta/120);
		}
		return TRUE;
	}
	
	

	::glMatrixMode(GL_MODELVIEW);
	::glLoadIdentity();
	SetupViewingTranform();

	Invalidate();

	// control the primitives
	/*
	::glLoadIdentity();
	SetupViewingTranform();
	::glTranslatef(0.0f, 0.0f, -1.0f);
	::glPopMatrix();

	Invalidate();
	*/

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void Cmfcproject1View::rotationStepper(GLdouble* temp, GLdouble* matrix) {
	// Normalize
	GLdouble norm = sqrt(temp[0] * temp[0] + temp[1] * temp[1]);
	if (norm == 0)
		return;
	temp[0] = temp[0] / norm;
	temp[1] = temp[1] / norm;

	GLdouble pi{ acos(-1) };
	temp[2] = temp[2] * pi / 180;

	GLdouble tempMatrix[16];
	tempMatrix[0] = temp[0] * temp[0] * (1 - cos(temp[2])) + cos(temp[2]);
	tempMatrix[4] = temp[0] * temp[1] * (1 - cos(temp[2]));
	tempMatrix[8] = temp[1] * sin(temp[2]);
	tempMatrix[12] = (GLdouble)0.0;

	tempMatrix[1] = temp[1] * temp[0] * (1 - cos(temp[2]));
	tempMatrix[5] = temp[1] * temp[1] * (1 - cos(temp[2])) + cos(temp[2]);
	tempMatrix[9] = -temp[0] * sin(temp[2]);
	tempMatrix[13] = (GLdouble)0;

	tempMatrix[2] = -temp[1] * sin(temp[2]);
	tempMatrix[6] = temp[0] * sin(temp[2]);
	tempMatrix[10] = cos(temp[2]);
	tempMatrix[14] = (GLdouble)0;

	tempMatrix[3] = (GLdouble)0;
	tempMatrix[7] = (GLdouble)0;
	tempMatrix[11] = (GLdouble)0;
	tempMatrix[15] = (GLdouble)1;

	matrixMulti(tempMatrix, matrix);
}


void Cmfcproject1View::rotateStepper(GLdouble* temp, GLdouble* matrix) {
	// Normalize
	GLdouble norm = sqrt(temp[0] * temp[0] + temp[1] * temp[1]);
	if (norm == 0)
		return;
	temp[0] = temp[0] / norm;
	temp[1] = temp[1] / norm;

	GLdouble pi{ acos(-1) };
	temp[2] = temp[2] * pi / 180;

	GLdouble tempMatrix[16];
	tempMatrix[0] = temp[0] * temp[0] * (1 - cos(temp[2])) + cos(temp[2]);
	tempMatrix[4] = temp[0] * temp[1] * (1 - cos(temp[2]));
	tempMatrix[8] = temp[1] * sin(temp[2]);
	tempMatrix[12] = (GLdouble)0.0;

	tempMatrix[1] = temp[1] * temp[0] * (1 - cos(temp[2]));
	tempMatrix[5] = temp[1] * temp[1] * (1 - cos(temp[2])) + cos(temp[2]);
	tempMatrix[9] = - temp[0] * sin(temp[2]);
	tempMatrix[13] = (GLdouble)0;

	tempMatrix[2] = - temp[1] * sin(temp[2]);
	tempMatrix[6] = temp[0] * sin(temp[2]);
	tempMatrix[10] = cos(temp[2]);
	tempMatrix[14] = (GLdouble)0;

	tempMatrix[3] = (GLdouble)0;
	tempMatrix[7] = (GLdouble)0;
	tempMatrix[11] = (GLdouble)0;
	tempMatrix[15] = (GLdouble)1;

	matrixMulti(tempMatrix, matrix);
}


void Cmfcproject1View::OnRButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_CONTROL) {
		rotationRButton = TRUE;
		mouseStart = point;
	}
	else if (nFlags & MK_SHIFT) { 
		translateRButton = TRUE;
		mouseStart = point;
	}
	else {
		rotateRButton = TRUE;
		mouseStart = point;
	}

	CView::OnRButtonDown(nFlags, point); // Only when you need OS default controls
}


void Cmfcproject1View::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags & MK_CONTROL && nFlags & MK_RBUTTON) {
		tempRotation[0] = static_cast<GLdouble>(-mouseStart.y + point.y);
		tempRotation[1] = static_cast<GLdouble>(-mouseStart.x + point.x);
		
		tempRotation[2] = sqrt(tempRotation[0] * tempRotation[0] + tempRotation[1] * tempRotation[1]) / cameraBack;

		::glLoadIdentity();
		SetupViewingTranform();
		Invalidate();
	}
	else if (nFlags & MK_SHIFT && nFlags & MK_RBUTTON) {
		tempTranslate[0] = static_cast<GLdouble>(point.x - mouseStart.x)/ cameraBack;
		tempTranslate[1] = static_cast<GLdouble>(mouseStart.y - point.y)/cameraBack;

		::glLoadIdentity();
		SetupViewingTranform();
		Invalidate();
	}
	else if (nFlags & MK_RBUTTON) {
		tempRotate[0] = static_cast<GLdouble>(-mouseStart.y + point.y);
		tempRotate[1] = static_cast<GLdouble>(-mouseStart.x + point.x);

		tempRotate[2] = sqrt(tempRotate[0] * tempRotate[0] + tempRotate[1] * tempRotate[1] + 1) / cameraBack;

		::glLoadIdentity();
		SetupViewingTranform();
		Invalidate();
	}
	CView::OnMouseMove(nFlags, point);
}


void Cmfcproject1View::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	if (rotationRButton) {
		rotationStepper(tempRotation, rotationMatrix);

		tempRotation[0] = 0.0;
		tempRotation[1] = 0.0;
		tempRotation[2] = 0.0;
		::glLoadIdentity();
		SetupViewingTranform();
		Invalidate();
		rotationRButton = FALSE;
	}
	else if (translateRButton) {
		translate[0] += tempTranslate[0];
		translate[1] += tempTranslate[1];

		tempTranslate[0] = tempTranslate[1] = 0.0;
		::glLoadIdentity();
		SetupViewingTranform();
		Invalidate();
		translateRButton = FALSE;
	}
	else if (rotateRButton) {
		rotateStepper(tempRotate, rotateMatrix);

		tempRotate[0] = 0.0;
		tempRotate[1] = 0.0;
		tempRotate[2] = 0.0;
		::glLoadIdentity();
		SetupViewingTranform();
		Invalidate();
		rotateRButton = FALSE;
	}

	
	CView::OnRButtonUp(nFlags, point);
}

void Cmfcproject1View::OnGeoPoint()
{
	// TODO: Add your command handler code here
	Cmfcproject1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	PointDialog dlg;
	dlg.point_x = x;
	dlg.point_y = y;
	dlg.point_z = z;

	int result = dlg.DoModal(); // Open modal dialog box
	if (result == IDOK) {
		x = dlg.point_x;
		y = dlg.point_y;
		z = dlg.point_z;
		
		Point* temp = new Point[pDoc->pointCapacity + 1];
		if (pDoc->points != nullptr) {
			for (size_t i = 0; i < pDoc->pointCapacity; ++i) {
				Point newPoint;
				newPoint.setPoint(x, y, z);
				temp[i].pushPoint(newPoint);
			}
			delete[] pDoc->points;
			pDoc->points = temp;
		}

		pDoc->points[pDoc->pointCapacity].setPoint(x,y,z);
		pDoc->pointCapacity += 1;

		pDoc->SetModifiedFlag();
		pDoc->UpdateAllViews(NULL);
	}
}


void Cmfcproject1View::OnGeoLine()
{
	// TODO: Add your command handler code here
	if (pLinedlg != NULL) {
		pLinedlg->SetFocus();
	}
	else {
		pLinedlg = new LineDialog(this); // create new object
		pLinedlg->pView = this;
		pLinedlg->createDialog();
		pLinedlg->lineX = 0;
		pLinedlg->lineY = 0;
		pLinedlg->lineZ = 0;

		pLinedlg->Create(IDD_LINE);
		pLinedlg->ShowWindow(SW_SHOW);
	}


}
