#ifndef _FLEXFLOW_RUNTIME_SRC_OPS_SIM_ENVIRONMENT_H
#define _FLEXFLOW_RUNTIME_SRC_OPS_SIM_ENVIRONMENT_H

#include "kernels/accessor.h"
#include "op-attrs/parallel_tensor_shape.h"
#include <vector>
#include "cost_metrics.h"
#include "kernels/allocation.h"

namespace FlexFlow {

struct SimEnvironment { };

struct SimEnvFactory {
  SimEnvironment new_environment() const;
};

GenericTensorAccessorW allocate_input(SimEnvironment &sim, TensorShape const &);
GenericTensorAccessorW allocate_input(SimEnvironment &sim, ParallelTensorShape const &);
std::vector<GenericTensorAccessorW> allocate_input(SimEnvironment &sim, std::vector<ParallelTensorShape> const &);

GenericTensorAccessorW allocate_weight(SimEnvironment &sim, TensorShape const &);
GenericTensorAccessorW allocate_weight(SimEnvironment &sim, ParallelTensorShape const &);
std::vector<GenericTensorAccessorW> allocate_weight(SimEnvironment &sim, std::vector<ParallelTensorShape> const &);

GenericTensorAccessorW allocate_output(SimEnvironment &sim, TensorShape const &);
GenericTensorAccessorW allocate_output(SimEnvironment &sim, ParallelTensorShape const &);
std::vector<GenericTensorAccessorW> allocate_output(SimEnvironment &sim, std::vector<ParallelTensorShape> const &);

GenericTensorAccessorW allocate_input_grad(SimEnvironment &sim, TensorShape const &);
GenericTensorAccessorW allocate_input_grad(SimEnvironment &sim, ParallelTensorShape const &);
std::vector<GenericTensorAccessorW> allocate_input_grad(SimEnvironment &sim, std::vector<ParallelTensorShape> const &);

GenericTensorAccessorW allocate_weight_grad(SimEnvironment &sim, TensorShape const &);
GenericTensorAccessorW allocate_weight_grad(SimEnvironment &sim, ParallelTensorShape const &);
std::vector<GenericTensorAccessorW> allocate_weight_grad(SimEnvironment &sim, std::vector<ParallelTensorShape> const &);

GenericTensorAccessorW allocate_output_grad(SimEnvironment &sim, TensorShape const &);
GenericTensorAccessorW allocate_output_grad(SimEnvironment &sim, ParallelTensorShape const &);
std::vector<GenericTensorAccessorW> allocate_output_grad(SimEnvironment &sim, std::vector<ParallelTensorShape> const &);


Allocator create_allocator(SimEnvironment &sim);
PerDeviceFFHandle get_ff_handle(SimEnvironment &sim);

size_t get_input_memory_usage(SimEnvironment const &);
size_t get_output_memory_usage(SimEnvironment const &);
size_t get_weights_memory_usage(SimEnvironment const &);
size_t get_op_total_memory(SimEnvironment const &);

CostMetrics make_metrics(float forward_time, float backward_time, float sync_time, SimEnvironment const &);

float default_estimate_sync_time(SimEnvironment const &);

}

#endif