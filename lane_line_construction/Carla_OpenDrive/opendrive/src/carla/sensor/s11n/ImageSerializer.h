// Copyright (c) 2017 Computer Vision Center (CVC) at the Universitat Autonoma
// de Barcelona (UAB).
//
// This work is licensed under the terms of the MIT license.
// For a copy, see <https://opensource.org/licenses/MIT>.

#pragma once

#include "carla/Memory.h"
#include "carla/sensor/RawData.h"

#include <cstdint>
#include <cstring>

namespace carla {
namespace sensor {

class SensorData;

namespace s11n {

/// Serializes image buffers generated by camera sensors.
class ImageSerializer {
public:
#pragma pack(push, 1)
  struct ImageHeader {
    uint32_t width;
    uint32_t height;
    float fov_angle;
  };
#pragma pack(pop)

  constexpr static auto header_offset = sizeof(ImageHeader);

  static const ImageHeader &DeserializeHeader(const RawData &data) {
    return *reinterpret_cast<const ImageHeader *>(data.begin());
  }

  template <typename Sensor>
  static Buffer Serialize(const Sensor &sensor, Buffer &&bitmap);

  static SharedPtr<SensorData> Deserialize(RawData &&data);
};

template <typename Sensor>
inline Buffer ImageSerializer::Serialize(const Sensor &sensor,
                                         Buffer &&bitmap) {
  DEBUG_ASSERT(bitmap.size() > sizeof(ImageHeader));
  ImageHeader header = {sensor.GetImageWidth(), sensor.GetImageHeight(),
                        sensor.GetFOVAngle()};
  std::memcpy(bitmap.data(), reinterpret_cast<const void *>(&header),
              sizeof(header));
  return std::move(bitmap);
}

} // namespace s11n
} // namespace sensor
} // namespace carla
