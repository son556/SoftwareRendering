#pragma once

#include <queue>

class Mesh;
class Shader;
class Clipper;
class RenderTexture;
class Vertex;

class Rasterizer
{
public:
	Rasterizer(int width, int height);
	~Rasterizer() = default;
	void draw(Mesh& mesh, int count, Shader* shader, Clipper* clipper);
	void setTarget(RenderTexture* rt);

private:
	Rasterizer() = delete;
	Rasterizer(const Rasterizer&) = delete;
	Rasterizer& operator=(const Rasterizer&) = delete;

private:
	int		width;
	int		height;
	RenderTexture* target;
	bool	depthTest(int x, int y, Vertex const& fragment);
	void	drawTriangle(Vertex& a, Vertex& b, Vertex& c, Shader* shader);
	void	drawPolygon(std::queue<Vertex>& polygon, Shader* shader);
};

