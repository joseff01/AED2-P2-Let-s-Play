#include "GenerativeImg.h"
#include <stdexcept>
#include <math.h>
#include <QPainter>

/*!
 * \brief Construct a new Generative Img object by giving it an image and the number of chunks you wish it to be split by
 * 
 * \param img the image you wish to utilize as a QImage
 * \param n number of chunks you wish the image to split in, MUST BE a square number or any power of 2 (greater than 0) 
 * \throws invalid_argument if number of chunks to be segmentated into is less than or equal to 2, or if it's neither a square nor a power of 2
 */
GenerativeImg::GenerativeImg(QImage img, int n)
{
    this->chunks = List<QImage>(); // initialize empty linked list
    this->originalImg = img.copy();

    if (n <= 2)
    {
        throw std::invalid_argument("Number of chunks must be greater than 2");
    }

    if (!isSquare(n) && !isPowerOf2(n))
    {
        throw std::invalid_argument("Number of chunks is neither a perfect square nor a power of 2 (for a power greater than 1)");
    }

    segmentate(img, n);
}

//! Destroy the Generative Img:: Generative Img object
GenerativeImg::~GenerativeImg()
{
    this->chunks.clear();
}

/*!
 * \brief Method that takes care of segmentating the QImage given to the object, gets called during the constructor
 * 
 * \param n number of chunks you wish the image to split in, MUST BE a square number or any power of 2 (greater than 0)
 */
void GenerativeImg::segmentate(QImage img, int n)
{
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

    if (blockSizeR < 1 || blockSizeC < 1)
    {
        throw std::invalid_argument("Number of chunks is too high (pixels would need to be split)");
    }

    // ---------Actual segmentation happens beyond this point------------

    QRect chunkWindow = QRect(0, 0, blockSizeC, blockSizeR); // rect representing the size of a chunk used to extract all the chunks from original image

    for (int rowChunk = 0; rowChunk < rows / blockSizeR; rowChunk++)
    {
        chunkWindow.moveTop(rowChunk * blockSizeR);
        for (int columnChunk = 0; columnChunk < columns / blockSizeC; columnChunk++)
        {
            chunkWindow.moveLeft(columnChunk * blockSizeC);
            this->chunks.push_back(img.copy(chunkWindow));
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

// /*!
//  * \brief Get the pointer that points to the start of the array holding the chunks of the image
//  *
//  * \return QImage* pointing to the start of the array that holds the chunks of the image
//  */
// QImage *GenerativeImg::getChunks()
// {
//     return this->chunks;
// }

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
    return this->chunks.length();
}

/*!
 * \brief Call this method by giving it an orderList which denotes the order in which you wish to add chunks to your new combined image. The orderList must be the same size as the amount of chunks in which the image was originally segmentated.
 * 
 * \param orderList List of ints that must be the same size as the amount of chunks the original image was segmentated in. It denotes the order to use for the chunks to build a new combined image.
 * \return QImage get the combined image of the chunks denoted in the orderList
 * \throws invalid_argument if orderList is not the appropiate length or has elements that would be out of range
 */
QImage GenerativeImg::getFrankenImg(List<int> orderList)
{
    if (orderList.length() != this->chunks.length())
    {
        throw std::invalid_argument("Error called from getFrankenImg(): Size of list denoting the order of chunks must have a length equal to the number of chunks the original image was segmentated into.");
    }

    int blockSizeR = this->chunks[0].height();
    int blockSizeC = this->chunks[0].width();

    int rows;
    int columns;

    if (isSquare(this->chunks.length()))
    {
        rows = blockSizeR * sqrt(this->chunks.length());
        columns = blockSizeC * sqrt(this->chunks.length());
    }
    else
    {
        rows = blockSizeR * sqrt(this->chunks.length() / 2);
        columns = blockSizeC * sqrt(this->chunks.length() * 2);
    }

    QImage frankenstein(columns, rows, originalImg.format());
    frankenstein.fill(0);
    QPainter painter(&frankenstein);

    int i = 0;
    for (int rowChunk = 0; rowChunk < rows / blockSizeR; rowChunk++)
    {
        for (int columnChunk = 0; columnChunk < columns / blockSizeC; columnChunk++)
        {
            if (orderList[i] < 0 || orderList[i] >= this->chunks.length())
            {
                throw std::invalid_argument("Error called from getFrankenImg(): passed orderList may not have any element >= the amount of chunks the image was split in. Nor may it have any negative elements.");
            }
            painter.drawImage(columnChunk * blockSizeC, rowChunk * blockSizeR, this->chunks[orderList[i]]);
            i++;
        }
    }
    return frankenstein;
}