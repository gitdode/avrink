/* 
 * File:   bitmaps.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 16. April 2023, 18:19
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#define TUX 0

/**
 * A bitmap with its width and height, and data.
 */
typedef struct {
    const uint16_t width;
    const uint16_t height;
    const uint8_t *bitmap;
} Bitmap;

/**
 * Returns the bitmap at the given index.
 * @param index
 * @return Bitmap
 */
Bitmap getBitmap(uint8_t index);

#endif /* BITMAPS_H */

