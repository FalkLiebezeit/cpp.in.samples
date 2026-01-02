// base.h
#ifndef BASIC_H
#define BASIC_H

class HalloWeltApp : public wxApp {
public:
	virtual bool OnInit();
};

class BasicFrame : public wxFrame {
private:
	wxPanel* panel;
	wxButton* button;
	// Ereignis-Tabelle einrichten
	DECLARE_EVENT_TABLE()
public:
	BasicFrame( const wxChar *title,
	int xpos, int ypos,
	int width, int height);
	~BasicFrame();
	// Methoden die auf das Ereignis reagiert
 	void OnClickButtonOK(wxCommandEvent &event);
};
#endif
