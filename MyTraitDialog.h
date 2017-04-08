#ifndef MYTRAITDIALOG_H
#define MYTRAITDIALOG_H

#include <wx/wx.h>
wxDECLARE_EVENT(EVENEMENT_TRAIT, wxCommandEvent);

class MyTraitDialog : public wxDialog{
    public:
        MyTraitDialog(int traitActuel, wxWindow* parent, wxWindowID id = wxID_ANY,
            const wxString& title = wxEmptyString, const wxPoint& pos = wxDefaultPosition,
            const wxSize& size = wxDefaultSize, long style = wxDEFAULT_DIALOG_STYLE);
        virtual ~MyTraitDialog();
        void OnScrollTrait( wxScrollEvent& event );
        wxSlider* m_trait;

    protected:

    private:
        wxButton* m_okButton;
        wxButton* m_cancelButton;
};

#endif // MYLUMINOSITEDIALOG_H
