/*
 * Copyright (C) 2018 Arm Limited or its affiliates. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __KWS_MFCC_H__
#define __KWS_MFCC_H__

#include "mfcc.h"

#define SAMP_FREQ 44100
#define MFCC_DEC_BITS 1
#define FRAME_SHIFT_MS 10
#define FRAME_SHIFT ((int16_t)(SAMP_FREQ * 0.001 * FRAME_SHIFT_MS))
#define NUM_FRAMES 249
#define NUM_MFCC_COEFFS 13
#define MFCC_BUFFER_SIZE (NUM_FRAMES*NUM_MFCC_COEFFS)
#define FRAME_LEN_MS 25
#define FRAME_LEN ((int16_t)(SAMP_FREQ * 0.001 * FRAME_LEN_MS))

class KWS_MFCC
{
public:  
  KWS_MFCC(float* audio_data_buffer);
  KWS_MFCC(int record_win);
  ~KWS_MFCC();
  void extract_features();
  float* audio_buffer;
  float *mfcc_buffer;
  int num_frames;
  int num_mfcc_features;
  int frame_len;
  int frame_shift;
  int audio_block_size;
  int audio_buffer_size;

protected:
  void init_mfcc();
  MFCC *mfcc;
  int mfcc_buffer_size;
  int recording_win;
};

#endif
