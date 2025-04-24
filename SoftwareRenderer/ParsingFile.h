#pragma once

#include <vector>
#include <string>

#include "Vertex.h"

class ParsingFile
{
public:
    ParsingFile(std::string file_name);
    ~ParsingFile() = default;
    Vertex getTrianglesFactor(int index);
    int getTrianglesSize();

private:
    ParsingFile() = delete;
    ParsingFile(ParsingFile const&) = delete;
    ParsingFile& operator=(ParsingFile const&) = delete;

private:
    std::string file_name;
    std::vector<Vector4> vertices;
    std::vector<Vertex> triangles;
    std::vector<Vector4> normals;
    void readFile();
};

