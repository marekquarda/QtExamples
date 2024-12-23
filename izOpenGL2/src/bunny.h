/**
 * @file
 * @brief This file contains model of Standford bunny in static arrays.
 *
 * @author Tomáš Milet, imilet@fit.vutbr.cz
 * @author Dominik Harmim <harmim6@gmail.com>
 */


#pragma once

#include <stdint.h>

/**
 * @brief This structure represents vertex that contains only position and
 * normal.
 */
typedef struct BunnyVertex
{
	float position[3];  ///< position of vertex
	float normal[3];    ///< normal of vertex
} BunnyVertex;


/// This variable contains vertices of Standford bunny.
extern const BunnyVertex bunnyVertices[1048];

using VertexIndex = uint32_t; // < type of index

/// This variable contains Standford bunny indices.
extern const VertexIndex bunnyIndices[2092][3];

