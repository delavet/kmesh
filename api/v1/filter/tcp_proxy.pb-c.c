/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: api/filter/tcp_proxy.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "filter/tcp_proxy.pb-c.h"
void   filter__tcp_proxy__init
                     (Filter__TcpProxy         *message)
{
  static const Filter__TcpProxy init_value = FILTER__TCP_PROXY__INIT;
  *message = init_value;
}
size_t filter__tcp_proxy__get_packed_size
                     (const Filter__TcpProxy *message)
{
  assert(message->base.descriptor == &filter__tcp_proxy__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t filter__tcp_proxy__pack
                     (const Filter__TcpProxy *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &filter__tcp_proxy__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t filter__tcp_proxy__pack_to_buffer
                     (const Filter__TcpProxy *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &filter__tcp_proxy__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Filter__TcpProxy *
       filter__tcp_proxy__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Filter__TcpProxy *)
     protobuf_c_message_unpack (&filter__tcp_proxy__descriptor,
                                allocator, len, data);
}
void   filter__tcp_proxy__free_unpacked
                     (Filter__TcpProxy *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &filter__tcp_proxy__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor filter__tcp_proxy__field_descriptors[1] =
{
  {
    "cluster",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Filter__TcpProxy, cluster),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned filter__tcp_proxy__field_indices_by_name[] = {
  0,   /* field[0] = cluster */
};
static const ProtobufCIntRange filter__tcp_proxy__number_ranges[1 + 1] =
{
  { 2, 0 },
  { 0, 1 }
};
const ProtobufCMessageDescriptor filter__tcp_proxy__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "filter.TcpProxy",
  "TcpProxy",
  "Filter__TcpProxy",
  "filter",
  sizeof(Filter__TcpProxy),
  1,
  filter__tcp_proxy__field_descriptors,
  filter__tcp_proxy__field_indices_by_name,
  1,  filter__tcp_proxy__number_ranges,
  (ProtobufCMessageInit) filter__tcp_proxy__init,
  NULL,NULL,NULL    /* reserved[123] */
};
