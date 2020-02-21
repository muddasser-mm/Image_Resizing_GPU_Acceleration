//------------------------------------------------------------------------------
// File : tga_helper.h
//------------------------------------------------------------------------------
// GLVU : Original work Copyright 1997 - 2002 
//			The University of North Carolina at Chapel Hill
//		  Modified work by Mohammed Muddasser 2020
//------------------------------------------------------------------------------
// Permission to use, copy, modify, distribute and sell this software and its 
// documentation for any purpose is hereby granted without fee, provided that 
// the above copyright notice appear in all copies and that both that copyright 
// notice and this permission notice appear in supporting documentation. 
// Binaries may be compiled with this software without any royalties or 
// restrictions. 
//
// The University of North Carolina at Chapel Hill makes no representations 
// about the suitability of this software for any purpose. It is provided 
// "as is" without express or implied warranty.

//============================================================================
// tga_helper.h : Targa image format module
//============================================================================

//============================================================================
// Includes
//============================================================================
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <memory.h>
#include <fstream>
#include <iostream>
#include <vector>

//============================================================================
// Declarations and Macro Defintions
//============================================================================

// Macro definitions for image types.
#define TGA_NULL				0							// Null
#define TGA_MAP					1							// For future extension to support color Map format
#define TGA_RGB					2							// Currently supported
#define TGA_MONO				3							// Currently supported
#define TGA_RLEMAP				9							// For future extension to support RLE
#define TGA_RLERGB				10							// For future extension to support RLE
#define TGA_RLEMONO				11							// For future extension to support RLE

#define TGA_IDLENGTH			(uint8_t)0
#define TGA_COLORMAPTYPE		(uint8_t)1
#define TGA_TYPE				(uint8_t)2
#define TGA_COLORMAPINDEX		(uint8_t)3
#define TGA_COLORMAPLENGTH		(uint8_t)5
#define TGA_COLORMAPSIZE		(uint8_t)7
#define TGA_XORIGIN				(uint8_t)8
#define TGA_YORIGIN				(uint8_t)10
#define TGA_WIDTH				(uint8_t)12
#define TGA_HEIGHT				(uint8_t)14
#define TGA_PIXELSIZE			(uint8_t)16
#define TGA_DESC				(uint8_t)17

#define TGA_HEADER_LENGTH		(uint8_t)18

// Macro definitions of masks for the desscriptor
#define TGA_DESC_ALPHA_MASK		((uint8_t)0xF)				// number of alpha channel bits
#define TGA_DESC_ORG_MASK		((uint8_t)0x30)				// origin mask

// Macro definitions for origin
#define TGA_ORG_BOTTOM_LEFT		0x00					
#define TGA_ORG_BOTTOM_RIGHT	0x10
#define TGA_ORG_TOP_LEFT		0x20
#define TGA_ORG_TOP_RIGHT		0x30

// Structures

// TGA header structure
typedef struct tgaHeader_
{
	uint8_t  imgIDLength;									// Image Identifier length.
	uint8_t  imgColorMapType;								// No map -> 0
	uint8_t  imgType;										// Image type (see MACROS defined below for values)
	uint16_t imgColorMapIndex;								// Index of first color map entry
	uint16_t imgColorMapLength;								// Number of entries in color map
	uint8_t  imgColorMapSize;								// Size of color map entry (15,16,24,32)
	uint16_t imgXOrigin;									// X origin of image
	uint16_t imgYOrigin;									// Y origin of image
	uint16_t imgWidth;										// width of image
	uint16_t imgHeight;										// height of image
	uint8_t  imgPixelSize;									// Pixel size (8,16,24,32)
	uint8_t  imgDesc;										// Bits 3-0 give the alpha channel depth, bits 5-4 give direction
} tgaHeader;

// TGA Image as structure
struct TGA {

	// By default all kept public
	// Member Variables
	tgaHeader				mHeader;
	uint32_t				mPixelDataLen;
	std::vector<uint8_t>	mID;
	std::vector<uint8_t>	mColorMapSpec;
	std::vector<uint8_t>	mPixelData;

	// Default Constructor
	TGA() {
		mHeader = {0};
		mPixelDataLen = 0;
	}

	// Parameterised Constructor
    TGA(const char *imgName) {
        read(imgName);
	}

	// Member functions
	void read(const char *imgName);
	bool write(const char *imgName);
};