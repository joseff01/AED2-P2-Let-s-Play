#ifndef GENERATIVE_IMAGE_H
#define GENERATIVE_IMAGE_H

#include <QImage>
#include "List.h"

class GenerativeImg
{
private:
    /* data */

    void segmentate(int n);

    //! The base image that's worked from
    QImage originalImg;

    //! Pointer to array holding the chunks of the image
    List<QImage> chunks;

    bool isSquare(int n);

    bool isPowerOf2(int n);

public:
    GenerativeImg(QImage img, int n);

    QImage *getChunks();

    QImage getOriginalImg();

    size_t getNumOfChunks();
};

#endif