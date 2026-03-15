#!/bin/zsh

##
##  preview-documentation.zsh
##  image-io-framework
##
##  Created by Fang Ling on 2026/3/15.
##
##  Licensed under the Apache License, Version 2.0 (the "License");
##  you may not use this file except in compliance with the License.
##  You may obtain a copy of the License at
##
##    http://www.apache.org/licenses/LICENSE-2.0
##
##  Unless required by applicable law or agreed to in writing, software
##  distributed under the License is distributed on an "AS IS" BASIS,
##  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
##  See the License for the specific language governing permissions and
##  limitations under the License.
##

FRAMEWORK_NAME="ImageIOFramework"
SYMBOLS_FOLDER=".build/symbol-graphs"

# Extract the symbols
clang \
  -extract-api \
  --product-name=$FRAMEWORK_NAME \
  -o $SYMBOLS_FOLDER/$FRAMEWORK_NAME.symbols.json \
  -x c-header Sources/ImageIOFrameworkEssentials/*.h \
  -I . \
  -I ../foundation-framework/Sources/FoundationFrameworkEssentials/Includes \
  -isysroot $(xcrun --show-sdk-path) \
  -F $(xcrun --show-sdk-path)/System/Library/Frameworks

# Copy the FoundationFramework symbols
cp \
  ../foundation-framework/$SYMBOLS_FOLDER/FoundationFramework.symbols.json \
  $SYMBOLS_FOLDER

# Preview the documentation
$(xcrun --find docc) \
  preview \
  Sources/ImageIOFrameworkEssentials/Documentation.docc \
  -o .build/.docc-build \
  --additional-symbol-graph-dir $SYMBOLS_FOLDER
