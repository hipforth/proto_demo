#ifndef GRID_2D_H
#define GRID_2D_H

#include "map_limits.h"
#include <Eigen/Dense>
#include "proto/grid_2d.pb.h"

class Grid2D {
  public:
    Grid2D(const MapLimits& limits, const std::vector<uint16_t>& correspondence_cost_cells,
           const Eigen::AlignedBox2i& known_cells_box, 
           const float& min_correspondence_cost, const float& max_correspondence_cost);
    explicit Grid2D(const proto::Grid2D& proto);
    proto::Grid2D ToProto() const;

    const MapLimits limits() const { return limits_; }

    const Eigen::AlignedBox2i known_cells_box() const { return known_cells_box_; }
    std::vector<uint16_t> correspondence_cost_cells() const { return correspondence_cost_cells_; }
    Eigen::AlignedBox2i* mutable_known_cells_box() { return &known_cells_box_; }
  private:
    MapLimits limits_;
    std::vector<uint16_t> correspondence_cost_cells_;
    Eigen::AlignedBox2i known_cells_box_;
    float min_correspondence_cost_;
    float max_correspondence_cost_;
}; // class Grid2D

#endif // GRID_2D_H