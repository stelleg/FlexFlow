#ifndef _FLEXFLOW_OPS_KERNELS_ATTENTION_KERNELS_H
#define _FLEXFLOW_OPS_KERNELS_ATTENTION_KERNELS_H

#include "kernels/device.h"
#include "kernels/per_device_op_state.h"
#include "kernels/ff_handle.h"
#include "kernels/allocation.h"
#include <memory>
#include "op-attrs/ops/attention.h"

namespace FlexFlow {

class MHAPerDeviceState : public use_visitable_cmp<MHAPerDeviceState> {
public:
  MHAPerDeviceState() = delete;
  MHAPerDeviceState(PerDeviceFFHandle const &,
                    size_t weightSize,
                    size_t reserveSpaceSize,
                    ffAttnDescriptor_t attnDesc,
                    ffSeqDataDescriptor_t qDesc,
                    ffSeqDataDescriptor_t kDesc,
                    ffSeqDataDescriptor_t vDesc,
                    ffSeqDataDescriptor_t oDesc,
                    int *devQoSeqArray,
                    int *devKvSeqArray,
                    int *loWinIdx,
                    int *hiWinIdx,
                    void *reserveSpace,
                    Allocator const &allocator);
public:
  PerDeviceFFHandle handle;
  size_t weightSize;
  size_t reserveSpaceSize;
  ffAttnDescriptor_t attnDesc;
  ffSeqDataDescriptor_t qDesc;
  ffSeqDataDescriptor_t kDesc;
  ffSeqDataDescriptor_t vDesc;
  ffSeqDataDescriptor_t oDesc;
  int *devQoSeqArray;
  int *devKvSeqArray;
  int *loWinIdx;
  int *hiWinIdx;
  void *reserveSpace;
  Allocator allocator;
};


namespace Kernels {
namespace MultiHeadAttention {

MHAPerDeviceState init_kernel(PerDeviceFFHandle const &,
                              Allocator const &,
                              int num_samples,
                              int num_heads,
                              int qSize,
                              int kSize,
                              int vSize,
                              int qProjSize,
                              int kProjSize,
                              int vProjSize,
                              int oProjSize,
                              int qoSeqLength,
                              int kvSeqLength,
                              bool add_bias_kv);

void forward_kernel(ffStream_t stream,
                    MHAPerDeviceState const &device_state,
                    float const *query_ptr,
                    float const *key_ptr,
                    float const *value_ptr,
                    float const *weight_ptr,
                    float *output_ptr);

void backward_kernel(ffStream_t stream,
                     MHAPerDeviceState const &device_state,
                     float const *query_ptr,
                     float *query_grad_ptr,
                     float const *key_ptr,
                     float *key_grad_ptr,
                     float const *value_ptr,
                     float *value_grad_ptr,
                     float const *weight_ptr,
                     float *weight_grad_ptr,
                     float const *output_grad_ptr);

} 
}
}

#endif 