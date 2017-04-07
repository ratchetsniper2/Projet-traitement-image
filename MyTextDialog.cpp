#include "MyTextDialog.h"



MyTextDialog::MyTextDialog(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style){
    SetClientSize(wxSize(200,150));

    m_TextCtrl = new wxTextCtrl(this, -1, wxT("Text"),
      wxPoint(50, 50));

    m_okButton = new wxButton(this, wxID_OK, _("OK"), wxPoint(16,110), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    m_cancelButton = new wxButton(this, wxID_CANCEL, _("Cancel"), wxPoint(104,110), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));
}

MyTextDialog::~MyTextDialog(){
}
