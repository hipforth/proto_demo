#ifndef RANGE_DATA_H
#define RANGE_DATA_H

#include <Eigen/Core>
#include <Eigen/Dense>

#include <vector>

#include "proto/range_data.pb.h"

namespace sensor {

struct Rigid3d {
  Eigen::Quaterniond rotation;
  Eigen::Vector3d translation;
};

struct RangeData {
  RangeData();
  explicit RangeData(const proto::RangeData& range_data);
  std::vector<double> points_x;
  std::vector<double> points_y;
  Rigid3d local_pose;
}; // class RangeData

} // namespace sensor


#endif // RANGE_DATA_H