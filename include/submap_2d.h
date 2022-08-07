#ifndef SUBMAP_2D_H
#define SUBMAP_2D_H

#include "grid_2d.h"
#include <memory>
#include <vector>
#include <Eigen/Dense>
#include "proto/submap_2d.pb.h"

class Submap2D {
  public:
    Submap2D(std::unique_ptr<Grid2D> grid){ grid_ = std::move(grid); }
    explicit Submap2D(const proto::Submap2D& proto);

    const Grid2D* grid() const { return grid_.get(); }
    bool is_finished() { return is_finished_; }
    int num_range_data() { return num_range_data_; }

    proto::Submap2D ToProto();

  private:
    std::unique_ptr<Grid2D> grid_;
    bool is_finished_ = false;
    int num_range_data_ = 35;
}; // calss Submap2D

#endif // SUBMAP_2D_H