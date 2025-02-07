// Copyright (c) 2019 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/NonCopyable.h"
#include "carla/road/RoadTypes.h"
#include <string>
#include <vector>

namespace carla {
namespace road {
namespace object {

class RepeatRecord : private MovableNonCopyable {
public:
  RepeatRecord() {}

private:
  ObjId _id;
};

} // namespace object
} // namespace road
} // namespace carla
