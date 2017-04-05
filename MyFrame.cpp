#include "MyFrame.h"
#include <time.h>
#include <wx/event.h>

// énumération. Elle gère la numérotation automatiquement
enum{
	ID_Hello = 1,
	ID_About,
	ID_EnCours,
	ID_PlusLarge,
	ID_MoinsLarge,
	ID_Open,
	ID_Save,
	ID_MirrorVertical,
	ID_MirrorHorizontal,
	ID_Blur,
	ID_Rotate,
	ID_Negative,
	ID_Desaturate,
	ID_Threshold,
	ID_Posterize,
	ID_Nbcolor,
	ID_EnhenceContrast,
	ID_Back,
	ID_ReSize,
	ID_Threshold_V2,
	ID_Luminosite,
	ID_BLEU,
	ID_ROUGE,
	ID_NOIR,
	ID_VERT


};


// -------------------------------------------------------


MyFrame::MyFrame(const wxString& title, const wxPoint& pos, const wxSize& size)
: wxFrame(NULL, wxID_ANY, title, pos, size){
    m_panel = new MyPanel(this);

    wxMenuBar *menuBar = new wxMenuBar ;

    // menu file ---------------------------------------------------

	wxMenu *menuFile = new wxMenu ;
	menuFile->Append(ID_Hello, wxT("Hello..."), wxT("Hello message"));
	Bind(wxEVT_MENU, &MyFrame::OnHello, this, ID_Hello);

	menuFile->Append(ID_PlusLarge, wxT("Plus large...\tCtrl-+"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_PlusLarge);

	menuFile->Append(ID_MoinsLarge, wxT("Moins large...\tCtrl--"));
	Bind(wxEVT_MENU, &MyFrame::OnResize, this, ID_MoinsLarge);

	menuFile->Append(ID_Open, wxT("Open...\tCtrl-O"));
	Bind(wxEVT_MENU, &MyFrame::OnOpenImage, this, ID_Open);

	menuFile->Append(ID_Save, wxT("Save As...\tCtrl-S"));
	Bind(wxEVT_MENU, &MyFrame::OnSaveImage, this, ID_Save);

	menuFile->Append(ID_Back, wxT("Undo...\tCtrl-Z"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Back);

	menuFile->AppendSeparator();

	menuFile->Append(ID_About, wxT("About...\tCtrl-A"));
	Bind(wxEVT_MENU, &MyFrame::OnAbout, this, ID_About);

	menuFile->Append(wxID_EXIT);
	Bind(wxEVT_MENU, &MyFrame::OnExit, this, wxID_EXIT);

	menuBar->Append( menuFile, wxT("File" ));

    // menu help ---------------------------------------------------

	wxMenu *menuHelp = new wxMenu ;
	menuHelp->Append(ID_EnCours, wxT("En Cours..."));
	Bind(wxEVT_MENU, &MyFrame::OnEnCours, this, ID_EnCours);

	menuBar->Append( menuHelp, wxT("Help" ));

    // menu process ---------------------------------------------------

	wxMenu *menuProcess = new wxMenu ;
	menuProcess->Append(ID_MirrorVertical, wxT("Vertical Mirror...\tCtrl-V"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorVertical);

	menuProcess->Append(ID_MirrorHorizontal, wxT("Horizontal Mirror...\tCtrl-H"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_MirrorHorizontal);

	menuProcess->Append(ID_Blur, wxT("Blur...\tCtrl-B"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Blur);

	menuProcess->Append(ID_Rotate, wxT("Rotate...\tCtrl-R"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Rotate);

	menuProcess->Append(ID_Negative, wxT("Negative...\tCtrl-N"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Negative);

	menuProcess->Append(ID_Desaturate, wxT("Desaturate...\tCtrl-D"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Desaturate);

	menuProcess->Append(ID_Threshold, wxT("Threshold...\tCtrl-T"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Threshold);

	menuProcess->Append(ID_Threshold_V2, wxT("Threshold_V2..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Threshold_V2);

	menuProcess->Append(ID_Posterize, wxT("Posterize...\tCtrl-P"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Posterize);

	menuProcess->Append(ID_Nbcolor, wxT("Nb-color..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Nbcolor);

	menuProcess->Append(ID_EnhenceContrast, wxT("EnhenceContrast...\tCtrl-E"));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_EnhenceContrast);

	menuProcess->Append(ID_ReSize, wxT("ReSize..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ReSize);

	menuProcess->Append(ID_Luminosite, wxT("Luminosité..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_Luminosite);

	menuBar->Append( menuProcess, wxT("Process" ));

    //menu couleur --------------------------------------------------------

    wxMenu *menuDessin = new wxMenu ;

    menuDessin->Append(ID_BLEU, wxT("Bleu..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_BLEU);

	menuDessin->Append(ID_NOIR, wxT("Noir..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_NOIR);

	menuDessin->Append(ID_ROUGE, wxT("Rouge..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_ROUGE);

	menuDessin->Append(ID_VERT, wxT("Vert..."));
	Bind(wxEVT_MENU, &MyFrame::OnProcessImage, this, ID_VERT);

	menuBar->Append( menuDessin, wxT("Dessin" ));

    SetMenuBar(menuBar) ;

	wxStatusBar *statusBar = this->CreateStatusBar();
	statusBar->SetStatusText(wxT(""));
	this->SetStatusBar(statusBar);

}

void MyFrame::OnHello(wxCommandEvent& event){
	wxLogMessage(wxT("Hello world from wxWidgets!"));
}

void MyFrame::OnAbout(wxCommandEvent& event){
	wxLogMessage(wxT("Creator :\nValentin Bouchet\nGuerre-Chaley Mathieu"));
}

// resize de la fenetre
void MyFrame::OnResize(wxCommandEvent& event){
    wxSize size = this->GetSize();
    if (event.GetId() == ID_PlusLarge){ // plus
        if (size.GetHeight() < 800){
            size.IncBy(100, 100);
        }
    }else{
        if (size.GetHeight() > 200){
            size.IncBy(-100, -100);
        }
    }
    this->SetSize(size);

}

void MyFrame::OnExit(wxCommandEvent& event){
	Close(true);
}

void MyFrame::OnEnCours(wxCommandEvent& event){
	wxLogMessage(wxT("En cours de construction ..."));
}

void MyFrame::OnOpenImage(wxCommandEvent& event){
	wxString filename = wxFileSelector("Choose a image to open", "", "", "", "PNG files (*.png)|*.png|JPG files (*.jpg)|*.jpg|JPEG files (*.jpeg)|*.jpeg|BMP files (*.bmp)|*.bmp|GIF files (*.gif)|*.gif");
	if (!filename.empty()){
            m_panel->OpenImage(filename);
            GetStatusBar()->SetStatusText("");
    }
}

void MyFrame::OnSaveImage(wxCommandEvent& event){
    m_panel->SaveImage();
}

void MyFrame::OnProcessImage(wxCommandEvent& event){
    switch (event.GetId()){
        case ID_MirrorHorizontal:
            m_panel->MirrorImage(true);
            break;

        case ID_MirrorVertical:
            m_panel->MirrorImage(false);
            break;

        case ID_Blur:
            m_panel->BlurImage();
            break;

        case ID_Rotate:
            m_panel->RotateImage();
            break;

        case ID_Negative:
            clock_t t; t = clock();
            m_panel->Negative();
            t = clock() - t;
            GetStatusBar()->SetStatusText("Temps de traitement : "+std::to_string(((float)t)/CLOCKS_PER_SEC));
            break;

        case ID_Desaturate:
            m_panel->Desaturate();
            break;

        case ID_Threshold:
            m_panel->Threshold();
            break;

        case ID_Threshold_V2:
            m_panel->ThresholdImage();
            break;

        case ID_Posterize:
            m_panel->Posterize();
            break;

        case ID_Nbcolor:
            m_panel->Nbcolor();
            break;
        case ID_EnhenceContrast:
            m_panel->EnhenceContrast();
            break;

        case ID_Luminosite:
            m_panel->Luminosite();
            break;

        case ID_Back:
            m_panel->BackTraitment();
            break;

        case ID_BLEU:
            m_panel->SetCouleur("BLUE");
            break;

        case ID_NOIR:
            m_panel->SetCouleur("BLACK");
            break;

        case ID_ROUGE:
            m_panel->SetCouleur("RED");
            break;

        case ID_VERT:
            m_panel->SetCouleur("GREEN");
            break;

        case ID_ReSize:
            m_panel->ReSize();
            break;
    }
}
