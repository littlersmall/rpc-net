// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: pb_packet.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "pb_packet.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/once.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)

namespace pb_net {

namespace {

const ::google::protobuf::Descriptor* PbPacket_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  PbPacket_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_pb_5fpacket_2eproto() {
  protobuf_AddDesc_pb_5fpacket_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "pb_packet.proto");
  GOOGLE_CHECK(file != NULL);
  PbPacket_descriptor_ = file->message_type(0);
  static const int PbPacket_offsets_[9] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, packet_code_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, uuid_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, send_time_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, stat_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, lock_name_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, memo_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, json_str_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, email_),
  };
  PbPacket_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      PbPacket_descriptor_,
      PbPacket::default_instance_,
      PbPacket_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(PbPacket, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(PbPacket));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_pb_5fpacket_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    PbPacket_descriptor_, &PbPacket::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_pb_5fpacket_2eproto() {
  delete PbPacket::default_instance_;
  delete PbPacket_reflection_;
}

void protobuf_AddDesc_pb_5fpacket_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\017pb_packet.proto\022\006pb_net\"\234\001\n\010PbPacket\022\023"
    "\n\013packet_code\030\001 \002(\t\022\014\n\004uuid\030\002 \002(\t\022\021\n\tsen"
    "d_time\030\003 \002(\005\022\014\n\004stat\030\004 \001(\t\022\021\n\tlock_name\030"
    "\005 \001(\t\022\014\n\004memo\030\006 \001(\t\022\020\n\010json_str\030\007 \001(\t\022\n\n"
    "\002id\030\010 \001(\005\022\r\n\005email\030\t \001(\t", 184);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "pb_packet.proto", &protobuf_RegisterTypes);
  PbPacket::default_instance_ = new PbPacket();
  PbPacket::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_pb_5fpacket_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_pb_5fpacket_2eproto {
  StaticDescriptorInitializer_pb_5fpacket_2eproto() {
    protobuf_AddDesc_pb_5fpacket_2eproto();
  }
} static_descriptor_initializer_pb_5fpacket_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int PbPacket::kPacketCodeFieldNumber;
const int PbPacket::kUuidFieldNumber;
const int PbPacket::kSendTimeFieldNumber;
const int PbPacket::kStatFieldNumber;
const int PbPacket::kLockNameFieldNumber;
const int PbPacket::kMemoFieldNumber;
const int PbPacket::kJsonStrFieldNumber;
const int PbPacket::kIdFieldNumber;
const int PbPacket::kEmailFieldNumber;
#endif  // !_MSC_VER

PbPacket::PbPacket()
  : ::google::protobuf::Message() {
  SharedCtor();
}

void PbPacket::InitAsDefaultInstance() {
}

PbPacket::PbPacket(const PbPacket& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
}

void PbPacket::SharedCtor() {
  _cached_size_ = 0;
  packet_code_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  uuid_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  send_time_ = 0;
  stat_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  lock_name_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  memo_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  json_str_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  id_ = 0;
  email_ = const_cast< ::std::string*>(&::google::protobuf::internal::kEmptyString);
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

PbPacket::~PbPacket() {
  SharedDtor();
}

void PbPacket::SharedDtor() {
  if (packet_code_ != &::google::protobuf::internal::kEmptyString) {
    delete packet_code_;
  }
  if (uuid_ != &::google::protobuf::internal::kEmptyString) {
    delete uuid_;
  }
  if (stat_ != &::google::protobuf::internal::kEmptyString) {
    delete stat_;
  }
  if (lock_name_ != &::google::protobuf::internal::kEmptyString) {
    delete lock_name_;
  }
  if (memo_ != &::google::protobuf::internal::kEmptyString) {
    delete memo_;
  }
  if (json_str_ != &::google::protobuf::internal::kEmptyString) {
    delete json_str_;
  }
  if (email_ != &::google::protobuf::internal::kEmptyString) {
    delete email_;
  }
  if (this != default_instance_) {
  }
}

void PbPacket::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* PbPacket::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return PbPacket_descriptor_;
}

const PbPacket& PbPacket::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_pb_5fpacket_2eproto();
  return *default_instance_;
}

PbPacket* PbPacket::default_instance_ = NULL;

PbPacket* PbPacket::New() const {
  return new PbPacket;
}

void PbPacket::Clear() {
  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (has_packet_code()) {
      if (packet_code_ != &::google::protobuf::internal::kEmptyString) {
        packet_code_->clear();
      }
    }
    if (has_uuid()) {
      if (uuid_ != &::google::protobuf::internal::kEmptyString) {
        uuid_->clear();
      }
    }
    send_time_ = 0;
    if (has_stat()) {
      if (stat_ != &::google::protobuf::internal::kEmptyString) {
        stat_->clear();
      }
    }
    if (has_lock_name()) {
      if (lock_name_ != &::google::protobuf::internal::kEmptyString) {
        lock_name_->clear();
      }
    }
    if (has_memo()) {
      if (memo_ != &::google::protobuf::internal::kEmptyString) {
        memo_->clear();
      }
    }
    if (has_json_str()) {
      if (json_str_ != &::google::protobuf::internal::kEmptyString) {
        json_str_->clear();
      }
    }
    id_ = 0;
  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (has_email()) {
      if (email_ != &::google::protobuf::internal::kEmptyString) {
        email_->clear();
      }
    }
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool PbPacket::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) return false
  ::google::protobuf::uint32 tag;
  while ((tag = input->ReadTag()) != 0) {
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required string packet_code = 1;
      case 1: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_packet_code()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->packet_code().data(), this->packet_code().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(18)) goto parse_uuid;
        break;
      }

      // required string uuid = 2;
      case 2: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_uuid:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_uuid()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->uuid().data(), this->uuid().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(24)) goto parse_send_time;
        break;
      }

      // required int32 send_time = 3;
      case 3: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_send_time:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &send_time_)));
          set_has_send_time();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(34)) goto parse_stat;
        break;
      }

      // optional string stat = 4;
      case 4: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_stat:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_stat()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->stat().data(), this->stat().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(42)) goto parse_lock_name;
        break;
      }

      // optional string lock_name = 5;
      case 5: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_lock_name:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_lock_name()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->lock_name().data(), this->lock_name().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(50)) goto parse_memo;
        break;
      }

      // optional string memo = 6;
      case 6: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_memo:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_memo()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->memo().data(), this->memo().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(58)) goto parse_json_str;
        break;
      }

      // optional string json_str = 7;
      case 7: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_json_str:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_json_str()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->json_str().data(), this->json_str().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(64)) goto parse_id;
        break;
      }

      // optional int32 id = 8;
      case 8: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_VARINT) {
         parse_id:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &id_)));
          set_has_id();
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectTag(74)) goto parse_email;
        break;
      }

      // optional string email = 9;
      case 9: {
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED) {
         parse_email:
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_email()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8String(
            this->email().data(), this->email().length(),
            ::google::protobuf::internal::WireFormat::PARSE);
        } else {
          goto handle_uninterpreted;
        }
        if (input->ExpectAtEnd()) return true;
        break;
      }

      default: {
      handle_uninterpreted:
        if (::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          return true;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
  return true;
#undef DO_
}

void PbPacket::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // required string packet_code = 1;
  if (has_packet_code()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->packet_code().data(), this->packet_code().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->packet_code(), output);
  }

  // required string uuid = 2;
  if (has_uuid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->uuid().data(), this->uuid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      2, this->uuid(), output);
  }

  // required int32 send_time = 3;
  if (has_send_time()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(3, this->send_time(), output);
  }

  // optional string stat = 4;
  if (has_stat()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->stat().data(), this->stat().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      4, this->stat(), output);
  }

  // optional string lock_name = 5;
  if (has_lock_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->lock_name().data(), this->lock_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      5, this->lock_name(), output);
  }

  // optional string memo = 6;
  if (has_memo()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->memo().data(), this->memo().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      6, this->memo(), output);
  }

  // optional string json_str = 7;
  if (has_json_str()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->json_str().data(), this->json_str().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      7, this->json_str(), output);
  }

  // optional int32 id = 8;
  if (has_id()) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(8, this->id(), output);
  }

  // optional string email = 9;
  if (has_email()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->email().data(), this->email().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    ::google::protobuf::internal::WireFormatLite::WriteString(
      9, this->email(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
}

::google::protobuf::uint8* PbPacket::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // required string packet_code = 1;
  if (has_packet_code()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->packet_code().data(), this->packet_code().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->packet_code(), target);
  }

  // required string uuid = 2;
  if (has_uuid()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->uuid().data(), this->uuid().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        2, this->uuid(), target);
  }

  // required int32 send_time = 3;
  if (has_send_time()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(3, this->send_time(), target);
  }

  // optional string stat = 4;
  if (has_stat()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->stat().data(), this->stat().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        4, this->stat(), target);
  }

  // optional string lock_name = 5;
  if (has_lock_name()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->lock_name().data(), this->lock_name().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        5, this->lock_name(), target);
  }

  // optional string memo = 6;
  if (has_memo()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->memo().data(), this->memo().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        6, this->memo(), target);
  }

  // optional string json_str = 7;
  if (has_json_str()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->json_str().data(), this->json_str().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        7, this->json_str(), target);
  }

  // optional int32 id = 8;
  if (has_id()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(8, this->id(), target);
  }

  // optional string email = 9;
  if (has_email()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8String(
      this->email().data(), this->email().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE);
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        9, this->email(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  return target;
}

int PbPacket::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // required string packet_code = 1;
    if (has_packet_code()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->packet_code());
    }

    // required string uuid = 2;
    if (has_uuid()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->uuid());
    }

    // required int32 send_time = 3;
    if (has_send_time()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->send_time());
    }

    // optional string stat = 4;
    if (has_stat()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->stat());
    }

    // optional string lock_name = 5;
    if (has_lock_name()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->lock_name());
    }

    // optional string memo = 6;
    if (has_memo()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->memo());
    }

    // optional string json_str = 7;
    if (has_json_str()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->json_str());
    }

    // optional int32 id = 8;
    if (has_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
          this->id());
    }

  }
  if (_has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    // optional string email = 9;
    if (has_email()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->email());
    }

  }
  if (!unknown_fields().empty()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        unknown_fields());
  }
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = total_size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
  return total_size;
}

void PbPacket::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const PbPacket* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const PbPacket*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void PbPacket::MergeFrom(const PbPacket& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_packet_code()) {
      set_packet_code(from.packet_code());
    }
    if (from.has_uuid()) {
      set_uuid(from.uuid());
    }
    if (from.has_send_time()) {
      set_send_time(from.send_time());
    }
    if (from.has_stat()) {
      set_stat(from.stat());
    }
    if (from.has_lock_name()) {
      set_lock_name(from.lock_name());
    }
    if (from.has_memo()) {
      set_memo(from.memo());
    }
    if (from.has_json_str()) {
      set_json_str(from.json_str());
    }
    if (from.has_id()) {
      set_id(from.id());
    }
  }
  if (from._has_bits_[8 / 32] & (0xffu << (8 % 32))) {
    if (from.has_email()) {
      set_email(from.email());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void PbPacket::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void PbPacket::CopyFrom(const PbPacket& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PbPacket::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;

  return true;
}

void PbPacket::Swap(PbPacket* other) {
  if (other != this) {
    std::swap(packet_code_, other->packet_code_);
    std::swap(uuid_, other->uuid_);
    std::swap(send_time_, other->send_time_);
    std::swap(stat_, other->stat_);
    std::swap(lock_name_, other->lock_name_);
    std::swap(memo_, other->memo_);
    std::swap(json_str_, other->json_str_);
    std::swap(id_, other->id_);
    std::swap(email_, other->email_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata PbPacket::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = PbPacket_descriptor_;
  metadata.reflection = PbPacket_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace pb_net

// @@protoc_insertion_point(global_scope)
