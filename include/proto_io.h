#ifndef PROTO_IO_H
#define PROTO_IO_H

#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/gzip.hpp>
#include <boost/iostreams/filtering_stream.hpp>

#include <fstream>

#include "google/protobuf/message.h"

class ProtoStreamWriter {
  public:
    ProtoStreamWriter(const std::string& filename);
    ~ProtoStreamWriter() = default;

    ProtoStreamWriter(const ProtoStreamWriter&) = delete;
    ProtoStreamWriter& operator=(const ProtoStreamWriter&) = delete;

    void WriteProto(const google::protobuf::Message& proto);

    bool Close();

  private:
    void Write(const std::string& uncompressed_data);            
  
  private:
    std::ofstream out_;

}; // class ProtoStreamWriter

class ProtoStreamReader {
  public:
    explicit ProtoStreamReader(const std::string& filename);
    ~ProtoStreamReader() = default;

    ProtoStreamReader(const ProtoStreamReader&) = delete;
    ProtoStreamReader& operator=(const ProtoStreamReader&) = delete;

    bool ReadProto(google::protobuf::Message* proto);
    bool eof() const;

  private:
    bool Read(std::string* decompressed_data);
  
  private:
    std::ifstream in_;
}; // class ProtoStreamReader

#endif // PROTO_IO_H