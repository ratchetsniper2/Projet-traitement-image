#include "MyThresholdDialog.h"

MyThresholdDialog::MyThresholdDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style ){
	SetClientSize(wxSize(200,110));

	m_threshold = new wxSlider( this, wxID_ANY, 128, 0, 255, wxPoint(25,10), wxSize(150,50), wxSL_HORIZONTAL|wxSL_LABELS );
	m_okButton = new wxButton( this, wxID_OK, wxT("OK"), wxPoint(16,70), wxDefaultSize, 0 );
	m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,70), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}

MyThresholdDialog::~MyThresholdDialog(){
}
