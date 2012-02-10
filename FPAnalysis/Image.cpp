//////////////////////////////////////////////////////////////////////
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
// Image.cpp: implementation of the class(s):CImage,pixel,hsvpixel .
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FPAnalysis.h"
#include "Image.h"


#include "jpegfile.h"
#include "BMPFile.h"
#include "Dialogs.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif



/////////////////////////////user definitions//////////////////////////
    
/////////////////////////////global variables//////////////////////////

////////////////////////////special functions//////////////////////////
float minimum(float** array,int row,int col)
{
	float Min=255;
	for(int i=0 ; i < row ;i++)
	{
		for(int j=0 ; j < col ; j++)
		{
			Min=(array[i][j]<Min)?array[i][j]:Min;
		}
	}
	return Min;
}

int IndexOf(END_LIST& arr, int X, int Y)
{
	CEndPoint* pMinutiae;
	for(int _index = 0; _index < arr.GetSize(); _index++)
	{
		pMinutiae = arr.GetAt(_index);
		if ((pMinutiae->pt.x == X) &&
			(pMinutiae->pt.y == Y))
		{
			return _index;
		}
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////
// pixel Class
//////////////////////////////////////////////////////////////////////
void pixel::operator =(pixel &p)
//
// Desc:   RGB pixel assignment
//
{
	r = p.r;
	g = p.g;
	b = p.b;
}

void pixel::operator =(hsvpixel& hsv)
//
// Desc:   Converstion of Hue-Saturation-Value pixel to RGB	
// Pre:    hsv is an HSV pixel
// Post:   the equavalent RGB pixel is returned
{
	double R, G, B;

	if (hsv.s == 0) 
	{
		R = hsv.v;
		G = hsv.v;
		B = hsv.v;
	}
	else
	{
		int i;
		double f, p, q, t;

		if (hsv.h == 360)
			hsv.h = 0;
		hsv.h /= 60;			// h now in [0,6)
		i = int(floor(hsv.h));
		f = hsv.h - i;
		p = hsv.v * (1 - hsv.s);
		q = hsv.v * (1 - (hsv.s * f));
		t = hsv.v * (1 - (hsv.s * (1 - f)));
		
		switch (i)
		{
			case 0: R = hsv.v;
				    G = t;
					B = p;
					break;
			case 1: R = q;
				    G = hsv.v;
					B = p;
					break;
			case 2: R = p;
				    G = hsv.v;
					B = t;
					break;
			case 3: R = p;
				    G = q;
					B = hsv.v;
					break;
			case 4: R = t;
				    G = p;
					B = hsv.v;
					break;
			case 5: R = hsv.v;
				    G = p;
					B = q;
		}
	}

	r = (BYTE)(R * 255);
	g = (BYTE)(G * 255);
	b = (BYTE)(B * 255);
}

void pixel::operator =(COLORREF& crColor)
{
    r=GetRValue(crColor);
	g=GetGValue(crColor);
	b=GetBValue(crColor);
}

bool pixel::operator>(pixel& p)
{
	return ((r>p.r)&&(g>p.g)&&(b>p.b));
}

bool pixel::operator>(BYTE x)
{
	return ((r>x)&&(g>x)&&(b>x));
}

bool pixel::operator<(pixel& p)
{
    return ((r<p.r)&&(g<p.g)&&(b<p.b));
}


bool pixel::operator<(BYTE x)
{
	return ((r<x)&&(g<x)&&(b<x));
}

void pixel::color(BYTE R, BYTE G, BYTE B)
//
// Desc:   Assigns pixel the values R, G, and B
//
{
	r = R;
	g = G;
	b = B;
}

void pixel::color(BYTE X)
//
// Desc:   Makes gray pixel with intensity X
//
{
	r = X;
	g = X;
	b = X;
}

void pixel::color(float R, float G, float B)
//
// Desc:   Colors a pixel given the float values R, G, and B.
//         If the float is < 0 or > 255, the color will be set
//         to 0 or 255 respectively.
//
{
	if (R < 0) R = 0;
	if (R > 255) R = 255;
	if (G < 0) G = 0;
	if (G > 255) G = 255;
	if (B < 0) B = 0;
	if (B > 255) B = 255;

	r = (BYTE)R;
	g = (BYTE)G;
	b = (BYTE)B;
}

void pixel::color(float X)
{
	if (X < 0) X = 0;
	if (X > 255) X=255;

	r=(BYTE)X;
	g=(BYTE)X;
	b=(BYTE)X;

}

void pixel::color(COLORREF cr)
{

  r=GetRValue(cr);
  g=GetGValue(cr);
  b=GetBValue(cr);

}

bool pixel::IsGray()
{

   return((r == g) && (g == b) && (b == r));

}

BYTE pixel::intensity()
//
// Desc:   Returns the intensity of a RGB pixel.  This is the Luminance (Y)
//         component of the YIQ color model (used in TV displays).  Intensity
//         is most commonly used as the basis for color image analysis.  This
//         intensity 'formula' appears to produce the best results when using
//         this basis.
{
	return BYTE(0.3*r + 0.59*g + 0.11*b);
}

BYTE pixel::Gray()
//
// Desc:   Returns the gray scale equivalent of an RGB pixel.Now everyone should use this
//         because it's ITU standard.
//
{
    return BYTE((222*r + 707*g + 71*b) / 1000);
}

void pixel::lighten(UINT i)
//
// Desc:   Lightens a pixel by i.
//
{
	if (r >= 255-i) r = 255;
	else r += i;
	if (g >= 255-i) g = 255;
	else g += i;
	if (b >= 255-i) b = 255;
	else b += i;
}

void pixel::darken(UINT i)
//
// Desc:   Darkens a pixel by i.
//
{
	if (r <= i) r = 0;
	else r -= i;
	if (g <= i) g = 0;
	else g -= i;
	if (b <= i) b = 0;
	else b -= i;
}


//////////////////////////////////////////////////////////////////////
// hsvpixel Class
//////////////////////////////////////////////////////////////////////
void hsvpixel::operator =(hsvpixel& hsv)
//
// Desc:   HSV pixel assignment.
//
{
	h = hsv.h;
	s = hsv.s;
	v = hsv.v;
}

void hsvpixel::operator =(pixel& p)
//
// Desc:   Converstion of RGB pixel to Hue-Saturation-Value pixel
// Pre:    p is a RGB pixel
// Post:   the equavalent HSV pixel is returned
{
	//convert p to range [0,1]
	double r = p.r / 255.0;
	double g = p.g / 255.0;
	double b = p.b / 255.0;

	double Max = max(max(r, g), b);
	double Min = min(min(r, g), b);

	// set value/brightness v
	v = Max;

	// calculate saturation s
	if (Max != 0)
		s = (Max - Min) / Max;
	else
		s = 0;

	// calculate hue h
	if (s == 0)
		h = UNDEFINED;
	else
	{
		double delta = Max - Min;
		if (r == Max)
			h = (g - b) / delta;			// resulting color is between yellow and magenta
		else if (g == Max)
			h = 2 + (b - r) / delta;		// resulting color is between cyan and yellow
		else if (b == Max)
			h = 4 + (r - g) / delta;		// resulting color is between magenta and cyan

		h *= 60;							// convert hue to degrees

		if (h < 0)							// make sure positive
			h += 360;
	}

}

/*********************************************************************
**************************  Filter Classes  **************************
**********************************************************************/
C3By3Filter::C3By3Filter()
{
 	
	for(int i=0;i<3;i++)
	 for(int j=0;j<3;j++)
		m_kernel[i][j]=0.0;

  /* from here each 3 * 3 filter will be initialized by following matrix
     to do nothing with the image :-

                  | 0  0  0 |
			H  =  | 0  1  0 |
				  | 0  0  0 |
   
   */	
	 m_kernel[1][1]=1.0;
	 m_iDivision=1;
	 m_iBias=0;
	 
}

COLORREF C3By3Filter::Filter(CImage* image,UINT m,UINT n)
{
	/*  input image = u[m][n] : output image = v[m][n]
							3	  3
	calculates  v[m][n] = Sigma Sigma ( h[k][l] * u[m - k][n - l] )
						   k=1   l=1
     v[m][n]'s color !

     */
	float R,G,B;
	pixel pix;
	int circumference = 2;
	int radius = 1;
	int x,y;

	for(int k = 0; k <= circumference; k++)
	{
	  for(int l = 0; l <= circumference; k++)
	  {
		x = m + k - radius;
		y = n + l - radius;

		if (image->GetPixel(x,y,&pix))
		{
			R += m_kernel[k][l] * pix.r;
			G += m_kernel[k][l] * pix.g;
			B += m_kernel[k][l] * pix.b;
		}
	  }
	}

	ASSERT(m_iDivision != 0);

	// be aware of greater than 255 !
	R = min(R/m_iDivision + m_iBias,255);
	G = min(G/m_iDivision + m_iBias,255);
	B = min(B/m_iDivision + m_iBias,255);

	// be aware of less than 0 !
	R = max(R,0);
	G = max(G,0);
	B = max(B,0);

	return RGB((BYTE)R,(BYTE)G,(BYTE)B);

}

C5By5Filter::C5By5Filter()
{
  for(int i = 0; i < 5; i++)
	 for(int j = 0; j < 5; j++)
		m_kernel[i][j]=0.0;

  /* from here each 5 * 5 filter will be initialized by following matrix
     to do nothing with the image :-

                  | 0  0  0  0  0|
			H  =  | 0  0  0  0  0|
				  | 0  0  1  0  0|
				  | 0  0  0  0  0|
				  | 0  0  0  0  0|
   */	
	 m_kernel[2][2]=1.0;
	 m_iDivision=1;
	 m_iBias=0;

}

COLORREF C5By5Filter::Filter(CImage* image,UINT m,UINT n)
{

	/* input image = u[m][n] : output image = v[m][n] 
							5	  5
	calculates  v[m][n] = Sigma Sigma ( h[k][l] * u[m - k][n - l] )
						   k=1   l=1
     v[m][n]'s color !

     */
	float R,G,B;
	pixel pix;
	int circumference = 4;
	int radius = 2;
	int x,y;

	for(int k = 0; k <= circumference; k++)
	{
	  for(int l = 0; l <= circumference; k++)
	  {
		x = m + k - radius;
		y = n + l - radius;

		if (image->GetPixel(x,y,&pix))
		{
			R += m_kernel[k][l] * pix.r;
			G += m_kernel[k][l] * pix.g;
			B += m_kernel[k][l] * pix.b;
		}
	  }
	}

	ASSERT(m_iDivision != 0);

	// be aware of  > 255 !
	R = min(R/m_iDivision + m_iBias,255);
	G = min(G/m_iDivision + m_iBias,255);
	B = min(B/m_iDivision + m_iBias,255);

	// be aware of < 0 !
	R = max(R,0);
	G = max(G,0);
	B = max(B,0);

	return RGB((BYTE)R,(BYTE)G,(BYTE)B);

}

C7By7Filter::C7By7Filter()
{
  for(int i = 0; i < 7; i++)
	 for(int j = 0; j < 7; j++)
		m_kernel[i][j]=0.0;

  /* from here each 7 * 7 filter will be initialized by following matrix
     to do nothing with the image :-

                  | 0  0  0  0  0  0  0|
			H  =  | 0  0  0  0  0  0  0|
				  | 0  0  0  0  0  0  0|
				  | 0  0  0  1  0  0  0|
				  | 0  0  0  0  0  0  0|
				  | 0  0  0  0  0  0  0|
				  | 0  0  0  0  0  0  0|
   */	
	 m_kernel[3][3]=1.0;
	 m_iDivision=1;
	 m_iBias=0;

}

COLORREF C7By7Filter::Filter(CImage* image,UINT m,UINT n)
{
  /* input image = u[m][n] : output image = v[m][n] 
							7	  7
	calculates  v[m][n] = Sigma Sigma ( h[k][l] * u[m - k][n - l] )
						   k=1   l=1
     v[m][n]'s color !

     */
	float R,G,B;
	pixel pix;
	int circumference = 6;
	int radius = 3;
	int x,y;

	for(int k = 0; k <= circumference; k++)
	{
	  for(int l = 0; l <= circumference; k++)
	  {
		x = m + k - radius;
		y = n + l - radius;

		if (image->GetPixel(x,y,&pix))
		{
			R += m_kernel[k][l] * pix.r;
			G += m_kernel[k][l] * pix.g;
			B += m_kernel[k][l] * pix.b;
		}
	  }
	}

	ASSERT(m_iDivision != 0);

	// be aware of greater than 255 !
	R = min(R/m_iDivision + m_iBias,255);
	G = min(G/m_iDivision + m_iBias,255);
	B = min(B/m_iDivision + m_iBias,255);

	// be aware of less than 0 !
	R = max(R,0);
	G = max(G,0);
	B = max(B,0);

	return RGB((BYTE)R,(BYTE)G,(BYTE)B);

}

/*********************************************************************
************************* Minutiae specific classes ******************
**********************************************************************/
//////////////////////////////////////////////////////////////////////
// CMinutiae Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMinutiae::CMinutiae()
{

	pt = CPoint(0,0);
	theta = 0.0;
}

CMinutiae::~CMinutiae()
{

}

//////////////////////////////////////////////////////////////////////
// CEndPoint Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEndPoint::CEndPoint()
{
	iNeighbours = 1;
}

CEndPoint::~CEndPoint()
{
	
}

//////////////////////////////////////////////////////////////////////
// CBifurcationPoint Class
//////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBifurcationPoint::CBifurcationPoint()
{
	iNeighbours = 3;
}

CBifurcationPoint::~CBifurcationPoint()
{

}

//////////////////////////////////////////////////////////////////////
// CImage Class
//////////////////////////////////////////////////////////////////////
CImage::CImage()
{
	m_buf     = NULL;
	m_undobuf = NULL;
	m_original= NULL;
	m_thinmap = NULL;
	m_binaryimage = NULL;
	m_width   = 0;
	m_height  = 0;
	m_widthDW = 0;
	m_filename.Empty();
	
	//initialize minutiae lists...
	
}


CImage::~CImage()
{

	if (m_buf != NULL)
	{
		delete[] m_buf;
		m_buf = NULL;
		
		FreeImageMatrix(m_original,m_height);

	}	
	
	if (m_undobuf != NULL)
	{
	 for(UINT i = 0; i < MAXUNDO; i++)
	 {
		delete [] m_undobuf[i];
	 }
	 delete m_undobuf;
	}

	// one time memory clean-up
	if (m_thinmap != NULL)
		FreeBinaryMatrix(m_thinmap,m_height);
	if (m_binaryimage != NULL)
	    FreeBinaryMatrix(m_binaryimage,m_height);

	Detach();

	if (m_endlist.GetUpperBound() != -1)
	{
		for(int i = 0; i < m_endlist.GetSize(); i++)
		{
			free(m_endlist.GetAt(i));
		}
		m_endlist.RemoveAll();
	}

	if ((m_branchlist.GetUpperBound()) != -1)
	{
		for(int i = 0; i < m_branchlist.GetSize(); i++)
		{
			free(m_branchlist.GetAt(i));
		}
		m_branchlist.RemoveAll();

	}

	
}

bool CImage::operator ==(CImage& image)
{
	// not implemented yet
	return true;
}

CImage& CImage::operator =(CImage& image)
{

   // not implemented yet
   return *this;
}
/************************************************************************
***************************** Misc... ***********************************
*************************************************************************/
bool CImage::GetPixel(UINT x,UINT y,pixel* pix)
{
  if (m_img == NULL)
	  return false;
  

  // check for positions out of range
  if (x > m_width || x < 0 || y > m_height || y < 0)
	  return false;

  (*pix) = m_img[x][y];

  return true;

}

bool CImage::SetPixel(UINT x,UINT y,pixel& pix)
{
  if (m_processed == NULL)
	  return false;

  // check for positions out of range
  if (x > m_width || x < 0 || y > m_height || y < 0)
	  return false;

  m_processed[x][y] = pix;

  return true;

}
CString CImage::GetPixelValueString(CPoint point)
{
   CopyImageMatrix(m_img,InvertImageMatrix(m_img));
	
   CString str;
   pixel pix=m_img[point.y][point.x];
   str.Format("Red :%d Green :%d Blue:%d",pix.r,pix.g,pix.b);
	
   CopyImageMatrix(m_img,InvertImageMatrix(m_img));

   return str;

}
void CImage::go()
{
	bool ok=false;

	if ((m_type == UNDO)  && (m_undolevel >= 1))
	{
	
		 CopyImageBuffer(m_buf,m_undobuf[--m_undolevel]);	
		
	}
	else
	{
	  InitializeOperation();
         
	  //             ___________________ 				
	  // m_img  ----|--image-operation--|---->  m_processed
	  //            |___________________|
	  switch(m_type)
	  {
		case NEGATIVE:          ok=Negative();                 break;
		case GRAYINT:           ok=Gray();                     break;

		case HISTOGRAMBINARIZE: ok=Binarize();                 break;
		case ADAPTIVEBINARIZE:  ok=Binarize(true,20);          break;
		case FPSEGMENTATION:    ok=Segmentation();             break;

		case EQUALIZE:          ok=Equalize();                 break;
		case EDGEDETECTION:     ok=EdgeDetection();            break;
		case CONV:			    ok=Convolution();              break;
		case BLUR:			    ok=BlurFilter();               break;
		case NORMALIZE:		    ok=Normalize();                break;
		case ORIENTATION:       ok=OrientationEstimation();    break;
		case MARKROI:           ok=MarkRegionOfInterest(190); break;
		case DRAWLINE:		    ok=DrawLineOnTop(m_processed,CPoint(100,100),CPoint(150,50),RGB(255,0,0));break;
		
		case THINNING:          ok=Thinning();					break;
								
			                    //ok=MorphologyDilate();          break;

		case EXTRACT:		    ok=ExtractMinutiae();		   break;
		case CORE:              ok=LocateCore();               break;
		case MINUTIAE_FILTERING: ok=FilterMinutiae();		   break;
		default:                ok=false;                      break;
	  }

	  if (ok)
	  {
		  //fill UNDO buffer :: save it!
		  CopyImageBuffer(m_undobuf[m_undolevel++],m_buf);	
		 /*

		  CWnd* pMain = AfxGetMainWnd();
		  if (pMain)
		  {
				CMenu* pMenu = pMain->GetMenu();
				pMenu->EnableMenuItem(ID_EDIT_UNDO,MF_ENABLED);
		  }

        */
		  MatrixToBuffer(m_processed,m_buf);

		  // free those image-matrix junks...
		  FreeImageMatrix(m_img,m_height);
		  FreeImageMatrix(m_processed,m_height);
		  
	  }

	}

}

bool CImage::UserDefinedFilter(CUserDefinedFilter* filter,CString szFilterName)
{
  
	InitializeOperation();

    // Setup and Call Progress Dialog
	CProgressDlg pdlg(szFilterName);
	pdlg.Create();
	UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	UINT pixelsProcessed = 0;
	bool canceled = false;

	// Algorithm 

	UINT  m, n;
	COLORREF cr;

    for (m = 0; m < m_height; m++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (n = 0; n < m_width; n++)
		{
			//TODO: add extra pixel operations here

			//runtime polymorphism baby!
			cr = filter->Filter(this,m,n);		
			m_processed[m][n] = cr;
			
            pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
 
	
	pdlg.DestroyWindow();
	
    return !canceled;

}

/**************************************************************************
****************************** Helper Functions ***************************
***************************************************************************/
bool CImage::IsCrossedBoundary(UINT height,UINT width, UINT x, UINT y, int iNeighborhoodType)
{

	int radius = iNeighborhoodType/2;
	UINT xLimit = height - 1 - radius;
	UINT yLimit = width - 1 - radius;

	if (x < (unsigned)radius)
		return true;
	else
		if (x > xLimit)
			return true;
    else
		if (y < (unsigned)radius)
			return true;
	else
		if (y > yLimit)
			return false;

	return false; //default

}
BYTE CImage::And248(binarymatrix img, UINT x, UINT y)
{

	return(img[x-1][y] * img[x][y-1] * img[x][y+1]);

}

BYTE CImage::And246(binarymatrix img, UINT x, UINT y)
{
    
	return(img[x-1][y] * img[x][y-1] * img[x+1][y]);

}

BYTE CImage::And268(binarymatrix img, UINT x, UINT y)
{
	/*
		 |   |   |   |
		 |_p3|_p2|_p9|
		 |	 |   |   |
		 |_p4|_p1|_p8|
		 |	 |   |   |
		 |_p5|_p6|_p7|
	*/

	return(img[x-1][y] * img[x+1][y] * img[x][y+1]);
}

BYTE CImage::And468(binarymatrix img, UINT x, UINT y)
{
	return(img[x][y-1] * img[x+1][y] * img[x][y+1]);

}

BYTE CImage::NeighborhoodSum(binarymatrix img, UINT x, UINT y)
{

	//did we have crossed our boundary !
	if (x >= 1 && x <=(m_height-2) && y >= 1 && y<=(m_width-2))
	{
		
		BYTE sum = 0;

	  /*
	      from here on i will follow the below neighborhood convension :-
	      Note :: And248 & And268 are named by this convension
		    ___ ___ ___
		   |   |   |   |
		   |_p3|_p2|_p9|
		   |   |   |   |
		   |_p4|_p1|_p8|
		   |   |   |   |
		   |_p5|_p6|_p7|

      */


	   sum += img[x-1][y];
	   sum += img[x-1][y-1];
	   sum += img[x][y-1];
	   sum += img[x+1][y-1];
	   sum += img[x+1][y];
	   sum += img[x+1][y+1];
	   sum += img[x][y+1];
	   sum += img[x-1][y+1];

	   return sum;
	}

}


BYTE CImage::TransitionSum(binarymatrix img, UINT x, UINT y)
{

	//remember :No of 0 to 1 transition = TransitionSum(...) - 1
	//reason   :You are counting img[x][y-1] twice.Think about it ?

	//Do it in c clockwise way(not ACW)
	/*

		  _____________________________________
		 |			  |			 |		      |
		 |_p3(x-1,y-1)|_p2(x-1,y)|_p9(x-1,y+1)|
		 |			  |			 |			  |
		 |_p4(x,y-1)__|__p1(x,y)_|_p8(x,y+1)__|
		 |			  |			 |			  |
		 |_p5(x+1,y-1)|_p6(x+1,y)|_p7(x+1,y+1)|

	*/
		
	//did we have crossed our boundary !
	if (x >= 1 && x <=(m_height-2) && y >= 1 && y<=(m_width-2))
	{

		BYTE sum = 0;

		sum += (BYTE)fabs_b(img[x-1][y]   - img[x-1][y-1]);
		sum += (BYTE)fabs_b(img[x-1][y-1] - img[x][y-1]);
		sum += (BYTE)fabs_b(img[x][y-1]   - img[x+1][y-1]);
		sum += (BYTE)fabs_b(img[x+1][y-1] - img[x+1][y]);
		sum += (BYTE)fabs_b(img[x+1][y]   - img[x+1][y+1]);
		sum += (BYTE)fabs_b(img[x+1][y+1] - img[x][y+1]);
		sum += (BYTE)fabs_b(img[x][y+1]   - img[x-1][y+1]);
		sum += (BYTE)fabs_b(img[x-1][y+1] - img[x-1][y]);

		return sum;
	}

	
}

/**************************************************************************
********************** Minutiae related functions **************************
***************************************************************************/
bool CImage::IsBifurcation(binarymatrix img, UINT x, UINT y)
{

	// No meaning of minutiae at boundary
	//if (x <= 1 || x >= m_width-2 || y <= 1 || y  m_height-1)
	//	return false;
	//else
	    return (TransitionSum(img,x,y) == 6)?true:false;
}

bool CImage::IsEnd(binarymatrix img,UINT x,UINT y)
{
    // No meaning of minutiae at boundary
	//if (x == 0 || x == m_width-1 || y == 0 || y == m_height-1)
	//	return false;
	//else
	    return (TransitionSum(img,x,y) == 2)?true:false;
}


bool CImage::IsSingle(binarymatrix img,UINT x,UINT y)
{
	return (NeighborhoodSum(img,x,y) == 0)?true:false;
}

/*************************************************************************
****************************** Disk functions ****************************
**************************************************************************/
void CImage::LoadBMP()
//
// Desc:   Loads a BMP image from a file into the buffer
// Pre:    m_filename is the name of the file containting the BMP image
// Post:   m_buf contains the file; m_width and m_height are set;
//         m_undobuf has been allocated enough space to hold a copy of an
//         image the size of m_buf.
{
	if (m_buf != NULL)
	{
		delete[] m_buf;
		m_buf = NULL;
	}

	if (m_undobuf != NULL)
	{
		delete[] m_undobuf;
		m_undobuf = NULL;
	}

    //call the actual BMP loading routine...
	BMPFile theBmpFile;
	m_buf = theBmpFile.LoadBMP(m_filename, &m_width, &m_height,m_pbihdr);
    
	if ((m_buf == NULL) || (theBmpFile.m_errorText != "OK"))
	{
		AfxMessageBox(theBmpFile.m_errorText, MB_ICONSTOP);
		m_buf = NULL;
		return;
	}
	
	int size=m_height * m_width * 3;

	//allocate undobuf...
	m_undobuf = (BYTE**)new BYTE*[MAXUNDO];
	for(UINT i = 0; i < MAXUNDO; i++)
	{
		m_undobuf[i]=(BYTE*)new BYTE[size];
	}
	m_undolevel=0;

	JpegFile::BGRFromRGB(m_buf, m_width, m_height);
	JpegFile::VertFlipBuf(m_buf, m_width * 3, m_height);

	//create the matrix to store the original image matrix
	m_original = CreateImageMatrix(m_height,m_width);

	imagematrix temp = CreateImageMatrix(m_height,m_width);
	BufferToMatrix(m_buf,temp);

	CopyImageMatrix(m_original,temp);

	//attach to the CBimap class::remember to detach the previous GDI handle first !
	//call CBitmap::Attach.
	Detach();
	Attach(::LoadImage(NULL,(LPCTSTR)m_filename,IMAGE_BITMAP,
                    0, 0, LR_LOADFROMFILE |LR_CREATEDIBSECTION|LR_DEFAULTSIZE));

	// free last-used matrices
	if (m_thinmap)
	{
	   FreeBinaryMatrix(m_thinmap,m_height);
	   m_thinmap = NULL;
	}
	if (m_binaryimage)
	{
	   FreeBinaryMatrix(m_binaryimage,m_height);
	   m_binaryimage = NULL;
	}

	//check to see whether picture being loaded is gray-scale or not?
	//don't allow color images
	UINT x,y;
	bool bGrayed=false;
	for(x = 0; x < m_height; x++)
	{
	  for(y = 0; y < m_width; y++)
	  {
		  if (temp[x][y].IsGray())
			  bGrayed=true;
		  else
		  {
			  //colored pixel...
			  bGrayed=false;
			  break;
		  }
	  }
	}

	if (bGrayed==false)
	{
		if (AfxMessageBox("Image to be loaded is not a gray-scale image.Do you wish to\n convert it to black & white",MB_YESNO|MB_ICONINFORMATION)==IDYES)
		{
			SetOperationType();  //default is B/W
			go();
		}
	}

	FreeImageMatrix(temp,m_height);
    
	


}

void CImage::DrawBMP(CDC* dc,int left,int top,int iNum,int iDen)
//
// Desc:   Displays m_buf on the screen.
// Pre:    dc is a handle to the screen device context.
// Post:   m_buf is displayed, centered, on the screen;
//		   iNum, iDen are zoom factor used by StretchDIBits(...).
{
	if (m_buf == NULL)		// if nothing in the buffer, get out
		return;

	if (dc != NULL)
	{
		
        // a 24-bit DIB is DWORD-aligned, vertically flipped and has Red and Blue bytes
		// swapped.  We already did the RGB->BGR and the flip when we read the image, 
		// now do the DWORD-align

		BYTE* tmp;
		tmp = JpegFile::MakeDwordAlignedBuf(m_buf, m_width, m_height, &m_widthDW);

		// set up DIB
		BITMAPINFOHEADER bmiHeader;
		bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
		bmiHeader.biWidth = m_width;
		bmiHeader.biHeight = m_height;
		bmiHeader.biPlanes = 1;
		bmiHeader.biBitCount = 24;
		bmiHeader.biCompression = BI_RGB;
		bmiHeader.biSizeImage = 0;
		bmiHeader.biXPelsPerMeter = 0;
		bmiHeader.biYPelsPerMeter = 0;
		bmiHeader.biClrUsed = 0;
		bmiHeader.biClrImportant = 0;

		// send it to the CDC:If required stretch it
		// lines returns the number of lines actually displayed

		int width  = m_width * iNum / iDen;
		int height = m_height * iNum / iDen;
		
		int lines = StretchDIBits(
			dc->m_hDC,
			left,
			top,
			width,
			height,
			0,
			0,
			bmiHeader.biWidth,
			bmiHeader.biHeight,
			tmp,
			(LPBITMAPINFO)&bmiHeader,
			DIB_RGB_COLORS,
			SRCCOPY);

		delete[] tmp;
	}
}

void CImage::SaveBMP(CString sFilename)
//
// Desc:   Saves the image in m_buf to file sFilename as a BMP
// Pre:    m_buf contains an image; sFilename is the filename to save m_buf to 
// Post:   file has been saved as BMP to sFilename
{
	if (m_buf == NULL)
	{
		AfxMessageBox ("No Image to Save!");
		return;
	}

	// image in m_buf is already BGR and vertically flipped
	// so we don't need to do that for this function

	BMPFile theBmpFile;
	theBmpFile.SaveBMP(
		sFilename,
		m_buf,
		m_width,
		m_height);

	if (theBmpFile.m_errorText != "OK")
		AfxMessageBox(theBmpFile.m_errorText, MB_ICONSTOP);
	else
	{
		m_filename = sFilename;
		LoadBMP();
	}
}

/******************** Allocation,De-allocation,Copy of matrices  ***************
******************** and other related data-structures *************************
/*******************************************************************************/

imagematrix CImage::CreateImageMatrix(UINT row,UINT col)
// Desc:   Allocates memory for an image matrix of pixels, of size row by col
// Pre:    row are col are size for matrix allocation
// Post:   Pointer to allocated memory returned.
{
	// dynmaic allocation of a two-dimensional array
	imagematrix img = NULL;
	img = (imagematrix)malloc(row * sizeof(imagerow));
	
	if (img == NULL)
		return(NULL);

	for (UINT i = 0; i < row; i++)
	{
		img[i] = (imagerow)malloc(col * sizeof(pixel));
		if (img[i] == NULL)
		{
			FreeImageMatrix(img, row);
			return(NULL);
		}
	}

	return(img);
}


imagematrix CImage::InvertImageMatrix(imagematrix img)
{

	//img is a upside-down mapping of the original:change it...
	imagematrix tempmatrix=CreateImageMatrix(m_height,m_width);
	for(int i = (int)m_height - 1; i > 0;  i--)
	{
		CopyImageRow((imagerow)tempmatrix[(m_height-1) - i],(imagerow)img[i],m_width);
	}

	return tempmatrix;
}


float** CImage::CreateFloatMatrix(UINT row,UINT col)
{
  float** fMatrix = NULL;
  UINT i,j;
  fMatrix = (float**)new float*[row];

  if (fMatrix == NULL)
	  return NULL;
   
  for(i = 0; i < row; i++)
  {
	  fMatrix[i] =(float*)new float[col];
  }

  for(i = 0; i < row; i++)
	 for(j = 0; j < col; j++)
		 fMatrix[i][j] = 0.0;

  return fMatrix;
  
}


boolmatrix CImage::CreateBoolMatrix(UINT row,UINT col)
{
   boolmatrix bm = NULL;
   UINT i,j;
   bm=(bool**)new bool*[row];


   for(i = 0; i < row; i++)
   {
	   bm[i]=(bool*)new bool[col];
   }

   for(i = 0; i < row; i++)
	 for(j = 0; j < col; j++)
       bm[i][j]=false;

   return bm;
 
}

binarymatrix CImage::CreateBinaryMatrix(UINT row, UINT col)
{
	UINT i,j;
	binarymatrix binary=NULL;

	binary=(BYTE**)new BYTE*[row];
	for(i=0;i<row;i++)
		binary[i]=(BYTE*)new BYTE[col];

	//initialize !
	for(i = 0; i < row; i++)
	{
	  for(j = 0; j < col; j++)
	  {
		  binary[i][j] = 0x00;
	  }
	}

	return binary;

}

bool CImage::CompareBinaryMatrix(binarymatrix binThis, binarymatrix binThat)
{
	//assume binary matrices have the same order of image matrices : [m_height : m_width]
	//if you need more flexibility pass additional arguements to this function.

	UINT i,j;
	for(i = 0; i < m_height; i++)
	{
	  for(j = 0; j < m_width; j++)
	  {
		  if (binThis[i][j] != binThat[i][j])
			  return false;
	  }
	}

	return true;
 
}

bool CImage::DrawBinaryImageAfterThinning(binarymatrix binImg,UINT rowStart,UINT rowEnd,UINT colStart,UINT colEnd)
{
    CProgressDlg pdlg("Drawing Binary Image...");
    pdlg.Create();
    UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
    UINT pixelsProcessed = 0;
	bool canceled = false;

	UINT i,j;

	// clean up m_processed first
	
	for(i = 0;i < m_height; i++)
	{
	   for(j = 0;j < m_width; j++)
	   {
		   m_processed[i][j].color((BYTE)WHITE);
	   }
	}
	
	//CString s = "";
	// now draw according to the binary image
	for (i = rowStart; i <= rowEnd; i++)
    {
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = colStart; j <= colEnd; j++)
		{
		  //TODO: add extra pixel operations here...

			if (binImg[i][j] == 0x00)
				m_processed[i][j].color((BYTE)WHITE);
			else
				m_processed[i][j].color((BYTE)BLACK);


			 pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();

		}


   }

	pdlg.DestroyWindow();
	
	return !canceled;

}


bool CImage::DrawBinaryImageAfterBinarization(binarymatrix binImg,UINT rowStart,UINT rowEnd,UINT colStart,UINT colEnd)
{
    CProgressDlg pdlg("Drawing Binary Image...");
    pdlg.Create();
    UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
    UINT pixelsProcessed = 0;
	bool canceled = false;

	UINT i,j;

	// clean up m_processed first
	/*
	for(i = 0;i < m_height; i++)
	{
	   for(j = 0;j < m_width; j++)
	   {
		   //Default white
		   
	   }
	}*/
	
	//CString s = "";
	// now draw according to the binary image
	for (i = rowStart; i <= rowEnd; i++)
    {
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = colStart; j <= colEnd; j++)
		{
		  //TODO: add extra pixel operations here...

			if (binImg[i][j] == 0x01)
				m_processed[i][j].color((BYTE)0x00);
			else
				m_processed[i][j].color((BYTE)0xFF);


			 pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();

		}


   }

	pdlg.DestroyWindow();
	
	return !canceled;

}

void CImage::FreeImageMatrix(imagematrix img,UINT row)
// Desc:   Deallocates memory from an image matrix of pixels, of row rows
// Pre:    img was allocated by CreateImageMatrix(...); row is number
//         of rows in imagematrix img
// Post:   memory deallocated
{
	if (img)
	{
		for (unsigned int i = 0; i < row; i++) 
		{
			if (img[i] != NULL)
				free(img[i]);
		}
		free(img);
	}
}

void CImage::FreeBinaryMatrix(binarymatrix bin, UINT row)
{

	for(UINT i = 0; i < row; i++)
		free(bin[i]);
	free(bin);
}


void CImage::FreeFloatMatrix(float** fMatrix,UINT row)
{
    for(UINT i =0; i < row; i++)
		free(fMatrix[i]);
	free(fMatrix);
 
}

void CImage::FreeBoolMatrix(boolmatrix bm, UINT row)
{
	
	for(UINT i = 0; i < row; i++)
		free(bm[i]);
	free(bm);
}


void CImage::BufferToMatrix(BYTE* buf, imagematrix img)
// Desc:   Converts string of BYTEs (buf) to imagematrix img 
// Pre:    buf != NULL, img created from CreateImageMatrix,
//         m_height and m_width are dimensions of imagematrix img
// Post:   img contains RGB pixels translated from buf
{
	UINT col, row;
	for (row=0; row < m_height; row++)
	{
		for (col=0; col < m_width; col++)
		{
			LPBYTE pRed, pGrn, pBlu;
			pBlu = buf + row * m_width * 3 + col * 3;
			pGrn = buf + row * m_width * 3 + col * 3 + 1;
			pRed = buf + row * m_width * 3 + col * 3 + 2;
			img[row][col].r = *pRed;
			img[row][col].g = *pGrn;
			img[row][col].b = *pBlu;
		}
	}
}

void CImage::MatrixToBuffer(imagematrix img, BYTE* buf)
// Desc:   Converts imagematrix img to string of BYTEs (buf) 
{
	UINT col, row;
	for (row = 0; row < m_height; row++)
	{
		for (col = 0; col < m_width; col++)
		{
			BYTE Red, Grn, Blu;
			Red = img[row][col].r;
			Grn = img[row][col].g;
			Blu = img[row][col].b;
			buf[row * m_width * 3 + col * 3] = Blu;
			buf[row * m_width * 3 + col * 3 + 1] = Grn;
			buf[row * m_width * 3 + col * 3 + 2] = Red;
		}
	}
}

void CImage::CopyImageBuffer(BYTE* bufcopy,BYTE* buf)
// Desc:   Copies buf to bufcopy. 
{
	if (buf==NULL)
		return;

	if (bufcopy==NULL)
		return;

	int size = m_height * m_width * 3;

	for (int i = 0; i < size; i++)
	{
		bufcopy[i] = buf[i];
	}
	return;
}

void CImage::CopyImageMatrix(imagematrix imgDst, imagematrix imgSrc)
{
	if (imgSrc == NULL)
		return;
	if (imgDst == NULL)
		return;

	UINT col, row;
	for (row = 0; row < m_height; row++)
	{
		for (col = 0; col < m_width; col++)
		{
			imgDst[row][col] = imgSrc[row][col];
		}
	}

}

void CImage::CopyBinaryMatrix(binarymatrix binDst, binarymatrix binSrc)
{
	if (binSrc == NULL)
		return;
	if (binDst == NULL)
		return;

	UINT row,col;
	for (row = 0; row < m_height; row++)
	{
		for (col = 0; col < m_width; col++)
		{
			binDst[row][col] = binSrc[row][col];
		}
	}
	

}
imagerow CImage::CreateImageRow(int col)
{

	imagerow imgrow=NULL;
	imgrow=(imagerow)new pixel[col * sizeof(pixel)];
	return imgrow;
}

void CImage::CopyImageRow(imagerow dest, imagerow src,int col)
{

	if (src==NULL)
		return;

	if (dest==NULL)
		return;

	for(int i=0;i < col; i++)
	{
		dest[i]=src[i];
	}
	return;

}

/*******************************************************************
*********************	private member functions  ******************
********************************************************************/
// we willn't use DC's geomatric drawing functions !
void CImage::CirclePoint(imagematrix img,CPoint point, int x, int y,int radius, COLORREF value)
///////////////////////////////////////////////////////////////////////////////
// Desc :: Helper functions for Bresenham algorithm of CIRCLE drawing
//
{
	//did we crossed the image boundary ?
	if ((point.x + radius) > m_height ||(point.x - radius) < 0 ||
		     (point.y + radius) > m_width ||(point.y - radius) < 0)
	  return;

	// octet symmetry !
	img[NONZERO(point.x + x)][NONZERO(point.y + y)] = value;
	img[NONZERO(point.x + y)][NONZERO(point.y + x)] = value;
    img[NONZERO(point.x + y)][NONZERO(point.y - x)] = value;
	img[NONZERO(point.x + x)][NONZERO(point.y - y)] = value;
	img[NONZERO(point.x - x)][NONZERO(point.y - y)] = value;
	img[NONZERO(point.x - y)][NONZERO(point.y - x)] = value;
	img[NONZERO(point.x - y)][NONZERO(point.y + x)] = value;
	img[NONZERO(point.x - x)][NONZERO(point.y + y)] = value;
	
	

}
bool CImage::DrawCircleOnTop(imagematrix img,CPoint centre, int radius, COLORREF value)
///////////////////////////////////////////////////////////////////////
// Desc :: This algorithm of drawing circle is due to Bresenham[BRES77]
//		   Its called mid-point algorithm for scan-conversion of a circle.
//         
{
	

	int x=0;
	int y=radius;
	int d=1 - radius;
	CirclePoint(img,centre,x,y,radius,value);

	while(y > x)
	{
		if (d < 0)
		{
			d += 2 * x + 3; 
		}
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}

		x++;
		CirclePoint(img,centre,x,y,radius,value);
	}
	
	return true;
}



bool CImage::DrawLineOnTop(imagematrix img,CPoint& from, CPoint& to, COLORREF value)
//////////////////////////////////////////////////////////////////
// Desc :: DDA algorithm for scan-conversion of a LINE
//
{
   // now we have  drawing scenario like...
   // -----> y
   // |
   // |
   // |
   // x
   //
   CPoint pt;
   
   // special cases first.

   // 1. horizontal line...
   if (to.x == from.x)
   {
	   
	   int x = from.x;
	   int y;

	   if (from.y > to.y)
	   {
		   // swap...
		   pt = from;
		   from = to;
		   to = pt;
	   }

	   for(y = from.y; y <= to.y; y++)
		 img[x][y] = value;

   }
   else	// 2. vertical line...
	   if (to.y == from.y)
	   {
		   int y = from.y;
		   int x;

		   if (from.x > to.x)
		   {
			   //swap...
			   pt = from;
			   from = to;
			   to = pt;
		   }

		   for(x = from.x; x <= to.x; x++)
			   img[x][y] = value;

	   }
       else
	   {
		// line is not a vector.so always start from left.
		double slope=(to.y - from.y)/(to.x - from.x);

         if (fabs(slope) < 1)			// |m| < 1
		 {
			 if (from.x > to.x)
			 {
	            //swap...
	           pt = from;
	           from = to;
	           to= pt;
			 }

	        int  x;
            double y = from.y;

	        for(x = from.x; x <= to.x; x++)
			{
		       img[x][ROUND(y)] = value;
		       y += slope;
			}
		 }
         else							// |m| > 1
		 {
			 if (from.y > to.y)
			 {
				//swap...
				pt = from;
				from = to;
				to = pt;
			 } 

	         int y;
	         double x = from.x;
 
	         for(y = from.y; y <= to.y; y++)
			 {
		         img[ROUND(x)][y] = value;
		         x += (1/slope);
			 }
		 }

	   }

   
	return true;
}

void CImage::InitializeOperation()
////////////////////////////////////////////////////////////////
// Desc : Initialize & allocate m_img;allocate m_processed
//
{

	//create the matrix...
	m_img=CreateImageMatrix(m_height,m_width);
	BufferToMatrix(m_buf,m_img);

	//create the matrix to be processed/dirty things to be done here...
	m_processed=CreateImageMatrix(m_height,m_width);

	

		
}	  


/****************************************************************
************************  HGLOBAL Chemistry  ********************
*****************************************************************/
BOOL CImage::Lock()
//////////////////////////////////////////////////////////////////
// Desc : Lock() assumes that m_hMem has the reference of memory bitmap !
//
{
	CString str;

   if (m_pbihdr == NULL)
   {
	   if (m_hMem)	//attached already; just lock / set members of  it !
	   {
		   m_pbihdr=(LPBITMAPINFOHEADER)::GlobalLock(m_hMem);

		   ASSERT(m_pbihdr != NULL);
		   ASSERT(m_pbihdr->biSize == sizeof(BITMAPINFOHEADER));  //validity ??

		   m_width=(UINT)m_pbihdr->biWidth;
		   m_height=(UINT)(m_pbihdr->biHeight);

		   
		   str.Format("Width & Height is %d and %d",(int)m_width,(int)m_height);
		   AfxMessageBox(str);
		   
		   //find m_buf from raw bits...
           BMPFile theBmpFile;
		   m_buf=theBmpFile.FindBits(m_pbihdr);
		   ////////////////////////////////////////////////////////////////////
	      if ((m_buf == NULL) || (theBmpFile.m_errorText != "OK"))
		  { 
		    AfxMessageBox(theBmpFile.m_errorText,MB_ICONSTOP);
		    m_buf = NULL;
		    return FALSE;
		  }

		  int size=m_height * m_width * 3;

	      //allocate undobuf...
	      m_undobuf = (BYTE**)new BYTE*[MAXUNDO];
	      for(UINT i = 0; i < MAXUNDO; i++)
		  {
		     m_undobuf[i]=(BYTE*)new BYTE[size];
		  }
	      m_undolevel=0;

		  JpegFile::BGRFromRGB(m_buf, m_width, m_height);
	      JpegFile::VertFlipBuf(m_buf, m_width * 3, m_height);

	      
	   }

   }

  return OK(); 

}

void CImage::Unlock()
{

	if (m_pbihdr)
	{
		m_pbihdr = NULL;
		m_buf = NULL;
		m_undobuf = NULL;

		FreeImageMatrix(m_img,m_height);
		FreeImageMatrix(m_processed,m_height);
		FreeBinaryMatrix(m_binaryimage,m_height);

		m_filename.Empty();
		m_width = m_height = m_widthDW = 0;
		::GlobalUnlock(m_hMem);

	}

}

BOOL CImage::AttachToMemBitmap(HGLOBAL hGlobal)
{
	BOOL success=FALSE;

    m_hMem = hGlobal;
	success = Lock();
	/*
	if (success)
	{
		AfxMessageBox("Bitmap is retrieved from global memory");
		return TRUE;
	}
	else
	{
		AfxMessageBox("Bitmap is not retrieved from global memory");
	    return FALSE;
	}
	*/
	return TRUE;
}


void CImage::DeleteObject()
{
	//do all those in reverse order
	Unlock();
	m_hMem = NULL;

}

/****************************************************************
********************* Image Operations **************************	
****************************************************************/
bool CImage::Binarize(bool adaptive,UINT block)
{
	
	//allocate the binary image matrix...
	m_binaryimage=CreateBinaryMatrix(m_height,m_width);
	
    // Setup and Call Progress Dialog
	CProgressDlg pdlg;
	pdlg.Create();
	bool canceled = false;

	// Binarization
    
	UINT  i,j,k,l;
	BYTE  mean;

	if (adaptive==false)
	{
	  
	  long sum = 0;
	  pdlg.SetDialogCaption("Calculating Mean...");
      UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	  UINT pixelsProcessed = 0;
	 //////////////////////////// Mean Calculation //////////////
	  for (i = 0; i < m_height; i++)
	  {
		 if (pdlg.CheckCancelButton())
			 if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			 {
				 canceled = true; 
				 break;
			 }

		 for (j = 0; j < m_width; j++)
		 {
			 //TODO: add extra pixel operations here

			 sum += m_img[i][j].intensity();

			 pixelsProcessed++;			
			 if (pixelsProcessed % pixels == 0)
				 pdlg.StepIt();
		 }
	  }

	    mean = (sum / ((int)(m_height * m_width)));
	
	   ///////////////// Algorithm /////////////////////////////////
	   // Desc : Ridler and Calvard's automatic thresholding...
	   /////////////////////////////////////////////////////////////
	   pdlg.SetPos(0);
	   pdlg.SetDialogCaption("Applying Histogram-based Thresholding...");

	   long* h = Histogram(m_img);
	   BYTE T,Tnew = mean,Tb,To;
	   long sumTb1,sumTb2;
	   long sumTo1,sumTo2;

	    do
		{
		  //assign last one
		  T = Tnew;

		  sumTb1 = 0;
		  sumTb2 = 0;

	      // mean of all the pixels below brightness T
		  for(k = 0; k < T; k++)
		  {
			 sumTb1 += (k * h[k]);
			 sumTb2 += (h[k]);
		  }


		  // bug fix..
		  if (sumTb2 == 0)
			  Tb = T;
		  else
		      Tb = (sumTb1/sumTb2);

		  sumTo1 = 0;
		  sumTo2 = 0;

	      // mean of all the pixels above brightness T
		  for(k = T; k < MAXINTENSITY; k++)
		  {
			  sumTo1 += (k * h[k]);
			  sumTo2 += (h[k]);
		  }
		
		  //bug fix..
		  if (sumTo2 == 0)
			  To = T;
		  else
			  To = (sumTo1/sumTo2);

		  // calculate new T
		  Tnew = ( Tb + To )/2;


		}while(Tnew != T);

		
	
 	   pdlg.SetPos(0);
	   pdlg.SetDialogCaption("Binarizing...");
			
	   for (i = 0; i < m_height; i++)
	   {
		   if (pdlg.CheckCancelButton())
			   if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			   {
				   canceled = true;
				   break;
			   }

		    for (j = 0; j < m_width; j++)
			{
			     //TODO: add extra pixel operations here...

                //thresholding...
		        if (m_img[i][j].intensity() < Tnew)
				{
				    //object/foreground  pixels(BLACK)
				    m_binaryimage[i][j]=0x01;
		
				}
			    else
				{ 
				    //background pixels(WHITE)
                    m_binaryimage[i][j]=0x00;
					
				}

			        pixelsProcessed++;			
			        if (pixelsProcessed % pixels == 0)
				        pdlg.StepIt();
			}

	   }

		
	}
	else
	{
		//do adaptive thresholding. what's that? Cosider a square block of sufficient size
		//now calculate the mean for each block . If intensity of a pixel in that block
		//is higher than mean just calculated for that block ,set the pixel ON;otherwise 
		//set it OFF in the resulting binary matrix.

		
        pdlg.SetDialogCaption("Applying Adaptive Thresholding...");
		UINT blocks = ((m_height * m_width)/(block * block)) * 0.01; // 1% of total blocks
		if (blocks == 0)
			blocks = 1;

		UINT blocksProcessed = 0;
		long sum;

		for(i = 0;; i += block)
		{
			if (i+block > m_height)
				break;

			if (pdlg.CheckCancelButton())
			 if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			 {
				 canceled = true;
				 break;
			 }

			 for(j = 0;; j += block)
			 {
				 if (j+block > m_width)
					 break;
				 
			   sum = 0;
			   for(k = i; k <= (i+block-1); k++)
			   {
				   for(l = j; l <= (j+block-1); l++)
				   {
						sum += m_img[k][l].intensity();
				   }
			   }

			   mean = (BYTE)(sum/(block * block));

			   // now again go through that block to set ON/OFF
			   for(k = i; k <= (i+block-1); k++)
			   {
				   for(l = j; l <= (j+block-1); l++)
				   {

					  if (m_img[k][l].intensity() < mean)
					  {
						  // paint as black
						  m_binaryimage[k][l] = 0x01;
						  
					  }
					  else
					  {
						  // paint as white
						  m_binaryimage[k][l] = 0x00;
						  
					  }

				   }
			   }

			   blocksProcessed++;
			   if (blocksProcessed % blocks == 0)
				   pdlg.StepIt();

			 }	//end for j

		}  //end for i

	}

    pdlg.DestroyWindow();

	if (canceled == true)
		return false;
	else
	    return DrawBinaryImageAfterBinarization(m_binaryimage,0,m_height-1,0,m_width-1);
}

///////////////////////////////////////////////////////////////////////////////
// Separate out three forking path from a single bifurcation point for
// ridge tracking
///////////////////////////////////////////////////////////////////////////////
void CImage::BranchSeparate(CBifurcationPoint* ptBP , PATH* path1,PATH* path2,PATH* path3)
{
	if ((path1 == NULL) ||
		(path2 == NULL) ||
		(path3 == NULL))
	{
		return;
	}

    if (m_binaryimage == NULL)
		return;

	CPoint Next[3];

	//Initialize  all paths
	path1->SetAt(0,&ptBP->pt);
	path2->SetAt(0,&ptBP->pt);
	path3->SetAt(0,&ptBP->pt);

	int Count = 0;
	int X = (ptBP->pt).x;
	int Y = (ptBP->pt).y;

	if (m_binaryimage[X-1][Y-1] == 0x01)
	{
       Next[Count] = CPoint(X-1,Y-1);
	   Count++;
	}

	if (m_binaryimage[X-1][Y] == 0x01)
	{
       Next[Count] = CPoint(X-1,Y);
	   Count++;
	}

	if (m_binaryimage[X-1][Y+1] == 0x01)
	{
       Next[Count] = CPoint(X-1,Y+1);
	   Count++;
	}

	if (m_binaryimage[X][Y+1] == 0x01)
	{
       Next[Count] = CPoint(X,Y+1);
	   Count++;
	}

	if (m_binaryimage[X+1][Y+1] == 0x01)
	{
       Next[Count] = CPoint(X+1,Y+1);
	   Count++;
	}

	if (m_binaryimage[X+1][Y] == 0x01)
	{
       Next[Count] = CPoint(X+1,Y);
	   Count++;
	}

	if (m_binaryimage[X+1][Y-1] == 0x01)
	{
       Next[Count] = CPoint( X + 1 , Y - 1 );
	   Count++;
	}

	if (m_binaryimage[X][Y-1] == 0x01)
	{
       Next[Count] = CPoint(X,Y-1);
	   Count++;
	}

	path1->SetAt(1,&Next[0]);
    path2->SetAt(1,&Next[1]);
	path3->SetAt(1,&Next[2]);

	if ( Count > 3 )
		AfxMessageBox("BranchSeparate fails : Supplied point is not a BifurcationPoint");
		

}

///////////////////////////////////////////////////////////////////////////////
// Follow through a path forked from a Bifurcation point
///////////////////////////////////////////////////////////////////////////////
CPoint* CImage::FindNext(PATH* path)
{
	
   int Current = path->GetSize() - 1;    // 0-based index
   int X = (path->GetAt(Current))->x;
   int Y = (path->GetAt(Current))->y;
   int NextX = 0,NextY = 0;

   if (IsCrossedBoundary(m_height,m_width,(unsigned)X,(unsigned)Y)==false)
   {
    if ( Current == 0 )                  // only one pixel in the path list
    {                                    // so, simply track forward
	   if ( m_binaryimage[X][Y-1] == 0x01)
	   {
		   NextX = X;
		   NextY = Y-1;
	   }
	   else if ( m_binaryimage[X-1][Y-1] == 0x01)
	   {  
		   NextX = X-1;
		   NextY = Y-1;
	   }
	   else if ( m_binaryimage[X-1][Y] == 0x01)
	   {
		   NextX = X-1;
		   NextY = Y;
	   }
	   else if ( m_binaryimage[X-1][Y+1] == 0x01)
	   {
		   NextX = X-1;
		   NextY = Y+1;
	   }
	   else if ( m_binaryimage[X][Y+1] == 0x01)
	   {
		   NextX = X;
		   NextY = Y+1;
	   }
	   else if ( m_binaryimage[X+1][Y+1] == 0x01)
	   {
		   NextX = X+1;
		   NextY = Y+1;
	   }
	   else if ( m_binaryimage[X+1][Y] == 0x01)
	   {
		   NextX = X+1;
		   NextY = Y;
	   }
       else 
	   {
		   NextX = X+1;
		   NextY = Y-1;
	   }
    }
    else
    {
	  // more than one pixels in the path need to check the back tracking condition
	   int PrevX = (path->GetAt(Current-1))->x;
	   int PrevY = (path->GetAt(Current-1))->y;

	   if ((m_binaryimage[X][Y-1] == 0x01) && ((PrevX != X) && (PrevY != Y-1)))
	   {
		   NextX = X;
		   NextY = Y-1;
	   }
	   else if ((m_binaryimage[X-1][Y-1] == 0x01) && ((PrevX != X-1) && (PrevY != Y-1)))
	   {
		   NextX = X-1;
		   NextY = Y-1;
	   }
	   else if ((m_binaryimage[X-1][Y] == 0x01) && ((PrevX != X-1) && (PrevY != Y)))
	   {
		   NextX = X-1;
		   NextY = Y;
	   }
	   else if ((m_binaryimage[X-1][Y+1] == 0x01) && ((PrevX != X-1) && (PrevY != Y+1)))
	   {
		   NextX = X-1;
		   NextY = Y+1;
	   }
	   else if ((m_binaryimage[X][Y+1] == 0x01) && ((PrevX != X) && (PrevY != Y+1)))
	   {
		   NextX = X;
		   NextY = Y+1;
	   }
	   else if ((m_binaryimage[X+1][Y+1] == 0x01) && ((PrevX != X+1) && (PrevY != Y+1)))
	   {
		   NextX = X+1;
		   NextY = Y+1;
	   }
	   else if ((m_binaryimage[X+1][Y] == 0x01) && ((PrevX != X+1) && (PrevY != Y)))
	   {
		   NextX = X+1;
		   NextY = Y;
	   }
	   else
	   {
		   NextX = X+1;
		   NextY = Y-1;
	   }
	}
   }

   //Update the path
   CPoint* Next = new CPoint(NextX , NextY);
   path->SetAtGrow(Current + 1,Next);
   
   return Next;
   

}

bool CImage::CheckSingularityWhileTracking(PATH* path)
{
 
	if (path->GetUpperBound() != -1)
	{
	  int CurrX = path->GetAt(path->GetSize() - 1)->x;
	  int CurrY = path->GetAt(path->GetSize() - 1)->y;

	  if (IsBifurcation(m_thinmap,(unsigned)CurrX,(unsigned)CurrY))
	  {
		  // Bifurcation : not to be included in validated branch-list
		  return true;
	  }
	  else if (IsEnd(m_thinmap,(unsigned)CurrX,(unsigned)CurrY))
	  {
		  // Endpoint : not to be included in validated end-list
		  CEndPoint* EP = new CEndPoint();
		  EP->pt.SetPoint(CurrX, CurrY);
		  m_badendlist.SetAtGrow(m_bad_endlist_index++, EP);
		  return true;
	  }
	  else if ((CurrX == 0) && (CurrY == 0))
	  {
		  return true;
	  }
	}

}

void CImage::BranchTrack()
{
	
	// Main branch tracking function
	BRANCH_LIST realbranchlist;
	realbranchlist.SetSize(100);

	
	if (m_branchlist.GetUpperBound() == -1)
	{
		AfxMessageBox("Minutiae list is yet to be extracted\n No question to validate them",MB_OK|MB_ICONSTOP);
	}
    else
	{
		int iNoOfBranchPoints = m_branchlist.GetSize() - 1;
		PATH path1,path2,path3;

		bool flag1 = false,flag2 = false , flag3 = false;
		bool flag  = false;

		int  iCount = 0;
		CBifurcationPoint realBP;


		// Avoid memory fragmentation
		path1.SetSize(100);
		path2.SetSize(100);
		path3.SetSize(100);

		
		for(int i = 0 ; i < iNoOfBranchPoints ; i++)
		{
			// clear three paths
			path1.RemoveAll();
			path2.RemoveAll();
			path3.RemoveAll();

			path1.Add(&m_branchlist[i]->pt);
			path2.Add(&m_branchlist[i]->pt);
			path3.Add(&m_branchlist[i]->pt);


			// if ridge length > 25 pixels , it's a valid branch point
		
			for(int j = 0 ; j < 25 ; j++)
			{
				if ( j == 1 )
				{
					// for first time just separate out all three paths 
					// from the i-th BifurcationPoint

					BranchSeparate(m_branchlist[i],&path1,&path2,&path3);

				}
				else
				{
					// iterate through all three paths simultaneously
					
					FindNext(&path1);
					FindNext(&path2);
					FindNext(&path3);

				}


				flag1 = CheckSingularityWhileTracking(&path1);
				flag2 = CheckSingularityWhileTracking(&path2);
				flag3 = CheckSingularityWhileTracking(&path2);


				if (flag1 || flag2 || flag3)
				{
					flag = true;
					break;
				}
			}

			
			// If the path length of the ridge is  longer than 24 pixels
		    // it consider as a valid minutia
		
			if (flag == false )
			{
				// no abnormal exit upon singularity
				// so, store it in the real_branch
				
				realbranchlist.SetAtGrow(iCount++, m_branchlist.GetAt(i));
			}
		}
		
		// Update the member function m_branchlist
		m_branchlist.RemoveAll();
		m_branchlist.Append(realbranchlist);
				
	}
}

bool CImage::Segmentation(UINT block)
{
 
	//do Segmentation. what's that? Cosider a square block of sufficient size
	//now calculate the mean for each block . If intensity of a pixel in that block
	//is higher( WHITE : 255 , BLACK : 0)than mean just calculated for that block ,
	//set the pixel White;otherwise keep it unchanged in the resulting matrix.
        
	// Setup and Call Progress Dialog
	CProgressDlg pdlg("Segmenting The Fingerprint...");
	pdlg.Create();
	unsigned int pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	unsigned int pixelsProcessed = 0;
	bool canceled = false;

	// fill convolution kernel
	float hcoe[5][5];
	hcoe[0][0] = 1.00;
	hcoe[0][1] = 1.00;
	hcoe[0][2] = 1.00;
    hcoe[0][3] = 1.00;
	hcoe[0][4] = 1.00;
    hcoe[1][0] = 1.00;
	hcoe[1][1] = 1.00;
	hcoe[1][2] = 1.00;
	hcoe[1][3] = 1.00;
	hcoe[1][4] = 1.00;
    hcoe[2][0] = 1.00;
	hcoe[2][1] = 1.00;
	hcoe[2][2] = 1.00;
	hcoe[2][3] = 1.00;
	hcoe[2][4] = 1.00;
	hcoe[3][0] = 1.00;
	hcoe[3][1] = 1.00;
	hcoe[3][2] = 1.00;
	hcoe[3][3] = 1.00;
	hcoe[3][4] = 1.00;
	hcoe[4][0] = 1.00;
	hcoe[4][1] = 1.00;
	hcoe[4][2] = 1.00;
	hcoe[4][3] = 1.00;
	hcoe[4][4] = 1.00;

	float R, G, B;
	pixel pix;
	int a, b, i, j, k, l, x, y;
	
	const int radius = 2;
	const int circumference = 4;	

	// convolution kernal sum
	float sum = 0;					
	for (a = 0; a < 5; a++)
		for (b = 0; b < 5; b++)
			sum += hcoe[a][b];

	if (sum <= 0)
		sum = 1;
	else
	{
		for (a = 0; a < 5; a++)
			for (b = 0; b < 5; b++)
				hcoe[a][b] /= sum;
	}


	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
		    //TODO: add extra pixel operations here

			R = G = B = 0;
			for (k = 0; k <= circumference; k++)
			{
				for (l = 0; l <= circumference; l++)
				{
					x = i + k - radius;
					y = j + l - radius;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * hcoe[k][l];
						G += (float)m_img[x][y].g * hcoe[k][l];
						B += (float)m_img[x][y].b * hcoe[k][l];
					}
				}
			}
			
			pix.color(R, G, B);
			if (m_img[i][j].intensity() < pix.intensity())
				m_processed[i][j] = m_img[i][j];
			else 
				m_processed[i][j].color((BYTE)255);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	pdlg.DestroyWindow();

	return !canceled;


}

bool CImage::Gray()
{
	// Setup and Call Progress Dialog
	CProgressDlg pdlg("Gray Scaling...");
	pdlg.Create();
	UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	UINT pixelsProcessed = 0;
	bool canceled = false;

	// gray-scaling

	UINT  i, j;
	BYTE x;

    for (i = 0; i < m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < m_width; j++)
		{
			//TODO: add extra pixel operations here

		 
            x = m_img[i][j].Gray();
			m_processed[i][j].color(x);

            pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
 
	
	pdlg.DestroyWindow();
	
    return !canceled;
}

bool CImage::Negative()
{
	// Setup and Call Progress Dialog
	CProgressDlg pdlg("Making Negative...");
	pdlg.Create();
	UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	UINT pixelsProcessed = 0;
	bool canceled = false;

	// Negative algorithm

	UINT  i, j;
    pixel pix;

    for (i = 0; i < m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < m_width; j++)
		{
			//TODO: add extra pixel operations here

            pix=m_img[i][j];
			pix.r=255 - pix.r;
			pix.g=255 - pix.g;
			pix.b=255 - pix.b;

			m_processed[i][j] = pix;
            
            pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
 
	
	pdlg.DestroyWindow();

	return !canceled;

}

bool CImage::Convolution()
/////////////////////////////////////////////////////////////////////////////
// Desc  : Custom Convolution( 5 By 5)
//
{
	CConvolutionDlg dlg;
	if (dlg.DoModal() != IDOK)
		return false;
    
	// Fetch filter name...
	CString szFilterName("Applying ");
    switch(dlg.m_iSel)
	{
	  case 0: szFilterName += "2D Laplacian Operator...";
		      break;
	  case 1: szFilterName += "Sobel Operator...";
		      break;
	  case 2: szFilterName += "Roberts Operator...";
		      break;
	  case 3: szFilterName += "Isotropic Operator...";
		      break;
	  case 4: szFilterName += "Prewitt Operator...";
		      break;
	  case 5: szFilterName += "Kirsch Compass Operator...";
		      break;
	  case 6: szFilterName += "Stochastic Operator For SNR = 1...";
		      break;
	  case 7: szFilterName += "Pyramidal Filter...";
		      break;
	  case 8: szFilterName += "Cone Filter...";
		      break;
	  case 9: szFilterName += "Gaussian Operator...";
			  break;
	  case 10:szFilterName += "Unsharp Masking Operator...";
		      break;
	  default:szFilterName.Empty();
		      break;
	}

   // Setup and Call Progress Dialog
	CProgressDlg pdlg(szFilterName);
	pdlg.Create();
	unsigned int pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	unsigned int pixelsProcessed = 0;
	bool canceled = FALSE;

	// fill convolution kernel
	float hcoe[5][5];
	hcoe[0][0] = (float)dlg.m_iPos1;
	hcoe[0][1] = (float)dlg.m_iPos2;
	hcoe[0][2] = (float)dlg.m_iPos3;
    hcoe[0][3] = (float)dlg.m_iPos4;
	hcoe[0][4] = (float)dlg.m_iPos5;
    hcoe[1][0] = (float)dlg.m_iPos6;
	hcoe[1][1] = (float)dlg.m_iPos7;
	hcoe[1][2] = (float)dlg.m_iPos8;
	hcoe[1][3] = (float)dlg.m_iPos9;
	hcoe[1][4] = (float)dlg.m_iPos10;
    hcoe[2][0] = (float)dlg.m_iPos11;
	hcoe[2][1] = (float)dlg.m_iPos12;
	hcoe[2][2] = (float)dlg.m_iPos13;
	hcoe[2][3] = (float)dlg.m_iPos14;
	hcoe[2][4] = (float)dlg.m_iPos15;
	hcoe[3][0] = (float)dlg.m_iPos16;
	hcoe[3][1] = (float)dlg.m_iPos17;
	hcoe[3][2] = (float)dlg.m_iPos18;
	hcoe[3][3] = (float)dlg.m_iPos19;
	hcoe[3][4] = (float)dlg.m_iPos20;
	hcoe[4][0] = (float)dlg.m_iPos21;
	hcoe[4][1] = (float)dlg.m_iPos22;
	hcoe[4][2] = (float)dlg.m_iPos23;
	hcoe[4][3] = (float)dlg.m_iPos24;
	hcoe[4][4] = (float)dlg.m_iPos25;

	float R, G, B;
	int a, b, i, j, k, l, x, y;
	
	const int radius = 2;
	const int circumference = 4;	

	// convolution kernal sum
	float sum = 0;					
	for (a = 0; a < 5; a++)
		for (b = 0; b < 5; b++)
			sum += hcoe[a][b];

	if (sum <= 0)
		sum = 1;
	else
	{
		for (a = 0; a < 5; a++)
			for (b = 0; b < 5; b++)
				hcoe[a][b] /= sum;
	}


	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
		    //TODO: add extra pixel operations here

			R = G = B = 0;
			for (k = 0; k <= circumference; k++)
			{
				for (l = 0; l <= circumference; l++)
				{
					x = i + k - radius;
					y = j + l - radius;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * hcoe[k][l];
						G += (float)m_img[x][y].g * hcoe[k][l];
						B += (float)m_img[x][y].b * hcoe[k][l];
					}
				}
			}
			m_processed[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	pdlg.DestroyWindow();

	return !canceled;


}


bool CImage::EdgeDetection()
////////////////////////////////////////////////////////////////////////////
// Desc   :This algorithm is by Sobel's[SOBEL7] gradient operator technique
//         for finding edges of images especially digital images
//
{
	float R, G, B;
	int a, b, i, j, k, l, x, y;

	// Setup and Call Progress Dialog
	CProgressDlg pdlg("Detecting Edges...");
	pdlg.Create();
	unsigned int pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	unsigned int pixelsProcessed = 0;
	bool canceled = FALSE;
    
	//prepare for h1 & h2
	float H1[3][3];

	H1[0][0]=(float)1.0;
	H1[0][1]=(float)0.0;
	H1[0][2]=(float)-1.0;
	H1[1][0]=(float)2.0;
	H1[1][1]=(float)0.0;
	H1[1][2]=(float)-2.0;
	H1[2][0]=(float)1.0;
	H1[2][1]=(float)0.0;
	H1[2][2]=(float)-1.0;

	// convolution kernal sum
	float sum = 0.0;					
	for (a = 0; a < 3; a++)
		for (b = 0; b < 3; b++)
			sum += H1[a][b];

	if (sum <= 0.00)
        sum = 1.0;
    else
	{
		for (a = 0; a < 3; a++)
			for (b = 0; b < 3; b++)
				H1[a][b] /= sum;
	} 


    float H2[3][3];

	H2[0][0]=(float)1.0;
	H2[0][1]=(float)2.0;
	H2[0][2]=(float)1.0;
	H2[1][0]=(float)0.0;
	H2[1][1]=(float)0.0;
	H2[1][2]=(float)0.0;
	H2[2][0]=(float)-1.0;
	H2[2][1]=(float)-2.0;
	H2[2][2]=(float)-1.0;

	sum = 0.0;						// convolution kernal sum
	for (a = 0; a < 3; a++)
		for (b = 0; b < 3; b++)
			sum += H2[a][b];

	if (sum <= 0.0)
		sum = 1.0;
	else
	{
		for (a = 0; a < 3; a++)
			for (b = 0; b < 3; b++)
				H2[a][b] /= sum;
	}


	imagematrix G1=CreateImageMatrix(m_height,m_width);
    imagematrix G2=CreateImageMatrix(m_height,m_width);
    
    // fill G1
	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			R = G = B = 0;
			for (k = 0; k <=2; k++)
			{
				for (l = 0; l <= 2; l++)
				{
					x = i + k - 1;
					y = j + l - 1;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * H1[k][l];
						G += (float)m_img[x][y].g * H1[k][l];
						B += (float)m_img[x][y].b * H1[k][l];
					}
				}
			}
			G1[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
    
    // fill G2
    pdlg.SetPos(0);

	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			R = G = B = 0;
			for (k = 0; k <=2; k++)
			{
				for (l = 0; l <= 2; l++)
				{
					x = i + k - 1;
					y = j + l - 1;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * H2[k][l];
						G += (float)m_img[x][y].g * H2[k][l];
						B += (float)m_img[x][y].b * H2[k][l];
					}
				}
			}
			G2[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
	
    //allocate & calculate G[m][n]::sqrt(sqr(G1[m][n])+sqr(G2[m][n]))
	pdlg.SetPos(0);
	

	BYTE x1,x2,val;
	

	// Threshold may be selected using cumulative histogram of G[m][n] 
	// so that 5 to 10% of pixels with largest gradients are declared as edges...
	BYTE Threshold=70; //fixed ???
	
  
   for(i = 0; i < (int)m_height; i++)
   {
	   if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;   //get out of the this loop & these loops...
			}
	   for(j = 0; j < (int)m_width; j++)
	   {
		   x1=G1[i][j].intensity();
		   x2=G2[i][j].intensity();
		   
		   val=(BYTE)sqrt((float)(x1 * x1 + x2 * x2));
		  
           if (val < Threshold)
			   m_processed[i][j].color((BYTE)255);
		   else
			   m_processed[i][j].color((BYTE)0);


		   pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
	   }
   }

	pdlg.DestroyWindow();

	return !canceled;

}


bool CImage::OrientationEstimation()
{

 /*
   ALTERNATIVE:

	  We compute the orientation at each pixel P(i,j) by sliding the 5 x 5 mask 


							 ___ ___ ___ ___ ___
		                    |   |   |   |   |   |
		                    |_3_|___|_2_|___|_1_|
		                    |	|   |   |   |   |
		                    |___|___|___|___|___|
		                    |	|   |   |   |   |
		                    |_0_|___|_c_|___|_0_|
							|   |   |   |   |   |
							|___|___|___|___|___|
			                |   |   |   |   |   |
			  				|_1_|___|_2_|___|_3_|
				

									Fig - 1


	  over P where c is the center pixel P(i,j). We look at the differences 
	  between P(i,j) and P(im,jm) for m = 1,2,3,4 where im = {i+2, i+2, i,i-2,i-2} and 
	  jm = {j, j+2, j+2, j+2,j} in Fig - 1 . We use the minimum absolute difference
	  to estimate the slope V(i,j) of the orientation at P(i,j):
               
				     V(i,j) = min { | P(i,j) - P(im,jm) | }

      We compute a directional histogram for each q x q (5 x 5) block in V. For each 
	  block, we quantize the dominant direction to 0, 1, 2, or 3, which represent 
	  0°, 45° , 90° and 135°


                            3          2          1
                              \        |        /
                                \      |      /
                                  \    |    /
                                    \  |  /
                      0  -------------\|/------------- 0


									Fig - 2

  ACTUAL :
			
	  

*/
	// First make m_processed a copy of original m_img to draw on
	CopyImageMatrix(m_processed,m_img);
	//m_img = InvertImageMatrix(m_img);

	float R, G, B;
	int   a, b, i, j, k, l, x, y;

	// Setup and Call Progress Dialog
	CProgressDlg pdlg;
	pdlg.Create();

	unsigned int pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	unsigned int pixelsProcessed = 0;
	bool canceled = false;
    
	//prepare for h1 & h2
	float H1[3][3];

	H1[0][0]=(float)1.0;
	H1[0][1]=(float)2.0;
	H1[0][2]=(float)1.0;
	H1[1][0]=(float)0.0;
	H1[1][1]=(float)0.0;
	H1[1][2]=(float)0.0;
	H1[2][0]=(float)-1.0;
	H1[2][1]=(float)-2.0;
	H1[2][2]=(float)-1.0;

	// convolution kernal sum
	float sum = 0.0;					
	for (a = 0; a < 3; a++)
		for (b = 0; b < 3; b++)
			sum += H1[a][b];

	if (sum <= 0.0)
        sum = 1.0;
    else
	{
		for (a = 0; a < 3; a++)
			for (b = 0; b < 3; b++)
				H1[a][b] /= sum;
	} 

    float H2[3][3];

	H2[0][0]=(float)1.0;
	H2[0][1]=(float)0.0;
	H2[0][2]=(float)-1.0;
	H2[1][0]=(float)2.0;
	H2[1][1]=(float)0.0;
	H2[1][2]=(float)-2.0;
	H2[2][0]=(float)1.0;
	H2[2][1]=(float)0.0;
	H2[2][2]=(float)-1.0;

	sum = 0.0;						// convolution kernal sum
	for (a = 0; a < 3; a++)
		for (b = 0; b < 3; b++)
			sum += H2[a][b];

	if (sum <= 0.0)
		sum = 1.0;
	else
	{
		for (a = 0; a < 3; a++)
			for (b = 0; b < 3; b++)
				H2[a][b] /= sum;
	}


	imagematrix G1=CreateImageMatrix(m_height,m_width);
    imagematrix G2=CreateImageMatrix(m_height,m_width);
    pdlg.SetDialogCaption("Calculating HZ & VR Gradients - Gx & Gy...");

    // fill G1
	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			R = G = B = 0.0;
			for (k = 0; k <=2; k++)
			{
				for (l = 0; l <= 2; l++)
				{
					x = i + k - 1;
					y = j + l - 1;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * H1[k][l];
						G += (float)m_img[x][y].g * H1[k][l];
						B += (float)m_img[x][y].b * H1[k][l];
					}
				}
			}

			G1[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
    
	if (canceled) return false;

    // fill G2
    pdlg.SetPos(0);

	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			R = G = B = 0.0;
			for (k = 0; k <=2; k++)
			{
				for (l = 0; l <= 2; l++)
				{
					x = i + k - 1;
					y = j + l - 1;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * H2[k][l];
						G += (float)m_img[x][y].g * H2[k][l];
						B += (float)m_img[x][y].b * H2[k][l];
					}
				}
			}

			G2[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	if (canceled) return false;

	pdlg.SetPos(0);
	pdlg.SetDialogCaption("Applying Least-Square Technique...");

	float** orientNUM = CreateFloatMatrix(m_height,m_width);
    float** orientDEN = CreateFloatMatrix(m_height,m_width);
    BYTE    x1,x2;

	 for(i = 0; i < (int)m_height; i++)
	 {
	   if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;   //get out of the this loop & these loops...
			}
	   for(j = 0; j < (int)m_width; j++)
	   {
		   x1=G1[i][j].intensity();
		   x2=G2[i][j].intensity();
		   
		   orientNUM[i][j] = (float)(2.0 * x1 * x2);
		   orientDEN[i][j] = (float)(sqr(x1) - sqr(x2));


		   pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
	   }
   }

	if (canceled) return false;

	/*
	pdlg.SetPos(0);
	pdlg.SetDialogCaption("Applying Gaussian Filter On HZ & VR Gradients...");

	float** orientNUMSmoothed = CreateFloatMatrix(m_height,m_width);
    float** orientDENSmoothed = CreateFloatMatrix(m_height,m_width);
	float   N,D;

	//prepare Gauusian masks
	float hcoe[5][5];
	hcoe[0][0] = 2.00/115;
	hcoe[0][1] = 4.00/115;
	hcoe[0][2] = 5.00/115;
    hcoe[0][3] = 4.00/115;
	hcoe[0][4] = 2.00/115;

    hcoe[1][0] = 4.00/115;
	hcoe[1][1] = 9.00/115;
	hcoe[1][2] = 12.00/115;
	hcoe[1][3] = 9.00/115;
	hcoe[1][4] = 4.00/115;

    hcoe[2][0] = 5.00/115;
	hcoe[2][1] = 12.00/115;
	hcoe[2][2] = 15.00/115;
	hcoe[2][3] = 12.00/115;
	hcoe[2][4] = 5.00/115;

	hcoe[3][0] = 4.00/115;
	hcoe[3][1] = 9.00/115;
	hcoe[3][2] = 12.00/115;
	hcoe[3][3] = 9.00/115;
	hcoe[3][4] = 4.00/115;

	hcoe[4][0] = 2.00/115;
	hcoe[4][1] = 4.00/115;
	hcoe[4][2] = 5.00/115;
	hcoe[4][3] = 4.00/115;
	hcoe[4][4] = 2.00/115;


	// convolution kernal sum
	sum = 0.0;					
	for (a = 0; a < 5; a++)
		for (b = 0; b < 5; b++)
			sum += hcoe[a][b];

	if (sum <= 0.0)
		sum = 1.0;
	else
	{
		for (a = 0; a < 5; a++)
			for (b = 0; b < 5; b++)
				hcoe[a][b] /= sum;
	}


	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
		    //TODO: add extra pixel operations here

			N = D = 0.0;
			for (k = 0; k <= 4; k++)
			{
				for (l = 0; l <= 4; l++)
				{
					x = i + k - 2;
					y = j + l - 2;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						N += (float)orientNUM[x][y] * hcoe[k][l];
						D += (float)orientDEN[x][y] * hcoe[k][l];
					}
				}
			}
			
			orientNUMSmoothed[i][j] = N;
			orientDENSmoothed[i][j] = D;

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	if (canceled) return false;

  */
	pdlg.SetPos(0);
	pdlg.SetDialogCaption("Calculating Orientation Estimation...");

    // Divide the image in [block * block] sized sectors...
	// Avoid hard-coding block-size in the program.
	//UINT    block = floor(floor((m_width + m_height)/2)/25);  
	UINT block = 16;

	// Alloacte orientation-map member variable...
	m_orientation = CreateFloatMatrix(m_height/block,m_width/block);

	UINT    blocks = ((m_height * m_width)/(block * block)) * 0.01; // 1% of total blocks
	if (blocks == 0)
		blocks = 1;

	UINT    blocksProcessed = 0;
	float   sumNUM,sumDEN;
	float   angle;

	for(i = 0 ;; i += block)
	{
		if (i+block > (int)m_height)
			break;

		if (pdlg.CheckCancelButton())
		   if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
			   canceled = true;
			   break;
			}

		for(j = 0;; j += block)
		{
			if (j+block > (int)m_width)
				break;
				 
			sumNUM = sumDEN = 0.0;
			for(k = i; k <= (i+block-1); k++)
			{
			  for(l = j; l <= (j+block-1); l++)
			  {
				  //TODO : Add your block operation here

				  sumNUM += orientNUM[k][l];
				  sumDEN += orientDEN[k][l];
					
			  }
			}

			angle = 0.5 * (float)atan2((double)sumNUM,(double)sumDEN);

	/*
		To get the correct orinentation the sign of numerator & denominator are
		first checked.If numerator is negative & denominator is positive 90 degree(PI/2 
		radian)is added to angle.If numerator is positive & denominator is negative
		180(PI radian) degree is added to angle.Otherwise angle is kept unchanged.

        Adapted from the paper "Fingerprint Feature Extraction Using Block-Direction
		On Reconstructed Images" By S. Kasaei,M. Deriche,B. Boashash From
		 
		Signal Processing Research Centre(SPRC),QUT
        GPO Box 2434
		Brisbane Q 4001
		Australia
		email : skasaei@lux.sprc.qut.edu.au
     
     */
	
			
			if (angle < 0)
			{
				// NUM & DEN are of opposite sign

				
				if (sumNUM < 0)
				{
					angle += PI/2;
				}
				else
				{
					angle += PI;
				}
				
			}
			else   
			{
				// NUM & DEN are of same sign

				if (sumNUM > 0)
				{
				  // NUM & DEN are both positive
				 
				 angle += PI/2;

				}
			}


			// Store the dominant ridge direction (DRD) for this block
			m_orientation[i/block][j/block] = angle;
			
			if (angle > 0)
			{
				DrawLineOnTop(
					m_processed,
					CPoint(
						NONZERO(i+block/2-5*cos(angle)),
						NONZERO(j+block/2-5*sin(angle))),
					CPoint(
						NONZERO(i+block/2+5*cos(angle)),
						NONZERO(j+block/2+5*sin(angle))),
					RGB(0,0,255));
			}
			else
			{
				DrawLineOnTop(
					m_processed,
					CPoint(
						NONZERO(i+block/2-5*cos(angle)),
						NONZERO(j+block/2-5*sin(angle))),
					CPoint(
						NONZERO(i+block/2+5*cos(angle)),
						NONZERO(j+block/2+5*sin(angle))),
					RGB(0,0,255));
			}

			   blocksProcessed++;
			   if (blocksProcessed % blocks == 0)
				   pdlg.StepIt();

			 }	//end for j

		}  //end for i

	pdlg.DestroyWindow();

	//Free all those memory junks...
	FreeImageMatrix(G1,m_height);
	FreeImageMatrix(G2,m_height);
	FreeFloatMatrix(orientNUM,m_height);
	FreeFloatMatrix(orientDEN,m_height);
	//FreeFloatMatrix(orientNUMSmoothed,m_height);
	//FreeFloatMatrix(orientDENSmoothed,m_height);

	if (canceled) return false;

	return true;
}

bool CImage::MarkRegionOfInterest(float Threshold)
{

	// Setup and Call Progress Dialog
	CProgressDlg pdlg("Applying 3X3 Sobel filter before marking ROI...");
	pdlg.Create();
	UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	UINT pixelsProcessed = 0;
	bool canceled = false;

    //prepare for Hx & Hx ( 3 * 3 SOBEL operator masks )
	float Hx[3][3];

	Hx[0][0]=1.0;
	Hx[0][1]=0.0;
	Hx[0][2]=-1.0;
	Hx[1][0]=1.414;      
	Hx[1][1]=0.0;		 
	Hx[1][2]=-1.414;	 
	Hx[2][0]=1.0;
	Hx[2][1]=0.0;
	Hx[2][2]=-1.0;

	float Hy[3][3];

	Hy[0][0]=1.00;
    Hy[0][1]=1.414;
	Hy[0][2]=1.00;
	Hy[1][0]=0.0;
	Hy[1][1]=0.0;
	Hy[1][2]=0.0;
	Hy[2][0]=-1.0;
	Hy[2][1]=-1.414;
	Hy[2][2]=-1.00;

	// Allocate Gx & GY
	imagematrix GX=CreateImageMatrix(m_height,m_width);
	imagematrix GY=CreateImageMatrix(m_height,m_width);
	
	int i,j,k,l,x,y;
	BYTE R,G,B;

	// Fill GX
	pdlg.SetDialogCaption("Calculating Horizontal Gradient...");
	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			R = G = B = 0;
			for (k = 0; k <=2; k++)
			{
				for (l = 0; l <= 2; l++)
				{
					x = i + k - 1;
					y = j + l - 1;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * Hx[k][l];
						G += (float)m_img[x][y].g * Hx[k][l];
						B += (float)m_img[x][y].b * Hx[k][l];
					}
				}
			}

			GX[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
    
	// Fill GY
    pdlg.SetPos(0);
	pdlg.SetDialogCaption("Calculating Vertical Gradient...");

	for (i = 0; i < m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < m_width; j++)
		{
			R = G = B = 0;
			for (k = 0; k <=2; k++)
			{
				for (l = 0; l <= 2; l++)
				{
					x = i + k - 1;
					y = j + l - 1;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * Hy[k][l];
						G += (float)m_img[x][y].g * Hy[k][l];
						B += (float)m_img[x][y].b * Hy[k][l];
					}
				}
			}

			GY[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}


	//Make a copy
	CopyImageMatrix(m_processed,m_img);

	pdlg.SetPos(0);
	pdlg.SetDialogCaption("Identifying the ROI(Region OfInterest)...");
	UINT block = 16;
	UINT    blocks = ((m_height * m_width)/(block * block)) * 0.01; // 1% of total blocks
	if (blocks == 0)
		blocks = 1;

	UINT    blocksProcessed = 0;
	float   sum;
	float   angle;
	float	certaintyLevel,Vx,Vy;

	for(i = 0 ;; i += block)
	{
		if (i+block > (int)m_height)
			break;

		if (pdlg.CheckCancelButton())
		   if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
			   canceled = true;
			   break;
			}

		for(j = 0;; j += block)
		{
			if (j+block > (int)m_width)
				break;
				 
			sum = 0.0;
			Vx = Vy = 0.0;
			certaintyLevel = 0.0;
			for(k = i; k <= (i+block-1); k++)
			{
			  for(l = j; l <= (j+block-1); l++)
			  {
				  //TODO : Add your block operation here

				  sum += (float)(sqr(GX[k][l].Gray()) + sqr(GY[k][l].Gray()));
				  Vx += 2 * GX[k][l].Gray() * GY[k][l].Gray();
				  Vy += (float)(sqr(GX[k][l].Gray()) - sqr(GY[k][l].Gray()));
					
			  }
			}


			//Certainty level calculation
			certaintyLevel = sqrt((sqr(Vx) + sqr(Vy)) / (sqr(block) * sum));

			if (certaintyLevel > Threshold)
			{
				//Background pixel..Make the entire block white(background)
				for(k = i; k <= (i+block-1); k++)
				{
					for(l = j; l <= (j+block-1); l++)
					{
					
						//TODO : Add your block operation here
						m_processed[k][l].color((BYTE)WHITE);	
					
					}
				}

			
			}

			
			blocksProcessed++;
			if (blocksProcessed % blocks == 0)
			   pdlg.StepIt();

		}	//end for j

	}  //end for i


	//Delete memory junks for sobel filter
	FreeImageMatrix(GX,m_height);
	FreeImageMatrix(GY,m_height);

	pdlg.DestroyWindow();

	if (canceled == true)
		return false;


}


bool CImage::Equalize()
{
	
	//InitializeOperation();

   // Setup and Call Progress Dialog
	CProgressDlg pdlg("Equalizing...");
	pdlg.Create();
	UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	UINT pixelsProcessed = 0;
	bool canceled = false;
	const BYTE MAXGREY=255;

	// Equalization
	UINT  i, j,k;
	BYTE x,value;
	long *h=Histogram(m_img);
	long cumulative;
	int dummy;
   
    for (i = 0; i < m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < m_width; j++)
		{
			//TODO: add extra pixel operations here
		  
            x = m_img[i][j].Gray();
			cumulative=0;

			for(k = 0; k < x; k++)
			{
				cumulative+=h[k];
			}
			
			dummy=ROUND(((MAXGREY * cumulative)/(m_height * m_width))-1);

			if (dummy < 0)
				value=0;
			else
				value=dummy;

			m_processed[i][j].color(value);

			
            pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
 
	
	pdlg.DestroyWindow();
	
	return !canceled;

}


bool CImage::BlurFilter()
{
  // Setup and Call Progress Dialog
  CProgressDlg pdlg;
  pdlg.Create();
  unsigned int pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
  unsigned int pixelsProcessed = 0;
  bool canceled = FALSE;

  
  float R, G, B;
  int a,b,i,j,k,l,x,y;
  float h[7][7];

  for(a = 0; a < 7; a++)
	for(b = 0; b < 7; b++)
		h[a][b]=0.0;


  h[3][3] = -4;
  h[2][2] = 1;
  h[2][3] = 4;
  h[2][4] = 1;
  h[3][2] = 4;
  h[3][4] = 4;
  h[4][2] = 1;
  h[4][3] = 4;
  h[4][4] = 1;
  
  const int radius = 3;
  const int circumference = 6;	

  // convolution kernal sum
  float sum = 0;					
  for (a = 0; a < 7; a++)
	for (b = 0; b < 7; b++)
		sum += h[a][b];

	if (sum <= 0)
		sum = 1;
	else
	{
		for (a = 0; a < 7; a++)
			for (b = 0; b < 7; b++)
				h[a][b] /= sum;
	}

	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			R = G = B = 0;
			for (k = 0; k <= circumference; k++)
			{
				for (l = 0; l <= circumference; l++)
				{
					x = i + k - radius;
					y = j + l - radius;

					if (x >= 0 && x < (int)m_height && y >= 0 && y < (int)m_width)
					{
						R += (float)m_img[x][y].r * h[k][l];
						G += (float)m_img[x][y].g * h[k][l];
						B += (float)m_img[x][y].b * h[k][l];
					}
				}
			}
			m_processed[i][j].color(R, G, B);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	pdlg.DestroyWindow();

    return !canceled;
    
}

bool CImage::Normalize(float DesiredMean,float DesiredVariance)
{

  // Setup and Call Progress Dialog
  CProgressDlg pdlg;
  pdlg.Create();
  UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
  UINT pixelsProcessed = 0;
  bool canceled = false;


  int i,j,k,l,x,y;
  BYTE value,intensity;
  float sum1 = 0,sum2 = 0;
  float Mean,Variance;
  float result;

  pdlg.SetDialogCaption("Calculating Mean & Variances...");

  	for (i = 0; i < (int)m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{
			
			intensity = m_img[i][j].intensity();
			sum1 += intensity;
			sum2 += sqr(intensity);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();

		}
	}

  // estimated mean & variance
  Mean = (sum1/pixelsProcessed);
  Variance =((sum2/pixelsProcessed) - (Mean * Mean));
     
  pdlg.SetPos(0);
  pdlg.SetDialogCaption("Fixing To Desired Mean & Variance...");

  for (i = 0; i < (int)m_height; i++)
  {
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < (int)m_width; j++)
		{

			intensity = m_img[i][j].intensity();
			if (intensity > Mean)
			{
				result = DesiredMean + sqrt((sqr(intensity - Mean) * DesiredVariance)/Variance);
			}
			else
			{ 
				result = DesiredMean - sqrt((sqr(intensity - Mean) * DesiredVariance)/Variance);
			}

			m_processed[i][j].color(result);

			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	pdlg.DestroyWindow();

    return !canceled;

	
}

bool CImage::Thinning()
///////////////////////////////////////////////////////////////////////////
// Desc : The thinning algorithm implemented here is picked-up from the book
//        "Fundamentals Of Digital Image Processing"[P - 383] by prof. Anil
//        Kumar Jain.Although algorithm is known as - Zhang-Suen thinning 
//		  algorithm.
//
{
   // if binarization is yet to be done  --
   if (m_binaryimage == NULL) 
   {
      // thinning demands that image must be binarized first...
	  bool bResult=true;
	  int  iResponse=AfxMessageBox("Binarization is necessary before thinning.If you want adaptive binarization\nthen press Yes or If you want histogram-based binarization press No",MB_YESNOCANCEL|MB_ICONINFORMATION);

	  switch(iResponse)
	  {
	    case IDYES:
		    bResult = Binarize(true);		//adaptive 
		    break;
	    case IDNO:
		    bResult = Binarize();			//histogram-based
		    break;
	    case IDCANCEL:					    //no binarization
		    return false;
		    break;
	  }
	
	  //binarization is stopped,so thinning must be stopped.
	  if (bResult == false)
		  return false;
   }

	// allocate & initialize m_thinmap
	m_thinmap=CreateBinaryMatrix(m_height,m_width);
	CopyBinaryMatrix(m_thinmap,m_binaryimage);


	// Setup and Call Progress Dialog
    CProgressDlg pdlg("Thinning The Binarized Image...");
    pdlg.Create();
    UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
    UINT pixelsProcessed = 0;
	bool canceled = false;

    
	// The Zhang-Suen thinning algorithm  
	UINT i,j;
	BYTE nsum,tsum,tsumP2,tsumP4;
	bool changed = true;

  while(changed == true)
  {
	   
	   /*

	   Note: by inspecting each location such p1 we end up examining pixels from a 
	   5 by 5 neighborhood.so, i = [2, m_height-3] and j = [2, m_width-3]

   		  ___ ___ ___
		 |   |   |   |
		 |_p9|_p2|_p3|
		 |	 |   |   |
		 |_p8|_p1|_p4|
		 |	 |   |   |
		 |_p7|_p6|_p5|

		
		
		  if ((And248(m_thinmap,i,j) == 0)  || (tsumP2 != 2))
					  {
						 if ((And246(m_thinmap,i,j) == 0) || (tsumP4 != 2))

    
	   */
	changed = false;

	/*
			//first sub-iteration
			For all pixels J(i,j)
			
			  Delete K(i,j) if all of the following are true:
				a)	2 <= B(i,j) <= 6
				b)	A(i,j)=1
				c)	P2*P4*P6 = 0
				d)	P4*P6*P8 = 0

    */
	for (i = 2; i <= (m_height-3); i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 2; j <= (m_width-3); j++)
		{
		  //TODO: add extra pixel operations here...

		  nsum   = NeighborhoodSum(m_thinmap,i,j);
		  tsum   = TransitionSum(m_thinmap,i,j);
		  tsumP2 = TransitionSum(m_thinmap,i-1,j);
		  tsumP4 = TransitionSum(m_thinmap,i,j-1);

		  if (m_thinmap[i][j] == 0x01)	//is pixel is on ?
		  {
			  if ((nsum >= 2) && (nsum <= 6))
			  {
				  if (tsum == 2)
				  {
					  if (And246(m_thinmap,i,j) == 0) 
					  {
						 if (And468(m_thinmap,i,j) == 0)
						 {
						    //delete it :: white
							m_thinmap[i][j]=0x00;
							changed = true;
							
						 }
						 else
						 {
							// keep it :: black
							m_thinmap[i][j]=0x01;
							
						 }
					  }
					  else
					  {
						  // keep it :: black
						  m_thinmap[i][j]=0x01;
						 
					  }
				  }
				  else
				  {
					  // keep it :: black
					  m_thinmap[i][j]=0x01;
					  
				  }

			  }

		  }


			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();

		}

	}

	/*
		
		//second sub-iteration
		for all pixels J(i,j)
			
			  Delete K(i,j) if all of the following are true:
				a)	2 <= B(i,j) <= 6
				b)	A(i,j)=1
				c)	P2*P4*P8 = 0
				d)	P2*P6*P8 = 0
		end
   */
	for (i = 2; i <= (m_height-3); i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 2; j <= (m_width-3); j++)
		{
		  //TODO: add extra pixel operations here...

		  nsum   = NeighborhoodSum(m_thinmap,i,j);
		  tsum   = TransitionSum(m_thinmap,i,j);
		  tsumP2 = TransitionSum(m_thinmap,i-1,j);
		  tsumP4 = TransitionSum(m_thinmap,i,j-1);

		  if (m_thinmap[i][j] == 0x01)	//is pixel is on ?
		  {
			  if ((nsum >= 2) && (nsum <= 6))
			  {
				  if (tsum == 2)
				  {
					  if (And248(m_thinmap,i,j) == 0) 
					  {
						 if (And268(m_thinmap,i,j) == 0)
						 {
						    //delete it :: white
							m_thinmap[i][j]=0x00;
							changed = true;
							
						 }
						 else
						 {
							// keep it :: black
							m_thinmap[i][j]=0x01;
							
						 }
					  }
					  else
					  {
						  // keep it :: black
						  m_thinmap[i][j]=0x01;
						 
					  }
				  }
				  else
				  {
					  // keep it :: black
					  m_thinmap[i][j]=0x01;
					  
				  }

			  }

		  }


			pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();

		}

	}


	// loop through until no further changes occur in the image
  }


  pdlg.DestroyWindow();

  if (canceled == true)
	   return false;

  // actually plot the pixels of m_thinmap :: draw from binary image
  return DrawBinaryImageAfterThinning(m_thinmap,2,m_height-3,2,m_width-3);

  
}


/* Use a structural operator to dilate the image 
**    1
**  1 1 1
**    1

Morphological filtering is applied to eliminate artifacts in noisy regions and to fill 
some gaps in valid ridgelines. 
*/

bool CImage::MorphologyDilate()
{


	// Setup and Call Progress Dialog
	CProgressDlg pdlg("Applying Morphological Operators...");
	pdlg.Create();
	UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
	UINT pixelsProcessed = 0;
	bool canceled = false;

	// Dilate algorithm

	UINT  i, j;
    pixel pix;

    for (i = 2; i < m_height-2; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 2; j < m_width-2; j++)
		{
			//TODO: add extra pixel operations here

			if (m_thinmap[i][j] == 0xFF)
			{
               m_thinmap[i - 1][j] |= 0x80;
               m_thinmap[i + 1][j] |= 0x80;
               m_thinmap[i][j - 1] |= 0x80;
               m_thinmap[i][j + 1] |= 0x80;
			}


            //Advance progressbar
            pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}

	pdlg.SetPos(0);
	pdlg.SetDialogCaption("Finishing Up Morphological Operation...");

	for (i = 0; i < m_height; i++)
	{
		if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}

		for (j = 0; j < m_width; j++)
		{
			//TODO: add extra pixel operations here

			if (m_thinmap[i][j])
				m_thinmap[i][j] = 0xFF;

            //Advance progressbar
            pixelsProcessed++;			
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();
		}
	}
    
	
	pdlg.DestroyWindow();

	if (canceled == true)
		return false;

	// actually plot the pixels of m_thinmap :: draw from binary image
    return DrawBinaryImageAfterThinning(m_thinmap,2,m_height-3,2,m_width-3);

  


}

bool CImage::ExtractMinutiae()
{


	//Thinning is necessary for this step
	if (m_thinmap == NULL)
	{
	  // minutiae extraction demands that image must be thinned first...
	  bool bResult=true;
	  int  iResponse=AfxMessageBox("Thinning is necessary before minutiae extraction.Do you want to continue?",MB_YESNO|MB_ICONINFORMATION);

	  switch(iResponse)
	  {
	    case IDYES:
		    bResult = Thinning();		//Thinning
		    break;
	    case IDNO:
		   	return false;			    //no thinning
		    break;
	  }
	
	  //thinning is stopped so minutiae extraction must be stopped.
	  if (bResult == false)
		  return false;
	}

	//make m_processed a copy of original m_img to draw on
	CopyImageMatrix(m_processed,m_img);

	//Save the thinned image
	/*if (m_thinnedimage != NULL)
	{
		FreeImageMatrix(m_thinnedimage, m_height);
	}*/
	m_thinnedimage = CreateImageMatrix(m_height, m_width);
	CopyImageMatrix(m_thinnedimage, m_img);

	//set list sizes
	m_endlist.SetSize(200);
	m_branchlist.SetSize(200);

	// Setup and Call Progress Dialog
    /*CProgressDlg pdlg("Extracting Minutiae Lists...");
    pdlg.Create();*/
    UINT pixels = (unsigned int)(m_height * m_width * 0.01); // 1% of total pixels
    UINT pixelsProcessed = 0;
	bool canceled = false;

	UINT i,j,k;

	int m = 0,n = 0;

	CEndPoint* EP;
	//END_LIST endlist;
	
	CBifurcationPoint* BP;
    //BRANCH_LIST branchlist;
	
	for(i = 3; i <= (m_height-4); i++)
	{
	 /* if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}*/
	  for(j = 3; j <= (m_width-4); j++)
	  {
		  //TODO: Add extra pixel operations here

		  if (m_thinmap[i][j] == 0x01)
		  {
			  if (IsEnd(m_thinmap,i,j))
			  {
				  EP = new CEndPoint();	//On the heap
				  EP->pt = CPoint(i,j);

				  //theta(s) are yet to be calculated.below is a virtual statement
				  //BP.theta = Orientation[i][j]; - like this

				  try
				  {
					DrawCircleOnTop(
					  m_processed,
					  CPoint(i,j),
					  5,
					  RGB(255,0,0));

					m_endlist.SetAtGrow(m++, EP);
				  }
				  catch(CException* e)
				  {
					  AfxMessageBox("Error while drawing minutiae circles !!!");
					  
					  //continue;
				  }
			  }
			  
			  if (IsBifurcation(m_thinmap,i,j))
			  {
				  // Yes, a bifurcation point
				  BP = new CBifurcationPoint(); //On the heap
				  BP->pt = CPoint(i,j);
 
				  //theta(s) are yet to be calculated.below is virtual statement
				  //BP.theta = Orientation[i][j]; - like this

				  try
				  {
					DrawCircleOnTop(
					  m_processed,
					  CPoint(i,j),
					  5,
					  RGB(0,255,0));

					m_branchlist.SetAtGrow(n++, BP);
				  }
				  catch(CException* e)
				  {

					  AfxMessageBox("Error while drawing minutiae circles !!!");
					  
					  continue;
				  }
			  }
			  
		  }
				  

		  /*pixelsProcessed++;
			if (pixelsProcessed % pixels == 0)
				pdlg.StepIt();*/
	  }
	}

	m_numend = m;
	m_numbranch = n;

	

  //pdlg.DestroyWindow();

  return !canceled;

}




bool CImage::FilterMinutiae()
{
	//ME = Minutiae Extraction
	//
	// ME is necessary for this step
	if ((m_branchlist.GetUpperBound() != -1) &&
		(m_endlist.GetUpperBound() != -1))
	{
	  // minutiae extraction demands that image must be thinned first...
	  bool bResult=true;
	  int  iResponse=AfxMessageBox("Minutiae Extraction is necessary before this post-processing step.Do you want to continue?",MB_YESNO|MB_ICONINFORMATION);

	  switch(iResponse)
	  {
	    case IDYES:
		    bResult = ExtractMinutiae();		//Thinning
		    break;
	    case IDNO:
		   	return false;			    //no thinning
		    break;
	  }
	
	  //ME is stopped so filtering must be stopped.
	  if (bResult == false)
		  return false;
	}

	//make m_processed a copy of original thinned image to draw on
	CopyImageMatrix(m_processed,m_thinnedimage);

	//Release previous lists...
	if (m_endlist.GetUpperBound() != -1)
	{
		for(int i = 0; i < m_endlist.GetSize(); i++)
		{
			free(m_endlist.GetAt(i));
		}
		m_endlist.RemoveAll();
	}

	if ((m_branchlist.GetUpperBound()) != -1)
	{
		for(int i = 0; i < m_branchlist.GetSize(); i++)
		{
			free(m_branchlist.GetAt(i));
		}
		m_branchlist.RemoveAll();

	}

	//Filter minutiae
	BranchTrack();

	int m = 0, n = 0;
	CEndPoint* EP;
	CBifurcationPoint* BP;
	for(int i = 3; i <= (m_height-4); i++)
	{
	 /* if (pdlg.CheckCancelButton())
			if(AfxMessageBox("Are you sure you want to Cancel?", MB_YESNO)==IDYES)
			{
				canceled = true;
				break;
			}*/
	  for(int j = 3; j <= (m_width-4); j++)
	  {
		  //TODO: Add extra pixel operations here

		  if (m_thinmap[i][j] == 0x01)
		  {
			  if (IsEnd(m_thinmap,i,j))
			  {
				  //Is its a bad endpoint? If yes, skip
				  if (IndexOf(m_badendlist, i, j) != -1)
				  {
					  EP = new CEndPoint();
					  EP->pt = CPoint(i, j);

					  try
					  {
						DrawCircleOnTop(
						  m_processed,
						  CPoint(i,j),
						  5,
						  RGB(255,0,0));

						 m_endlist.SetAtGrow(m++, EP);
					  }
					  catch(CException* e)
					  {
						  AfxMessageBox("Error while drawing minutiae circles !!!");
						  
						  //continue;
					  }
				  }
			  }

			  if (IsBifurcation(m_thinmap,i,j))
			  {
				  // Yes, a bifurcation point
				  BP = new CBifurcationPoint(); //On the heap
				  BP->pt = CPoint(i,j);
 
				  //theta(s) are yet to be calculated.below is virtual statement
				  //BP.theta = Orientation[i][j]; - like this

				  try
				  {
					DrawCircleOnTop(
					  m_processed,
					  CPoint(i,j),
					  5,
					  RGB(0,255,0));

					m_branchlist.SetAtGrow(n++, BP);
				  }
				  catch(CException* e)
				  {

					  AfxMessageBox("Error while drawing minutiae circles !!!");
					  
					  continue;
				  }
			  }


		  }
	  }
	}

}

float CImage::EuclidianDistance(CPoint P1, CPoint P2)
{

	return (float)sqrt((double)(sqr(P1.x - P2.x) + sqr(P1.y - P2.y)));

}

bool CImage::LocateCore()
{
	//make m_processed a copy of original m_img to draw on
	CopyImageMatrix(m_processed,m_original);

    /* 
      roughly CORE is the EndPoint located nearest to the physical centre of the fingerprint
	  image.Mark it by BLUE color.
    */

	CPoint centre = CPoint(m_height/2,m_width/2);
	CPoint core;
	CPoint current;
	float distance;
	float closest = 999999.0;

	for(int i = 0; i < m_numend ; i++)
	{
	   current  = m_endlist[i]->pt;
       distance = EuclidianDistance(centre,current);
	   if (distance < closest)
	   {
		   closest = distance;
		   core    = current;
	   }
	}

    if (closest < 999999.0)
	{
		DrawCircleOnTop(m_processed,core,25,RGB(0,0,255));
		return true;
	}
	else
	{
		AfxMessageBox("FATAL ERROR  : EndList Possibly Empty");
		return false;
	}


}
/********************************************************************
************************* Histogram related functions ***************
*********************************************************************/
long* CImage::Histogram(imagematrix img,BOOL bSmooth,int W)
{
	
    int  i, j,b;
	BYTE  val;
	long  count;
    long* h=(long*)new long[256];
	

    for(b = 0; b < 256; b++)
	{
	  count=0;
	  for (i = 0; i < (int)m_height; i++)
	   {
		for (j = 0; j < (int)m_width; j++)
		{
		     val = img[i][j].intensity();
		       if (val==b)
			      count++;
		}

	   }

      h[b]=count;

	}
    
	return h;

	
}



