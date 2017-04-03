#ifndef MYROTATEDIALOG_H
#define MYROTATEDIALOG_H

#include <wx/wx.h>

class MyRotateDialog : public wxDialog{
    public:
        MyRotateDialog(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyRotateDialog();

        wxRadioBox* m_radioBox;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYROTATEDIALOG_H
