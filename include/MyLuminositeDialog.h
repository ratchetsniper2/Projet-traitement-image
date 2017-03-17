#ifndef MYLUMINOSITEDIALOG_H
#define MYLUMINOSITEDIALOG_H

#include <wx/wx.h>
wxDECLARE_EVENT(EVENEMENT_LUMINOSITE, wxCommandEvent);

class MyLuminositeDialog : public wxDialog{
    public:
        MyLuminositeDialog(wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyLuminositeDialog();
        void OnScrollLuminosite( wxScrollEvent& event );
        wxSlider* m_luminosite;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYLUMINOSITEDIALOG_H
