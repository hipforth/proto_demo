#include "submap_2d.h"

Submap2D::Submap2D(const proto::Submap2D& proto)
{
  if(proto.has_grid()) {
    grid_ = std::make_unique<Grid2D>(proto.grid());
  }
}

proto::Submap2D Submap2D::ToProto() {
  proto::Submap2D proto;
  auto* const submap_2d = &proto;
  // auto* const submap_2d = proto.mutable_submap_2d();
  // *submap_2d->mutable_local_pose() = transform::ToProto(local_pose());
  proto.set_num_range_data(35);
  proto.set_is_finished(true);

  *submap_2d->mutable_grid() = grid_->ToProto();
  return proto;
}