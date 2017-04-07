#include "MyPanel.h"

// Evenement pour traitement dynamique
wxDEFINE_EVENT(MON_EVENEMENT, wxCommandEvent); // seuillage
wxDEFINE_EVENT(EVENEMENT_LUMINOSITE, wxCommandEvent); // luminosite

wxDEFINE_EVENT(EVENEMENT_TRAIT, wxCommandEvent); // dessin

MyPanel::MyPanel(wxFrame *parent) : wxScrolledCanvas(parent), m_image(NULL), histogram(NULL), parent(parent){

    Bind(wxEVT_PAINT, &MyPanel::OnPaint, this);
    Bind(MON_EVENEMENT, &MyPanel::OnThresholdImage, this);
    Bind(EVENEMENT_LUMINOSITE, &MyPanel::OnLuminosite, this);
    Bind(wxEVT_MOUSEWHEEL, &MyPanel::OnMouseWheel, this);
    Bind(wxEVT_LEFT_DOWN, &MyPanel::OnMouse, this);

    imageScale = 1.0;

    couleur = "BLACK";
    on_off = false;
    trait = 1;
    mode = "trait";
    texte = "test";

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

        DoPrepareDC(dc); // prépare l'image pour etre afficher dans une fenetre scrollable
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

// fonction dession : au click souris
void MyPanel::OnMouse(wxMouseEvent& event){
    if (m_image != NULL && on_off == true){
        // modification pour récupérer la vrai position du curseur sur l'image en fonction du zoom
        wxPoint point = ScreenToClient(wxGetMousePosition());
        int mx = (GetViewStart().x + point.x) * (1/imageScale);
        int my = (GetViewStart().y + point.y) * (1/imageScale);
        // -----------------------------------------------------------------

        // modification pour draw sur l'image
        wxMemoryDC dc;
        dc.SelectObject(m_bitmap);
        // ----------------------------------

        // initialisation trait
        wxPen MonCrayon(couleur, trait, wxSOLID);
        dc.SetPen(MonCrayon);


        if(x_mouse == 0){
            x_mouse = mx;
            y_mouse = my;

            //pour écrire
            if(strcmp(mode,"text")==0){
                dc.DrawText(texte,x_mouse,y_mouse);
                x_mouse = 0;
                y_mouse = 0;
        }
        //pour tracer un trait
        }else if(strcmp(mode,"trait")==0){
            dc.DrawLine(x_mouse,y_mouse,mx,my);
            x_mouse = 0;
            y_mouse = 0;
        }
        //pour tracer un cercle
        else if(strcmp(mode,"cercle")==0){
            wxBrush MaBrush(couleur,wxSOLID );
            dc.SetBrush(MaBrush);
            dc.DrawCircle(x_mouse,y_mouse,std::max(abs(mx-x_mouse),abs(my-y_mouse)));
            x_mouse = 0;
            y_mouse = 0;
        }
        //pour tracer un rectangle
        else if(strcmp(mode,"rectangle")==0){
            wxBrush MaBrush(couleur,wxSOLID );
            dc.SetBrush(MaBrush);
            dc.DrawRectangle(x_mouse,y_mouse,mx-x_mouse,my-y_mouse);
            x_mouse = 0;
            y_mouse = 0;
        }

        // modification pour draw sur l'image
        delete(m_image);
        m_image = new MyImage(m_bitmap.ConvertToImage());
        Refresh();
        // ----------------------------------

    }
}

// changer la couleur du pinceau
void MyPanel::SetCouleur(const char* coul){
    couleur = coul;
}

//pour modifier la taille du trait avec une fenetre de dialogue
void MyPanel::Trait(){
    MyTraitDialog *dlg = new MyTraitDialog(this, -1, wxT("Taille du trait"), wxDefaultPosition, wxSize(250,140));

    if (dlg->ShowModal() == wxID_OK){

    }
    else{
        trait = 1;
    }
}
//permet d'activer ou de desactiver la fonction dessin
void MyPanel::SetOn_off(bool on){
    on_off = on;
}

//permet de savoir si on peut dessiner
bool MyPanel::GetOn_off(){
    return on_off;
}

//permet de changer le mode de dessin
void MyPanel::SetMode(const char * mod){
    mode = mod;
}


void MyPanel::Text(){

    MyTextDialog *dlg = new MyTextDialog(this, -1, wxT(""), wxDefaultPosition, wxSize(250,140));

    if (dlg->ShowModal() == wxID_OK){
        texte = dlg->m_TextCtrl->GetValue();
    }

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

        int xSize = m_image->GetWidth();
        int ySize = m_image->GetHeight();

        MyReSizeDialog *dlg = new MyReSizeDialog(xSize, ySize, this, -1, wxT("ReSize"), wxDefaultPosition, wxSize(200,200));
        if (dlg->ShowModal() == wxID_OK){
            SaveImageBeforeTraitment();

            // vérification de validité des dimensions
            int repX = wxAtoi(dlg->m_widthSize->GetValue());
            if (repX > 0){
                xSize = repX;
            }

            int repY = wxAtoi(dlg->m_heightSize->GetValue());
            if (repY > 0){
                ySize = repY;
            }

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
        if (imageScale > 2){
            incrScale = 0.1;
            if (imageScale > 5){
                incrScale = 0.2;
            }
        }

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
        parent->GetStatusBar()->SetStatusText("Zoom : "+std::to_string(wxRound(imageScale*100))+" %");
        SetScrollbars(1, 1, m_width*imageScale, m_height*imageScale, GetViewStart().x+deltaPosXScroll, GetViewStart().y+deltaPosYScroll);
        Refresh();
    }
}
