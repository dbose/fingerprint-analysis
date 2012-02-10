////////////////////////////////////////////////////////////////////////
//
// Author   : Debasish Bose
//
// Email    : quantum1981@vsnl.net
//			  quantum19812001@yahoo.com
//
// Desc.    : Basic image processing functions &
//		      Algorithm implementation of fingerprint matching
//
// Note     :This source code is the confidential property of Debasish Bose,QUANTUM
//           Inc.  All proprietary rights, including but not limited to any trade secret,
//           copyright, patent or trademark rights in and to this source code are the
//           property of Debasish Bose,QUANTUM Inc.  This source code is not to be
//           used, disclosed or reproduced in any form without the express written
//           consent of Debasish Bose,QUANTUM Inc.
//
//////////////////////////////////////////////////////////////////////
//
// Image.h: interface for the CImage,pixel,hsvpixel,CBifurcationPoint
//          UserDefinedFilter,C3By3Filter,C5By5Filter,C7By7Filter,
//          CEndPoint,CMinutiae class(s).
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMAGE_H__DE1DE0E1_BB31_11D6_AF71_9E97648C2C45__INCLUDED_)
#define AFX_IMAGE_H__DE1DE0E1_BB31_11D6_AF71_9E97648C2C45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//////////////////////// Extra Headers ///////////////////////////////
#include <math.h>


class hsvpixel;	 // forward declaration

class pixel  
{
 public:
	void operator=(pixel& p);
	void operator=(hsvpixel& hsv);
	void operator=(COLORREF& crColor);
	bool operator>(pixel& p);
	bool operator>(BYTE x);
	bool operator<(pixel& p);
	bool operator<(BYTE x);

	void color(BYTE R, BYTE G, BYTE B);
	void color(BYTE X);
	void color(float R, float G, float B);
	void color(float X);
	void color(COLORREF cr);

	BYTE intensity();
	void lighten(UINT i);
	void darken(UINT i);
    BYTE Gray();
	bool IsGray();

	BYTE r;
	BYTE g; 
	BYTE b;

};


class hsvpixel  
{
 public:
	void operator= (hsvpixel& hsv);
	void operator= (pixel& p);

	double h;		// hue				[0,360]
	double s;		// saturation		[0,1]
	double v;		// value/brightness [0,1]

};

//////////////////////////////////////////////////////////////////////
////////////////// Filter classes ////////////////////////////////////
//////////////////////////////////////////////////////////////////////
class CImage;
class CUserDefinedFilter
{
	//pure virtual(abstract)class::no implementation now !
 public:
	 virtual COLORREF Filter(CImage* image,UINT m,UINT n)=0;

};


class C3By3Filter : public CUserDefinedFilter
{
 public:
   C3By3Filter();
   float m_kernel[3][3];
   int   m_iDivision;
   int   m_iBias;

   // it must override Filter(...)
   virtual COLORREF Filter(CImage* image,UINT m,UINT n);
};


class C5By5Filter : public CUserDefinedFilter
{
 public:
   C5By5Filter();
   float m_kernel[5][5];
   int   m_iDivision;
   int   m_iBias;

   // it must override Filter(...)
   virtual COLORREF Filter(CImage* image,UINT m,UINT n);
};

class C7By7Filter : public CUserDefinedFilter
{
 public:
   C7By7Filter();
   float m_kernel[7][7];
   int   m_iDivision;
   int   m_iBias;

   // it must override Filter(...)
   virtual COLORREF Filter(CImage* image,UINT m,UINT n);
};

//////////////////////////////////////////////////////////////////////////////
////////////////////////////// Minutiae classes //////////////////////////////
//////////////////////////////////////////////////////////////////////////////
// CMinutiae class

// OOps ! Microsoft's BUG here
// Initially derived from CObject but microsoft has a bug --"when copy-constructor
// or assignment operator of a CObject-derived class is called compiler generates an 
// error".Here TYPE is CObject-derived class.CArray<TYPE,TYPE> class's helper functions
// (Ex : ConstructElements)do call TYPE's copy-constructor(s). 
// Details :: Details symptoms and resolution are give in MSDN::Article ID: Q117794 
class CMinutiae
{
public:
	CMinutiae();
	virtual ~CMinutiae();

//public data members
    CPoint pt;
	float  theta;

};

///////////////////////////////////////////////////////////////////////////////
// CEndPoint class
class CEndPoint : public CMinutiae  
{
public:
	CEndPoint();
	virtual ~CEndPoint();

//specific to CEndPoint
	int iNeighbours;

};

////////////////////////////////////////////////////////////////////////////////
// CBifurcationPoint class
class CBifurcationPoint : public CMinutiae  
{
public:
	CBifurcationPoint();
	virtual ~CBifurcationPoint();

//specific to CBifurcationPoint
	int iNeighbours;

};

////////////////////////////////////////////////////////////////////////////////
// Structures For Tracking Purpose
/*
struct _TriPath
{
	CArray<CPoint,CPoint>  path1;
	CArray<CPoint,CPoint>  path2;
	CArray<CPoint,CPoint>  path3;
};
*/
//////////////////////////////////////////////////////////////////////
//////////////////////// Type Definitions ////////////////////////////
//////////////////////////////////////////////////////////////////////
typedef pixel*                                        imagerow;
typedef pixel**                                       imagematrix;
typedef BYTE**                                        binarymatrix;
typedef bool**                                        boolmatrix;
typedef CArray<CEndPoint*,CEndPoint*>                 END_LIST;
typedef CArray<CBifurcationPoint*,CBifurcationPoint*> BRANCH_LIST;
//typedef struct _TriPath                               TriPath;
typedef CArray<CPoint*,CPoint*>                       PATH;

enum operationtype
{
	UNDO,
	NEGATIVE,
	GRAYINT,
	HISTOGRAMBINARIZE,
	ADAPTIVEBINARIZE,
	FPSEGMENTATION,
	EQUALIZE,
	EDGEDETECTION,
	CONV,
	BLUR,
	NORMALIZE,
	ORIENTATION,
	DRAWCIRCLE,
	DRAWLINE,
	THINNING,
	EXTRACT,
	CORE,
	MARKROI,
	MINUTIAE_FILTERING
};

#define UNDEFINED            -1
#define ROUND(x)        (int)((x)+(0.5))
#define sqr(x)          ((x)*(x))
#define MAXUNDO         20
#define PI              3.1428
#define MAXINTENSITY    255
#define MIN(x,y)        (((x) < (y))?(x):(y))
#define WHITE 0xFF
#define BLACK 0x00
#define NONZERO(x)		(((x) < (0)) ? (0) : (x))
#define fabs_b(x)       (((x) >= (0)) ? (x) : -(x))


//////////////////////////////////////////////////////////////////////////////
/////////////////////////// Basic Image class : CImage  //////////////////////
//////////////////////////////////////////////////////////////////////////////
class CImage :public CBitmap
{

public:
	//constructor & destructor
	CImage();
	virtual ~CImage();
	bool operator==(CImage& image);
	CImage& operator=(CImage& image);
public:
	// inline functions...
	void SetFilename(CString sFilename)       { m_filename = sFilename; };
	void SetOperationType(operationtype type = GRAYINT) { m_type=type; }
	bool OK()							      { return (m_buf != NULL); };
	UINT GetWidth()						      { return m_width;         };
	UINT GetHeight()                          { return m_height;		  };
	CString GetFilename()				      { return m_filename;	  };
	operator HBITMAP() const  
	{
		if (m_buf == NULL)
			return NULL;
		else
			return CBitmap::operator HBITMAP();
	}

public:
	//public data member
	LPBITMAPINFOHEADER   m_pbihdr;		 //bitmap info header

	// HGLOBAL related functions
	void DeleteObject();
	void Unlock();
	BOOL AttachToMemBitmap(HGLOBAL hGlobal);
	
    // disk functions
	void LoadBMP();
	void DrawBMP(CDC* dc,int left,int top,int iNum,int iDen);
	void SaveBMP(CString sFilename);

	// allocation,de-allocation,copy,inversion[,draw] of related matrixes,arrays,
	// and related data-structures
	imagematrix   CreateImageMatrix(UINT row,UINT col);
	imagematrix   InvertImageMatrix(imagematrix img);
	binarymatrix  CreateBinaryMatrix(UINT row,UINT col);
	bool          CompareBinaryMatrix(binarymatrix binThis,binarymatrix binThat);
	bool          DrawBinaryImageAfterBinarization(binarymatrix binImg,UINT rowStart,UINT rowEnd,UINT colStart,UINT colEnd);
	bool          DrawBinaryImageAfterThinning(binarymatrix binImg,UINT rowStart,UINT rowEnd,UINT colStart,UINT colEnd);
	float**       CreateFloatMatrix(UINT row,UINT col);
    boolmatrix    CreateBoolMatrix(UINT row,UINT col);
	void		  FreeImageMatrix(imagematrix img,UINT row);
	void          FreeBinaryMatrix(binarymatrix bin,UINT row);
	void          FreeBoolMatrix(boolmatrix bm,UINT row);
	void          FreeFloatMatrix(float** fMatrix,UINT row);
	void		  BufferToMatrix(BYTE* buf, imagematrix img);
	void		  MatrixToBuffer(imagematrix img, BYTE* buf);
	void		  CopyImageBuffer(BYTE* bufcopy,BYTE* buf);
	void          CopyImageMatrix(imagematrix imgDst,imagematrix imgSrc);
	void          CopyBinaryMatrix(binarymatrix binDst,binarymatrix binSrc);
	imagerow      CreateImageRow(int col);
	void          CopyImageRow(imagerow dest,imagerow src,int col);

	// Misc...
	CString GetPixelValueString(CPoint point);
	bool    GetPixel(UINT x,UINT y,pixel* pix);	//read pixel
	bool    SetPixel(UINT x,UINT y,pixel& pix); //write pixel
	void    go();								//do the magic !

	//polymorphic declaration...
	bool    UserDefinedFilter(CUserDefinedFilter* filter,CString szFilterName);  

	//helper function
	void    CirclePoint(imagematrix img,CPoint point,int x,int y,int radius,COLORREF value);  
	bool    DrawCircleOnTop(imagematrix img,CPoint centre,int radius,COLORREF value);
	bool    DrawLineOnTop(imagematrix img,CPoint& from,CPoint& to,COLORREF value);

private:
	bool MorphologyDilate();
	float EuclidianDistance(CPoint P1,CPoint P2);
	bool  LocateCore();
	
	/******************* private member functions **********************************/

    bool  IsCrossedBoundary(UINT height,UINT width,UINT x,UINT y,int iNeighborhoodType = 3);

	//1. helper functions in thinning operation
	BYTE  And248(binarymatrix img,UINT x,UINT y);
	BYTE  And246(binarymatrix img,UINT x,UINT y);
	BYTE  And268(binarymatrix img, UINT x, UINT y);
	BYTE  And468(binarymatrix img, UINT x, UINT y);
	BYTE  TransitionSum(binarymatrix img,UINT x,UINT y);
	BYTE  NeighborhoodSum(binarymatrix img,UINT x,UINT y);
	
	//minutiae related functions
	bool IsBifurcation(binarymatrix img,UINT x,UINT y);
	bool IsEnd(binarymatrix img,UINT x,UINT y);
	bool IsSingle(binarymatrix img,UINT x,UINT y);
	bool ExtractMinutiae();

	//2. operation-specific initialisation
	void InitializeOperation();

	//3. ridge tracking operations
	void    BranchSeparate(CBifurcationPoint* ptBP,PATH* path1,PATH* path2,PATH* path3);
    CPoint* FindNext(PATH* path);
	bool    CheckSingularityWhileTracking(PATH* path);
	void    BranchTrack();

	//A lot of stuff !
	/******************** private member variables *********************************/
	HGLOBAL              m_hMem;		 //memory bitmap handle
    BYTE*                m_buf;			 //formatted buffer
	imagematrix          m_original;     //original image matrix
    imagematrix          m_img;          //input image
	imagematrix          m_processed;	 //output image
	binarymatrix         m_binaryimage;  //binary image
	float**              m_orientation;  //local orientation of fingerprint
	binarymatrix         m_regionmask;   //holds ROI(Region Of Interest) mask(s)
	binarymatrix         m_thinmap;		 //thinned binary image
	imagematrix			 m_thinnedimage;  //Thinned image
	BYTE**               m_undobuf;		 //array of (BYTE*)/(undo buffer)
	UINT                 m_width;		 //image width
	UINT                 m_height;		 //image height
	UINT                 m_widthDW;		 //scanline width with DWORD padding
	CString              m_filename;     //FQN of associated image file
	operationtype        m_type;         //operation type
	int                  m_undolevel;	 //how deep UNDO is supported ?

	END_LIST			 m_endlist;		 //minutiae specific lists...
	BRANCH_LIST		     m_branchlist;
	END_LIST             m_badendlist;
	int					 m_bad_endlist_index;
	//CArray<CEndPoint*, CEndPoint*>					  m_endlist;
	//CArray<CBifurcationPoint*, CBifurcationPoint*>    m_branchlist;
	int                  m_numend;
	int                  m_numbranch;
protected:
	
	// operations on image
	bool        Binarize(bool adaptive=false,UINT block = 20);
	bool        Segmentation(UINT block = 5);
	bool        Negative();
	long*       Histogram(imagematrix img,BOOL bSmooth=FALSE,int W=3);
	bool        Gray();
	bool        Equalize();
	bool        EdgeDetection();
	bool        Convolution();
	bool        MarkRegionOfInterest(float Threshold);
	bool        Normalize(float DesiredMean=100,float DesiredVariance=100);
	bool        BlurFilter();
	bool        OrientationEstimation();
	bool        Thinning();
	BOOL        Lock(void);
	bool		FilterMinutiae();
};

#endif // !defined(AFX_IMAGE_H__DE1DE0E1_BB31_11D6_AF71_9E97648C2C45__INCLUDED_)
