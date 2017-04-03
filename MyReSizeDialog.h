#ifndef MYRESIZEDIALOG_H
#define MYRESIZEDIALOG_H

#include <wx/wx.h>

class MyReSizeDialog : public wxDialog{
    public:
        MyReSizeDialog(int width, int height, wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyReSizeDialog();

        wxTextCtrl* m_widthSize;
        wxTextCtrl* m_heightSize;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYRESIZEDIALOG_H
