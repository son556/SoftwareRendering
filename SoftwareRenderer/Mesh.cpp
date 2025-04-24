#include "pch.h"
#include "Mesh.h"
#include "Vertex.h"
#include "Quaternion.h"

Mesh::Mesh(int size)
{
	this->vertices = new Vertex[size];
	this->size = size;
}

Vertex& Mesh::get(int idx) 
{
	return (this->vertices[idx]);
}

Vertex& Mesh::operator[](int idx) 
{
	return (this->vertices[idx]);
}

void Mesh::setTestVertices()
{
	if (this->vertices) {
		delete[] this->vertices;
		this->size = 0;
	}
	this->vertices = new Vertex[6];
	this->size = 6;

	this->get(0).pos = Vector4(-0.5, 0.5, 0, 1);
	this->get(1).pos = Vector4(-0.5, -0.5, 0, 1);
	this->get(2).pos = Vector4(0.5, -0.5, 0, 1);
	this->get(3).pos = Vector4(-0.5, 0.5, 0, 1);
	this->get(4).pos = Vector4(0.5, -0.5, 0, 1);
	this->get(5).pos = Vector4(0.5, 0.5, 0, 1);

	this->get(0).normal = Vector4(1, 0, 0, 0);
	this->get(1).normal = Vector4(0, 1, 0, 0);
	this->get(2).normal = Vector4(0, 0, 1, 0);
	this->get(3).normal = Vector4(1, 0, 0, 0);
	this->get(4).normal = Vector4(0, 0, 1, 0);
	this->get(5).normal = Vector4(0, 1, 0, 0);
}

void Mesh::setTestTriangle()
{
	if (this->vertices) {
		delete[] this->vertices;
		this->size = 0;
	}
	this->vertices = new Vertex[3];
	this->size = 3;

	this->vertices[0].pos = Vector4(0, sqrtf(3) * (2.f / 3.f), 0, 1);
	this->vertices[0].normal = Vector4(1, 0, 0, 0);
	
	this->vertices[1].pos = Vector4(-1, -sqrtf(3) * (1.f / 3.f), 0, 1);
	this->vertices[1].normal = Vector4(0, 1, 0, 0);

	this->vertices[2].pos = Vector4(1, -sqrtf(3) * (1.f / 3.f), 0, 1);
	this->vertices[2].normal = Vector4(0, 0, 1, 0);
}

void Mesh::setTestOverlapVertices()
{
	if (this->vertices) {
		delete[] this->vertices;
		this->size = 0;
	}
	this->vertices = new Vertex[12];
	this->size = 12;

	this->get(0).pos = Vector4(-0.5, 0.5, 0, 1);
	this->get(1).pos = Vector4(-0.5, -0.5, 0, 1);
	this->get(2).pos = Vector4(0.5, -0.5, 0, 1);
	this->get(3).pos = Vector4(-0.5, 0.5, 0, 1);
	this->get(4).pos = Vector4(0.5, -0.5, 0, 1);
	this->get(5).pos = Vector4(0.5, 0.5, 0, 1);

	this->get(0).normal = Vector4(1, 0, 0, 0);
	this->get(1).normal = Vector4(0, 1, 0, 0);
	this->get(2).normal = Vector4(0, 0, 1, 0);
	this->get(3).normal = Vector4(1, 0, 0, 0);
	this->get(4).normal = Vector4(0, 0, 1, 0);
	this->get(5).normal = Vector4(0, 1, 0, 0);


	this->get(6).pos = Vector4(-0.5, 0.5, 0, 1);
	this->get(7).pos = Vector4(-0.5, -0.5, 0, 1);
	this->get(8).pos = Vector4(0.5, -0.5, 0, 1);
	this->get(9).pos = Vector4(-0.5, 0.5, 0, 1);
	this->get(10).pos = Vector4(0.5, -0.5, 0, 1);
	this->get(11).pos = Vector4(0.5, 0.5, 0, 1);

	this->get(6).normal = Vector4(1, 0, 0, 0);
	this->get(7).normal = Vector4(0, 1, 0, 0);
	this->get(8).normal = Vector4(0, 0, 1, 0);
	this->get(9).normal = Vector4(1, 0, 0, 0);
	this->get(10).normal = Vector4(0, 0, 1, 0);
	this->get(11).normal = Vector4(0, 1, 0, 0);


	// move second rect
	for (int i = 6; i < 12; i++)
		this->get(i).pos = this->get(i).pos + Vector4(0.5, 0, 0.001, 0.1);
	
	// rot second rect;
	Quaternion q(Vector3(1, 0, 0), 45);
	for (int i = 6; i < 12; i++)
		this->get(i).pos = q * this->get(i).pos;
}

int Mesh::getSize() 
{
	return this->size;
}

Mesh::~Mesh()
{
	delete[] vertices;
}
