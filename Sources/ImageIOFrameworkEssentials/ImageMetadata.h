//
//  ImageMetadata.h
//  image-io-framework
//
//  Created by Fang Ling on 2026/2/13.
//
//  Licensed under the Apache License, Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing, software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef ImageMetadata_h
#define ImageMetadata_h

#include <FoundationFramework/FoundationFramework.h>

ASSUME_NONNULL_BEGIN

struct _ImageIO_ImageMetadata {
  struct Foundation_ObjectBase _objectBase;

  Foundation_UnsignedInteger64 _width;
  Foundation_UnsignedInteger64 _height;
  NULLABLE Foundation_String _exifDateTimeOriginal;
}
SWIFT_NAME(ImageMetadata)
SWIFT_SHARED_REFERENCE(ImageIO_ImageMetadata_Retain,
                       ImageIO_ImageMetadata_Release);

/**
 * An immutable object that contains the metadata associated with an image.
 *
 * A ``ImageIO_ImageMetadata`` object stores the metadata associated with an
 * image. Create this object from your image’s associated metadata data, and use
 * it to fetch individual metadata tags.
 *
 * ## Topics
 *
 * ### Creating and Destroying an ImageIO_ImageMetadata Object
 *
 * - ``ImageIO_ImageMetadata_Initialize``
 * - ``ImageIO_ImageMetadata_Retain``
 * - ``ImageIO_ImageMetadata_Release``
 *
 * ### Examining an ImageIO_ImageMetadata Object
 *
 * - ``ImageIO_ImageMetadata_GetWidth``
 * - ``ImageIO_ImageMetadata_GetHeight``
 * - ``ImageIO_ImageMetadata_GetEXIFDateTimeOriginal``
 */
typedef const struct _ImageIO_ImageMetadata* ImageIO_ImageMetadata;

/* MARK: - Creating and Destroying an ImageIO_ImageMetadata Object */
/**
 * Creates a collection of metadata tags from the specified metadata.
 *
 * Use this function to parse the raw metadata from an image and build a
 * parseable set of metadata tags.
 *
 * - Parameters:
 *   - width: The width of the image, in the image's coordinate space.
 *   - height: The height of the image, in the image's coordinate space.
 *   - exifData: An optional object containing EXIF data. The EXIF data must
 *     include the packet header -- "Exif\0\0".
 *
 * - Returns: A ``ImageIO_ImageMetadata`` object that contains the parsed
 *   metadata information, or `NULL` if an error occurs. You're responsible for
 *   releasing this type using ``ImageIO_ImageMetadata_Release``.
 */
NULLABLE ImageIO_ImageMetadata
ImageIO_ImageMetadata_Initialize(Foundation_UnsignedInteger64 width,
                                 Foundation_UnsignedInteger64 height,
                                 NULLABLE Foundation_Data exifData)
SWIFT_NAME(ImageMetadata.init(width:height:exifData:))
SWIFT_RETURNS_RETAINED;

/**
 * Retains an image metadata object.
 *
 * - Parameter imageMetadata: The image metadata object to retain. This value
 *   must not be `NULL`.
 */
void ImageIO_ImageMetadata_Retain(ImageIO_ImageMetadata imageMetadata);

/**
 * Releases an image metadata object.
 *
 * If the retain count of `imageMetadata` becomes zero the memory allocated to
 * the object is deallocated and the object is destroyed.
 *
 * - Parameter imageMetadata: An image metadata object to release. This value
 *   must not be `NULL`.
 */
void ImageIO_ImageMetadata_Release(ImageIO_ImageMetadata imageMetadata);

/* MARK: - Examining an ImageIO_ImageMetadata Object */
/**
 * Returns the width of the image, in the image's coordinate space.
 *
 * - Parameter imageMetadata: The image metadata object to examine.
 *
 * - Returns: An integer that specifies the width of the image.
 */
Foundation_UnsignedInteger64
ImageIO_ImageMetadata_GetWidth(ImageIO_ImageMetadata imageMetadata)
SWIFT_NAME(getter:ImageMetadata.width(self:));

/**
 * Returns the height of the image, in the image's coordinate space.
 *
 * - Parameter imageMetadata: The image metadata object to examine.
 *
 * - Returns: An integer that specifies the height of the image.
 */
Foundation_UnsignedInteger64
ImageIO_ImageMetadata_GetHeight(ImageIO_ImageMetadata imageMetadata)
SWIFT_NAME(getter:ImageMetadata.height(self:));

/**
 * Returns the original date and time.
 *
 * - Parameter imageMetadata: The image metadata object to examine.
 *
 * - Returns: A string that specifies the original date and time.
 */
NULLABLE Foundation_String
ImageIO_ImageMetadata_GetEXIFDateTimeOriginal(
  ImageIO_ImageMetadata imageMetadata
)
SWIFT_NAME(getter:ImageMetadata.exifDateTimeOriginal(self:));

ASSUME_NONNULL_END

#endif /* ImageMetadata_h */
