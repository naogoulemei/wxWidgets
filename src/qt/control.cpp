/////////////////////////////////////////////////////////////////////////////
// Name:        src/qt/control.cpp
// Author:      Peter Most
// Copyright:   (c) Peter Most
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#include "wx/control.h"
#include "wx/qt/converter.h"

IMPLEMENT_DYNAMIC_CLASS( wxControl, wxControlBase )

wxControl::wxControl()
{
}

wxControl::wxControl(wxWindow *parent, wxWindowID id,
         const wxPoint& pos,
         const wxSize& size, long style,
         const wxValidator& validator,
         const wxString& name )
{
    Create( parent, id, pos, size, style, validator, name );
}


bool wxControl::Create(wxWindow *parent, wxWindowID id,
        const wxPoint& pos,
        const wxSize& size, long style,
        const wxValidator& validator,
        const wxString& name )
{
    bool isCreated = wxWindow::Create(parent, id, pos, size, style, name);

#if wxUSE_VALIDATORS
    SetValidator(validator);
#endif

    return isCreated;
}

bool wxControl::QtCreateControl( wxWindow *parent, wxWindowID id,
    const wxPoint &pos, const wxSize &size, long style,
    const wxValidator &validator, const wxString &name )
{
    // The Qt widget has been created without a position/size so move/resize it:

    wxSize bestSize = GetBestSize();
    int width = ( size.GetWidth() == wxDefaultCoord ) ? bestSize.GetWidth() : size.GetWidth();
    int height = ( size.GetHeight() == wxDefaultCoord ) ? bestSize.GetHeight() : size.GetHeight();

    DoMoveWindow( pos.x, pos.y, width, height );

    // Let Qt handle the background:
    SetBackgroundStyle(wxBG_STYLE_SYSTEM);
    PostCreation(false);

    return CreateControl( parent, id, pos, size, style, validator, name );
}

wxSize wxControl::DoGetBestSize() const
{
    wxSize minsize = wxQtConvertSize( GetHandle()->minimumSizeHint() );
    wxSize size = wxQtConvertSize( GetHandle()->sizeHint() );
    // best effort to ensure a correct size (note that some qt controls implement just one or both size hints)
    if (size.GetWidth() < minsize.GetWidth())
        size.SetWidth(minsize.GetWidth());
    if (size.GetHeight() < minsize.GetHeight())
        size.SetHeight(minsize.GetHeight());
    return size;
}