/* Copyright 2023 CMU, Facebook, LANL, MIT, NVIDIA, and Stanford (alphabetical)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _FF_LOSS_FUNCTIONS_H_
#define _FF_LOSS_FUNCTIONS_H_

#include "op-attrs/ffconst.h"
#include "legion.h"
#include "parallel_tensor.h"
#include "op-attrs/ops/loss_functions.h"
#include "operator.h"
#include "tasks.h"

namespace FlexFlow {

LossType from_loss_type_name(std::string const &loss_type_name);

template <> TaskSignature get_signature<LOSS_BWD_TASK_ID>();
template <> void register_task<LOSS_BWD_TASK_ID>();

TaskInvocation backward_invocation(LossAttrs const &, 
                                   EnableProfiling, 
                                   parallel_tensor_guid_t logit, 
                                   parallel_tensor_guid_t label);

}

#endif