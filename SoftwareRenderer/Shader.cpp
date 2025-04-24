#include "pch.h"
#include "Shader.h"
#include "Vertex.h"

#include "MatrixUtils.h"

Shader::Shader()
{
	this->model.m[0][0] = 1;
	this->model.m[0][1] = 0;
	this->model.m[0][2] = 0;
	this->model.m[0][3] = 0;

	this->model.m[1][0] = 0;
	this->model.m[1][1] = 1;
	this->model.m[1][2] = 0;
	this->model.m[1][3] = 0;

	this->model.m[2][0] = 0;
	this->model.m[2][1] = 0;
	this->model.m[2][2] = 1;
	this->model.m[2][3] = 0;

	this->model.m[3][0] = 0;
	this->model.m[3][1] = 0;
	this->model.m[3][2] = 0;
	this->model.m[3][3] = 1;
}

void Shader::setViewMatrix(Matrix4x4& m)
{
	this->view = m;
}

void Shader::setProjectionMatrix(Matrix4x4& m)
{
	this->projection = m;
}

void Shader::setModelMatrix(Matrix4x4& m)
{
	this->model = m;
}

void Shader::vertex(Vertex const& in, Vertex& out)
{
	out.pos.w = 1;
	out.pos = this->model * in.pos;
	out.pos = this->view * out.pos;
	out.pos = this->projection * out.pos;
	
	Vector4 n = in.normal;
	n.w = 0;
	out.normal = this->model.inverse().Trnaspose() * n;
}

void Shader::fragment(Vertex const& in, Vector4& color)
{
	Vector4 c = in.normal.normalized();
	float f = c * Vector4(0, 0, -1, 0);
	//color = Vector4(1, 1, 1, 0) * f;
	color = Vector4(c.x * 0.5 + 0.5, c.y * 0.5 + 0.5, c.z * 0.5 + 0.5, -1);
	color = c;
	//test
	//color = color + Vector4(0.2, 0.2, 0.2, 0);
}
