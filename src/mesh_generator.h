#pragma once 

#include "engine_t.h"  

namespace EngineT
{

    class RawMesh
    {
    public:
        vector<Vertex> vertices;
        vector<int> indices;

        //concat vertices and uv
        void AddMesh(RawMesh* mesh);

        //translate the whole mesh
        void Translate(const vec3& amount);

        //generate the real mesh
        Mesh* Finalize();
    };



    class MeshGenerator
    {
    public:
        static RawMesh* GenerateWall(float x1, float z1, float x2, float z2, float height, bool inverted = false, float uvXoff = 0, float uvYoff = 0);
        static RawMesh* GenerateWall(float xlen, float zlen, float height, bool inverted = false, float uvXoff = 0, float uvYoff = 0);
        static RawMesh* GenerateFloor(float xlen, float zlen, bool inverted = false, float uvXoff = 0, float uvYoff = 0, float uvXscal = 1, float uvYscal = 1);
        static RawMesh* GenerateFloorGrid(int** grid, int gridW, int gridH, float cellW = 1.0f, float cellH = 1.0f, float uvU = 1.0f, float uvV = 1.0f);
    };


}