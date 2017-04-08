#include "MyTraitDialog.h"

void MyTraitDialog::OnScrollTrait( wxScrollEvent& event )
{
    wxCommandEvent outEvent(EVENEMENT_TRAIT) ;	// création d'un événement propre
    outEvent.SetInt(m_trait->GetValue()) ;	// stockage de la valeur du seuil dans l'événement
    wxPostEvent(GetParent(), outEvent);		// poste le message au wxPanel
}


MyTraitDialog::MyTraitDialog(int traitActuel, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style ){
	SetClientSize(wxSize(200,110));

    m_trait = new wxSlider( this, wxID_ANY, traitActuel, 1, 20, wxPoint(25,10), wxSize(150,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_trait->Bind( wxEVT_SCROLL_THUMBTRACK, &MyTraitDialog::OnScrollTrait, this );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(16,70), wxDefaultSize, 0 );
	m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}
MyTraitDialog::~MyTraitDialog(){
    m_trait->Unbind( wxEVT_SCROLL_THUMBTRACK, &MyTraitDialog::OnScrollTrait, this );

}
