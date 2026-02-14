//
//  ImageProperty.h
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

#ifndef ImageProperty_h
#define ImageProperty_h

#include <FoundationFramework/FoundationFramework.h>

struct _ImageIO_ImageProperty;

typedef struct _ImageIO_ImageProperty* ImageIO_ImageProperty;

/* MARK: - Creating and Destroying an ImageIO_ImageProperty Object */
/**
 * Creates a new image property.
 *
 * - Returns: An image property. You're responsible for releasing this type
 *   using ``ImageIO_ImageProperty_Release``.
 */
ImageIO_ImageProperty ImageIO_ImageProperty_Initialize();

/**
 * Retains an image property object.
 *
 * - Parameter imageProperty: The image property object to retain. This value
 *   must not be `NULL`.
 */
void ImageIO_ImageProperty_Retain(ImageIO_ImageProperty imageProperty);

/**
 * Releases an image property object.
 *
 * If the retain count of `imageProperty` becomes zero the memory allocated to
 * the object is deallocated and the object is destroyed.
 *
 * - Parameter imageProperty: An image property object to release. This value
 *   must not be `NULL`.
 */
void ImageIO_ImageProperty_Release(ImageIO_ImageProperty imageProperty);

/* MARK: - Examining an ImageIO_ImageProperty Object */
/**
 * Returns the width of the image, in the image's coordinate space.
 *
 * - Parameter imageProperty: The image property object to examine.
 *
 * - Returns: An integer that specifies the width of the image.
 */
Foundation_UnsignedInteger64
ImageIO_ImageProperty_GetWidth(ImageIO_ImageProperty imageProperty);

/**
 * Returns the height of the image, in the image's coordinate space.
 *
 * - Parameter imageProperty: The image property object to examine.
 *
 * - Returns: An integer that specifies the height of the image.
 */
Foundation_UnsignedInteger64
ImageIO_ImageProperty_GetHeight(ImageIO_ImageProperty imageProperty);

/* MARK: - Modifying an ImageIO_ImageProperty Object (Internal) */
void _ImageIO_ImageProperty_SetWidth(ImageIO_ImageProperty imageProperty,
                                     Foundation_UnsignedInteger64 width);

void _ImageIO_ImageProperty_SetHeight(ImageIO_ImageProperty imageProperty,
                                      Foundation_UnsignedInteger64 height);

#endif /* ImageProperty_h */
