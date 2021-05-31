#ifndef GENERATIVE_IMAGE_H
#define GENERATIVE_IMAGE_H

#include <QImage>
#include "List.h"

class GenerativeImg
{
private:
    /* data */

    void segmentate(QImage img, int n);

    //! The base image that's worked from
    QImage originalImg;

public:
    static bool isSquare(int n);

    static bool isPowerOf2(int n);

    //! Pointer to array holding the chunks of the image
    List<QImage> chunks;
    GenerativeImg(QImage img, int n);

    ~GenerativeImg();

    // QImage *getChunks();

    QImage getOriginalImg();

    size_t getNumOfChunks();

    QImage getFrankenImg(List<int> orderList);
};

#endif