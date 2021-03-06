// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sim_data_transf.proto

#define INTERNAL_SUPPRESS_PROTOBUF_FIELD_DEPRECATION
#include "sim_data_transf.pb.h"

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

namespace data_transf {

namespace {

const ::google::protobuf::Descriptor* Data_dump_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Data_dump_reflection_ = NULL;
const ::google::protobuf::Descriptor* Oscillator_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Oscillator_reflection_ = NULL;
const ::google::protobuf::Descriptor* Saddle_t_and_id_descriptor_ = NULL;
const ::google::protobuf::internal::GeneratedMessageReflection*
  Saddle_t_and_id_reflection_ = NULL;

}  // namespace


void protobuf_AssignDesc_sim_5fdata_5ftransf_2eproto() {
  protobuf_AddDesc_sim_5fdata_5ftransf_2eproto();
  const ::google::protobuf::FileDescriptor* file =
    ::google::protobuf::DescriptorPool::generated_pool()->FindFileByName(
      "sim_data_transf.proto");
  GOOGLE_CHECK(file != NULL);
  Data_dump_descriptor_ = file->message_type(0);
  static const int Data_dump_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Data_dump, oscillator_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Data_dump, saddle_t_and_id_),
  };
  Data_dump_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Data_dump_descriptor_,
      Data_dump::default_instance_,
      Data_dump_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Data_dump, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Data_dump, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Data_dump));
  Oscillator_descriptor_ = file->message_type(1);
  static const int Oscillator_offsets_[1] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Oscillator, reset_t_),
  };
  Oscillator_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Oscillator_descriptor_,
      Oscillator::default_instance_,
      Oscillator_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Oscillator, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Oscillator, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Oscillator));
  Saddle_t_and_id_descriptor_ = file->message_type(2);
  static const int Saddle_t_and_id_offsets_[2] = {
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Saddle_t_and_id, saddle_id_),
    GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Saddle_t_and_id, saddle_t_),
  };
  Saddle_t_and_id_reflection_ =
    new ::google::protobuf::internal::GeneratedMessageReflection(
      Saddle_t_and_id_descriptor_,
      Saddle_t_and_id::default_instance_,
      Saddle_t_and_id_offsets_,
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Saddle_t_and_id, _has_bits_[0]),
      GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(Saddle_t_and_id, _unknown_fields_),
      -1,
      ::google::protobuf::DescriptorPool::generated_pool(),
      ::google::protobuf::MessageFactory::generated_factory(),
      sizeof(Saddle_t_and_id));
}

namespace {

GOOGLE_PROTOBUF_DECLARE_ONCE(protobuf_AssignDescriptors_once_);
inline void protobuf_AssignDescriptorsOnce() {
  ::google::protobuf::GoogleOnceInit(&protobuf_AssignDescriptors_once_,
                 &protobuf_AssignDesc_sim_5fdata_5ftransf_2eproto);
}

void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Data_dump_descriptor_, &Data_dump::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Oscillator_descriptor_, &Oscillator::default_instance());
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedMessage(
    Saddle_t_and_id_descriptor_, &Saddle_t_and_id::default_instance());
}

}  // namespace

void protobuf_ShutdownFile_sim_5fdata_5ftransf_2eproto() {
  delete Data_dump::default_instance_;
  delete Data_dump_reflection_;
  delete Oscillator::default_instance_;
  delete Oscillator_reflection_;
  delete Saddle_t_and_id::default_instance_;
  delete Saddle_t_and_id_reflection_;
}

void protobuf_AddDesc_sim_5fdata_5ftransf_2eproto() {
  static bool already_here = false;
  if (already_here) return;
  already_here = true;
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
    "\n\025sim_data_transf.proto\022\013data_transf\"o\n\t"
    "Data_dump\022+\n\noscillator\030\001 \003(\0132\027.data_tra"
    "nsf.Oscillator\0225\n\017saddle_t_and_id\030\002 \003(\0132"
    "\034.data_transf.Saddle_t_and_id\"!\n\nOscilla"
    "tor\022\023\n\007reset_t\030\001 \003(\001B\002\020\001\"6\n\017Saddle_t_and"
    "_id\022\021\n\tsaddle_id\030\001 \001(\t\022\020\n\010saddle_t\030\002 \001(\001", 240);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "sim_data_transf.proto", &protobuf_RegisterTypes);
  Data_dump::default_instance_ = new Data_dump();
  Oscillator::default_instance_ = new Oscillator();
  Saddle_t_and_id::default_instance_ = new Saddle_t_and_id();
  Data_dump::default_instance_->InitAsDefaultInstance();
  Oscillator::default_instance_->InitAsDefaultInstance();
  Saddle_t_and_id::default_instance_->InitAsDefaultInstance();
  ::google::protobuf::internal::OnShutdown(&protobuf_ShutdownFile_sim_5fdata_5ftransf_2eproto);
}

// Force AddDescriptors() to be called at static initialization time.
struct StaticDescriptorInitializer_sim_5fdata_5ftransf_2eproto {
  StaticDescriptorInitializer_sim_5fdata_5ftransf_2eproto() {
    protobuf_AddDesc_sim_5fdata_5ftransf_2eproto();
  }
} static_descriptor_initializer_sim_5fdata_5ftransf_2eproto_;

// ===================================================================

#ifndef _MSC_VER
const int Data_dump::kOscillatorFieldNumber;
const int Data_dump::kSaddleTAndIdFieldNumber;
#endif  // !_MSC_VER

Data_dump::Data_dump()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:data_transf.Data_dump)
}

void Data_dump::InitAsDefaultInstance() {
}

Data_dump::Data_dump(const Data_dump& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:data_transf.Data_dump)
}

void Data_dump::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Data_dump::~Data_dump() {
  // @@protoc_insertion_point(destructor:data_transf.Data_dump)
  SharedDtor();
}

void Data_dump::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Data_dump::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Data_dump::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Data_dump_descriptor_;
}

const Data_dump& Data_dump::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_sim_5fdata_5ftransf_2eproto();
  return *default_instance_;
}

Data_dump* Data_dump::default_instance_ = NULL;

Data_dump* Data_dump::New() const {
  return new Data_dump;
}

void Data_dump::Clear() {
  oscillator_.Clear();
  saddle_t_and_id_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Data_dump::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:data_transf.Data_dump)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated .data_transf.Oscillator oscillator = 1;
      case 1: {
        if (tag == 10) {
         parse_oscillator:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_oscillator()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(10)) goto parse_oscillator;
        if (input->ExpectTag(18)) goto parse_saddle_t_and_id;
        break;
      }

      // repeated .data_transf.Saddle_t_and_id saddle_t_and_id = 2;
      case 2: {
        if (tag == 18) {
         parse_saddle_t_and_id:
          DO_(::google::protobuf::internal::WireFormatLite::ReadMessageNoVirtual(
                input, add_saddle_t_and_id()));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(18)) goto parse_saddle_t_and_id;
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:data_transf.Data_dump)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:data_transf.Data_dump)
  return false;
#undef DO_
}

void Data_dump::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:data_transf.Data_dump)
  // repeated .data_transf.Oscillator oscillator = 1;
  for (int i = 0; i < this->oscillator_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      1, this->oscillator(i), output);
  }

  // repeated .data_transf.Saddle_t_and_id saddle_t_and_id = 2;
  for (int i = 0; i < this->saddle_t_and_id_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteMessageMaybeToArray(
      2, this->saddle_t_and_id(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:data_transf.Data_dump)
}

::google::protobuf::uint8* Data_dump::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:data_transf.Data_dump)
  // repeated .data_transf.Oscillator oscillator = 1;
  for (int i = 0; i < this->oscillator_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        1, this->oscillator(i), target);
  }

  // repeated .data_transf.Saddle_t_and_id saddle_t_and_id = 2;
  for (int i = 0; i < this->saddle_t_and_id_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteMessageNoVirtualToArray(
        2, this->saddle_t_and_id(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:data_transf.Data_dump)
  return target;
}

int Data_dump::ByteSize() const {
  int total_size = 0;

  // repeated .data_transf.Oscillator oscillator = 1;
  total_size += 1 * this->oscillator_size();
  for (int i = 0; i < this->oscillator_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->oscillator(i));
  }

  // repeated .data_transf.Saddle_t_and_id saddle_t_and_id = 2;
  total_size += 1 * this->saddle_t_and_id_size();
  for (int i = 0; i < this->saddle_t_and_id_size(); i++) {
    total_size +=
      ::google::protobuf::internal::WireFormatLite::MessageSizeNoVirtual(
        this->saddle_t_and_id(i));
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

void Data_dump::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Data_dump* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Data_dump*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Data_dump::MergeFrom(const Data_dump& from) {
  GOOGLE_CHECK_NE(&from, this);
  oscillator_.MergeFrom(from.oscillator_);
  saddle_t_and_id_.MergeFrom(from.saddle_t_and_id_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Data_dump::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Data_dump::CopyFrom(const Data_dump& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Data_dump::IsInitialized() const {

  return true;
}

void Data_dump::Swap(Data_dump* other) {
  if (other != this) {
    oscillator_.Swap(&other->oscillator_);
    saddle_t_and_id_.Swap(&other->saddle_t_and_id_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Data_dump::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Data_dump_descriptor_;
  metadata.reflection = Data_dump_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Oscillator::kResetTFieldNumber;
#endif  // !_MSC_VER

Oscillator::Oscillator()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:data_transf.Oscillator)
}

void Oscillator::InitAsDefaultInstance() {
}

Oscillator::Oscillator(const Oscillator& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:data_transf.Oscillator)
}

void Oscillator::SharedCtor() {
  _cached_size_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Oscillator::~Oscillator() {
  // @@protoc_insertion_point(destructor:data_transf.Oscillator)
  SharedDtor();
}

void Oscillator::SharedDtor() {
  if (this != default_instance_) {
  }
}

void Oscillator::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Oscillator::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Oscillator_descriptor_;
}

const Oscillator& Oscillator::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_sim_5fdata_5ftransf_2eproto();
  return *default_instance_;
}

Oscillator* Oscillator::default_instance_ = NULL;

Oscillator* Oscillator::New() const {
  return new Oscillator;
}

void Oscillator::Clear() {
  reset_t_.Clear();
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Oscillator::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:data_transf.Oscillator)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated double reset_t = 1 [packed = true];
      case 1: {
        if (tag == 10) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, this->mutable_reset_t())));
        } else if (tag == 9) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 1, 10, input, this->mutable_reset_t())));
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:data_transf.Oscillator)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:data_transf.Oscillator)
  return false;
#undef DO_
}

void Oscillator::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:data_transf.Oscillator)
  // repeated double reset_t = 1 [packed = true];
  if (this->reset_t_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(1, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(_reset_t_cached_byte_size_);
  }
  for (int i = 0; i < this->reset_t_size(); i++) {
    ::google::protobuf::internal::WireFormatLite::WriteDoubleNoTag(
      this->reset_t(i), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:data_transf.Oscillator)
}

::google::protobuf::uint8* Oscillator::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:data_transf.Oscillator)
  // repeated double reset_t = 1 [packed = true];
  if (this->reset_t_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      1,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
      _reset_t_cached_byte_size_, target);
  }
  for (int i = 0; i < this->reset_t_size(); i++) {
    target = ::google::protobuf::internal::WireFormatLite::
      WriteDoubleNoTagToArray(this->reset_t(i), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:data_transf.Oscillator)
  return target;
}

int Oscillator::ByteSize() const {
  int total_size = 0;

  // repeated double reset_t = 1 [packed = true];
  {
    int data_size = 0;
    data_size = 8 * this->reset_t_size();
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(data_size);
    }
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _reset_t_cached_byte_size_ = data_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
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

void Oscillator::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Oscillator* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Oscillator*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Oscillator::MergeFrom(const Oscillator& from) {
  GOOGLE_CHECK_NE(&from, this);
  reset_t_.MergeFrom(from.reset_t_);
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Oscillator::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Oscillator::CopyFrom(const Oscillator& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Oscillator::IsInitialized() const {

  return true;
}

void Oscillator::Swap(Oscillator* other) {
  if (other != this) {
    reset_t_.Swap(&other->reset_t_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Oscillator::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Oscillator_descriptor_;
  metadata.reflection = Oscillator_reflection_;
  return metadata;
}


// ===================================================================

#ifndef _MSC_VER
const int Saddle_t_and_id::kSaddleIdFieldNumber;
const int Saddle_t_and_id::kSaddleTFieldNumber;
#endif  // !_MSC_VER

Saddle_t_and_id::Saddle_t_and_id()
  : ::google::protobuf::Message() {
  SharedCtor();
  // @@protoc_insertion_point(constructor:data_transf.Saddle_t_and_id)
}

void Saddle_t_and_id::InitAsDefaultInstance() {
}

Saddle_t_and_id::Saddle_t_and_id(const Saddle_t_and_id& from)
  : ::google::protobuf::Message() {
  SharedCtor();
  MergeFrom(from);
  // @@protoc_insertion_point(copy_constructor:data_transf.Saddle_t_and_id)
}

void Saddle_t_and_id::SharedCtor() {
  ::google::protobuf::internal::GetEmptyString();
  _cached_size_ = 0;
  saddle_id_ = const_cast< ::std::string*>(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  saddle_t_ = 0;
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
}

Saddle_t_and_id::~Saddle_t_and_id() {
  // @@protoc_insertion_point(destructor:data_transf.Saddle_t_and_id)
  SharedDtor();
}

void Saddle_t_and_id::SharedDtor() {
  if (saddle_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
    delete saddle_id_;
  }
  if (this != default_instance_) {
  }
}

void Saddle_t_and_id::SetCachedSize(int size) const {
  GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
  _cached_size_ = size;
  GOOGLE_SAFE_CONCURRENT_WRITES_END();
}
const ::google::protobuf::Descriptor* Saddle_t_and_id::descriptor() {
  protobuf_AssignDescriptorsOnce();
  return Saddle_t_and_id_descriptor_;
}

const Saddle_t_and_id& Saddle_t_and_id::default_instance() {
  if (default_instance_ == NULL) protobuf_AddDesc_sim_5fdata_5ftransf_2eproto();
  return *default_instance_;
}

Saddle_t_and_id* Saddle_t_and_id::default_instance_ = NULL;

Saddle_t_and_id* Saddle_t_and_id::New() const {
  return new Saddle_t_and_id;
}

void Saddle_t_and_id::Clear() {
  if (_has_bits_[0 / 32] & 3) {
    if (has_saddle_id()) {
      if (saddle_id_ != &::google::protobuf::internal::GetEmptyStringAlreadyInited()) {
        saddle_id_->clear();
      }
    }
    saddle_t_ = 0;
  }
  ::memset(_has_bits_, 0, sizeof(_has_bits_));
  mutable_unknown_fields()->Clear();
}

bool Saddle_t_and_id::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:data_transf.Saddle_t_and_id)
  for (;;) {
    ::std::pair< ::google::protobuf::uint32, bool> p = input->ReadTagWithCutoff(127);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // optional string saddle_id = 1;
      case 1: {
        if (tag == 10) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->mutable_saddle_id()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->saddle_id().data(), this->saddle_id().length(),
            ::google::protobuf::internal::WireFormat::PARSE,
            "saddle_id");
        } else {
          goto handle_unusual;
        }
        if (input->ExpectTag(17)) goto parse_saddle_t;
        break;
      }

      // optional double saddle_t = 2;
      case 2: {
        if (tag == 17) {
         parse_saddle_t:
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   double, ::google::protobuf::internal::WireFormatLite::TYPE_DOUBLE>(
                 input, &saddle_t_)));
          set_has_saddle_t();
        } else {
          goto handle_unusual;
        }
        if (input->ExpectAtEnd()) goto success;
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0 ||
            ::google::protobuf::internal::WireFormatLite::GetTagWireType(tag) ==
            ::google::protobuf::internal::WireFormatLite::WIRETYPE_END_GROUP) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:data_transf.Saddle_t_and_id)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:data_transf.Saddle_t_and_id)
  return false;
#undef DO_
}

void Saddle_t_and_id::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:data_transf.Saddle_t_and_id)
  // optional string saddle_id = 1;
  if (has_saddle_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->saddle_id().data(), this->saddle_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "saddle_id");
    ::google::protobuf::internal::WireFormatLite::WriteStringMaybeAliased(
      1, this->saddle_id(), output);
  }

  // optional double saddle_t = 2;
  if (has_saddle_t()) {
    ::google::protobuf::internal::WireFormatLite::WriteDouble(2, this->saddle_t(), output);
  }

  if (!unknown_fields().empty()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:data_transf.Saddle_t_and_id)
}

::google::protobuf::uint8* Saddle_t_and_id::SerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:data_transf.Saddle_t_and_id)
  // optional string saddle_id = 1;
  if (has_saddle_id()) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->saddle_id().data(), this->saddle_id().length(),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "saddle_id");
    target =
      ::google::protobuf::internal::WireFormatLite::WriteStringToArray(
        1, this->saddle_id(), target);
  }

  // optional double saddle_t = 2;
  if (has_saddle_t()) {
    target = ::google::protobuf::internal::WireFormatLite::WriteDoubleToArray(2, this->saddle_t(), target);
  }

  if (!unknown_fields().empty()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:data_transf.Saddle_t_and_id)
  return target;
}

int Saddle_t_and_id::ByteSize() const {
  int total_size = 0;

  if (_has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    // optional string saddle_id = 1;
    if (has_saddle_id()) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::StringSize(
          this->saddle_id());
    }

    // optional double saddle_t = 2;
    if (has_saddle_t()) {
      total_size += 1 + 8;
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

void Saddle_t_and_id::MergeFrom(const ::google::protobuf::Message& from) {
  GOOGLE_CHECK_NE(&from, this);
  const Saddle_t_and_id* source =
    ::google::protobuf::internal::dynamic_cast_if_available<const Saddle_t_and_id*>(
      &from);
  if (source == NULL) {
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
    MergeFrom(*source);
  }
}

void Saddle_t_and_id::MergeFrom(const Saddle_t_and_id& from) {
  GOOGLE_CHECK_NE(&from, this);
  if (from._has_bits_[0 / 32] & (0xffu << (0 % 32))) {
    if (from.has_saddle_id()) {
      set_saddle_id(from.saddle_id());
    }
    if (from.has_saddle_t()) {
      set_saddle_t(from.saddle_t());
    }
  }
  mutable_unknown_fields()->MergeFrom(from.unknown_fields());
}

void Saddle_t_and_id::CopyFrom(const ::google::protobuf::Message& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Saddle_t_and_id::CopyFrom(const Saddle_t_and_id& from) {
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Saddle_t_and_id::IsInitialized() const {

  return true;
}

void Saddle_t_and_id::Swap(Saddle_t_and_id* other) {
  if (other != this) {
    std::swap(saddle_id_, other->saddle_id_);
    std::swap(saddle_t_, other->saddle_t_);
    std::swap(_has_bits_[0], other->_has_bits_[0]);
    _unknown_fields_.Swap(&other->_unknown_fields_);
    std::swap(_cached_size_, other->_cached_size_);
  }
}

::google::protobuf::Metadata Saddle_t_and_id::GetMetadata() const {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::Metadata metadata;
  metadata.descriptor = Saddle_t_and_id_descriptor_;
  metadata.reflection = Saddle_t_and_id_reflection_;
  return metadata;
}


// @@protoc_insertion_point(namespace_scope)

}  // namespace data_transf

// @@protoc_insertion_point(global_scope)
