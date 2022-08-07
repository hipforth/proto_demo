#include "grid_2d.h"

Grid2D::Grid2D(const MapLimits& limits, 
               const std::vector<uint16_t>& correspondence_cost_cells,
               const Eigen::AlignedBox2i& known_cells_box, 
               const float& min_correspondence_cost, 
               const float& max_correspondence_cost)
  : limits_(limits), correspondence_cost_cells_(correspondence_cost_cells),
    known_cells_box_(known_cells_box), min_correspondence_cost_(min_correspondence_cost),
    max_correspondence_cost_(max_correspondence_cost) {}

Grid2D::Grid2D(const proto::Grid2D& proto)
  : limits_(proto.limits()),
    correspondence_cost_cells_(),
    min_correspondence_cost_(proto.min_correspondence_cost()),
    max_correspondence_cost_(proto.max_correspondence_cost())
{
  if(proto.has_konwn_cell_box()) {
    const auto& box = proto.konwn_cell_box();
    known_cells_box_ = Eigen::AlignedBox2i(
                        Eigen::Vector2i(box.min_x(), box.min_y()),
                        Eigen::Vector2i(box.max_x(), box.max_y()));
  }
  correspondence_cost_cells_.reserve(proto.cells_size());
  for(const auto& cell : proto.cells()) {
    if(cell <= std::numeric_limits<uint16_t>::max())
      correspondence_cost_cells_.push_back(cell);
  }
}


proto::Grid2D Grid2D::ToProto() const {
  proto::Grid2D result;
  *result.mutable_limits() = MapLimitsToProto(limits_);
  *result.mutable_cells() = {correspondence_cost_cells_.begin(),
                             correspondence_cost_cells_.end()};
  if (!known_cells_box().isEmpty()) { 
    auto* const box = result.mutable_konwn_cell_box();
    box->set_max_x(known_cells_box().max().x());
    box->set_max_y(known_cells_box().max().y());
    box->set_min_x(known_cells_box().min().x());
    box->set_min_y(known_cells_box().min().y());
  }
  result.set_min_correspondence_cost(min_correspondence_cost_);
  result.set_max_correspondence_cost(max_correspondence_cost_);
  return result;
}