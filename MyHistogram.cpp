#include "MyHistogram.h"

MyHistogram::MyHistogram(MyImage* m_image){
    unsigned char* data = m_image->GetData();
    tableau =(int*) calloc(sizeof(int), 256);

    unsigned long int sizeImage = m_image->GetHeight()*m_image->GetWidth()*3;
    for(unsigned long int i = 0 ; i < sizeImage ; i+=1){
        tableau[data[i]]++;
    }
}

MyHistogram::~MyHistogram(){
    free(tableau);
}

void MyHistogram::getBorderValues(int *minValue, int *maxValue){
    // min et max doivent etre initialisés

    int i = 0;
    while (tableau[i] == 0){
        i++;
    }
    *minValue = i;

    while (i < 256){
        if (tableau[i] != 0){
            *maxValue = i;
        }
        i++;
    }

}
