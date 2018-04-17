// Copyright 2018 Xiaomi, Inc.  All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "mace/public/mace_runtime.h"
#include "mace/core/runtime/cpu/cpu_runtime.h"
#include "mace/core/runtime/opencl/opencl_runtime.h"

namespace mace {

std::shared_ptr<KVStorageFactory> kStorageFactory = nullptr;

void SetGPUHints(GPUPerfHint gpu_perf_hint, GPUPriorityHint gpu_priority_hint) {
  VLOG(1) << "Set GPU configurations, gpu_perf_hint: " << gpu_perf_hint
          << ", gpu_priority_hint: " << gpu_priority_hint;
  OpenCLRuntime::Configure(gpu_perf_hint, gpu_priority_hint);
}

void SetKVStorageFactory(std::shared_ptr<KVStorageFactory> storage_factory) {
  VLOG(1) << "Set internal KV Storage Engine";
  kStorageFactory = storage_factory;
}

MaceStatus SetOpenMPThreadPolicy(int num_threads_hint,
                                 CPUAffinityPolicy policy) {
  VLOG(1) << "Set CPU openmp num_threads_hint: " << num_threads_hint
          << ", affinity policy: " << policy;
  return SetOpenMPThreadsAndAffinityPolicy(num_threads_hint, policy);
}

void SetOpenMPThreadAffinity(int num_threads, const std::vector<int> &cpu_ids) {
  return SetOpenMPThreadsAndAffinityCPUs(num_threads, cpu_ids);
}

MaceStatus GetBigLittleCoreIDs(std::vector<int> *big_core_ids,
                               std::vector<int> *little_core_ids) {
  return GetCPUBigLittleCoreIDs(big_core_ids, little_core_ids);
}

};  // namespace mace
