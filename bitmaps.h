/* 
 * File:   bitmaps.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 16. April 2023, 18:19
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#define TUX 0
#define LINUS 1

/**
 * A bitmap with its width and height, and data.
 */
typedef struct {
    /** Width of the bitmap, must be a multiple of 8. */
    const uint16_t width;
    /** Height of the bitmap, must be a multiple of 8. */
    const uint16_t height;
    /** The actual bitmap. */
    const uint8_t *bitmap;
} Bitmap;

/**
 * Returns the bitmap at the given index.
 * @param index
 * @return Bitmap
 */
Bitmap getBitmap(uint8_t index);

#endif /* BITMAPS_H */

