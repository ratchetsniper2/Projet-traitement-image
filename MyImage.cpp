#include "MyImage.h"

MyImage::MyImage(int largeur, int hauteur) : wxImage(largeur, hauteur){
}

MyImage::MyImage(const wxString& fileName) : wxImage(fileName){
}

MyImage::MyImage(wxImage image) : wxImage(image){
}

MyImage::MyImage() : wxImage(){
}

MyImage::~MyImage(){
}

void MyImage::Negative(){
    unsigned char* data = this->GetData();

    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i++){
        data[i] = 255 - data[i];
    }
}

void MyImage::Desaturate(){
    unsigned char* data = this->GetData();

    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=3){
        int result = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
        data[i] = result;
        data[i+1] = result;
        data[i+2] = result;
    }
}

void MyImage::Threshold(int seuil){
    unsigned char* data = this->GetData();

    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=3){
        int result = 0.2126*data[i] + 0.7152*data[i+1] + 0.0722*data[i+2];
        if (result >= seuil){
            result = 255;
        }else{
            result = 0;
        }

        data[i] = result;
        data[i+1] = result;
        data[i+2] = result;
    }
}

void MyImage::Posterize(int nbColor){
    unsigned char* data = this->GetData();

    int nbBorne = (pow(nbColor, (1.0/3.0))-1);
    int bornes[nbBorne];
    for (int i = 0 ; i < nbBorne ; i++){
        bornes[i] = (i+1)*255/(nbBorne);
    }

    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=1){
            for (int iBorn = 0 ; iBorn < nbBorne ; iBorn++){
                if (data[i] <= bornes[iBorn]-bornes[0]/2){
                    data[i] = bornes[iBorn]-bornes[0];
                    break;
                }else if (data[i] <= bornes[iBorn]){
                    data[i] = bornes[iBorn];
                    break;
                }
            }
    }
}

int MyImage::Nbcolor(){
    /*unsigned char* data = this->GetData();
    std::set<int> setPx;

    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=3){
        setPx.insert(data[i]*1000000+data[i+1]*1000+data[i+2]);
    }

    return setPx.size();*/

    unsigned char* data = this->GetData();
    int* tabPx = (int*) calloc(sizeof(int), 16777216);

    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=3){
        tabPx[data[i+2]+(data[i+1]<<8)+(data[i]<<16)] = 1;
    }

    int nbColor = 0;
    for (int i = 0 ; i < 16777216 ; i++){
        nbColor += tabPx[i];
    }

    free(tabPx);
    return nbColor;
}

void MyImage::EnhenceContrast(int minValue, int maxValue){
    unsigned char* data = GetData();

    int dif = maxValue-minValue;
    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=1){
        data[i] = (255/dif)*(data[i] - minValue);
    }
}

void MyImage::Luminosite(int lumi){
    unsigned char* data = GetData();
    unsigned long int sizeImage = this->GetHeight()*this->GetWidth()*3;
    if(lumi>=100){
        lumi= lumi - 200;
    }
    for(unsigned long int i = 0 ; i < sizeImage ; i+=3){
        data[i] = std::max(0, std::min(255, data[i]+lumi));
        data[i+1] = std::max(0, std::min(255, data[i+1]+lumi));
        data[i+2] = std::max(0, std::min(255, data[i+2]+lumi));
    }

}
