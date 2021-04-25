// Part of the Eelbot Framework project, under the MIT License.
// Copyright (c) 2020 The Emseers.

#include "catch2/catch_test_macros.hpp"
#include "eelbot_framework/compression.hpp"

#include <fstream>
#include <memory>

inline std::string load_from_file(const std::string &filename) {
	std::ifstream file(filename);
	std::string   file_contents;

	file.seekg(0, std::ios::end);
	file_contents.reserve(file.tellg());
	file.seekg(0, std::ios::beg);

	file_contents.assign((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
	return file_contents;
}

TEST_CASE("a compressed message can be inflated", "[unit-test][compression]") {
	const std::string input = load_from_file("test/data/compressed_input_1.bin");

	eelbot_framework::zlib_inflate_context          z_context;
	std::unique_ptr<eelbot_framework::zlib_inflate> z_inflator;

	SECTION("inflate with a large chunk size") {
		z_context.chunk_size = 65536;
		z_inflator           = std::make_unique<eelbot_framework::zlib_inflate>(z_context);
	}

	SECTION("inflate with a small chunk size") {
		z_context.chunk_size = 1;
		z_inflator           = std::make_unique<eelbot_framework::zlib_inflate>(z_context);
	}

	z_inflator->push(input);

	REQUIRE(z_inflator->get_result() == "Time is an illusion. Lunchtime doubly so.");
}

TEST_CASE("a piecewise compressed message can be inflated", "[unit-test][compression]") {
	const std::string input = load_from_file("test/data/compressed_input_2.bin");

	// Split the input into three parts.
	const size_t      part_size = input.size() / 3;
	const std::string input_1   = input.substr(0, part_size);
	const std::string input_2   = input.substr(part_size, part_size);
	const std::string input_3   = input.substr(2 * part_size);

	eelbot_framework::zlib_inflate_context          z_context;
	std::unique_ptr<eelbot_framework::zlib_inflate> z_inflator;

	SECTION("inflate with a large chunk size") {
		z_context.chunk_size = 65536;
		z_inflator           = std::make_unique<eelbot_framework::zlib_inflate>(z_context);
	}

	SECTION("inflate with a small chunk size") {
		z_context.chunk_size = 1;
		z_inflator           = std::make_unique<eelbot_framework::zlib_inflate>(z_context);
	}

	z_inflator->push(input_1);
	z_inflator->push(input_2);
	z_inflator->push(input_3);

	REQUIRE(z_inflator->get_result() ==
	        "It is known that there are an infinite number of worlds, simply because there is an infinite amount of "
	        "space for them to be in. However, not every one of them is inhabited. Therefore, there must be a finite "
	        "number of inhabited worlds. Any finite number divided by infinity is as near to nothing as makes no odds, "
	        "so the average population of all the planets in the Universe can be said to be zero. From this it follows "
	        "that the population of the whole Universe is also zero, and that any people you may meet from time to "
	        "time are merely the products of a deranged imagination.");
}
