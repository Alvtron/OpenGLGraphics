#include "Sphere.h"

unsigned int Sphere::num_spheres = 0;

Sphere::Sphere() : Mesh()
{
	num_spheres++;
}

Sphere::Sphere(float size, unsigned int quality)
{
	Diamond diamond = Diamond(1.0f);
	vertices = diamond.getVertices();
	normals = diamond.getNormals();
	colors = diamond.getColors();
	textures = diamond.getTextures();

	breakup(quality);

	for (int i = 0; i < vertices.size(); i++)
		vertices.at(i) = vec3::scale(vec3::normalize(vertices.at(i)), size);

	Mesh::createVertexData(vertices, normals, colors, textures);
	num_spheres++;
}

Sphere::~Sphere()
{
	num_spheres--;
}

void Sphere::breakup(unsigned int times) {
	std::vector<vec3> new_vertices;
	std::vector<vec3> new_normals;
	std::vector<vec3> new_colors;
	std::vector<vec2> new_textures;
	for (int t = 0; t < times; t++) {
		for (int i = 0; i < vertices.size(); i += 3) {
			vec3 a = vertices.at(i + 0);
			vec3 b = vertices.at(i + 1);
			vec3 c = vertices.at(i + 2);

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

			vec2 ta = textures.at(i + 0);
			vec2 tb = textures.at(i + 1);
			vec2 tc = textures.at(i + 2);

			vec2 nta = midpoint(ta, tb);
			vec2 ntb = midpoint(tb, tc);
			vec2 ntc = midpoint(ta, tc);

			new_textures.push_back(ta);
			new_textures.push_back(nta);
			new_textures.push_back(ntc);

			new_textures.push_back(nta);
			new_textures.push_back(ntb);
			new_textures.push_back(ntc);

			new_textures.push_back(nta);
			new_textures.push_back(tb);
			new_textures.push_back(ntb);

			new_textures.push_back(ntc);
			new_textures.push_back(ntb);
			new_textures.push_back(tc);
		}
		vertices = new_vertices;
		textures = new_textures;
	}
	for (int s = 0; s < vertices.size(); s++) {
		new_colors.push_back(vec3(0.1f * s, 0.1f * s, 0.1f * s));
	}
	for (int s = 0; s < vertices.size(); s++) {
		new_normals.push_back(vec3(0.0f, 0.0f, 0.0f));
	}
	normals = new_normals;
	colors = new_colors;
}

vec3 Sphere::midpoint(vec3 a, vec3 b) {
	return vec3((a.x + b.x) / 2, (a.y + b.y) / 2, (a.z + b.z) / 2);
}

vec2 Sphere::midpoint(vec2 a, vec2 b) {
	return vec2((a.x + b.x) / 2, (a.y + b.y) / 2);
}

std::vector<vec3> Sphere::getVertices()
{
	return vertices;
}

std::vector<vec3> Sphere::getNormals()
{
	return normals;
}

std::vector<vec3> Sphere::getColors()
{
	return colors;
}

std::vector<vec2> Sphere::getTextures()
{
	return textures;
}