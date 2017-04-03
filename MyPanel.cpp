#include "MyPanel.h"

// Evenement pour traitement dynamique
wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent); // seuillage
wxDEFINE_EVENT(EVENEMENT_LUMINOSITE, wxCommandEvent); // luminosite

MyPanel::MyPanel(wxFrame *parent) : wxScrolledCanvas(parent), m_image(NULL), histogram(NULL), parent(parent){
    imageScale = 1.0;

    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this);
    Bind(EVENEMENT_LUMINOSITE, &MyPanel::OnLuminosite, this);
    Bind(wxEVT_MOUSEWHEEL, &MyPanel::OnMouseWheel, this);
    Bind(wxEVT_LEFT_DOWN, &MyPanel::OnMouse, this);

}

MyPanel::~MyPanel(){}

// message d'erreur tentative de traitement sans avoir ouver d'image
void MyPanel::noImageOpen(){
    wxLogMessage(wxT("No image open  ..."));
}

// ouvrir une image
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

// sauvegarde de l'image
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

// Miroire
void MyPanel::MirrorImage(bool horizontal){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        *m_image = m_image->Mirror(horizontal);

        Refresh();
    }else{
        noImageOpen();
    }
}

// Blur
void MyPanel::BlurImage(){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        *m_image = m_image->Blur(1);

        Refresh();
    }else{
        noImageOpen();
    }
}

// Rotation d'image
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

// Négatif
void MyPanel::Negative(){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        m_image->Negative();
        Refresh();
    }else{
        noImageOpen();
    }
}

// Désaturation
void MyPanel::Desaturate(){
    if (m_image != NULL){
        SaveImageBeforeTraitment();
        m_image->Desaturate();
        Refresh();
    }else{
        noImageOpen();
    }
}

// Posterisation
void MyPanel::Posterize(){
    if (m_image != NULL){


        SaveImageBeforeTraitment();
        m_image->Posterize(8);

        Refresh();
    }else{
        noImageOpen();
    }
}

// contage du nombre de couleur
void MyPanel::Nbcolor(){
    if (m_image != NULL){
        int nbColor = m_image->Nbcolor();
        wxLogMessage(wxString::Format(wxT("%i"),nbColor)+wxT(" colors"));
    }else{
        noImageOpen();
    }
}

// amélioration du contrast
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

// seuillage de l'image
void MyPanel::Threshold(){
    if (m_image != NULL){
        MyThresholdDialog *dlg = new MyThresholdDialog(false, this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));
        if (dlg->ShowModal() == wxID_OK){
            SaveImageBeforeTraitment();
            m_image->Threshold(dlg->m_threshold->GetValue());
            Refresh();
        }
    }else{
        noImageOpen();
    }
}

// seuillage de l'image dynamique
void MyPanel::ThresholdImage(){
    if (m_image != NULL){

        SaveImageBeforeTraitment();
        MyThresholdDialog *dlg = new MyThresholdDialog(true, this, -1, wxT("Threshold"), wxDefaultPosition, wxSize(250,140));

        if (dlg->ShowModal() != wxID_OK){
            BackTraitment();
            //annuler la transformation
        }
    }else{
        noImageOpen();

    }
}

// pour un changement dynamique
void MyPanel::OnThresholdImage(wxCommandEvent& event){

    //remmettre l'image d'origine avant de faire la transformation
    BackTraitment();
    SaveImageBeforeTraitment();

    m_image->Threshold(event.GetSelection());
    Refresh();
}

// changer la luminosité de l'image
void MyPanel::Luminosite(){
if (m_image != NULL){

        SaveImageBeforeTraitment();
        MyLuminositeDialog *dlg = new MyLuminositeDialog(this, -1, wxT("Luminosité"), wxDefaultPosition, wxSize(250,140));

        if (dlg->ShowModal() != wxID_OK){
            BackTraitment();
            //annuler la transformation
        }
    }else{
        noImageOpen();

    }

}

// pour un changement dynamique
void MyPanel::OnLuminosite(wxCommandEvent& event){

    //remmettre l'image d'origine avant de faire la transformation
    BackTraitment();
    SaveImageBeforeTraitment();

    m_image->Luminosite(event.GetSelection());
    Refresh();
}

// au click souris
void MyPanel::OnMouse(wxMouseEvent& event){
    int mx = wxGetMousePosition().x - this->GetScreenPosition().x;
    int my = wxGetMousePosition().y - this->GetScreenPosition().y;
    wxPaintDC dc(this);
    if(couleur != NULL){
      wxPen MonCrayon(couleur,5,wxSOLID);
        dc.SetPen(MonCrayon);
    }


    if(x_mouse == 0){
        x_mouse = mx;
        y_mouse = my;
    }else{
    dc.DrawLine(x_mouse,y_mouse,mx,my);
        x_mouse = 0;
        y_mouse = 0;
    }
}

// changer la couleur du pinceau
void MyPanel::SetCouleur(const char* coul){
    couleur = coul;
}

// sauvegarder l'image avant le traitement
void MyPanel::SaveImageBeforeTraitment(){
    m_imageCopie = m_image->Copy();
}

// annuler le dernier traitement
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

// redimention d'image
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
        double incrScale = 0.05; // incrémentation du zoom "5%"

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

        // actualisation de la fenetre
        parent->GetStatusBar()->SetStatusText("Zoom : "+std::to_string((int) (imageScale*100))+" %");
        SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale, GetViewStart().x+deltaPosXScroll, GetViewStart().y+deltaPosYScroll);
        Refresh();
    }
}
