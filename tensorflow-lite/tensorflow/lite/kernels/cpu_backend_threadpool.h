/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

/* File modified by NXP. Changes are described in file
   /middleware/eiq/tensorflow-lite/readme.txt in section "Release notes" */

#ifndef TENSORFLOW_LITE_KERNELS_CPU_BACKEND_THREADPOOL_H_
#define TENSORFLOW_LITE_KERNELS_CPU_BACKEND_THREADPOOL_H_

#include "tensorflow/lite/kernels/cpu_backend_context.h"
#include "tensorflow/lite/kernels/internal/compatibility.h"

#ifdef TFLITE_WITH_RUY
#include "tensorflow/lite/experimental/ruy/context.h"
#include "tensorflow/lite/experimental/ruy/thread_pool.h"
#else
#include "public/gemmlowp.h"
#endif

namespace tflite {
namespace cpu_backend_threadpool {

#ifdef TFLITE_WITH_RUY

using Task = ruy::Task;

template <typename TaskType>
void Execute(int tasks_count, TaskType* tasks,
             CpuBackendContext* cpu_backend_context) {
  TFLITE_DCHECK_LE(tasks_count, cpu_backend_context->max_num_threads());
  cpu_backend_context->ruy_context()->workers_pool.Execute(tasks_count, tasks);
}

// not TFLITE_WITH_RUY
#elif defined TFLITE_MCU

// A workload for a worker.
struct Task {
  Task(){};
  virtual ~Task() {}
  virtual void Run() = 0;
};

#else //TFLITE_MCU

using Task = gemmlowp::Task;

template <typename TaskType>
void Execute(int tasks_count, TaskType* tasks,
             CpuBackendContext* cpu_backend_context) {
  TFLITE_DCHECK_LE(tasks_count, cpu_backend_context->max_num_threads());
  cpu_backend_context->gemmlowp_context()->workers_pool()->Execute(tasks_count,
                                                                   tasks);
}

#endif

}  // namespace cpu_backend_threadpool
}  // namespace tflite

#endif  // TENSORFLOW_LITE_KERNELS_CPU_BACKEND_THREADPOOL_H_
