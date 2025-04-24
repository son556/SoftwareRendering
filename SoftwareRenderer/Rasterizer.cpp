#include "pch.h"
#include "Rasterizer.h"
#include "Vertex.h"
#include "Clipper.h"
#include "Shader.h"
#include "RenderTexture.h"
#include "Mesh.h"

Rasterizer::Rasterizer(int width, int height)
	: width(width), height(height), target(nullptr)
{
}

static
float	min(float a, float b, float c) {
	if (a > b)
		a = b;
	if (a > c)
		a = c;
	return (a);
}

static
float	max(float a, float b, float c) {
	if (a < b)
		a = b;
	if (a < c)
		a = c;
	return (a);
}

static
inline Vertex	toNDC(Vertex const& clip_space) {
	Vertex	ret;
	float one = 1;

	ret = clip_space;
	ret.pos.x /= ret.pos.w;
	ret.pos.y /= ret.pos.w;
	ret.pos.z /= ret.pos.w;
	ret.pos.w = one / ret.pos.w;
	return (ret);
}

static
inline Vector4	toScreenSpace(Vector4 a, int width, int height) {
	a.x = (a.x * 0.5f + 0.5f) * width + 0.5f;
	a.y = (-a.y * 0.5f + 0.5f) * height + 0.5f;
	return (a);
}

static
inline float	cross(Vector4& a, Vector4& b, Vector4& c) {
	return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

void Rasterizer::draw(Mesh& mesh, int count, Shader* shader, Clipper* clipper)
{
	std::queue<Vertex>	polygon;
	Vertex				tmp;

	if (this->target == nullptr)
		return;
	for (int i = 0; i + 3 <= count; i += 3) {
		for (int j = 0; j < 3; j++) {
			shader->vertex(mesh[i + j], tmp);
			polygon.push(tmp);
		}
		clipper->clip(polygon);
		this->drawPolygon(polygon, shader);
	}
}

void Rasterizer::setTarget(RenderTexture* rt)
{
	this->target = rt;
}

bool Rasterizer::depthTest(int x, int y, Vertex const& fragment)
{
	float& storedDepth = target->pixelDepth(x, y);
	if (storedDepth <= fragment.pos.z)
		return false;
	storedDepth = fragment.pos.z;
	return true;
}

void Rasterizer::drawTriangle(Vertex& a, Vertex& b, Vertex& c, Shader* shader)
{
	Vector4	screen_a = toScreenSpace(a.pos, this->width, this->height);
	Vector4	screen_b = toScreenSpace(b.pos, this->width, this->height);
	Vector4 screen_c = toScreenSpace(c.pos, this->width, this->height);
	int	x_min = 
		std::max(static_cast<int>(floor(min(screen_a.x, screen_b.x, 
			screen_c.x))), 0);
	int	x_max = 
		std::min(static_cast<int>(ceil(max(screen_a.x, screen_b.x, 
			screen_c.x))), this->width - 1);
	int	y_min = 
		std::max(static_cast<int>(floor(min(screen_a.y, screen_b.y, 
			screen_c.y))), 0);
	int	y_max = 
		std::min(static_cast<int>(ceil(max(screen_a.y, screen_b.y, 
			screen_c.y))), this->height - 1);
	
	float area = cross(screen_a, screen_b, screen_c);
	
	// 뒷면 제거
	/*if (area > 0)
		return;*/

	float rwa = a.pos.w;
	float rwb = b.pos.w;
	float rwc = c.pos.w;

	for (int y = y_min; y <= y_max; y++) {
		for (int x = x_min; x <= x_max; x++) {
			Vector4	p(x, y, 0, 1);
			float	u = cross(screen_b, screen_c, p) / area;
			float	v = cross(screen_c, screen_a, p) / area;
			float	w = -u - v + 1.0f;

			if (u < 0 || v < 0 || w < 0)
				continue;
			float rw_sum = u * rwa + v * rwb + w * rwc;
			u = u * rwa / rw_sum;
			v = v * rwb / rw_sum;
			w = w * rwc / rw_sum;

			Vertex	fragment = Vertex::mix(a, b, c, u, v, w);
			if (u < 0 || v < 0 || w <= 0)
				continue;
			if (!this->depthTest(x, y, fragment))
				continue;
			shader->fragment(fragment, this->target->pixelColor(x, y));
		}
	}
}

void Rasterizer::drawPolygon(std::queue<Vertex>& polygon, Shader* shader)
{
	if (polygon.empty())
		return;
	Vertex	root = toNDC(polygon.front());
	polygon.pop();
	Vertex	prev = toNDC(polygon.front());
	polygon.pop();
	while (!polygon.empty()) {
		Vertex	curr = toNDC(polygon.front());
		polygon.pop();
		this->drawTriangle(root, curr, prev, shader);
		prev = curr;
	}
}
