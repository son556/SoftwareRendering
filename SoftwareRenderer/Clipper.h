#pragma once

class Vertex;

class Clipper
{
public:
	Clipper() = default;
	~Clipper() = default;
	void clip(std::queue<Vertex>& out);
};

