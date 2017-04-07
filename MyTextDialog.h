#ifndef MYTEXTDIALOG_H
#define MYTEXTDIALOG_H

#include <wx/wx.h>

class MyTextDialog : public wxDialog{
    public:
        MyTextDialog(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyTextDialog();

        wxTextCtrl *m_TextCtrl;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYRTEXTDIALOG_H
