#include "pch.h"
#include "Vertex.h"

Vertex::Vertex() : pos(Vector4(0, 0, 0, 1)), normal(Vector4(0, 0, 0, 0))
{
}

Vertex Vertex::mix(
    Vertex const& a, 
    Vertex const& b, 
    Vertex const& c, 
    float u, float v, float w
)
{
	
	Vertex	ret;
	ret.pos = a.pos * u + b.pos * v + c.pos * w;
	ret.normal = a.normal * u + b.normal * v + c.normal * w;
	ret.normal = ret.normal.normalized();
	return (ret);
}

// 선형 보간
Vertex Vertex::mix(Vertex const& a, Vertex const& b, float t)
{
	Vertex	ret;

	ret.pos = a.pos * (-t + 1) + b.pos * t;
	ret.normal = a.normal * (-t + 1) + b.normal * t;
	return (ret);
}
