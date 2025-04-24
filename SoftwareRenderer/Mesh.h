#pragma once

class Vertex;

class Mesh
{
public:
	Mesh(int size);
	~Mesh();
	int	getSize();
	Vertex& get(int idx);
	Vertex& operator[](int idx);
	void setTestVertices();
	void setTestTriangle();
	void setTestOverlapVertices();

private:
	Vertex* vertices = nullptr;
	int size = 0;
};

