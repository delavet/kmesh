/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: api/listener/listener.proto */

/* Do not generate deprecated warnings for self */
#ifndef PROTOBUF_C__NO_DEPRECATED
#define PROTOBUF_C__NO_DEPRECATED
#endif

#include "listener/listener.pb-c.h"
void   listener__listener__init
                     (Listener__Listener         *message)
{
  static const Listener__Listener init_value = LISTENER__LISTENER__INIT;
  *message = init_value;
}
size_t listener__listener__get_packed_size
                     (const Listener__Listener *message)
{
  assert(message->base.descriptor == &listener__listener__descriptor);
  return protobuf_c_message_get_packed_size ((const ProtobufCMessage*)(message));
}
size_t listener__listener__pack
                     (const Listener__Listener *message,
                      uint8_t       *out)
{
  assert(message->base.descriptor == &listener__listener__descriptor);
  return protobuf_c_message_pack ((const ProtobufCMessage*)message, out);
}
size_t listener__listener__pack_to_buffer
                     (const Listener__Listener *message,
                      ProtobufCBuffer *buffer)
{
  assert(message->base.descriptor == &listener__listener__descriptor);
  return protobuf_c_message_pack_to_buffer ((const ProtobufCMessage*)message, buffer);
}
Listener__Listener *
       listener__listener__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data)
{
  return (Listener__Listener *)
     protobuf_c_message_unpack (&listener__listener__descriptor,
                                allocator, len, data);
}
void   listener__listener__free_unpacked
                     (Listener__Listener *message,
                      ProtobufCAllocator *allocator)
{
  if(!message)
    return;
  assert(message->base.descriptor == &listener__listener__descriptor);
  protobuf_c_message_free_unpacked ((ProtobufCMessage*)message, allocator);
}
static const ProtobufCFieldDescriptor listener__listener__field_descriptors[3] =
{
  {
    "name",
    1,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_STRING,
    0,   /* quantifier_offset */
    offsetof(Listener__Listener, name),
    NULL,
    &protobuf_c_empty_string,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "address",
    2,
    PROTOBUF_C_LABEL_NONE,
    PROTOBUF_C_TYPE_MESSAGE,
    0,   /* quantifier_offset */
    offsetof(Listener__Listener, address),
    &core__socket_address__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
  {
    "filter_chains",
    3,
    PROTOBUF_C_LABEL_REPEATED,
    PROTOBUF_C_TYPE_MESSAGE,
    offsetof(Listener__Listener, n_filter_chains),
    offsetof(Listener__Listener, filter_chains),
    &listener__filter_chain__descriptor,
    NULL,
    0,             /* flags */
    0,NULL,NULL    /* reserved1,reserved2, etc */
  },
};
static const unsigned listener__listener__field_indices_by_name[] = {
  1,   /* field[1] = address */
  2,   /* field[2] = filter_chains */
  0,   /* field[0] = name */
};
static const ProtobufCIntRange listener__listener__number_ranges[1 + 1] =
{
  { 1, 0 },
  { 0, 3 }
};
const ProtobufCMessageDescriptor listener__listener__descriptor =
{
  PROTOBUF_C__MESSAGE_DESCRIPTOR_MAGIC,
  "listener.Listener",
  "Listener",
  "Listener__Listener",
  "listener",
  sizeof(Listener__Listener),
  3,
  listener__listener__field_descriptors,
  listener__listener__field_indices_by_name,
  1,  listener__listener__number_ranges,
  (ProtobufCMessageInit) listener__listener__init,
  NULL,NULL,NULL    /* reserved[123] */
};
