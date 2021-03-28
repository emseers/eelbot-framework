// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#ifndef EELBOT_FRAMEWORK_COMPRESSION_H
#define EELBOT_FRAMEWORK_COMPRESSION_H

#include "zlib.h"

#include <mutex>
#include <string>

namespace eelbot_framework {

/**
 * @brief The context for a zlib_inflate object.
 */
struct zlib_inflate_context {
	int chunk_size = 65536;
};

/**
 * @brief An object to decompress a deflate stream.
 */
class zlib_inflate {
private:
	mutable std::mutex  mutex;
	int                 chunk_size;
	z_stream            stream;
	mutable std::string result;

public:
	zlib_inflate(const zlib_inflate_context &context);
	~zlib_inflate();

	/**
	 * @brief Pushes additional data to the decompress buffer.
	 *
	 * @param data The data to push.
	 */
	void push(const std::string &data);

	/**
	 * @brief Gets the decompressed result.
	 *
	 * @return THe decompressed result.
	 */
	std::string get_result();
};

} // namespace eelbot_framework

#endif
