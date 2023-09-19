/* 
 * File:   bitmaps.h
 * Author: torsten.roemer@luniks.net
 *
 * Created on 16. April 2023, 18:19
 */

#ifndef BITMAPS_H
#define BITMAPS_H

#include <stdint.h>
#include "types.h"

#define TUX 0
#define LINUS 1
#define PHOTO 2

/**
 * A bitmap with its width and height, and data.
 */
typedef struct {
    /** Width of the bitmap, must be a multiple of 8. */
    const width_t width;
    /** Height of the bitmap, must be a multiple of 8. */
    const height_t height;
    /** The actual bitmap. */
    const __flash uint8_t *bitmap;
} Bitmap;

/**
 * Available bitmaps.
 */
extern const __flash Bitmap bitmaps[];

#endif /* BITMAPS_H */

