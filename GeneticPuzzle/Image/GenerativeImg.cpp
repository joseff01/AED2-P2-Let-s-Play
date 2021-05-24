#include "GenerativeImg.h"
#include <stdexcept>

/*!
 * \brief Construct a new Generative Img object by giving it an image and the number of chunks you wish it to be split by
 * 
 * \param img the image you wish to utilize as a QImage
 * \param n number of chunks you wish the image to split in, MUST BE a square number or any power of 2 (greater than 0) 
 */
GenerativeImg::GenerativeImg(QImage img, int n)
{
}

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
}

/*
function ca = segmentate (img, n)
%n is number of chunks, must be square or power of 2

[rows columns ~] = size(img);

if (ceil(sqrt(n))==floor(sqrt(n))) %if it's a square number
  blockSizeR = floor(rows/sqrt(n));
  blockSizeC = floor(columns/sqrt(n));
  
elseif (ceil(log2(n))==floor(log2(n))) %if it's a power of 2 (note it's only the odd ones that make it here)
  blockSizeR = floor(rows/sqrt(n/2));
  blockSizeC = floor(columns/sqrt(n*2));
  
else
  printf("Number of chunks must be square or power of 2")
  ca={}
  return
endif

if (blockSizeR<30||blockSizeC<30)
  printf("Number of chunks too high, ending up in chunks that are too small to work with")
  ca={}
  return
endif
*/
