/*
 *  Copyright (c) 2004-present, Facebook, Inc.
 *  All rights reserved.
 *
 *  This source code is licensed under the BSD-style license found in the
 *  LICENSE file in the root directory of this source tree. An additional grant
 *  of patent rights can be found in the PATENTS file in the same directory.
 *
 */
#pragma once

extern "C" {
#include <bcm/types.h>
#include <bcm/udf.h>
}

#include "fboss/agent/FbossError.h"
#include "fboss/agent/hw/bcm/BcmUdfGroup.h"
#include "fboss/agent/hw/bcm/BcmUdfPacketMatcher.h"
#include "fboss/agent/hw/bcm/types.h"
#include "fboss/agent/state/UdfGroupMap.h"
#include "fboss/agent/state/UdfPacketMatcherMap.h"

namespace facebook::fboss {

class BcmSwitch;

/**
 * BcmUdfManager is the class to manage UdfPackMatcher and UdfGroup objects
BcmWarmBootCache.cpp
 */
class BcmUdfManager {
 public:
  explicit BcmUdfManager(BcmSwitch* hw) : hw_(hw) {}
  ~BcmUdfManager();
  void addUdfConfig(
      const std::shared_ptr<UdfPacketMatcherMap>& udfPacketMatcherMap,
      const std::shared_ptr<UdfGroupMap>& udfGroupMap);
  void deleteUdfConfig(
      const std::shared_ptr<UdfPacketMatcherMap>& udfPacketMatcherMap,
      const std::shared_ptr<UdfGroupMap>& udfGroupMap);

  void createUdfPacketMatcher(
      const std::shared_ptr<UdfPacketMatcher>& udfPacketMatcher);
  void createUdfGroup(const std::shared_ptr<UdfGroup>& udfGroup);

  const std::map<std::string, std::shared_ptr<BcmUdfGroup>> getUdfGroupsMap()
      const {
    return udfGroupsMap_;
  }

  const std::map<std::string, std::shared_ptr<BcmUdfPacketMatcher>>
  getUdfPacketMatcherMap() const {
    return udfPacketMatcherMap_;
  }

 private:
  void attachUdfPacketMatcher(
      std::shared_ptr<BcmUdfGroup>& bcmUdfGroup,
      const std::string& udfPacketMatcherName);
  void deleteUdfPacketMatcher(const std::string& udfPacketMatcherName);
  void deleteUdfGroup(
      const std::string& udfGroupName,
      const std::shared_ptr<UdfGroup>& udfGroup);
  void detachUdfPacketMatcher(
      std::shared_ptr<BcmUdfGroup>& bcmUdfGroup,
      const std::string& udfPacketMatcherName);

  BcmSwitch* hw_;
  std::map<std::string, std::shared_ptr<BcmUdfGroup>> udfGroupsMap_;
  std::map<std::string, std::shared_ptr<BcmUdfPacketMatcher>>
      udfPacketMatcherMap_;
};

} // namespace facebook::fboss