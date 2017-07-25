/********************************************************
*                                                       *
*   Copyright (C) Microsoft. All rights reserved.       *
*                                                       *
********************************************************/

#include "precomp.h"

#include "vtrenderer.hpp"

#include <sstream>

#pragma hdrstop

using namespace Microsoft::Console::Render;

// Routine Description:
// - Creates a new GDI-based rendering engine
// - NOTE: Will throw if initialization failure. Caller must catch.
// Arguments:
// - <none>
// Return Value:
// - An instance of a Renderer.
VtEngine::VtEngine() 
{
    _hFile.reset(CreateFileW(L"\\\\.\\pipe\\convtpipe", GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr));
    THROW_IF_HANDLE_INVALID(_hFile.get());
}

// Routine Description:
// - Destroys an instance of a GDI-based rendering engine
// Arguments:
// - <none>
// Return Value:
// - <none>
VtEngine::~VtEngine()
{
}

HRESULT VtEngine::_Write(_In_ std::string& str)
{
    RETURN_LAST_ERROR_IF_FALSE(WriteFile(_hFile.get(), str.c_str(), (DWORD)str.length(), nullptr, nullptr));
    return S_OK;
}

// Routine Description:
// - This method will set the GDI brushes in the drawing context (and update the hung-window background color)
// Arguments:
// - wTextAttributes - A console attributes bit field specifying the brush colors we should use.
// Return Value:
// - S_OK if set successfully or relevant GDI error via HRESULT.
HRESULT VtEngine::UpdateDrawingBrushes(_In_ COLORREF const colorForeground, _In_ COLORREF const colorBackground, _In_ WORD const legacyColorAttribute, _In_ bool const fIncludeBackgrounds)
{
    try
    {
        std::stringstream ss;

        ss << "\x1b[38;2;" << (colorForeground & 0xff) << ";" << ((colorForeground >> 8) & 0xff) << ";" << ((colorForeground >> 16) & 0xff) << "m";
        ss << "\x1b[48;2;" << (colorBackground & 0xff) << ";" << ((colorBackground >> 8) & 0xff) << ";" << ((colorBackground >> 16) & 0xff) << "m";

        std::string s = ss.str();

        _Write(s);
    }
    CATCH_RETURN();

    colorForeground;
    colorBackground;
    legacyColorAttribute;
    fIncludeBackgrounds;
    
    return S_OK;
}

// Routine Description:
// - This method will update the active font on the current device context
// - NOTE: It is left up to the underling rendering system to choose the nearest font. Please ask for the font dimensions if they are required using the interface. Do not use the size you requested with this structure.
// Arguments:
// - pfiFontDesired - Pointer to font information we should use while instantiating a font.
// - pfiFont - Pointer to font information where the chosen font information will be populated.
// Return Value:
// - S_OK if set successfully or relevant GDI error via HRESULT.
HRESULT VtEngine::UpdateFont(_In_ FontInfoDesired const * const pfiFontDesired, _Out_ FontInfo* const pfiFont)
{
    pfiFontDesired;
    pfiFont;
    return S_OK;
}

// Routine Description:
// - This method will modify the DPI we're using for scaling calculations.
// Arguments:
// - iDpi - The Dots Per Inch to use for scaling. We will use this relative to the system default DPI defined in Windows headers as a constant.
// Return Value:
// - HRESULT S_OK, GDI-based error code, or safemath error
HRESULT VtEngine::UpdateDpi(_In_ int const iDpi)
{
    iDpi;
    return S_OK;
}

// Routine Description:
// - This method will figure out what the new font should be given the starting font information and a DPI.
// - When the final font is determined, the FontInfo structure given will be updated with the actual resulting font chosen as the nearest match.
// - NOTE: It is left up to the underling rendering system to choose the nearest font. Please ask for the font dimensions if they are required using the interface. Do not use the size you requested with this structure.
// - If the intent is to immediately turn around and use this font, pass the optional handle parameter and use it immediately.
// Arguments:
// - pfiFontDesired - Pointer to font information we should use while instantiating a font.
// - pfiFont - Pointer to font information where the chosen font information will be populated.
// - iDpi - The DPI we will have when rendering
// Return Value:
// - S_OK if set successfully or relevant GDI error via HRESULT.
HRESULT VtEngine::GetProposedFont(_In_ FontInfoDesired const * const pfiFontDesired, _Out_ FontInfo* const pfiFont, _In_ int const iDpi)
{
    pfiFontDesired;
    pfiFont;
    iDpi;
    return S_OK;
}

// Routine Description:
// - Retrieves the current pixel size of the font we have selected for drawing.
// Arguments:
// - <none>
// Return Value:
// - X by Y size of the font.
COORD VtEngine::GetFontSize()
{
    return{ 1, 1 };
}
