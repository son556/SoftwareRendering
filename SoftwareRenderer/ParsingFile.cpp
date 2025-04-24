#include "pch.h"
#include "ParsingFile.h"
#include "OBJ_Loader.h"

ParsingFile::ParsingFile(std::string file_name)
{
    this->file_name = file_name;
	this->readFile();
}

Vertex ParsingFile::getTrianglesFactor(int index)
{
    return triangles[index];
}

int ParsingFile::getTrianglesSize()
{
	return triangles.size();
}

void ParsingFile::readFile()
{
	objl::Loader loader;
	bool loadout = loader.LoadFile(this->file_name);

	if (loadout == false) {
		cout << "file load error" << endl;
		return;
	}
	objl::Mesh currMesh = loader.LoadedMeshes[0];
	objl::Vertex obj_v;
	Vertex v;
	for (int i = 0; i < currMesh.Indices.size(); i++) {
		int idx = currMesh.Indices[i];
		obj_v = currMesh.Vertices[idx];
		v.pos = 
			Vector4(obj_v.Position.X, obj_v.Position.Y, obj_v.Position.Z,1);
		v.normal =
			Vector4(obj_v.Normal.X, obj_v.Normal.Y, obj_v.Normal.Z, 0);
		this->triangles.push_back(v);
	}
}

