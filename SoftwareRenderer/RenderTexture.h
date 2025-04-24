#pragma once

class Vector4;

class RenderTexture
{
public:
	RenderTexture(int width, int height);
	~RenderTexture();
	void	clear(Vector4 const& color, float depth);
	Vector4& pixelColor(int x, int y);
	float& pixelDepth(int x, int y);

private:
	RenderTexture() = delete;
	RenderTexture(RenderTexture const&) = delete;
	RenderTexture& operator=(RenderTexture const&) = delete;

private:
	int		width;
	int		height;
	Vector4* color;
	float* depth;
};

