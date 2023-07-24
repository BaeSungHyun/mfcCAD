
// mfcproject1View.h : interface of the Cmfcproject1View class
//


#include <gl/GL.h>
#include <gl/GLU.h>
#include "PointDialog.h"

#pragma once

template <typename T>
void matrixMulti(T* a, T* b) { // save the result inside matrix 'a'
	T c[16]{ 0 };
	c[0] = a[0] * b[0] + a[4] * b[1] + a[8] * b[2] + a[12] * b[3];
	c[1] = a[1] * b[0] + a[5] * b[1] + a[9] * b[2] + a[13] * b[3];
	c[2] = a[2] * b[0] + a[6] * b[1] + a[10] * b[2] + a[14] * b[3];
	c[3] = a[3] * b[0] + a[7] * b[1] + a[11] * b[2] + a[15] * b[3];

	c[4] = a[0] * b[4] + a[4] * b[5] + a[8] * b[6] + a[12] * b[7];
	c[5] = a[1] * b[4] + a[5] * b[5] + a[9] * b[6] + a[13] * b[7];
	c[6] = a[2] * b[4] + a[6] * b[5] + a[10] * b[6] + a[14] * b[7];
	c[7] = a[3] * b[4] + a[7] * b[5] + a[11] * b[6] + a[15] * b[7];


	c[8] = a[0] * b[8] + a[4] * b[9] + a[8] * b[10] + a[12] * b[11];
	c[9] = a[1] * b[8] + a[5] * b[9] + a[9] * b[10] + a[13] * b[11];
	c[10] = a[2] * b[8] + a[6] * b[9] + a[10] * b[10] + a[14] * b[11];
	c[11] = a[3] * b[8] + a[7] * b[9] + a[11] * b[10] + a[15] * b[11];


	c[12] = a[0] * b[12] + a[4] * b[13] + a[8] * b[14] + a[12] * b[15];
	c[13] = a[1] * b[12] + a[5] * b[13] + a[9] * b[14] + a[13] * b[15];
	c[14] = a[2] * b[12] + a[6] * b[13] + a[10] * b[14] + a[14] * b[15];
	c[15] = a[3] * b[12] + a[7] * b[13] + a[11] * b[14] + a[15] * b[15];

	for (int i = 0; i < 16; ++i)
		b[i] = c[i];
}

class Cmfcproject1View : public CView
{
protected: // create from serialization only
	Cmfcproject1View() noexcept;
	DECLARE_DYNCREATE(Cmfcproject1View)

// Attributes
public:
	Cmfcproject1Doc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~Cmfcproject1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	// Pixel Format
	virtual BOOL SetupPixelFormat(void); 

	// On_Size
	virtual BOOL SetupViewport(int cx, int cy);
	virtual BOOL SetupViewingFrustum(GLdouble fovy, GLdouble aspect_ratio,
		GLdouble zNear, GLdouble zFar);
	virtual BOOL SetupViewingTranform(void);
	
	// Render
	virtual BOOL PreRenderScene(void) { return TRUE; }
	virtual void ThreeDimAxis(void);

	virtual void rotationStepper(GLdouble* temp, GLdouble* matrix);
	virtual void rotateStepper(GLdouble* temp, GLdouble* matrix);

private:
	BOOL InitializeOpenGL();

	// window coordinates
	GLfloat x{ 0 }, y{ 0 }, z{ 0 };

	int cx, cy;
	
	HGLRC m_hRC; // rendering context
	CDC* m_pDC;

	GLfloat sceneRotate;
	GLdouble aspect_ratio;
	GLdouble zoom{ 0.0 };

	GLdouble tempTranslate[2]{ 0 };
	GLdouble translate[2]{ 0 };

	GLdouble tempRotation[3]{ 0 };
	GLdouble rotationMatrix[16] = {(GLdouble)1 , (GLdouble)0, (GLdouble)0, (GLdouble)0,
									(GLdouble)0, (GLdouble)1, (GLdouble)0, (GLdouble)0,
									(GLdouble)0, (GLdouble)0, (GLdouble)1, (GLdouble)0,
									(GLdouble)0, (GLdouble)0, (GLdouble)0, (GLdouble)1};

	GLdouble tempRotate[3]{ 0 };
	GLdouble rotateMatrix[16] = { (GLdouble)1 , (GLdouble)0, (GLdouble)0, (GLdouble)0,
									(GLdouble)0, (GLdouble)1, (GLdouble)0, (GLdouble)0,
									(GLdouble)0, (GLdouble)0, (GLdouble)1, (GLdouble)0,
									(GLdouble)0, (GLdouble)0, (GLdouble)0, (GLdouble)1 };

	GLfloat zNear{ 0.1f };
	GLfloat zFar{ 100.0f };

	GLfloat cameraBack{ 20.0f };

	CPoint mouseStart;	
	BOOL rotationRButton{ FALSE };
	BOOL translateRButton{ FALSE };
	BOOL rotateRButton{ FALSE };

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnGeoPoint();
};

#ifndef _DEBUG  // debug version in mfcproject1View.cpp
inline Cmfcproject1Doc* Cmfcproject1View::GetDocument() const
   { return reinterpret_cast<Cmfcproject1Doc*>(m_pDocument); }
#endif

