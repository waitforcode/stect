# Using stect for visual attack at steganography. #

This method of replacing the least significant bit is best suited for uncompressed images, such as images in BMP or PNG. These formats are not yet gained such popularity as the format of JPEG. A BMP format now in general frankly outdated, but classic steganography - microchanges color of each pixel is gradually eroding . But in spite of this method of attack on the visual image is still something that can .

Let us take a simple program for steganography in JPEG - JSTEG and prepare the raw data - examines the file without the hidden message ( empty container) , and with steganography message.

|![http://1.bp.blogspot.com/-WY_yqQP-Mxc/UnnutfurI_I/AAAAAAAAIjY/cbAvF4J8BSc/s1600/images.jpg](http://1.bp.blogspot.com/-WY_yqQP-Mxc/UnnutfurI_I/AAAAAAAAIjY/cbAvF4J8BSc/s1600/images.jpg)|![http://4.bp.blogspot.com/-MPhSv_TazpQ/UnnvEjXAzpI/AAAAAAAAIjg/dehk-MB02ME/s1600/images_stego.jpg](http://4.bp.blogspot.com/-MPhSv_TazpQ/UnnvEjXAzpI/AAAAAAAAIjg/dehk-MB02ME/s1600/images_stego.jpg)|
|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|:----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
|Image without steganography                                                                                                                                                              |Image with steganography                                                                                                                                                                             |
Visual comparison of images in a modified jsteg- th visible image artifacts around small parts - but this in itself does not mean anything - that happens a lot in image compression with low quality. Now take a magic program stect load both files in it and ....


Result Attack visual image containing no
stego - insert

For a file that does not contain steganography in place , flat areas we see too monotonous black area - it tells us that there are no colors in the image microvibrations not.


Result Attack visual image , comprising
message hidden program JSTEG

Open the file containing the stegosoobschenie - and see the on-site self-colored filling is something very reminiscent of a chess board . The reason is that the program modifies the DCT coefficients JSTEG images that define the color blocks of pixels of 8x8 - so changes appear immediately in the big blocks .

Thus a visual attack on the stego stegosystems allows the analyst to quickly assess whether the modified image in the least significant bits or not.