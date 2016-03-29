
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

    }


    Mesh::Mesh(const  vector<Vertex>& vertices, const vector<int>& indices)
    {
        Clear();

        GenBuffers();
        
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* indices.size(), &indices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
        glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);/**/

        numIndices = indices.size();
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
        glEnableVertexAttribArray(3);
        glEnableVertexAttribArray(4);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, position));
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, texcoord));
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, normal));
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, tangent));
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, bitangent));

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
            aiProcess_FlipUVs |
            aiProcess_JoinIdenticalVertices |
            aiProcess_Triangulate |
            aiProcess_GenNormals |
            aiProcess_CalcTangentSpace
            );


        if(scene)
        {
            if(scene->mNumMeshes > 1)
                Engine.TrowError("Multiple meshes not implemented", __LINE__, __FILE__);
         
            vector<Vertex> vertices;
            vector<uint> indices;
             
            numVertices = scene->mMeshes[0]->mNumVertices;
            numIndices = scene->mMeshes[0]->mNumFaces * 3; 
            vertices.reserve(numVertices);
            indices.reserve(numIndices);

            /*
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
            */

            cout << "numVertices " << numVertices << endl;
            cout << "numIndices " << numIndices << endl;

             
            const aiMesh* paiMesh = scene->mMeshes[0]; 
            const aiVector3D zero(0.0f, 0.0f, 0.0f);

            // Populate the vertex attribute vectors
            for(unsigned int i = 0; i < paiMesh->mNumVertices; i++) {
                const aiVector3D* pos = &(paiMesh->mVertices[i]);

                bool n = paiMesh->HasNormals();
                const aiVector3D* norm = n ? &(paiMesh->mNormals[i]) : &zero;
                const aiVector3D* tan = n ? &(paiMesh->mTangents[i]) : &zero;
                const aiVector3D* bitan = n ? &(paiMesh->mBitangents[i]) : &zero;
                const aiVector3D* coord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &zero;

                vertices.push_back(
                    Vertex(
                        vec3(pos->x, pos->y, pos->z),
                        vec2(coord->x, coord->y),
                        vec3(norm->x, norm->y, norm->z),
                        vec3(tan->x, tan->y, tan->z),
                        vec3(bitan->x, bitan->y, bitan->z)
                        ));
            }

            // Populate the index buffer
            for(unsigned int i = 0; i < paiMesh->mNumFaces; i++)
            {
                const aiFace& face = paiMesh->mFaces[i];
                assert(face.mNumIndices == 3);
                indices.push_back(face.mIndices[0]);
                indices.push_back(face.mIndices[1]);
                indices.push_back(face.mIndices[2]);
            }

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * indices.size(), &indices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

            glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertices.size(), &vertices[0], GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
        else {
            cout << "Error parsing" << filename.c_str() << " : " << importer.GetErrorString() << endl;
        }

        return false;
    }


    void Mesh::Draw()
    {
        glBindVertexArray(vao);
        
        /*glDrawElementsBaseVertex(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT,
            (void*) (sizeof(uint)* subMeshes[i].firstIndex),
            subMeshes[i].firstVertex);*/

        glDrawElements(GL_TRIANGLES, numIndices, GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, numIndices);

        // Make sure the VAO is not changed from the outside 
        glBindVertexArray(0);
    }

}