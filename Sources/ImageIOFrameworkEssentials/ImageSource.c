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

#include <libexif/exif-data.h>
#include <jxl/decode.h>
#include <stdlib.h>
#include <string.h>

ASSUME_NONNULL_BEGIN

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

  imageSource->_imageData = data;

  return imageSource;
}

void ImageIO_ImageSource_Retain(ImageIO_ImageSource imageSource) {
  Foundation_ObjectBase_Retain(&imageSource->_objectBase);
}

void ImageIO_ImageSource_Release(ImageIO_ImageSource imageSource) {
  let shouldDeallocate =
    Foundation_ObjectBase_Release(&imageSource->_objectBase);

  if (shouldDeallocate) {
    Foundation_Data_Release(imageSource->_imageData);
    free((struct _ImageIO_ImageSource*)imageSource);
  }
}

NULLABLE
ImageIO_ImageProperty
ImageIO_ImageSource_GetImageProperty(ImageIO_ImageSource imageSource) {
  ImageIO_ImageSource_Retain(imageSource);

  var jxlDecoder = (JxlDecoder*)NULL;

  var width = 0ull;
  var height = 0ull;
  var exifDataBuffer = (Foundation_UnsignedInteger8*)NULL;
  var exifDataBufferSize = 0u;

  /* Decode metadata */
  if (imageSource->_codec == _ImageIO_ImageCodec_JPEG_XL) { /* JPEG-XL */
    jxlDecoder = JxlDecoderCreate(NULL);
    let events = JXL_DEC_BASIC_INFO | JXL_DEC_BOX;
    if (JXL_DEC_SUCCESS != JxlDecoderSubscribeEvents(jxlDecoder, events)) {
      goto errorHandler;
    }

    /* Enable decompression of brotli-compressed boxes. */
    JxlDecoderSetDecompressBoxes(jxlDecoder, true);
    JxlDecoderSetInput(jxlDecoder,
                       Foundation_Data_GetBytes(imageSource->_imageData),
                       Foundation_Data_GetCount(imageSource->_imageData));
    JxlDecoderCloseInput(jxlDecoder);

    var info = (JxlBasicInfo){ 0 };
    var exifBoxOutputOffset = 0ull;

    while (true) {
      let status = JxlDecoderProcessInput(jxlDecoder);

      if (status == JXL_DEC_ERROR) {
        goto errorHandler;
      } else if (status == JXL_DEC_NEED_MORE_INPUT) {
        goto errorHandler;
      } else if (status == JXL_DEC_BASIC_INFO) {
        if (JxlDecoderGetBasicInfo(jxlDecoder, &info) != JXL_DEC_SUCCESS) {
          goto errorHandler;
        }

        width = info.xsize;
        height = info.ysize;
      } else if (status == JXL_DEC_SUCCESS) {
        break;
      } else if (status == JXL_DEC_BOX) {
        /* Flush previous exif box if one was being filled */
        if (exifDataBufferSize > 0) {
          var remaining = JxlDecoderReleaseBoxBuffer(jxlDecoder);
          exifDataBufferSize -= remaining;
          /* We already have a complete exif box; stop decoding more boxes */
          break;
        }

        /* Check the 4-byte box type */
        var boxType = (JxlBoxType){ 0 };
        if (
          JXL_DEC_SUCCESS != JxlDecoderGetBoxType(jxlDecoder, boxType, true)
        ) {
          goto errorHandler;
        }
        if (memcmp(boxType, "Exif", 4) == 0) {
          exifBoxOutputOffset = 0;
          exifDataBufferSize = 4096;
          exifDataBuffer = malloc(exifDataBufferSize); /* First allocation */
          /* Hand the decoder our grow-able buffer */
          JxlDecoderSetBoxBuffer(jxlDecoder,
                                 exifDataBuffer,
                                 exifDataBufferSize);
        }
      } else if (status == JXL_DEC_BOX_NEED_MORE_OUTPUT) {
        /* Buffer too small */
        let remaining = JxlDecoderReleaseBoxBuffer(jxlDecoder);
        exifBoxOutputOffset = exifDataBufferSize - remaining;
        exifDataBufferSize += 4096;
        exifDataBuffer = realloc(exifDataBuffer, exifDataBufferSize);

        JxlDecoderSetBoxBuffer(jxlDecoder,
                               exifDataBuffer + exifBoxOutputOffset,
                               exifDataBufferSize - exifBoxOutputOffset);
      } else if (status == JXL_DEC_BOX_COMPLETE) {
        if (exifDataBufferSize > 0) {
          let remaining = JxlDecoderReleaseBoxBuffer(jxlDecoder);
          exifDataBufferSize -= remaining;
          break;
        }
      } else {
        goto errorHandler;
      }
    }

    JxlDecoderDestroy(jxlDecoder);
  } else { /* Unsupported codec */
    goto errorHandler;
  }

  /* Extract from exif */
  var dateTimeOriginal = (Foundation_CString)NULL;
  if (exifDataBufferSize > 4) {
    /*
     * The JXL exif box payload starts with a 4-byte offset (big-endian) that
     * indicates where the actual TIFF/Exif data begins within the box.
     */
    let tiffBlob = exifDataBuffer + 4;
    let tiffBlobSize = exifDataBufferSize - 4;

    /*
     * libexif requires the "Exif\0\0" APP1 magic prefix to recognize the buffer
     */
    let wrappedSize  = 6 + tiffBlobSize;
    let wrapped = malloc(wrappedSize);

    memcpy(wrapped, "Exif\0\0", 6);
    memcpy(wrapped + 6, tiffBlob, tiffBlobSize);

    let exifData = exif_data_new_from_data(wrapped, wrappedSize);
    free(wrapped);

    if (exifData) {
      let entry = exif_content_get_entry(exifData->ifd[EXIF_IFD_EXIF],
                                         EXIF_TAG_DATE_TIME_ORIGINAL);

      if (entry) {
        dateTimeOriginal = strndup((Foundation_CString)entry->data,
                                   entry->size);
      }

      exif_data_unref(exifData);
    }
  }

  let imageProperty = ImageIO_ImageProperty_Initialize(
    width,
    height,
    dateTimeOriginal == NULL
      ? NULL
      : Foundation_String_InitializeWithCString(dateTimeOriginal)
  );

  if (exifDataBuffer != NULL) {
    free(exifDataBuffer);
  }
  if (dateTimeOriginal != NULL) {
    free((void*)dateTimeOriginal);
  }
  ImageIO_ImageSource_Release(imageSource);
  return imageProperty;

  errorHandler: {
    if (exifDataBuffer != NULL) {
      free(exifDataBuffer);
    }
    if (jxlDecoder != NULL) {
      JxlDecoderDestroy(jxlDecoder);
    }
    ImageIO_ImageSource_Release(imageSource);

    return NULL;
  }
}

ASSUME_NONNULL_END
