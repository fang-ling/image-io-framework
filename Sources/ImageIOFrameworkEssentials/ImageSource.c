//
//  ImageSource.c
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

#include "ImageSource.h"

#include <jxl/decode.h>
#include <stdlib.h>
#include <string.h>

#pragma clang assume_nonnull begin

NULLABLE
ImageIO_ImageSource ImageIO_ImageSource_Initialize(Foundation_Data data) {
  Foundation_Data_Retain(data);

  let objectSize = sizeof(struct _ImageIO_ImageSource);
  let imageSource = (struct _ImageIO_ImageSource*)malloc(objectSize);
  imageSource->_objectBase.retainCount = 1;

  let bytes = Foundation_Data_GetBytes(data);
  let count = Foundation_Data_GetCount(data);

  if (JxlSignatureCheck(bytes, count) == JXL_SIG_CONTAINER) { /* JPEG-XL */
    imageSource->_codec = _ImageIO_ImageCodec_JPEG_XL;
  } else { /* Unsupported codec */
    Foundation_Data_Release(data);

    return NULL;
  }

  imageSource->_imageByteCount = count;
  imageSource->_imageBytes = malloc(count);
  memcpy(imageSource->_imageBytes, bytes, count);

  Foundation_Data_Release(data);
  return imageSource;
}

void ImageIO_ImageSource_Retain(ImageIO_ImageSource imageSource) {
  Foundation_ObjectBase_Retain(&imageSource->_objectBase);
}

void ImageIO_ImageSource_Release(ImageIO_ImageSource imageSource) {
  let shouldDeallocate =
    Foundation_ObjectBase_Release(&imageSource->_objectBase);

  if (shouldDeallocate) {
    free(imageSource->_imageBytes);
    free(imageSource);

    imageSource = NULL;
  }
}

NULLABLE
ImageIO_ImageProperty
ImageIO_ImageSource_GetImageProperty(ImageIO_ImageSource imageSource) {
  ImageIO_ImageSource_Retain(imageSource);

  var width = 0ull;
  var height = 0ull;

  if (imageSource->_codec == _ImageIO_ImageCodec_JPEG_XL) { /* JPEG-XL */
    let decoder = JxlDecoderCreate(NULL);
    if (JXL_DEC_SUCCESS != JxlDecoderSubscribeEvents(decoder,
                                                     JXL_DEC_BASIC_INFO)) {
      goto errorHandler;
    }

    JxlBasicInfo info;

    JxlDecoderSetInput(decoder,
                       imageSource->_imageBytes,
                       imageSource->_imageByteCount);
    JxlDecoderCloseInput(decoder);

    while (true) {
      let status = JxlDecoderProcessInput(decoder);

      if (status == JXL_DEC_ERROR) {
        goto errorHandler;
      } else if (status == JXL_DEC_NEED_MORE_INPUT) {
        goto errorHandler;
      } else if (status == JXL_DEC_BASIC_INFO) {
        if (JxlDecoderGetBasicInfo(decoder, &info) != JXL_DEC_SUCCESS) {
          goto errorHandler;
        }

        width = info.xsize;
        height = info.ysize;
      } else if (status == JXL_DEC_SUCCESS) {
        break;
      } else {
        goto errorHandler;
      }
    }
  } else { /* Unsupported codec */
    goto errorHandler;
  }


  let imageProperty = ImageIO_ImageProperty_Initialize();
  _ImageIO_ImageProperty_SetWidth(imageProperty, width);
  _ImageIO_ImageProperty_SetHeight(imageProperty, height);

  ImageIO_ImageSource_Release(imageSource);
  return imageProperty;

  errorHandler: {
    ImageIO_ImageSource_Release(imageSource);
    return NULL;
  }
}

#pragma clang assume_nonnull end
