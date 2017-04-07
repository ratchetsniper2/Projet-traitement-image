#ifndef MYPANEL_H
#define MYPANEL_H

#include "MyHistogram.h"
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyLuminositeDialog.h"
#include "MyTraitDialog.h"
#include "MyTextDialog.h"
#include "MyRotateDialog.h"
#include "MyReSizeDialog.h"

class MyPanel: public wxScrolledCanvas{
public:
    MyPanel( wxFrame *parent ) ;
    ~MyPanel() ;
    void OpenImage(wxString fileName);
    void SaveImage();

    void OnPaint(wxPaintEvent &WXUNUSED(event));

    void noImageOpen();

    void MirrorImage(bool horizontal);
    void BlurImage();
    void RotateImage();
    void Negative();
    void Desaturate();
    void Threshold();
    void ThresholdImage();
    void Posterize();
    void OnThresholdImage(wxCommandEvent& event);
    void OnLuminosite(wxCommandEvent& event);
    void Luminosite();
    void Nbcolor();
    void EnhenceContrast();

    // dessin
    void OnMouse(wxMouseEvent& event);
    void SetCouleur(const char* couleur);
    void OnTrait(wxCommandEvent& event);
    void Trait();
    void SetOn_off(bool on);
    bool GetOn_off();
    void SetMode(const char* mode);
    void Text();

    // undo
    void SaveImageBeforeTraitment();
    void BackTraitment();

    void ReSize();

private:
    MyImage *m_image;		// used to load and process the image
    MyImage m_imageCopie;	// data befor last traitment
    wxBitmap m_bitmap;	// used to display the image

    MyHistogram* histogram;

    // for dessin
    int x_mouse;
    int y_mouse;
    const char* couleur;
    const char* mode;
    bool on_off;
    int trait;
    wxString texte;

    double imageScale; // for zoom
    wxFrame* parent; // for change statusbar on zoom

    int m_width;
    int m_height;

    void OnMouseWheel(wxMouseEvent& event);

};

#endif // MYPANEL_H
