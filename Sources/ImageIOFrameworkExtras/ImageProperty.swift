//
//  ImageProperty.swift
//  image-io-framework
//
//  Created by Fang Ling on 2026/2/14.
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

/* MARK: - Creating and Destroying an ImageProperty Object */
public class ImageProperty {
  private let _imageProperty: ImageIO_ImageProperty

  public init() {
    _imageProperty = ImageIO_ImageProperty_Initialize()
  }

  public init(cImageProperty: ImageIO_ImageProperty) {
    _imageProperty = cImageProperty
  }

  deinit {
    ImageIO_ImageProperty_Release(_imageProperty)
  }
}

/* MARK: - Examining an ImageProperty Object */
extension ImageProperty {
  public var width: UnsignedInteger64 {
    ImageIO_ImageProperty_GetWidth(_imageProperty)
  }

  public var height: UnsignedInteger64 {
    ImageIO_ImageProperty_GetHeight(_imageProperty)
  }
}
