#ifndef MYFRAME_H
#define MYFRAME_H

#include "MyPanel.h"

class MyFrame: public wxFrame{
public:
	MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size);
private:
    MyPanel *m_panel; // the panel inside the main frame

	void OnHello(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnResize(wxCommandEvent& event);

	void OnExit(wxCommandEvent& event);

	void OnEnCours(wxCommandEvent& event);

	void OnOpenImage(wxCommandEvent& event);
	void OnSaveImage(wxCommandEvent& event);

<<<<<<< HEAD
	void OnProcessImage(wxCommandEvent& event);	//void OnMouse(wxEVT_MOTION& event);
=======
	void OnProcessImage(wxCommandEvent& event);

	void OnBack();

	//void OnMouse(wxEVT_MOTION& event);
>>>>>>> 3a34d1b92319a5b067e0bf813e9f6cf6155508a4
};

#endif // MYFRAME_H
