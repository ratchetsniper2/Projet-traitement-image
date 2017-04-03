#ifndef MYHISTOGRAM_H
#define MYHISTOGRAM_H

#include "../include/MyImage.h"

class MyHistogram{
    public:
        MyHistogram(MyImage* m_image);
        virtual ~MyHistogram();

        void getBorderValues(int *minValue, int *maxValue);

    private:
        int* tableau;
};

#endif // MYHISTOGRAM_H
