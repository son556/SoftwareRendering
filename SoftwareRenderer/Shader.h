#pragma once

#include "Matrix4x4.h"

class Vertex;
class Vector4;

class Shader
{
public:
	Shader();
	void	setViewMatrix(Matrix4x4& m);
	void	setProjectionMatrix(Matrix4x4& m);
	void	setModelMatrix(Matrix4x4& m);
	void	vertex(Vertex const& in, Vertex& out);
	void	fragment(Vertex const& in, Vector4& color);

private:
	Matrix4x4	view;
	Matrix4x4	projection;
	Matrix4x4	model;
};

