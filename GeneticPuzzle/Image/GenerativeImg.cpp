#include "GenerativeImg.h"
#include <stdexcept>
#include <math.h>

/*!
 * \brief Construct a new Generative Img object by giving it an image and the number of chunks you wish it to be split by
 * 
 * \param img the image you wish to utilize as a QImage
 * \param n number of chunks you wish the image to split in, MUST BE a square number or any power of 2 (greater than 0) 
 */
GenerativeImg::GenerativeImg(QImage img, int n)
{
    if (n <= 2)
    {
        throw std::invalid_argument("Number of chunks must be greater than 2");
    }

    if (!isSquare(n) && !isPowerOf2(n))
    {
        throw std::invalid_argument("Number of chunks is neither a perfect square nor a power of 2 (for a power greater than 1)");
    }

    this->chunks = new QImage[n]; //initialize array that'll hold chunks

    segmentate(n);
}

//! Destroy the Generative Img:: Generative Img object
GenerativeImg::~GenerativeImg()
{
    delete[] this->chunks;
}

/*!
 * \brief Method that takes care of segmentating the QImage given to the object, gets called during the constructor
 * 
 * \param n number of chunks you wish the image to split in, MUST BE a square number or any power of 2 (greater than 0)
 */
void GenerativeImg::segmentate(int n)
{
    QImage img = this->originalImg;

    int rows = img.height();
    int columns = img.width();

    int blockSizeR; // These are going to be the size of each chunk's rows and columns (width and height)
    int blockSizeC;

    if (isSquare(n))
    {
        blockSizeR = floor(rows / sqrt(n));
        blockSizeC = floor(columns / sqrt(n));
    }
    else if (isPowerOf2(n))
    {
        blockSizeR = floor(rows / sqrt(n / 2));
        blockSizeC = floor(columns / sqrt(n * 2));
    }
    else
    {
        throw std::invalid_argument("Number of chunks is neither a perfect square nor a power of 2 (for a power greater than 1)");
    }

    // ---------Actual segmentation happens beyond this point------------

    QRect chunkWindow = QRect(0, 0, blockSizeC, blockSizeR); // rect representing the size of a chunk used to extract all the chunks from original image

    int i = 0;
    for (int rowChunk = 0; rowChunk < rows / blockSizeR; rowChunk++)
    {
        chunkWindow.setY(rowChunk * blockSizeR);
        for (int columnChunk = 0; columnChunk < columns / blockSizeC; columnChunk++)
        {
            chunkWindow.setX(columnChunk * blockSizeC);
            *(this->chunks + i) = img.copy(chunkWindow);
            i++;
        }
    }
}

/*!
 * \brief Checks if given number is a perfect square
 * 
 * \param n int to be checked
 * \return true if n is a perfect square
 * \return false if n is not a perfect square
 */
bool GenerativeImg::isSquare(int n)
{
    if (ceil((double)sqrt(n)) == floor((double)sqrt(n)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Checks if given number is a power of 2
 * 
 * \param n int to be checked
 * \return true if n is a power of 2
 * \return false if n is not a power of 2
 */
bool GenerativeImg::isPowerOf2(int n)
{
    if (ceil(log2(n)) == floor(log2(n)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

/*!
 * \brief Get the pointer that points to the start of the array holding the chunks of the image
 * 
 * \return QImage* pointing to the start of the array that holds the chunks of the image
 */
QImage *GenerativeImg::getChunks()
{
    return this->chunks;
}

/*!
 * \brief Get the QImage corresponding to the original inputted complete image
 * 
 * \return QImage that is the original whole image given to the object in its constructor
 */
QImage GenerativeImg::getOriginalImg()
{
    return this->originalImg;
}

/*!
 * \brief Get the amount of chunks that there are for the image, important for indexing the chunks array
 * 
 * \return size_t corresponding to the amount of chunks the image was segmentated into
 */
size_t GenerativeImg::getNumOfChunks()
{
    return this->numOfChunks;
}