# Filter
I implement a program that applies filters to BMP (bitmap) images, using C.


I implemented a C program that applies filters to Bitmaps (BMP’s). 

Starter code was provided for this project, which I completed in the context of **Harvard University X**’s **[Introduction to Computer Science course](https://cs50.harvard.edu/x/2020/)**. 

## Specification

One can think of filtering an image as taking the pixels of some original image, and modifying each pixel in such a way that a particular effect is apparent in the resulting image.  

Click [here](https://cs50.harvard.edu/x/2020/psets/4/filter/more/#:~:text=Implement%20a%20program%20that%20applies%20filters%20to%20BMPs,%20per%20the%20below) for more information about the specifications for the project. Please do **not** directly use the source code as it is **only** for reference. Plagiarism is strictly prohibited by both Harvard University and the edX platform. See academic honesty for details.


## Implementation

I wrote 4 helper functions, such that a user can apply *grayscale*, *reflection*, *blur*, or, *edge detection* filters to their images.

- The *function grayscale* takes an image and turns it into a black-and-white version of the same image.
- The *reflect function* should take an image and reflect it horizontally.
- The *blur  function* should take an image and turn it into a box-blurred version of the same image.
- The *edges function* should take an image and highlight the edges between objects, according to the Sobel operator.

Images in the program are represented as 2D arrays, where image is an array of height many rows, and each row is itself another array of width. I mapped the different pixels of the image, traverse the 2D arrays and index into them, applying modifications to the pixel’s value and its neighbouring values to create the different filters.



