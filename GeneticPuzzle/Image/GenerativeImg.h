#ifndef GENERATIVE_IMAGE_H
#define GENERATIVE_IMAGE_H

#include <QImage>

class GenerativeImg
{
private:
    /* data */

    void segmentate(int n);

    //! The base image that's worked from
    QImage originalImg;

    //! Amount of chunks (used to know how long the array holding the chunks is, also to generate 'correct' order array)
    size_t numOfChunks;

    //! Pointer to array holding the chunks of the image
    QImage *chunks;

    bool isSquare(int n);

    bool isPowerOf2(int n);

public:
    GenerativeImg(QImage img, int n);
    ~GenerativeImg();
};

#endif