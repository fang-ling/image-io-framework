// swift-tools-version: 6.2

//
//  Package.swift
//  image-io-framework
//
//  Created by Fang Ling on 2025/12/27.
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

import PackageDescription

let dependencies = [
  ("../foundation-framework"),
  ("../swift-exif"),
  ("../swift-jpeg-xl")
]

let package = Package(
  name: "image-io-framework",
  products: [
    .library(name: "ImageIOFramework", targets: ["ImageIOFramework"])
  ],
  dependencies: dependencies.map({ .package(path: $0) }),
  targets: [
    .target(
      name: "ImageIOFramework",
      dependencies: [
        "ImageIOFrameworkEssentials",
        "ImageIOFrameworkExtras"
      ]
    ),
    .target(
      name: "ImageIOFrameworkEssentials",
      dependencies: [
        .product(name: "CEXIF", package: "swift-exif"),
        .product(name: "CJPEGXL", package: "swift-jpeg-xl"),
        .product(
          name: "FoundationFramework",
          package: "foundation-framework"
        )
      ],
      publicHeadersPath: "Includes"
    ),
    .target(
      name: "ImageIOFrameworkExtras",
      dependencies: ["ImageIOFrameworkEssentials"]
    ),
    .testTarget(
      name: "ImageIOFrameworkTests",
      dependencies: [
        "ImageIOFramework"
      ]
    )
  ]
)
