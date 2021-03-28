// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "eelbot_framework/compression.hpp"

#include <stdexcept>

namespace eelbot_framework {

class clear_result {
private:
	std::string *result_ptr;

public:
	clear_result(std::string *result) {
		if (!result) {
			throw std::logic_error("result cannot be nullptr");
		}

		this->result_ptr = result;
	}

	~clear_result() {
		result_ptr->clear();
	}
};

zlib_inflate::zlib_inflate(const zlib_inflate_context &context) : chunk_size(context.chunk_size) {
	if (this->chunk_size <= 0) {
		throw std::logic_error("invalid chunk size: " + std::to_string(this->chunk_size));
	}

	this->stream.zalloc = Z_NULL;
	this->stream.zfree  = Z_NULL;
	this->stream.opaque = Z_NULL;

	int status_code = inflateInit(&(this->stream));
	if (status_code != Z_OK) {
		inflateEnd(&(this->stream));
		throw std::runtime_error("zlib inflateInit failed; status code=" + std::to_string(status_code));
	}
}

zlib_inflate::~zlib_inflate() {
	std::scoped_lock lock(this->mutex);
	inflateEnd(&(this->stream));
}

void zlib_inflate::push(const std::string &data) {
	std::scoped_lock lock(this->mutex);
	this->stream.avail_in = (uInt)data.size();
	this->stream.next_in  = (Bytef *)data.data();

	int      status_code;
	char     buf[this->chunk_size];
	unsigned buf_size = 0;

	do {
		this->stream.avail_out = (uInt)(this->chunk_size - buf_size);
		this->stream.next_out  = (Bytef *)(buf + buf_size);

		status_code = inflate(&(this->stream), Z_SYNC_FLUSH);

		unsigned old_buf_size = buf_size;
		buf_size              = this->chunk_size - this->stream.avail_out;

		// If the stream end has been reached, reset the stream.
		if (status_code == Z_STREAM_END) {
			status_code = inflateReset(&(this->stream));
		}

		// If the buffer is full, flush it out to result and clear it.
		if (buf_size == chunk_size) {
			this->result.append(buf, buf_size);
			buf_size = 0;
			continue;
		}

		// If there was no change to the output buffer, flush it out to result and break.
		if (buf_size == old_buf_size) {
			this->result.append(buf, buf_size);
			break;
		}
	} while (status_code == Z_OK || status_code == Z_BUF_ERROR);

	if (status_code != Z_OK && status_code != Z_BUF_ERROR) {
		throw std::runtime_error("zlib error; status code=" + std::to_string(status_code));
	}
}

std::string zlib_inflate::get_result() {
	std::scoped_lock lock(this->mutex);
	clear_result     clear_after_return(&(this->result));
	return this->result;
}

} // namespace eelbot_framework
