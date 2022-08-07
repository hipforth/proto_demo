#include "map_limits.h"
#include "grid_2d.h"
#include "submap_2d.h"
#include "proto/submap_2d.pb.h"
#include "proto_io.h"

#include <fstream>

void printSubmap(const proto::Submap2D* proto_submap);

int main(int argc, char** argv)
{
  CellLimits cell_limits(10, 10);
  MapLimits map_limits(0.5, cell_limits);

  std::vector<uint16_t> correspondence_cost_cells(64);
  Eigen::AlignedBox2i known_cells_box;
  known_cells_box.max() = Eigen::Vector2i(32, 32);
  known_cells_box.min() = Eigen::Vector2i(16, 16);
  
  auto submap = std::make_shared<Submap2D>(std::make_unique<Grid2D>(
    map_limits, correspondence_cost_cells, known_cells_box,
    8., 8.));

  auto proto_submap = submap->ToProto();

  std::string proto_file = argv[1];
  auto proto_writer = std::make_shared<ProtoStreamWriter>(proto_file);
  proto_writer->WriteProto(proto_submap);
  proto_writer->Close();

  // read proto
  proto::Submap2D submap_read;
  auto proto_reader = std::make_shared<ProtoStreamReader>(proto_file);
  proto_reader->ReadProto(&submap_read);
  proto_reader->eof();
  printSubmap(&submap_read);
  return 0;
}

void printSubmap(const proto::Submap2D* proto_submap)
{
  auto submap_2d = std::make_shared<Submap2D>(*proto_submap);
  if(submap_2d->grid() != nullptr) {
    std::cout << "grid exist!\n";
    std::cout << submap_2d->grid()->known_cells_box().max().transpose() << std::endl;
    std::cout << submap_2d->grid()->limits().resolution() << std::endl;
    std::cout << submap_2d->grid()->limits().cell_limits().num_x_cells << " "
              << submap_2d->grid()->limits().cell_limits().num_y_cells << "\n";
  }
  else
    std::cout << "grid non exist!\n";
  
  if(submap_2d->is_finished()) std::cout << "true\n";
  else std::cout << "false\n";

  std::cout << submap_2d->num_range_data() << std::endl;
}