#ifndef MAP_LIMITS_H
#define MAP_LIMITS_H

#include <Eigen/Core>
#include "proto/cell_limits_2d.pb.h"
#include "proto/map_limits.pb.h"

struct CellLimits {
  CellLimits() = default;
  CellLimits(int init_num_x_cells, int init_num_y_cells)
      : num_x_cells(init_num_x_cells), num_y_cells(init_num_y_cells) {}

  explicit CellLimits(const proto::CellLimits& cell_limits)
      : num_x_cells(cell_limits.num_x_cells()),
        num_y_cells(cell_limits.num_y_cells()) {}

  int num_x_cells = 0;
  int num_y_cells = 0;
};

inline proto::CellLimits CellLimitsToProto(const CellLimits& cell_limits) {
  proto::CellLimits result;
  result.set_num_x_cells(cell_limits.num_x_cells);
  result.set_num_y_cells(cell_limits.num_y_cells);
  return result;
}

class MapLimits {
  public:
    MapLimits(const double& resolution, const CellLimits& cell_limits) :
      resolution_(resolution), cell_limits_(cell_limits) {}

    explicit MapLimits(const proto::MapLimits& map_limits)
      : resolution_(map_limits.resolution()), 
        cell_limits_(map_limits.cell_limits()) {}

    double resolution() const { return resolution_; }
    CellLimits cell_limits() const { return cell_limits_; }
  private:
   double resolution_;
   CellLimits cell_limits_;    
}; // class MapLimits

inline proto::MapLimits MapLimitsToProto(const MapLimits& map_limits) {
  proto::MapLimits result;
  result.set_resolution(map_limits.resolution());
  *result.mutable_cell_limits() = CellLimitsToProto(map_limits.cell_limits());
  return result;
}

#endif