/*
 * Copyright (c) Meta Platforms, Inc. and affiliates.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree.
 */

#include <executorch/kernels/test/FunctionHeaderWrapper.h> // Declares the operator
#include <executorch/kernels/test/TestUtil.h>
#include <executorch/runtime/core/exec_aten/exec_aten.h>
#include <executorch/runtime/core/exec_aten/testing_util/tensor_factory.h>
#include <executorch/runtime/core/exec_aten/testing_util/tensor_util.h>

#include <gtest/gtest.h>

using namespace ::testing;
using executorch::aten::Scalar;
using executorch::aten::ScalarType;
using executorch::aten::Tensor;
using torch::executor::testing::TensorFactory;

class OpRemainderOutTest : public OperatorTest {
 protected:
  Tensor& op_remainder_tensor_out(
      const Tensor& self,
      const Tensor& other,
      Tensor& out) {
    return torch::executor::aten::remainder_outf(context_, self, other, out);
  }

  Tensor& op_remainder_scalar_out(
      const Tensor& self,
      const Scalar& other,
      Tensor& out) {
    return torch::executor::aten::remainder_outf(context_, self, other, out);
  }
};

TEST_F(OpRemainderOutTest, SmokeTest) {
  TensorFactory<ScalarType::Long> tfDouble;
  TensorFactory<ScalarType::Long> tfLong;
  TensorFactory<ScalarType::Int> tfInt;

  Tensor self = tfLong.full({2, 2}, 46);
  Tensor other = tfInt.full({2, 2}, 4);
  Tensor out = tfDouble.zeros({2, 2});
  Tensor out_expected = tfDouble.full({2, 2}, 2.0);
  op_remainder_tensor_out(self, other, out);
  EXPECT_TENSOR_CLOSE(out, out_expected);
}
