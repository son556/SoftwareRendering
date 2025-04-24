#include "pch.h"
#include "RenderTexture.h"
#include "Vector4.h"

RenderTexture::RenderTexture(int width, int height)
{
	this->width = width;
	this->height = height;
	this->color = new Vector4[width * height];
	this->depth = new float[width * height];
	fill(depth, depth + width * height, 1);
	for (int i = 0; i < width * height; i++)
		this->color[i] = Vector4(0, 0, 0, 0);
}

RenderTexture::~RenderTexture()
{
	delete[] this->color;
	delete[] this->depth;
}

void RenderTexture::clear(Vector4 const& color, float depth)
{
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			this->color[x + y * width] = color;
			this->depth[x + y * width] = depth;
		}
	}
}

Vector4& RenderTexture::pixelColor(int x, int y)
{
	return (this->color[x + y * this->width]);
}

float& RenderTexture::pixelDepth(int x, int y)
{
	return (this->depth[x + y * this->width]);
}
