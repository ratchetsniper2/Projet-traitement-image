#ifndef MYTHRESHOLDDIALOG_H
#define MYTHRESHOLDDIALOG_H

#include <wx/wx.h>

class MyThresholdDialog : public wxDialog{
    public:
        MyThresholdDialog(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyThresholdDialog();

        wxSlider* m_threshold;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYTHRESHOLDDIALOG_H
