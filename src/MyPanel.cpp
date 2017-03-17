#include "../include/MyPanel.h"


wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);
wxDEFINE_EVENT(EVENEMENT_LUMINOSITE, wxCommandEvent);

MyPanel::MyPanel(wxWindow *parent) : wxPanel(parent), m_image(NULL), histogram(NULL){
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this) ;
    Bind(EVENEMENT_LUMINOSITE, &MyPanel::OnLuminosite, this) ;
}

MyPanel::~MyPanel(){}

void MyPanel::noImageOpen(){
    wxLogMessage(wxT("No image open  ..."));
}

void MyPanel::OpenImage(wxString fileName){
    if (m_image != NULL){
        delete(m_image);
        delete(histogram);
    }
    m_image = new MyImage(fileName);
    histogram = new MyHistogram(m_image);

    m_width = m_image->GetWidth();
    m_height = m_image->GetHeight();
    GetParent()->SetClientSize(m_width, m_height);
    Refresh();
}

void MyPanel::SaveImage(wxString fileName){
    if (m_image != NULL){
        m_image->SaveFile(fileName);
    }else{
        noImageOpen();
    }
}

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    if (m_image != NULL){
        m_bitmap = MyImage(*m_image);
        wxPaintDC dc(this);
        dc.DrawBitmap(m_bitmap, 0, 0);
        histogram = new MyHistogram(m_image);
    }
}

void MyPanel::MirrorImage(bool horizontal){
    if (m_image != NULL){
        *m_image = m_image->Mirror(horizontal);

        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::BlurImage(){
    if (m_image != NULL){
       *m_image = m_image->Blur(1);

        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::RotateImage(){
    if (m_image != NULL){

        MyRotateDialog *dlg = new MyRotateDialog(this, -1, wxT("Rotate"), wxDefaultPosition, wxSize(200,200));
        if (dlg->ShowModal() == wxID_OK){
            if (dlg->m_radioBox->GetSelection() == 0){
                *m_image = m_image->Rotate90();
            }else if (dlg->m_radioBox->GetSelection() == 1){
                *m_image = m_image->Rotate180();
            }else if (dlg->m_radioBox->GetSelection() == 2){
                *m_image = m_image->Rotate90(false);
            }

            // redimention ----
            m_width = m_image->GetWidth();
            m_height = m_image->GetHeight();
            GetParent()->SetClientSize(m_width, m_height);

            Refresh();
        }
    }else{
        noImageOpen();
    }
}

void MyPanel::Negative(){
    if (m_image != NULL){
        m_image->Negative();
        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::Desaturate(){
    if (m_image != NULL){
        m_image->Desaturate();
        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::Threshold(){
    if (m_image != NULL){
        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));
        if (dlg->ShowModal() == wxID_OK){
            m_image->Threshold(dlg->m_threshold->GetValue());
            //free(dlg);
            Refresh();
        }
    }else{
        noImageOpen();
    }
}

void MyPanel::Posterize(){
    if (m_image != NULL){
        m_image->Posterize(64);
        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::Nbcolor(){
    if (m_image != NULL){
        int nbColor = m_image->Nbcolor();
        wxLogMessage(wxString::Format(wxT("%i"),nbColor)+wxT(" colors"));
    }else{
        noImageOpen();
    }
}

void MyPanel::EnhenceContrast(){
    if (m_image != NULL){
        int minValue = m_image->GetWidth()*m_image->GetHeight();
        int maxValue = 0;
        histogram->getBorderValues(&minValue, &maxValue);

        m_image->EnhenceContrast(minValue, maxValue);
        Refresh();
    }else{
        noImageOpen();
    }
}


void MyPanel::ThresholdImage(){
    if (m_image != NULL){

        MyThresholdDialog *dlg = new MyThresholdDialog(this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));

        if (dlg->ShowModal() == wxID_OK){

        }
        else{
            //annuler la transformation
        }
    }else{
        noImageOpen();

    }
}

void MyPanel::OnThresholdImage(wxCommandEvent& event){

            //remmettre l'image d'origine avant de faire la transformation
            m_image->Threshold(event.GetSelection());
            Refresh();
}

void MyPanel::OnLuminosite(wxCommandEvent& event){

            //remmettre l'image d'origine avant de faire la transformation
            m_image->Luminosite(event.GetSelection());
            Refresh();
}

void MyPanel::Luminosite(){
if (m_image != NULL){

        MyLuminositeDialog *dlg = new MyLuminositeDialog(this, -1, wxT("Luminosité"), wxDefaultPosition, wxSize(250,140));

        if (dlg->ShowModal() == wxID_OK){

        }
        else{
            //annuler la transformation
        }
    }else{
        noImageOpen();

    }

}
