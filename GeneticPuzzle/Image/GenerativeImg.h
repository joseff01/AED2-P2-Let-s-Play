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

    bool isSquare(int n);

    bool isPowerOf2(int n);

public:
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