/*
 * @file   tiledb_serialization.h
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2019 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This file declares the TileDB C API for serialization.
 */

#ifndef TILEDB_SERIALIZATION_H
#define TILEDB_SERIALIZATION_H

#include "tiledb.h"

#ifdef __cplusplus
extern "C" {
#endif

/** Serialization type. */
typedef enum {
/** Helper macro for defining array type enums. */
#define TILEDB_SERIALIZATION_TYPE_ENUM(id) TILEDB_##id
#include "tiledb_enum.h"
#undef TILEDB_SERIALIZATION_TYPE_ENUM
} tiledb_serialization_type_t;

/* ****************************** */
/*          Serialization         */
/* ****************************** */

/**
 * Serializes the given array schema.
 *
 * @param ctx The TileDB context.
 * @param array_schema The array schema to serialize.
 * @param serialization_type Type of serialization to use
 * @param client_side If set to 1, deserialize from "client-side" perspective.
 *    Else, "server-side."
 * @param buffer Buffer to serialize to
 * @return `TILEDB_OK` for success and `TILEDB_ERR` for error.
 */
TILEDB_EXPORT int32_t tiledb_serialize_array_schema(
    tiledb_ctx_t* ctx,
    const tiledb_array_schema_t* array_schema,
    tiledb_serialization_type_t serialize_type,
    int32_t client_side,
    tiledb_buffer_t* buffer);

/**
 * Deserializes a new array schema from the given buffer.
 *
 * @param ctx The TileDB context.
 * @param buffer Buffer to deserialize from
 * @param serialization_type Type of serialization to use
 * @param client_side If set to 1, deserialize from "client-side" perspective.
 *    Else, "server-side."
 * @param array_schema Will be set to a newly allocated array schema.
 * @return `TILEDB_OK` for success and `TILEDB_ERR` for error.
 */
TILEDB_EXPORT int32_t tiledb_deserialize_array_schema(
    tiledb_ctx_t* ctx,
    const tiledb_buffer_t* buffer,
    tiledb_serialization_type_t serialize_type,
    int32_t client_side,
    tiledb_array_schema_t** array_schema);

/**
 * Serializes the given query.
 *
 * Where possible the serialization is zero-copy. The returned buffer list
 * contains an ordered list of pointers to buffers that logically contain the
 * entire serialized query when concatenated.
 *
 * @note The caller must free the returned `tiledb_buffer_list_t`.
 *
 * @param ctx The TileDB context.
 * @param query The query.
 * @param serialization_type Type of serialization to use
 * @param client_side If set to 1, deserialize from "client-side" perspective.
 *    Else, "server-side."
 * @param buffer_list Will be set to a newly allocated buffer list containing
 *    the serialized query.
 * @return `TILEDB_OK` for success and `TILEDB_ERR` for error.
 */
TILEDB_EXPORT int32_t tiledb_serialize_query(
    tiledb_ctx_t* ctx,
    const tiledb_query_t* query,
    tiledb_serialization_type_t serialize_type,
    int32_t client_side,
    tiledb_buffer_list_t** buffer_list);

/**
 * Deserializes into an existing query from the given buffer.
 *
 * @note The deserialization is zero-copy, so the source buffer must exceed
 * the lifetime of the query being deserialized to.
 *
 * @param ctx The TileDB context.
 * @param buffer Buffer to deserialize from
 * @param serialization_type Type of deserialization to use
 * @param client_side If set to 1, deserialize from "client-side" perspective.
 *    Else, "server-side."
 * @param query The query object to deserialize into (must be pre-allocated).
 * @return `TILEDB_OK` for success and `TILEDB_ERR` for error.
 */
TILEDB_EXPORT int32_t tiledb_deserialize_query(
    tiledb_ctx_t* ctx,
    const tiledb_buffer_t* buffer,
    tiledb_serialization_type_t serialize_type,
    int32_t client_side,
    tiledb_query_t* query);

/**
 * Serializes the given non-empty domain information into the given buffer.
 *
 * @param ctx The TileDB context.
 * @param array Array to which the domain belongs to
 * @param nonempty_domain The domain to serialize
 * @param is_empty 1 if the domain is empty
 * @param serialization_type Type of serialization to use
 * @param client_side If set to 1, serialize from "client-side" perspective.
 *    Else, "server-side."
 * @param buffer Buffer to serialize to
 * @return `TILEDB_OK` for success and `TILEDB_ERR` for error.
 */
TILEDB_EXPORT int32_t tiledb_serialize_array_nonempty_domain(
    tiledb_ctx_t* ctx,
    const tiledb_array_t* array,
    const void* nonempty_domain,
    int32_t is_empty,
    tiledb_serialization_type_t serialize_type,
    int32_t client_side,
    tiledb_buffer_t* buffer);

/**
 * Deserializes non-empty domain information from the given buffer.
 *
 * @param ctx The TileDB context.
 * @param array Array to which the domain belongs to
 * @param buffer Buffer to deserialize from
 * @param serialization_type Type of deserialization to use
 * @param client_side If set to 1, deserialize from "client-side" perspective.
 *    Else, "server-side."
 * @param nonempty_domain The buffer to deserialize into
 * @param is_empty Will be set to 1 if the domain is empty
 * @return `TILEDB_OK` for success and `TILEDB_ERR` for error.
 */
TILEDB_EXPORT int32_t tiledb_deserialize_array_nonempty_domain(
    tiledb_ctx_t* ctx,
    const tiledb_array_t* array,
    const tiledb_buffer_t* buffer,
    tiledb_serialization_type_t serialize_type,
    int32_t client_side,
    void* nonempty_domain,
    int32_t* is_empty);

#ifdef __cplusplus
}
#endif

#endif  // TILEDB_SERIALIZATION_H