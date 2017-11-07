#pragma once
#include <vector>
#include "maths.h"
#include "Vertex.h"
struct MeshUtility
{
	/* Calculate the normals of each vertex, https://www.khronos.org/opengl/wiki/Calculating_a_Surface_Normal */
	static void createNormals(Vertex &vertex) {
		vertex.normals.clear();

		if (vertex.hasIndices())
		{
			for (unsigned int i = 0; i < vertex.indices.size(); i += 3) {
				vec3 p1 = vertex.vertices.at(vertex.indices.at(i + 0));
				vec3 p2 = vertex.vertices.at(vertex.indices.at(i + 1));
				vec3 p3 = vertex.vertices.at(vertex.indices.at(i + 2));

				vec3 U = vec3(p2 - p1);
				vec3 V = vec3(p3 - p1);

				vec3 normal = vec3::cross(U, V);

				vertex.normals.insert(vertex.normals.end(), 3, normal);
			}
		}
		else {
			for (unsigned int i = 0; i < vertex.size(); i += 3) {
				vec3 p1 = vertex.vertices.at(i + 0);
				vec3 p2 = vertex.vertices.at(i + 1);
				vec3 p3 = vertex.vertices.at(i + 2);

				vec3 U = vec3(p2 - p1);
				vec3 V = vec3(p3 - p1);

				vec3 normal = vec3::cross(U, V);

				vertex.normals.insert(vertex.normals.end(), 3, normal);
			}
		}
	}

	/* Calculate tangent vectors for all triangles */
	static void createColors(Vertex &vertex, const vec3 &color = vec3(1.0f, 1.0f, 1.0f)) {
		vertex.colors = std::vector<vec3>(vertex.size(), color);
	}

	/* Calculate tangent vectors for all triangles */
	static void calculateTangents(Vertex &vertex) {
		
		// Remove any previous tangents and bitangents
		vertex.tangents.clear();
		vertex.bitangents.clear();
		
		if (vertex.hasIndices())
		{
			for (unsigned int i = 0; i < vertex.indices.size(); i += 3) {
				// Shortcuts for vertices
				vec3 p1 = vertex.vertices.at(vertex.indices.at(i + 0));
				vec3 p2 = vertex.vertices.at(vertex.indices.at(i + 1));
				vec3 p3 = vertex.vertices.at(vertex.indices.at(i + 2));

				// Shortcuts for UVs
				vec2 uv1 = vertex.uvs.at(vertex.indices.at(i + 0));
				vec2 uv2 = vertex.uvs.at(vertex.indices.at(i + 1));
				vec2 uv3 = vertex.uvs.at(vertex.indices.at(i + 2));

				// Edges of the triangle : postion delta
				vec3 deltaPos1 = p2 - p1;
				vec3 deltaPos2 = p3 - p1;

				// UV delta
				vec2 deltaUV1 = uv2 - uv1;
				vec2 deltaUV2 = uv3 - uv1;

				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
				vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

				// Set the same tangent for all three vertices of the triangle.
				// They will be merged later, in vboindexer.cpp
				vertex.tangents.push_back(tangent);
				vertex.tangents.push_back(tangent);
				vertex.tangents.push_back(tangent);

				// Same thing for binormals
				vertex.bitangents.push_back(bitangent);
				vertex.bitangents.push_back(bitangent);
				vertex.bitangents.push_back(bitangent);
			}
		}
		else {
			for (unsigned int i = 0; i < vertex.size(); i += 3) {
				// Shortcuts for vertices
				vec3 p1 = vertex.vertices.at(i + 0);
				vec3 p2 = vertex.vertices.at(i + 1);
				vec3 p3 = vertex.vertices.at(i + 2);

				// Shortcuts for UVs
				vec2 uv1 = vertex.uvs.at(i + 0);
				vec2 uv2 = vertex.uvs.at(i + 1);
				vec2 uv3 = vertex.uvs.at(i + 2);

				// Edges of the triangle : postion delta
				vec3 deltaPos1 = p2 - p1;
				vec3 deltaPos2 = p3 - p1;

				// UV delta
				vec2 deltaUV1 = uv2 - uv1;
				vec2 deltaUV2 = uv3 - uv1;

				float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
				vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y)*r;
				vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x)*r;

				// Set the same tangent for all three vertices of the triangle.
				// They will be merged later, in vboindexer.cpp
				vertex.tangents.push_back(tangent);
				vertex.tangents.push_back(tangent);
				vertex.tangents.push_back(tangent);

				// Same thing for binormals
				vertex.bitangents.push_back(bitangent);
				vertex.bitangents.push_back(bitangent);
				vertex.bitangents.push_back(bitangent);
			}
		}	
	}
};

