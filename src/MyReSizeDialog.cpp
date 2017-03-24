#include "../include/MyReSizeDialog.h"

MyReSizeDialog::MyReSizeDialog(int width, int height, wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxDialog( parent, id, title, pos, size, style){
    SetClientSize(wxSize(200,150));

    wxTextValidator validator(wxFILTER_INCLUDE_CHAR_LIST);

    wxArrayString list;
    wxString valChar(wxT("0123456789"));
    size_t sizeValChar = valChar.Length();
    for (size_t i = 0 ; i < sizeValChar ; i++){
        list.Add(wxString(valChar.GetChar(i)));
    }
    validator.SetIncludes(list);

    wxStaticText* textWidth = new wxStaticText(this, wxID_ANY, "Width (px)", wxPoint(16, 30), wxSize(80,20));
    wxStaticText* textHeight = new wxStaticText(this, wxID_ANY, "Height (px)", wxPoint(104, 30), wxSize(80,20));

    m_widthSize = new wxTextCtrl(this, wxID_ANY, wxString::Format(wxT("%i"), width), wxPoint(16, 50), wxSize(80,20), wxTE_PROCESS_ENTER, validator, _("Width"));
    m_heightSize = new wxTextCtrl(this, wxID_ANY, wxString::Format(wxT("%i"), height), wxPoint(104, 50), wxSize(80,20), wxTE_PROCESS_ENTER, validator, _("Height"));

    m_okButton = new wxButton(this, wxID_OK, "OK", wxPoint(16,110), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_OK"));
    m_cancelButton = new wxButton(this, wxID_CANCEL, "Cancel", wxPoint(104,110), wxDefaultSize, 0, wxDefaultValidator, _T("wxID_CANCEL"));

    (void) textWidth;
    (void) textHeight;
}

MyReSizeDialog::~MyReSizeDialog(){
}
