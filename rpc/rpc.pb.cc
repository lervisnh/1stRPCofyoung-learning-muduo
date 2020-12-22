// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: rpc.proto

#include "rpc.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
namespace RPCServices {
class RpcMessageDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<RpcMessage> _instance;
} _RpcMessage_default_instance_;
}  // namespace RPCServices
static void InitDefaultsscc_info_RpcMessage_rpc_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::RPCServices::_RpcMessage_default_instance_;
    new (ptr) ::RPCServices::RpcMessage();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::RPCServices::RpcMessage::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_RpcMessage_rpc_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_RpcMessage_rpc_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_rpc_2eproto[1];
static const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* file_level_enum_descriptors_rpc_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_rpc_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_rpc_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, type_),
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, id_),
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, service_),
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, method_),
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, request_),
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, response_),
  PROTOBUF_FIELD_OFFSET(::RPCServices::RpcMessage, error_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::RPCServices::RpcMessage)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::RPCServices::_RpcMessage_default_instance_),
};

const char descriptor_table_protodef_rpc_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\trpc.proto\022\013RPCServices\"\253\001\n\nRpcMessage\022"
  "&\n\004type\030\001 \001(\0162\030.RPCServices.MessageType\022"
  "\n\n\002id\030\002 \001(\006\022\017\n\007service\030\003 \001(\t\022\016\n\006method\030\004"
  " \001(\t\022\017\n\007request\030\005 \001(\014\022\020\n\010response\030\006 \001(\014\022"
  "%\n\005error\030\007 \001(\0162\026.RPCServices.ErrorCode*>"
  "\n\013MessageType\022\t\n\005VALID\020\000\022\013\n\007REQUEST\020\001\022\014\n"
  "\010RESPONSE\020\002\022\t\n\005ERROR\020\003*\201\001\n\tErrorCode\022\014\n\010"
  "NO_ERROR\020\000\022\017\n\013WRONG_PROTO\020\001\022\016\n\nNO_SERVIC"
  "E\020\002\022\r\n\tNO_METHOD\020\003\022\023\n\017INVALID_REQUEST\020\004\022"
  "\024\n\020INVALID_RESPONSE\020\005\022\013\n\007TIMEOUT\020\006b\006prot"
  "o3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_rpc_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_rpc_2eproto_sccs[1] = {
  &scc_info_RpcMessage_rpc_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_rpc_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_rpc_2eproto = {
  false, false, descriptor_table_protodef_rpc_2eproto, "rpc.proto", 402,
  &descriptor_table_rpc_2eproto_once, descriptor_table_rpc_2eproto_sccs, descriptor_table_rpc_2eproto_deps, 1, 0,
  schemas, file_default_instances, TableStruct_rpc_2eproto::offsets,
  file_level_metadata_rpc_2eproto, 1, file_level_enum_descriptors_rpc_2eproto, file_level_service_descriptors_rpc_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_rpc_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_rpc_2eproto)), true);
namespace RPCServices {
const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* MessageType_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_rpc_2eproto);
  return file_level_enum_descriptors_rpc_2eproto[0];
}
bool MessageType_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
      return true;
    default:
      return false;
  }
}

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ErrorCode_descriptor() {
  ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&descriptor_table_rpc_2eproto);
  return file_level_enum_descriptors_rpc_2eproto[1];
}
bool ErrorCode_IsValid(int value) {
  switch (value) {
    case 0:
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
    case 6:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void RpcMessage::InitAsDefaultInstance() {
}
class RpcMessage::_Internal {
 public:
};

RpcMessage::RpcMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:RPCServices.RpcMessage)
}
RpcMessage::RpcMessage(const RpcMessage& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  service_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_service().empty()) {
    service_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_service(),
      GetArena());
  }
  method_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_method().empty()) {
    method_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_method(),
      GetArena());
  }
  request_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_request().empty()) {
    request_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_request(),
      GetArena());
  }
  response_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_response().empty()) {
    response_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_response(),
      GetArena());
  }
  ::memcpy(&id_, &from.id_,
    static_cast<size_t>(reinterpret_cast<char*>(&error_) -
    reinterpret_cast<char*>(&id_)) + sizeof(error_));
  // @@protoc_insertion_point(copy_constructor:RPCServices.RpcMessage)
}

void RpcMessage::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_RpcMessage_rpc_2eproto.base);
  service_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  method_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  request_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  response_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&error_) -
      reinterpret_cast<char*>(&id_)) + sizeof(error_));
}

RpcMessage::~RpcMessage() {
  // @@protoc_insertion_point(destructor:RPCServices.RpcMessage)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void RpcMessage::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  service_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  method_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  request_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  response_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}

void RpcMessage::ArenaDtor(void* object) {
  RpcMessage* _this = reinterpret_cast< RpcMessage* >(object);
  (void)_this;
}
void RpcMessage::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void RpcMessage::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const RpcMessage& RpcMessage::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_RpcMessage_rpc_2eproto.base);
  return *internal_default_instance();
}


void RpcMessage::Clear() {
// @@protoc_insertion_point(message_clear_start:RPCServices.RpcMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  service_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  method_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  request_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  response_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::memset(&id_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&error_) -
      reinterpret_cast<char*>(&id_)) + sizeof(error_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* RpcMessage::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .RPCServices.MessageType type = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_type(static_cast<::RPCServices::MessageType>(val));
        } else goto handle_unusual;
        continue;
      // fixed64 id = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 17)) {
          id_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<::PROTOBUF_NAMESPACE_ID::uint64>(ptr);
          ptr += sizeof(::PROTOBUF_NAMESPACE_ID::uint64);
        } else goto handle_unusual;
        continue;
      // string service = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 26)) {
          auto str = _internal_mutable_service();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "RPCServices.RpcMessage.service"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string method = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 34)) {
          auto str = _internal_mutable_method();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "RPCServices.RpcMessage.method"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes request = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 42)) {
          auto str = _internal_mutable_request();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // bytes response = 6;
      case 6:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 50)) {
          auto str = _internal_mutable_response();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // .RPCServices.ErrorCode error = 7;
      case 7:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 56)) {
          ::PROTOBUF_NAMESPACE_ID::uint64 val = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
          _internal_set_error(static_cast<::RPCServices::ErrorCode>(val));
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* RpcMessage::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:RPCServices.RpcMessage)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .RPCServices.MessageType type = 1;
  if (this->type() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      1, this->_internal_type(), target);
  }

  // fixed64 id = 2;
  if (this->id() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteFixed64ToArray(2, this->_internal_id(), target);
  }

  // string service = 3;
  if (this->service().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_service().data(), static_cast<int>(this->_internal_service().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RPCServices.RpcMessage.service");
    target = stream->WriteStringMaybeAliased(
        3, this->_internal_service(), target);
  }

  // string method = 4;
  if (this->method().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_method().data(), static_cast<int>(this->_internal_method().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "RPCServices.RpcMessage.method");
    target = stream->WriteStringMaybeAliased(
        4, this->_internal_method(), target);
  }

  // bytes request = 5;
  if (this->request().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        5, this->_internal_request(), target);
  }

  // bytes response = 6;
  if (this->response().size() > 0) {
    target = stream->WriteBytesMaybeAliased(
        6, this->_internal_response(), target);
  }

  // .RPCServices.ErrorCode error = 7;
  if (this->error() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteEnumToArray(
      7, this->_internal_error(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:RPCServices.RpcMessage)
  return target;
}

size_t RpcMessage::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:RPCServices.RpcMessage)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string service = 3;
  if (this->service().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_service());
  }

  // string method = 4;
  if (this->method().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_method());
  }

  // bytes request = 5;
  if (this->request().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_request());
  }

  // bytes response = 6;
  if (this->response().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::BytesSize(
        this->_internal_response());
  }

  // fixed64 id = 2;
  if (this->id() != 0) {
    total_size += 1 + 8;
  }

  // .RPCServices.MessageType type = 1;
  if (this->type() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_type());
  }

  // .RPCServices.ErrorCode error = 7;
  if (this->error() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::EnumSize(this->_internal_error());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void RpcMessage::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:RPCServices.RpcMessage)
  GOOGLE_DCHECK_NE(&from, this);
  const RpcMessage* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<RpcMessage>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:RPCServices.RpcMessage)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:RPCServices.RpcMessage)
    MergeFrom(*source);
  }
}

void RpcMessage::MergeFrom(const RpcMessage& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:RPCServices.RpcMessage)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.service().size() > 0) {
    _internal_set_service(from._internal_service());
  }
  if (from.method().size() > 0) {
    _internal_set_method(from._internal_method());
  }
  if (from.request().size() > 0) {
    _internal_set_request(from._internal_request());
  }
  if (from.response().size() > 0) {
    _internal_set_response(from._internal_response());
  }
  if (from.id() != 0) {
    _internal_set_id(from._internal_id());
  }
  if (from.type() != 0) {
    _internal_set_type(from._internal_type());
  }
  if (from.error() != 0) {
    _internal_set_error(from._internal_error());
  }
}

void RpcMessage::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:RPCServices.RpcMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void RpcMessage::CopyFrom(const RpcMessage& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:RPCServices.RpcMessage)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool RpcMessage::IsInitialized() const {
  return true;
}

void RpcMessage::InternalSwap(RpcMessage* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  service_.Swap(&other->service_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  method_.Swap(&other->method_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  request_.Swap(&other->request_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  response_.Swap(&other->response_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(RpcMessage, error_)
      + sizeof(RpcMessage::error_)
      - PROTOBUF_FIELD_OFFSET(RpcMessage, id_)>(
          reinterpret_cast<char*>(&id_),
          reinterpret_cast<char*>(&other->id_));
}

::PROTOBUF_NAMESPACE_ID::Metadata RpcMessage::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace RPCServices
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::RPCServices::RpcMessage* Arena::CreateMaybeMessage< ::RPCServices::RpcMessage >(Arena* arena) {
  return Arena::CreateMessageInternal< ::RPCServices::RpcMessage >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
