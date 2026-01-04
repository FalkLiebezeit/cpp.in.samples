// base.cpp
#include "wx/wx.h"
#include "base.h"

IMPLEMENT_APP(HalloWeltApp)

bool HalloWeltApp::OnInit() {
	BasicFrame *frame =
	new BasicFrame( wxT("Hallo Welt"), 50, 50, 200, 100);
	frame->Show(TRUE);
	SetTopWindow(frame);
	return TRUE;
}

BasicFrame::BasicFrame (const wxChar *title,int xpos, int ypos,int width, int height): wxFrame ((wxFrame *) NULL,-1, title,wxPoint(xpos, ypos),wxSize(width, height),wxDEFAULT_FRAME_STYLE) {
	// Ein neues Panel zum Frame hinzufügen
	panel = new wxPanel(this, wxID_ANY,
	wxDefaultPosition, wxSize(200, 100));
	// Einen Button in den Panel hinzufügen
	button = new wxButton(panel, wxID_OK, wxT("OK"),
	wxPoint(10, 10), wxDefaultSize);
}

BasicFrame::~BasicFrame() { }

BEGIN_EVENT_TABLE(BasicFrame, wxFrame)
EVT_BUTTON(wxID_OK, BasicFrame::OnClickButtonOK)
END_EVENT_TABLE()

void BasicFrame::OnClickButtonOK(wxCommandEvent &event ) {
	// Fenster schließen/beenden
	Close();
}
