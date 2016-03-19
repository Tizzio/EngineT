
#pragma once

#include <assert.h>

#include "mesh.h" 
#include "texture.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace EngineT
{


    Mesh::Mesh(const string& filename)
    {
        Load(filename);
    }


    Mesh::~Mesh()
    {
        Clear();
    }


    void Mesh::Clear()
    {

        //destroy meshes buffers
        glDeleteBuffers(1, &vbo_v);
        glDeleteBuffers(1, &vbo_i);
        glDeleteVertexArrays(1, &vao);

        subMeshes.clear();
    }


    Mesh::Mesh(const  vector<Vertex>& vertices, const vector<int>& indices)
    {
        Clear();

        GenBuffers();


        subMeshes.resize(1);
        subMeshes[0].numIndices = indices.size();
        subMeshes[0].firstVertex = 0;
        subMeshes[0].firstIndex = 0;
        subMeshes[0].textures.push_back(NULL);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* indices.size(), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);/**/
    }

    void Mesh::GenBuffers()
    {
        //Vertex array object
        glGenVertexArrays(1, &vao);

        glGenBuffers(1, &vbo_v);
        glGenBuffers(1, &vbo_i);
        //glGenBuffers(1, &vbo_mat_wvp);
        //glGenBuffers(1, &vbo_mat_world);


        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
        glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo_mat_wvp);
        //glBindBuffer(GL_ARRAY_BUFFER, vbo_mat_world);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, texcoord));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, normal));

        ////world matrix
        //for (uint i = 0; i < 4; i++) {
        //	glEnableVertexAttribArray(3 + i);
        //	glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*) (sizeof(vec4)* i));
        //	glVertexAttribDivisor(3 + i, 1);
        //}

        ////world view projection matrix
        //for (uint i = 0; i < 4; i++) {
        //	glEnableVertexAttribArray(7 + i);
        //	glVertexAttribPointer(3 + i, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(vec4)* i));
        //	glVertexAttribDivisor(7 + i, 1);
        //}

        glBindVertexArray(0);
    }
    bool Mesh::Load(const string& filename)
    {
        Clear();

        Assimp::Importer importer;

        GenBuffers();

        const aiScene* scene = importer.ReadFile(filename.c_str(),
            aiProcess_GenNormals |
            aiProcess_CalcTangentSpace |
            aiProcess_Triangulate |
            aiProcess_JoinIdenticalVertices |
            aiProcess_FlipUVs 
            );


        if(scene) {

            subMeshes.resize(scene->mNumMeshes);

            vector<Vertex> vertices;
            vector<uint> indices;

            uint numVertices = 0;
            uint numIndices = 0;

            // Count the number of vertices and indices
            for(unsigned int i = 0; i < subMeshes.size(); i++)
            {
                uint verts = scene->mMeshes[i]->mNumVertices;
                int indices = scene->mMeshes[i]->mNumFaces * 3;
                subMeshes[i].numIndices = indices;
                subMeshes[i].firstVertex = numVertices;
                subMeshes[i].firstIndex = numIndices;
                subMeshes[i].textures.push_back(NULL);

                numVertices += verts;
                numIndices += indices;
            }

            cout << "numVertices " << numVertices << endl;
            cout << "numIndices " << numIndices << endl;

            vertices.reserve(numVertices);
            indices.reserve(numIndices);

            // Initialize the meshes in the scene one by one
            for(unsigned int i = 0; i < subMeshes.size(); i++) 
            {
                const aiMesh* paiMesh = scene->mMeshes[i];
                //InitMesh(paiMesh, positions, normals, texCoords, indices);

                const aiVector3D zero3d(0.0f, 0.0f, 0.0f);

                // Populate the vertex attribute vectors
                for(unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
                    const aiVector3D* pos = &(paiMesh->mVertices[i]);
                    const aiVector3D* norm = &(paiMesh->mNormals[i]);
                    const aiVector3D* coord = paiMesh->HasTextureCoords(0) ?
                        &(paiMesh->mTextureCoords[0][i]) : &zero3d;
                    bool n = paiMesh->HasNormals();
                    vertices.push_back(
                        Vertex(
                            vec3(pos->x, pos->y, pos->z),
                            vec2(coord->x, coord->y),
                            vec3(n ? norm->x : 0, n ? norm->y : 0, n ? norm->z : 0)
                            ));
                }

                // Populate the index buffer
                for(unsigned int i = 0; i < paiMesh->mNumFaces; i++) {
                    const aiFace& face = paiMesh->mFaces[i];
                    assert(face.mNumIndices == 3);
                    indices.push_back(face.mIndices[0]);
                    indices.push_back(face.mIndices[1]);
                    indices.push_back(face.mIndices[2]);
                }
            }

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* indices.size(), &indices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

        }
        else {
            cout << "Error parsing" << filename.c_str() << " : " << importer.GetErrorString() << endl;
        }

        return false;
    }

    void Mesh::SetTexture(Texture* texture, uint subMesh, uint textureIndex)
    {
        subMeshes[subMesh].textures[textureIndex] = texture;
    }

    void Mesh::Draw()
    {
        glBindVertexArray(vao);
        for(unsigned int i = 0; i < subMeshes.size(); i++)
        {
            if(subMeshes[i].textures[0])
                subMeshes[i].textures[0]->Bind(GL_TEXTURE0);
            glDrawElementsBaseVertex(GL_TRIANGLES, subMeshes[i].numIndices, GL_UNSIGNED_INT,
                (void*) (sizeof(uint)* subMeshes[i].firstIndex),
                subMeshes[i].firstVertex);
        }

        // Make sure the VAO is not changed from the outside 
        glBindVertexArray(0);
    }

}