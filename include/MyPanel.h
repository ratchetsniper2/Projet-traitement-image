#ifndef MYPANEL_H
#define MYPANEL_H

#include "../include/MyHistogram.h"
#include "../include/MyImage.h"
#include "../include/MyThresholdDialog.h"
#include "../include/MyLuminositeDialog.h"
#include "../include/MyRotateDialog.h"
#include "../include/MyReSizeDialog.h"

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
    void OnMouse(wxMouseEvent& event);
    void SetCouleur(const char* couleur);

    void ReSize();

private:
    MyImage *m_image;		// used to load and process the image
    wxBitmap m_bitmap;	// used to display the image

    MyHistogram* histogram;

    int x_mouse;
    int y_mouse;
    const char* couleur;

    double imageScale; // for zoom
    int m_width;
    int m_height;
    DECLARE_EVENT_TABLE()

    wxFrame* parent; // for change statusbar on zoom
    void OnMouseWheel(wxMouseEvent& event);

};

#endif // MYPANEL_H
