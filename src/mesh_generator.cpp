
#include "mesh_generator.h"
#include "mesh.h"

namespace EngineT
{
    void RawMesh::AddMesh(RawMesh* mesh)
    {
        int base_index = vertices.size();
        vertices.insert(vertices.end(), mesh->vertices.begin(), mesh->vertices.end());
        for(int tris : mesh->indices)
        {
            indices.push_back(base_index + tris);
        }
    }


    void RawMesh::Translate(const vec3& amount)
    {
        for(Vertex& v : vertices)
        {
            v.position += amount;
        }
    }


    Mesh* RawMesh::Finalize()
    {
        Mesh* mesh = new Mesh(vertices, indices);
        delete this;
        return mesh;
    }


    RawMesh* MeshGenerator::GenerateWall(float x1, float z1, float x2, float z2, float height, bool inverted, float uvXoff, float uvYoff)
    {
        float xw = x2 - x1;
        float zw = z2 - z1;
        return MeshGenerator::GenerateWall(xw, zw, height, inverted, uvXoff, uvYoff);

    }
    RawMesh* MeshGenerator::GenerateFloor(float xlen, float zlen, bool inverted, float uvXoff, float uvYoff, float xScale, float yScale)
    {
        RawMesh* rm = new RawMesh();

        vec3 v1 = vec3(0, 0, 0);
        vec3 v2 = vec3(xlen, 0, 0);
        vec3 v3 = vec3(xlen, 0, zlen);
        vec3 v4 = vec3(0, 0, zlen);


        vec3 normal;
        if(!inverted)
            normal = vec3(0, 1, 0);
        else 
            normal = vec3(0, -1, 0);

        //vertices 
        vector<Vertex> vertices = {
            Vertex(v1, vec2(uvXoff, uvYoff), normal),
            Vertex(v2, vec2(xlen / xScale + uvXoff,  uvYoff), normal),
            Vertex(v3, vec2(xlen / xScale + uvXoff, zlen / yScale + uvYoff), normal),
            Vertex(v4, vec2(uvXoff, zlen / yScale + uvYoff), normal)
        };


        rm->vertices.insert(rm->vertices.end(), vertices.begin(), vertices.end());


        //indices
        vector<int> indices;

        if(inverted)
        {
            indices = {
                0, 1, 2,
                2, 3, 0
            };
        }
        else
        {
            indices = {
                0, 3, 2,
                2, 1, 0
            };
        }
        rm->indices.insert(rm->indices.end(), indices.begin(), indices.end());

        return rm;
    }

    RawMesh* MeshGenerator::GenerateWall(float xlen, float zlen, float height, bool inverted, float uvXoff, float uvYoff)
    {
        RawMesh* rm = new RawMesh();

        vec3 v1 = vec3(0, height, 0);
        vec3 v2 = vec3(xlen, height, zlen);
        vec3 v3 = vec3(xlen, 0, zlen);
        vec3 v4 = vec3(0, 0, 0);

        vec3 normal;

        if(inverted)
            normal = cross((v3 - v1), (v2 - v1));
        else
            normal = -cross((v3 - v1), (v2 - v1));


        //vertices
        vector<Vertex> vertices = {
            Vertex(v1, vec2(0 + uvXoff, height + uvYoff), normal),
            Vertex(v2, vec2(xlen + zlen + uvXoff, height + uvYoff), normal),
            Vertex(v3, vec2(xlen + zlen + uvXoff, 0 + uvYoff), normal),
            Vertex(v4, vec2(0 + uvXoff, 0 + uvYoff), normal)
        };


        rm->vertices.insert(rm->vertices.end(), vertices.begin(), vertices.end());


        //indices
        vector<int> indices;

        if(!inverted)
        {
            indices = {
                0, 1, 2,
                2, 3, 0
            };
        }
        else
        {
            indices = {
                0, 3, 2,
                2, 1, 0
            };
        }
        rm->indices.insert(rm->indices.end(), indices.begin(), indices.end());

        return rm;

    }

    RawMesh* MeshGenerator::GenerateFloorGrid(int** grid, int gridW, int gridH, float cellW, float cellH, float uvU, float uvV)
    {
        RawMesh* raw_mesh = new RawMesh();
        int w = gridW;
        int h = gridH;

        //get real cell count
        int cellCount = 0;
        for(int x = 0; x < w; x++)
        {
            for(int y = 0; y < h; y++)
            {
                if(grid[x][y])
                    cellCount++;
            }
        }

        raw_mesh->vertices.resize(cellCount * 4);

        float deltaU = uvU * cellW / w;
        float deltaV = uvV * cellH / h;

        int i = 0;
        for(int x = 0; x < w; x++)
        {
            for(int y = 0; y < h; y++)
            {
                if(grid[x][y])
                {
                    raw_mesh->vertices[i + 0] = Vertex(
                        vec3(x * cellW, 0, y * cellH),
                        vec2(x * deltaU, y * deltaV),
                        vec3(0, 1, 0));


                    raw_mesh->vertices[i + 1] = Vertex(
                        vec3(x * cellW + cellW, 0, y * cellH),
                        vec2(x * deltaU + deltaU, y * deltaV),
                        vec3(0, 1, 0));

                    raw_mesh->vertices[i + 2] = Vertex(
                        vec3(x * cellW, 0, y * cellH + cellH),
                        vec2(x * deltaU, y * deltaV + deltaV),
                        vec3(0, 1, 0));

                    raw_mesh->vertices[i + 3] = Vertex(
                        vec3(x * cellW + cellW, 0, y * cellH + cellH),
                        vec2(x * deltaU + deltaU, y * deltaV + deltaV),
                        vec3(0, 1, 0));


                    //define triangles  Z-ordererd 
                    vector<int> indices = {
                        i + 1, i + 0, i + 2,
                        i + 2, i + 3, i + 1
                    };

                    raw_mesh->indices.insert(raw_mesh->indices.end(), indices.begin(), indices.end());

                    i += 4;
                }
            }
        }

        return raw_mesh;
    }

}