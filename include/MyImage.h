#ifndef MYIMAGE_H
#define MYIMAGE_H

#include <wx/wxprec.h>
#include <wx/event.h>
#ifndef WX_PRECOMP
#include <wx/wx.h>
#endif

#include <math.h>

class MyImage: public wxImage{
    public:
        MyImage(int largeur, int hauteur);
        MyImage(const wxString& fileName);
        MyImage(wxImage image);
        MyImage();
        ~MyImage();

        void Negative();
        void Desaturate();
        void Threshold(int seuil);
        void Posterize(int nbColor);
        void Luminosite(int lumi);

        int Nbcolor();

        void EnhenceContrast(int minValue, int maxValue);

};

#endif // MYIMAGE_H
