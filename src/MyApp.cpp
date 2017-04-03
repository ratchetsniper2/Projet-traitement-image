#include "../include/MyApp.h"

bool MyApp::OnInit(){
    wxInitAllImageHandlers();
	MyFrame *frame = new MyFrame( wxT("Traitement d'images"), wxPoint(50, 50), wxSize(450, 340) );
	frame->CenterOnScreen();
	frame->Show(true);
	return true;
}
