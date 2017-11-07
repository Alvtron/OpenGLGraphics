#include "Sphere.h"

Sphere::Sphere() : Mesh()
{
	createSphere(WIDTH, QUALITY);
}

Sphere::Sphere(const float width, const unsigned int quality)
{
	createSphere(width, quality);
}

Sphere::~Sphere()
{
}

void Sphere::createSphere(const float width, const unsigned int quality) {
	float radius = width / 2.0f;

	vertex.vertices = {
		vec3(-radius, 0.0f, -radius),
		vec3(+radius, 0.0f, -radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(+radius, 0.0f, -radius),
		vec3(+radius, 0.0f, +radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(+radius, 0.0f, +radius),
		vec3(-radius, 0.0f, +radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(-radius, 0.0f, +radius),
		vec3(-radius, 0.0f, -radius),
		vec3(0.0f, +radius, 0.0f),

		vec3(-radius, 0.0f, -radius),
		vec3(+radius, 0.0f, -radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(+radius, 0.0f, -radius),
		vec3(+radius, 0.0f, +radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(+radius, 0.0f, +radius),
		vec3(-radius, 0.0f, +radius),
		vec3(0.0f, -radius, 0.0f),

		vec3(-radius, 0.0f, +radius),
		vec3(-radius, 0.0f, -radius),
		vec3(0.0f, -radius, 0.0f)
	};

	vertex.uvs = {
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f),
		vec2(0.0f, 0.0f),
		vec2(1.0f, 0.0f),
		vec2(0.5f, 1.0f)
	};

	breakup(quality);

	for (int i = 0; i < vertex.vertices.size(); i++)
		vertex.vertices.at(i) = vec3::scale(vec3::normalize(vertex.vertices.at(i)), width);

	MeshUtility::createNormals(vertex);
	MeshUtility::createColors(vertex);
	MeshUtility::calculateTangents(vertex);
}

void Sphere::breakup(const unsigned int times) {
	std::vector<vec3> new_vertices;
	std::vector<vec2> new_uvs;
	for (int t = 0; t < times; t++) {
		for (int i = 0; i < vertex.vertices.size(); i += 3) {
			vec3 a = vertex.vertices.at(i + 0);
			vec3 b = vertex.vertices.at(i + 1);
			vec3 c = vertex.vertices.at(i + 2);

			vec3 na = midpoint(a, b);
			vec3 nb = midpoint(b, c);
			vec3 nc = midpoint(a, c);

			new_vertices.push_back(a);
			new_vertices.push_back(na);
			new_vertices.push_back(nc);

			new_vertices.push_back(na);
			new_vertices.push_back(nb);
			new_vertices.push_back(nc);

			new_vertices.push_back(na);
			new_vertices.push_back(b);
			new_vertices.push_back(nb);

			new_vertices.push_back(nc);
			new_vertices.push_back(nb);
			new_vertices.push_back(c);

			vec2 ta = vertex.uvs.at(i + 0);
			vec2 tb = vertex.uvs.at(i + 1);
			vec2 tc = vertex.uvs.at(i + 2);

			vec2 nta = midpoint(ta, tb);
			vec2 ntb = midpoint(tb, tc);
			vec2 ntc = midpoint(ta, tc);

			new_uvs.push_back(ta);
			new_uvs.push_back(nta);
			new_uvs.push_back(ntc);

			new_uvs.push_back(nta);
			new_uvs.push_back(ntb);
			new_uvs.push_back(ntc);

			new_uvs.push_back(nta);
			new_uvs.push_back(tb);
			new_uvs.push_back(ntb);

			new_uvs.push_back(ntc);
			new_uvs.push_back(ntb);
			new_uvs.push_back(tc);
		}
		vertex.vertices = new_vertices;
		vertex.uvs = new_uvs;
	}
}

vec3 Sphere::midpoint(const vec3 &a, const vec3 &b) {
	return vec3((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}

vec2 Sphere::midpoint(const vec2 &a, const vec2 &b) {
	return vec2((a.x + b.x) / 2, (a.y + b.y) / 2);
}