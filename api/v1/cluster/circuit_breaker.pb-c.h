/* Generated by the protocol buffer compiler.  DO NOT EDIT! */
/* Generated from: api/cluster/circuit_breaker.proto */

#ifndef PROTOBUF_C_api_2fcluster_2fcircuit_5fbreaker_2eproto__INCLUDED
#define PROTOBUF_C_api_2fcluster_2fcircuit_5fbreaker_2eproto__INCLUDED

#include <protobuf-c/protobuf-c.h>

PROTOBUF_C__BEGIN_DECLS

#if PROTOBUF_C_VERSION_NUMBER < 1003000
# error This file was generated by a newer version of protoc-c which is incompatible with your libprotobuf-c headers. Please update your headers.
#elif 1003002 < PROTOBUF_C_MIN_COMPILER_VERSION
# error This file was generated by an older version of protoc-c which is incompatible with your libprotobuf-c headers. Please regenerate this file with a newer version of protoc-c.
#endif

#include "core/base.pb-c.h"

typedef struct _Cluster__CircuitBreakers Cluster__CircuitBreakers;


/* --- enums --- */


/* --- messages --- */

struct  _Cluster__CircuitBreakers
{
  ProtobufCMessage base;
  Core__RoutingPriority priority;
  uint32_t max_connections;
  uint32_t max_pending_requests;
  uint32_t max_requests;
  uint32_t max_retries;
  uint32_t max_connection_pools;
};
#define CLUSTER__CIRCUIT_BREAKERS__INIT \
 { PROTOBUF_C_MESSAGE_INIT (&cluster__circuit_breakers__descriptor) \
    , CORE__ROUTING_PRIORITY__DEFAULT, 0, 0, 0, 0, 0 }


/* Cluster__CircuitBreakers methods */
void   cluster__circuit_breakers__init
                     (Cluster__CircuitBreakers         *message);
size_t cluster__circuit_breakers__get_packed_size
                     (const Cluster__CircuitBreakers   *message);
size_t cluster__circuit_breakers__pack
                     (const Cluster__CircuitBreakers   *message,
                      uint8_t             *out);
size_t cluster__circuit_breakers__pack_to_buffer
                     (const Cluster__CircuitBreakers   *message,
                      ProtobufCBuffer     *buffer);
Cluster__CircuitBreakers *
       cluster__circuit_breakers__unpack
                     (ProtobufCAllocator  *allocator,
                      size_t               len,
                      const uint8_t       *data);
void   cluster__circuit_breakers__free_unpacked
                     (Cluster__CircuitBreakers *message,
                      ProtobufCAllocator *allocator);
/* --- per-message closures --- */

typedef void (*Cluster__CircuitBreakers_Closure)
                 (const Cluster__CircuitBreakers *message,
                  void *closure_data);

/* --- services --- */


/* --- descriptors --- */

extern const ProtobufCMessageDescriptor cluster__circuit_breakers__descriptor;

PROTOBUF_C__END_DECLS


#endif  /* PROTOBUF_C_api_2fcluster_2fcircuit_5fbreaker_2eproto__INCLUDED */
