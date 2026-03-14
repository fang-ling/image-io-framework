//
//  ImageSource.h
//  image-io-framework
//
//  Created by Fang Ling on 2026/2/12.
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

#ifndef ImageSource_h
#define ImageSource_h

#include <FoundationFramework/FoundationFramework.h>

#include "ImageProperty.h"

ASSUME_NONNULL_BEGIN

enum _ImageIO_ImageCodec {
  _ImageIO_ImageCodec_JPEG_XL
};

struct _ImageIO_ImageSource {
  struct Foundation_ObjectBase _objectBase;

  Foundation_Data _imageData;
  enum _ImageIO_ImageCodec _codec;
}
SWIFT_NAME(ImageSource)
SWIFT_SHARED_REFERENCE(ImageIO_ImageSource_Retain, ImageIO_ImageSource_Release);

/**
 * An opaque type that you use to read image data from a data object.
 *
 * Use a ``ImageIO_ImageSource`` type to read data efficiently for most image
 * file formats. The image source object manages the data buffers needed to load
 * the image data and performs any operations on that data to turn it into a
 * usable image. For example, it decompresses data stored in a compressed
 * format. You can also use an image source to fetch or create thumbnail images
 * and access metadata stored with the image.
 *
 * Create an image source object from a ``Foundation_Data`` data type. The image
 * source object reads data from the specified type and extracts the image
 * information for you.
 */
typedef const struct _ImageIO_ImageSource* ImageIO_ImageSource;

/* MARK: - Creating and Destroying an ImageIO_ImageSource Object */
/**
 * Creates an image source that reads from a Foundation data object.
 *
 * - Parameter data: The data object from which to read.
 *
 * - Returns: An image source. You're responsible for releasing this type using
 *   ``ImageIO_ImageSource_Release``.
 */
NULLABLE
ImageIO_ImageSource ImageIO_ImageSource_Initialize(Foundation_Data data)
SWIFT_NAME(ImageSource.init(data:))
SWIFT_RETURNS_RETAINED;

/**
 * Retains an image source object.
 *
 * - Parameter imageSource: The image source object to retain. This value must
 *   not be `NULL`.
 */
void ImageIO_ImageSource_Retain(ImageIO_ImageSource imageSource);

/**
 * Releases an image source object.
 *
 * If the retain count of `imageSource` becomes zero the memory allocated to the
 * object is deallocated and the object is destroyed.
 *
 * - Parameter imageSource: An image source object to release. This value must
 *   not be `NULL`.
 */
void ImageIO_ImageSource_Release(ImageIO_ImageSource imageSource);

/* MARK: - Getting Information From an ImageIO_ImageSource Object */
/**
 * Returns the property of the image source.
 *
 * - Parameter imageSource: The image source that contains the image data.
 *
 * - Returns: An image property object associated with the image source
 *   container. You're responsible for releasing this type using
 *   ``ImageIO_ImageProperty_Release``.
 */
NULLABLE
ImageIO_ImageProperty
ImageIO_ImageSource_GetImageProperty(ImageIO_ImageSource imageSource)
SWIFT_NAME(getter:ImageSource.imageProperty(self:))
SWIFT_RETURNS_RETAINED;

ASSUME_NONNULL_END

#endif /* ImageSource_h */
