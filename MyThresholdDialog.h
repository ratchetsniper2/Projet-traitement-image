#ifndef MYTHRESHOLDDIALOG_H
#define MYTHRESHOLDDIALOG_H

#include <wx/wx.h>
wxDECLARE_EVENT(MON_EVENEMENT, wxCommandEvent);

class MyThresholdDialog : public wxDialog{
    public:
        MyThresholdDialog(bool v2, wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyThresholdDialog();
        void OnScroll( wxScrollEvent& event );
        wxSlider* m_threshold;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYTHRESHOLDDIALOG_H
