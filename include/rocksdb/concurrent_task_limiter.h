//  Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).
//
// Copyright (c) 2011 The LevelDB Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file. See the AUTHORS file for names of contributors.

#pragma once

#include "rocksdb/env.h"
#include "rocksdb/statistics.h"

namespace rocksdb {

class ConcurrentTaskLimiter {
 public:

  virtual ~ConcurrentTaskLimiter() {}

  virtual const std::string& GetName() const = 0;

  virtual void SetMaxOutstandingTask(int32_t limit) = 0;

  virtual void ResetMaxOutstandingTask() = 0;
  
  virtual int32_t GetOutstandingTask() const = 0;

  virtual bool GetToken(bool force, int32_t& tasks) = 0;

  virtual void ReturnToken(int32_t& tasks) = 0;
};

// Create a ConcurrentTaskLimiter that can be shared with mulitple CFs
// across RocksDB instances to control concurrent tasks.
//
// @param env: Pointer to Env object, please see "rocksdb/env.h".
// @param info_log: If not nullptr, info_log will be used to log errors.
//
// @param name: Name of the limiter.
// @param limit: max concurrent tasks. 
//        limit = 0 means no new task allowed.
//        limit < 0 means no limitation.
extern ConcurrentTaskLimiter* NewConcurrentTaskLimiter(
    Env* env, std::shared_ptr<Logger> info_log = nullptr,
    const std::string& name = "", int32_t limit = -1);

}  // namespace rocksdb
