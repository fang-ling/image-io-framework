//
//  ImageMetadata.c
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

#include "ImageMetadata.h"

#include <libexif/exif-data.h>
#include <stdlib.h>

ASSUME_NONNULL_BEGIN

NULLABLE ImageIO_ImageMetadata
ImageIO_ImageMetadata_Initialize(Foundation_UnsignedInteger64 width,
                                 Foundation_UnsignedInteger64 height,
                                 NULLABLE Foundation_Data exifData) {
  var dateTimeOriginal = (Foundation_String)NULL;
  if (exifData) {
    Foundation_Data_Retain(exifData);

    let exifDataBytes = Foundation_Data_GetBytes(exifData);
    let exifDataCount = Foundation_Data_GetCount(exifData);
    let exif = exif_data_new_from_data(
      exifDataBytes,
      (Foundation_UnsignedInteger32)exifDataCount
    );

    if (exif) {
      let entry = exif_content_get_entry(exif->ifd[EXIF_IFD_EXIF],
                                         EXIF_TAG_DATE_TIME_ORIGINAL);
      if (entry) {
        dateTimeOriginal = Foundation_String_InitializeWithCString(
          (Foundation_CString)entry->data
        );
      }

      exif_data_unref(exif);
    }

    Foundation_Data_Release(exifData);
  }

  let objectSize = sizeof(struct _ImageIO_ImageMetadata);
  let imageMetadata = (struct _ImageIO_ImageMetadata*)malloc(objectSize);
  imageMetadata->_objectBase.retainCount = 1;

  imageMetadata->_width = width;
  imageMetadata->_height = height;
  imageMetadata->_exifDateTimeOriginal = dateTimeOriginal;

  return imageMetadata;
}

void ImageIO_ImageMetadata_Retain(ImageIO_ImageMetadata imageMetadata) {
  Foundation_ObjectBase_Retain(&imageMetadata->_objectBase);
}

void ImageIO_ImageMetadata_Release(ImageIO_ImageMetadata imageMetadata) {
  let shouldDeallocate =
    Foundation_ObjectBase_Release(&imageMetadata->_objectBase);

  if (shouldDeallocate) {
    if (imageMetadata->_exifDateTimeOriginal != NULL) {
      Foundation_String_Release(imageMetadata->_exifDateTimeOriginal);
    }
    free((struct _ImageIO_ImageMetadata*)imageMetadata);
  }
}

Foundation_UnsignedInteger64
ImageIO_ImageMetadata_GetWidth(ImageIO_ImageMetadata imageMetadata) {
  ImageIO_ImageMetadata_Retain(imageMetadata);

  let width = imageMetadata->_width;

  ImageIO_ImageMetadata_Release(imageMetadata);
  return width;
}

Foundation_UnsignedInteger64
ImageIO_ImageMetadata_GetHeight(ImageIO_ImageMetadata imageMetadata) {
  ImageIO_ImageMetadata_Retain(imageMetadata);

  let height = imageMetadata->_height;

  ImageIO_ImageMetadata_Release(imageMetadata);
  return height;
}

NULLABLE Foundation_String
ImageIO_ImageMetadata_GetEXIFDateTimeOriginal(
  ImageIO_ImageMetadata imageMetadata
) {
  ImageIO_ImageMetadata_Retain(imageMetadata);

  let exifDateTimeOriginal = imageMetadata->_exifDateTimeOriginal;

  ImageIO_ImageMetadata_Release(imageMetadata);
  return exifDateTimeOriginal;
}

ASSUME_NONNULL_END
