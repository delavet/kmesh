/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: api/filter/http_connection_manager.proto */

#ifndef PROTOBUF_C_api_2ffilter_2fhttp_5fconnection_5fmanager_2eproto__INCLUDED
#define PROTOBUF_C_api_2ffilter_2fhttp_5fconnection_5fmanager_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif


typedef struct _Filter__HttpConnectionManager Filter__HttpConnectionManager;


/* --- enums --- */


/* --- messages --- */

struct  _Filter__HttpConnectionManager
{
  ProtobufCMessage base;
  char *route_config_name;
};
#define FILTER__HTTP_CONNECTION_MANAGER__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&filter__http_connection_manager__descriptor) \
    , (char *)protobuf_c_empty_string }


/* Filter__HttpConnectionManager methods */
void   filter__http_connection_manager__init
                     (Filter__HttpConnectionManager         *message);
size_t filter__http_connection_manager__get_packed_size
                     (const Filter__HttpConnectionManager   *message);
size_t filter__http_connection_manager__pack
                     (const Filter__HttpConnectionManager   *message,
                      uint8_t             *out);
size_t filter__http_connection_manager__pack_to_buffer
                     (const Filter__HttpConnectionManager   *message,
                      ProtobufCBuffer     *buffer);
Filter__HttpConnectionManager *
       filter__http_connection_manager__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   filter__http_connection_manager__free_unpacked
                     (Filter__HttpConnectionManager *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Filter__HttpConnectionManager_Closure)
                 (const Filter__HttpConnectionManager *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor filter__http_connection_manager__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_api_2ffilter_2fhttp_5fconnection_5fmanager_2eproto__INCLUDED */
