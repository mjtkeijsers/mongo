// Copyright 2008-2009 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_REGEXP_REGEXP_BYTECODE_GENERATOR_INL_H_
#define V8_REGEXP_REGEXP_BYTECODE_GENERATOR_INL_H_

#include "irregexp/imported/regexp-bytecode-generator.h"

#include "irregexp/imported/regexp-bytecodes.h"

namespace v8 {
namespace internal {

void RegExpBytecodeGenerator::Emit(uint32_t byte, uint32_t twenty_four_bits) {
  DCHECK(is_uint24(twenty_four_bits));
  Emit32((twenty_four_bits << BYTECODE_SHIFT) | byte);
}

void RegExpBytecodeGenerator::Emit(uint32_t byte, int32_t twenty_four_bits) {
  DCHECK(is_int24(twenty_four_bits));
  Emit32((static_cast<uint32_t>(twenty_four_bits) << BYTECODE_SHIFT) | byte);
}

void RegExpBytecodeGenerator::Emit16(uint32_t word) {
  DCHECK(pc_ <= buffer_.length());
  if (pc_ + 1 >= buffer_.length()) {
    Expand();
  }
  *reinterpret_cast<uint16_t*>(buffer_.begin() + pc_) = word;
  pc_ += 2;
}

void RegExpBytecodeGenerator::Emit8(uint32_t word) {
  DCHECK(pc_ <= buffer_.length());
  if (pc_ == buffer_.length()) {
    Expand();
  }
  *reinterpret_cast<unsigned char*>(buffer_.begin() + pc_) = word;
  pc_ += 1;
}

void RegExpBytecodeGenerator::Emit32(uint32_t word) {
  DCHECK(pc_ <= buffer_.length());
  if (pc_ + 3 >= buffer_.length()) {
    Expand();
  }
  *reinterpret_cast<uint32_t*>(buffer_.begin() + pc_) = word;
  pc_ += 4;
}

}  // namespace internal
}  // namespace v8

#endif  // V8_REGEXP_REGEXP_BYTECODE_GENERATOR_INL_H_