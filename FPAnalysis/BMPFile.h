// BMPFile.h: interface for the BMPFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BMPFILE_H__CEF34417_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
#define AFX_BMPFILE_H__CEF34417_BAE3_11D6_AF70_C559F9C10445__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define BMP_HEADERSIZE (3 * 2 + 4 * 12)
#define BMP_BYTESPERLINE (width, bits) ((((width) * (bits) + 31) / 32) * 4)
#define BMP_PIXELSIZE(width, height, bits) (((((width) * (bits) + 31) / 32) * 4) * height)
#define WIDTHBYTES(bits)    (((bits) + 31) / 32 * 4)

class BMPFile  
{
public:
	// parameters
	CString m_errorText;
	DWORD m_bytesRead;

	// operations
	BMPFile();
    BYTE * LoadBMP(CString fileName, UINT *width, UINT *height,BITMAPINFOHEADER* bihdr);
	BYTE*  FindBits(BITMAPINFOHEADER* pbihdr);
    void SaveBMP(CString fileName,		// output path
							BYTE * buf,				// RGB buffer
							UINT width,				// size
							UINT height);
    void SaveBMP(CString fileName, 			// output path
							 BYTE * colormappedbuffer,	// one BYTE per pixel colomapped image
							 UINT width,
							 UINT height,
 							 int bitsperpixel,			// 1, 4, 8
							 int colors,				// number of colors (number of RGBQUADs)
							 RGBQUAD *colormap);			// array of RGBQUADs 

	virtual ~BMPFile();

};

#endif // !defined(AFX_BMPFILE_H__CEF34417_BAE3_11D6_AF70_C559F9C10445__INCLUDED_)
