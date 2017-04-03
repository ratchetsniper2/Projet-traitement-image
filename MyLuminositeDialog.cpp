#include "MyLuminositeDialog.h"



void MyLuminositeDialog::OnScrollLuminosite( wxScrollEvent& event )
{
    wxCommandEvent outEvent(EVENEMENT_LUMINOSITE) ;	// création d'un événement propre
    outEvent.SetInt(m_luminosite->GetValue()) ;	// stockage de la valeur du seuil dans l'événement
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}


MyLuminositeDialog::MyLuminositeDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style ){
	SetClientSize(wxSize(200,110));

    m_luminosite = new wxSlider( this, wxID_ANY, 200, 100, 300, wxPoint(25,10), wxSize(150,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_luminosite->Bind( wxEVT_SCROLL_THUMBTRACK, &MyLuminositeDialog::OnScrollLuminosite, this );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(16,70), wxDefaultSize, 0 );
	m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}
MyLuminositeDialog::~MyLuminositeDialog(){
    m_luminosite->Unbind( wxEVT_SCROLL_THUMBTRACK, &MyLuminositeDialog::OnScrollLuminosite, this );

}
