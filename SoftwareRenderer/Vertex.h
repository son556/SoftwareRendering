#pragma once

#include "Vector4.h"

class Vertex
{
public:
	Vertex();

public:
	static Vertex	mix(Vertex const& a, Vertex const& b, 
		Vertex const& c, float u, float v, float w);
	static Vertex	mix(Vertex const& a, Vertex const& b, float t);

public:
	Vector4 pos;
	Vector4 normal;
};

