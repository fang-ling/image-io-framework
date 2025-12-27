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

let package = Package(
  name: "image-io-framework",
  products: [

  ],
  targets: [
    .target(
      name: "CJPEGXL",
      dependencies: [
        "CBrotli",
        "CHighway",
        "CLittleCMS"
      ],
      exclude: [
        "libjxl/third_party",

        "libjxl/lib/jxl/enc_external_image_gbench.cc",
        "libjxl/lib/jxl/splines_gbench.cc",
        "libjxl/lib/jxl/tf_gbench.cc",

        "libjxl/lib/jxl/ac_strategy_test.cc",
        "libjxl/lib/jxl/alpha_test.cc",
        "libjxl/lib/jxl/ans_common_test.cc",
        "libjxl/lib/jxl/ans_test.cc",

        "libjxl/lib/jxl/blending_test.cc",
        "libjxl/lib/jxl/bit_reader_test.cc",
        "libjxl/lib/jxl/bits_test.cc",
        "libjxl/lib/jxl/butteraugli/butteraugli_test.cc",
        "libjxl/lib/jxl/byte_order_test.cc",
        "libjxl/lib/jxl/cms/tone_mapping_test.cc",
        "libjxl/lib/jxl/cms/transfer_functions_test.cc",
        "libjxl/lib/jxl/coeff_order_test.cc",
        "libjxl/lib/jxl/color_encoding_internal_test.cc",
        "libjxl/lib/jxl/color_management_test.cc",
        "libjxl/lib/jxl/convolve_test.cc",
        "libjxl/lib/jxl/data_parallel_test.cc",
        "libjxl/lib/jxl/dct_test.cc",
        "libjxl/lib/jxl/dec_external_image_gbench.cc",
        "libjxl/lib/jxl/decode_test.cc",
        "libjxl/lib/jxl/enc_external_image_test.cc",
        "libjxl/lib/jxl/enc_gaborish_test.cc",
        "libjxl/lib/jxl/enc_linalg_test.cc",
        "libjxl/lib/jxl/enc_optimize_test.cc",
        "libjxl/lib/jxl/enc_photon_noise_test.cc",
        "libjxl/lib/jxl/encode_test.cc",
        "libjxl/lib/jxl/entropy_coder_test.cc",
        "libjxl/lib/jxl/fast_math_test.cc",
        "libjxl/lib/jxl/fields_test.cc",
        "libjxl/lib/jxl/gamma_correct_test.cc",
        "libjxl/lib/jxl/gradient_test.cc",
        "libjxl/lib/jxl/lehmer_code_test.cc",
        "libjxl/lib/jxl/iaca_test.cc",
        "libjxl/lib/jxl/icc_codec_test.cc",
        "libjxl/lib/jxl/image_bundle_test.cc",
        "libjxl/lib/jxl/image_ops_test.cc",
        "libjxl/lib/jxl/jxl_test.cc",
        "libjxl/lib/jxl/modular_test.cc",
        "libjxl/lib/jxl/opsin_image_test.cc",
        "libjxl/lib/jxl/opsin_inverse_test.cc",
        "libjxl/lib/jxl/padded_bytes_test.cc",
        "libjxl/lib/jxl/passes_test.cc",
        "libjxl/lib/jxl/patch_dictionary_test.cc",
        "libjxl/lib/jxl/preview_test.cc",
        "libjxl/lib/jxl/quant_weights_test.cc",
        "libjxl/lib/jxl/quantizer_test.cc",
        "libjxl/lib/jxl/rational_polynomial_test.cc",
        "libjxl/lib/jxl/render_pipeline/render_pipeline_test.cc",
        "libjxl/lib/jxl/roundtrip_test.cc",
        "libjxl/lib/jxl/simd_util_test.cc",
        "libjxl/lib/jxl/speed_tier_test.cc",
        "libjxl/lib/jxl/splines_test.cc",
        "libjxl/lib/threads/thread_parallel_runner_test.cc",
        "libjxl/lib/jxl/toc_test.cc",
        "libjxl/lib/jxl/xorshift128plus_test.cc",

        "libjxl/lib/jxl/test_image.cc",
        "libjxl/lib/jxl/test_utils.cc",

        "libjxl/lib/jxl/jxl.syms",
        "libjxl/lib/jxl/jxl.version",
        "libjxl/lib/jxl/jxl_osx.syms",
        "libjxl/lib/jxl/libjxl.pc.in",
        "libjxl/lib/jxl/libjxl_cms.pc.in",
        "libjxl/lib/jxl/version.h.in",
        "libjxl/lib/threads/libjxl_threads.pc.in"
      ],
      sources: [
        "libjxl/lib/jxl",
        "libjxl/lib/threads"
      ],
      publicHeadersPath: "libjxl/lib/include",
      cSettings: [
        .headerSearchPath("libjxl"),
        .headerSearchPath("extra")
      ]
    ),
    .target(
      name: "CBrotli",
      path: "Sources/CJPEGXL/libjxl/third_party/brotli/c",
      exclude: ["fuzz", "tools"],
      publicHeadersPath: "include"
    ),
    .target(
      name: "CHighway",
      path: "Sources/CJPEGXL/libjxl/third_party/highway",
      exclude: [
        "hwy/contrib",
        "hwy/examples",
        "hwy/tests",
        "hwy/abort_test.cc",
        "hwy/aligned_allocator_test.cc",
        "hwy/base_test.cc",
        "hwy/bit_set_test.cc",
        "hwy/highway_test.cc",
        "hwy/nanobenchmark_test.cc",
        "hwy/targets_test.cc"
      ],
      publicHeadersPath: "."
    ),
    .target(
      name: "CLittleCMS",
      path: "Sources/CJPEGXL/libjxl/third_party/lcms",
      exclude: [
        "Projects",
        "testbed",
        "utils"
      ]
    )
  ]
)
