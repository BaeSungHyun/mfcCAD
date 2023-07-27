
// mfcproject1Doc.h : interface of the Cmfcproject1Doc class
//


#pragma once
#include <gl/GL.h>
#include <gl/GLU.h>
#include "GLprimitive.h"

class Cmfcproject1Doc : public CDocument
{
protected: // create from serialization only
	Cmfcproject1Doc() noexcept;
	DECLARE_DYNCREATE(Cmfcproject1Doc)

// Attributes
public:
	size_t pointCapacity{ 0 };
	size_t lineCapacity{ 0 };

	point* points;
	Line* lines;

	
// Operations
public:

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~Cmfcproject1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
