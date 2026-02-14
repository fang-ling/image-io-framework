//
//  ImageSource.swift
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

import FoundationFramework
import ImageIOFrameworkEssentials

/* MARK: - Creating and Destroying an ImageSource Object */
public class ImageSource {
  private let _imageSource: ImageIO_ImageSource

  public init(data: Data) {
    _imageSource = ImageIO_ImageSource_Initialize(data.cData)
  }

  deinit {
    ImageIO_ImageSource_Release(_imageSource)
  }
}

/* MARK: - Getting Information From an ImageSource Object */
extension ImageSource {
  public var imageProperty: ImageProperty? {
    guard let cImageProperty = ImageIO_ImageSource_CopyProperty(
      _imageSource
    ) else {
      return nil
    }

    return .init(cImageProperty: cImageProperty)
  }
}
