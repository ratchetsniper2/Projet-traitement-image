#include "../include/MyThresholdDialog.h"



void MyThresholdDialog::OnScroll( wxScrollEvent& event )
{
    wxCommandEvent outEvent(MON_EVENEMENT) ;	// création d'un événement propre
    outEvent.SetInt(m_threshold->GetValue()) ;	// stockage de la valeur du seuil dans l'événement
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}
void MyThresholdDialog::OnScrollLuminosite( wxScrollEvent& event )
{
    wxCommandEvent outEvent(EVENEMENT_LUMINOSITE) ;	// création d'un événement propre
    outEvent.SetInt(m_luminosite->GetValue()) ;	// stockage de la valeur du seuil dans l'événement
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}

MyThresholdDialog::MyThresholdDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style ){
	SetClientSize(wxSize(200,110));


	m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(25,10), wxSize(150,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_threshold->Bind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScroll, this );

	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(16,70), wxDefaultSize, 0 );
	m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}

MyThresholdDialog::~MyThresholdDialog(){
    m_threshold->Unbind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScroll, this );
    m_luminosite->Unbind( wxEVT_SCROLL_THUMBTRACK, &MyThresholdDialog::OnScrollLuminosite, this );

}

