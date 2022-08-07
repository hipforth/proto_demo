#include "proto/range_data.pb.h"

#include "proto_io.h"
#include "range_data.h"

proto::Quaterniond ToProto(const Eigen::Quaterniond& quaternion);
proto::Vector3d ToProto(const Eigen::Vector3d& vector);
proto::Rigid3d RigidToProto(const sensor::Rigid3d& rigid);
proto::AllRangeData RangeDataToProto(const std::vector<sensor::RangeData>& vrange_datas);
void printRigid(const proto::AllRangeData* range_datas_read);

int main(int argc, char** argv) {

  std::vector<sensor::RangeData> vrange_datas;
  constexpr int16_t N = 10;
  constexpr int16_t num_range_data = 35;
  for(int16_t ii = 0; ii < N; ii ++) {
    sensor::Rigid3d local_pose;
    local_pose.rotation = local_pose.rotation.setIdentity();
    local_pose.translation = 0.6 * local_pose.translation.setOnes();

    sensor::RangeData range_data;
    range_data.local_pose = local_pose;
    for(int16_t jj = 0; jj < num_range_data; jj ++) {
      range_data.points_x.push_back(double(ii));
      range_data.points_y.push_back(double(jj));
    }
    vrange_datas.push_back(range_data);
  }
  // auto range_datas_write = RangeDataToProto(vrange_datas);

  // std::string proto_file = argv[1];
  // auto proto_writer = std::make_shared<ProtoStreamWriter>(proto_file);
  // proto_writer->WriteProto(range_datas_write);
  // proto_writer->Close();


  // // read proto
  // proto::AllRangeData range_datas_read;
  // auto proto_reader = std::make_shared<ProtoStreamReader>(proto_file);
  // proto_reader->ReadProto(&range_datas_read);
  // proto_reader->eof();

  return 0;
}

namespace sensor {
RangeData::RangeData(const proto::RangeData& range_data)
{

}
}


void printRigid(const proto::AllRangeData* range_datas_read) {
  std::vector<sensor::RangeData> vrange_datas(10);
  for(auto& range_data : vrange_datas) {
    const proto::RangeData range_data_proto = *range_datas_read->range_datas();
    range_data = sensor::RangeData();
  }
}

proto::Vector3d ToProto(const Eigen::Vector3d& vector) {
  proto::Vector3d proto;
  proto.set_x(vector.x());
  proto.set_y(vector.y());
  proto.set_z(vector.z());
  return proto;
}

proto::Quaterniond ToProto(const Eigen::Quaterniond& quaternion) {
  proto::Quaterniond proto;
  proto.set_w(quaternion.w());
  proto.set_x(quaternion.x());
  proto.set_y(quaternion.y());
  proto.set_z(quaternion.z());
  return proto;
}

proto::Rigid3d RigidToProto(const sensor::Rigid3d& rigid) {
  proto::Rigid3d proto;
  *proto.mutable_translation() = ToProto(rigid.translation);
  *proto.mutable_rotation() = ToProto(rigid.rotation);
  return proto;
}

// proto::AllRangeData RangeDataToProto(const std::vector<sensor::RangeData>& vrange_datas) {
//   proto::AllRangeData proto;
//   for(auto& range_data : vrange_datas) {
//     proto::RangeData* range_data_proto = proto.add_range_datas();
    
//     *range_data_proto->mutable_point_x() = {range_data.points_x.begin(),
//                                            range_data.points_x.end()};
//     *range_data_proto->mutable_point_y() = {range_data.points_y.begin(),
//                                            range_data.points_y.end()};                                           
//     *range_data_proto->mutable_pose() = RigidToProto(range_data.local_pose);
//   }
//   return proto;
// }