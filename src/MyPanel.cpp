#include "../include/MyPanel.h"


wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent);
wxDEFINE_EVENT(EVENEMENT_LUMINOSITE, wxCommandEvent);

MyPanel::MyPanel(wxFrame *parent) : wxScrolledCanvas(parent), m_image(NULL), histogram(NULL), parent(parent){
    imageScale = 1.0;
    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this);
    Bind(EVENEMENT_LUMINOSITE, &MyPanel::OnLuminosite, this);

    Bind(wxEVT_MOUSEWHEEL, &MyPanel::OnMouseWheel, this);

}

MyPanel::~MyPanel(){}

void MyPanel::noImageOpen(){
    wxLogMessage(wxT("No image open  ..."));
}

void MyPanel::OpenImage(wxString fileName){
    if (m_image != NULL){
        delete(m_image);
        delete(histogram);
        imageScale = 1.0;
    }
    m_image = new MyImage(fileName);
    SaveImageBeforeTraitment();
    histogram = new MyHistogram(m_image);

    m_width = m_image->GetWidth();
    m_height = m_image->GetHeight();
    SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale);
    GetParent()->SetClientSize(m_width, m_height);
    Refresh();
}

void MyPanel::SaveImage(){
    if (m_image != NULL){
        wxString filename = wxSaveFileSelector("Save", "", "");
        if (!filename.empty()){
            m_image->SaveFile(filename);
        }
    }else{
        noImageOpen();
    }
}

void MyPanel::OnPaint(wxPaintEvent &WXUNUSED(event)){
    if (m_image != NULL){
        m_bitmap = MyImage(*m_image);
        wxPaintDC dc(this);

        DoPrepareDC(dc); // pour l'image soit actualisée quand on bouge les scroll

        dc.SetUserScale(imageScale, imageScale); // pour le zoom

        dc.DrawBitmap(m_bitmap, 0, 0);
        histogram = new MyHistogram(m_image);
    }
}

void MyPanel::MirrorImage(bool horizontal){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        *m_image = m_image->Mirror(horizontal);

        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::BlurImage(){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
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
            SaveImageBeforeTraitment();
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
            SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale);
            GetParent()->SetClientSize(m_width, m_height);

            Refresh();
        }
    }else{
        noImageOpen();
    }
}

void MyPanel::Negative(){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        m_image->Negative();
        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::Desaturate(){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        m_image->Desaturate();
        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::Threshold(){
    if (m_image != NULL){
        MyThresholdDialog *dlg = new MyThresholdDialog(false, this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));
        if (dlg->ShowModal() == wxID_OK){
            SaveImageBeforeTraitment();
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
        SaveImageBeforeTraitment();
        m_image->Posterize(8);
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

        SaveImageBeforeTraitment();
        m_image->EnhenceContrast(minValue, maxValue);
        Refresh();
    }else{
        noImageOpen();
    }
}


void MyPanel::ThresholdImage(){
    if (m_image != NULL){

        SaveImageBeforeTraitment();
        MyThresholdDialog *dlg = new MyThresholdDialog(true, this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));

        if (dlg->ShowModal() == wxID_OK){

        }
        else{
            BackTraitment();
            //annuler la transformation
        }
    }else{
        noImageOpen();

    }
}

void MyPanel::OnThresholdImage(wxCommandEvent& event){

            BackTraitment();
            SaveImageBeforeTraitment();

            //remmettre l'image d'origine avant de faire la transformation
            m_image->Threshold(event.GetSelection());
            Refresh();
}

void MyPanel::OnLuminosite(wxCommandEvent& event){

            BackTraitment();
            SaveImageBeforeTraitment();

            m_image->Luminosite(event.GetSelection());
            Refresh();
}

void MyPanel::Luminosite(){
if (m_image != NULL){

        SaveImageBeforeTraitment();
        MyLuminositeDialog *dlg = new MyLuminositeDialog(this, -1, wxT("Luminosité"), wxDefaultPosition, wxSize(250,140));

        if (dlg->ShowModal() == wxID_OK){

        }
        else{
            BackTraitment();
            //annuler la transformation
        }
    }else{
        noImageOpen();

    }
}

void MyPanel::SaveImageBeforeTraitment(){
    m_imageCopie = m_image->Copy();
}

void MyPanel::BackTraitment(){
    if (m_image != NULL){
        MyImage temp = m_image->Copy();
        *m_image = m_imageCopie;
        m_imageCopie = temp;

        // redimention ---- pour refaire une rotation inverse
        if (m_width != m_image->GetWidth() || m_height != m_image->GetHeight()){
            m_width = m_image->GetWidth();
            m_height = m_image->GetHeight();
            SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale);
            GetParent()->SetClientSize(m_width, m_height);
        }

        Refresh();
    }else{
        noImageOpen();
    }
}

void MyPanel::ReSize(){
    if (m_image != NULL){

        MyReSizeDialog *dlg = new MyReSizeDialog(m_image->GetWidth() ,m_image->GetHeight() , this, -1, wxT("ReSize"), wxDefaultPosition, wxSize(200,200));
        if (dlg->ShowModal() == wxID_OK){
            SaveImageBeforeTraitment();
            int xSize = wxAtoi(dlg->m_widthSize->GetValue());
            int ySize = wxAtoi(dlg->m_heightSize->GetValue());

            m_image->Rescale(xSize, ySize);

            // redimention ----
            m_width = xSize;
            m_height = ySize;
            SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale);
            GetParent()->SetClientSize(m_width, m_height);

            Refresh();
        }
    }else{
        noImageOpen();
    }
}

// pour le zoom (ctrl + molette)
void MyPanel::OnMouseWheel(wxMouseEvent& event){
    if (m_image != NULL && event.ControlDown()){
        double incrScale = 0.05;

        // changement du zoom
        if (event.GetWheelRotation() > 0){
            // zoom in
            imageScale += incrScale;
        }else{
            imageScale -= incrScale;
            if (imageScale < 0){
                imageScale = 0;
            }
        }

        // calcul du delta (déplacement de l'image par rapport à l'encienne position) par rapport à la position de la souris
        // permet de zoomer à la position de la souris
        wxPoint point = ScreenToClient(wxGetMousePosition());

        int deltaPosXScroll = 0;
        double clientXSize = GetParent()->GetClientSize().GetWidth();
        if (clientXSize < m_width*imageScale){
            deltaPosXScroll = (incrScale*m_width/2)*(((double) point.x)/(clientXSize/2));
        }

        int deltaPosYScroll = 0;
        double clientYSize = GetParent()->GetClientSize().GetHeight();
        if (clientYSize < m_height*imageScale){
            deltaPosYScroll = (incrScale*m_height/2)*(((double) point.y)/(clientYSize/2));
        }

        // inversement du delta si on de-zoom
        if (event.GetWheelRotation() < 0){
                if (GetViewStart().x > deltaPosXScroll){ // inversement si on peut de-zoomer dans cette direction
                    deltaPosXScroll = -deltaPosXScroll;
                }else{
                    deltaPosXScroll = 0;
                }
        }
        if (event.GetWheelRotation() < 0){
                if (GetViewStart().y > deltaPosYScroll){
                    deltaPosYScroll = -deltaPosYScroll;
                }else{
                    deltaPosYScroll = 0;
                }
        }

        // actualisation de l'image
        parent->GetStatusBar()->SetStatusText("Zoom : "+std::to_string((int) (imageScale*100))+" %");
        SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale, GetViewStart().x+deltaPosXScroll, GetViewStart().y+deltaPosYScroll);
        Refresh();
    }
}
