//
//  ImageProperties.c
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

#include "ImageProperty.h"

#include <stdlib.h>

struct _ImageIO_ImageProperty {
  struct Foundation_ObjectBase _objectBase;

  Foundation_UnsignedInteger64 _width;
  Foundation_UnsignedInteger64 _height;
};

ImageIO_ImageProperty ImageIO_ImageProperty_Initialize() {
  let objectSize = sizeof(struct _ImageIO_ImageProperty);
  let imageProperty = (struct _ImageIO_ImageProperty*)malloc(objectSize);
  if (!imageProperty) {
    return NULL;
  }
  imageProperty->_objectBase.retainCount = 1;

  imageProperty->_width = 0;
  imageProperty->_height = 0;

  return imageProperty;
}

void ImageIO_ImageProperty_Retain(ImageIO_ImageProperty imageProperty) {
  Foundation_ObjectBase_Retain(&imageProperty->_objectBase);
}

void ImageIO_ImageProperty_Release(ImageIO_ImageProperty imageProperty) {
  let shouldDeallocate =
    Foundation_ObjectBase_Release(&imageProperty->_objectBase);

  if (shouldDeallocate) {
    free(imageProperty);
  }
}

Foundation_UnsignedInteger64
ImageIO_ImageProperty_GetWidth(ImageIO_ImageProperty imageProperty) {
  ImageIO_ImageProperty_Retain(imageProperty);

  let width = imageProperty->_width;

  ImageIO_ImageProperty_Release(imageProperty);
  return width;
}

Foundation_UnsignedInteger64
ImageIO_ImageProperty_GetHeight(ImageIO_ImageProperty imageProperty) {
  ImageIO_ImageProperty_Retain(imageProperty);

  let height = imageProperty->_height;

  ImageIO_ImageProperty_Release(imageProperty);
  return height;
}

void _ImageIO_ImageProperty_SetWidth(ImageIO_ImageProperty imageProperty,
                                     Foundation_UnsignedInteger64 width) {
  ImageIO_ImageProperty_Retain(imageProperty);

  imageProperty->_width = width;

  ImageIO_ImageProperty_Release(imageProperty);
}

void _ImageIO_ImageProperty_SetHeight(ImageIO_ImageProperty imageProperty,
                                      Foundation_UnsignedInteger64 height) {
  ImageIO_ImageProperty_Retain(imageProperty);

  imageProperty->_height = height;

  ImageIO_ImageProperty_Release(imageProperty);
}
