#ifndef MYPANEL_H
#define MYPANEL_H

#include "MyHistogram.h"
#include "MyImage.h"
#include "MyThresholdDialog.h"
#include "MyRotateDialog.h"

class MyPanel: public wxPanel{
public:
    MyPanel( wxWindow *parent ) ;
    ~MyPanel() ;
    void OpenImage(wxString fileName);
    void SaveImage(wxString fileName);

    void OnPaint(wxPaintEvent &WXUNUSED(event));

    void noImageOpen();

    void MirrorImage(bool horizontal);
    void BlurImage();
    void RotateImage();
    void Negative();
    void Desaturate();
    void Threshold();
    void Posterize();

    void Nbcolor();
    void EnhenceContrast();

    void SaveImageBeforeTraitment();
    void BackTraitment();

    void ReSize();

private:
    MyImage *m_image;		// used to load and process the image
    MyImage m_imageCopie;	// data befor last traitment
    wxBitmap m_bitmap;	// used to display the image

    MyHistogram* histogram;

    double imageScale; // pour zoomer sur l'image

    int m_width;
    int m_height;

};

#endif // MYPANEL_H
