#pragma once 

#include "engine_t.h"  

namespace EngineT
{

    class Vertex
    {
    public:
        vec3 position;
        vec2 texcoord;
        vec3 normal;
        vec3 tangent;
        vec3 bitangent;

        Vertex(const vec3& position, const vec2& texcoord, const vec3& normal)
        {
            this->position = position;
            this->texcoord = texcoord;
            this->normal = normal;
        }


        Vertex(const vec3& position, const vec2& texcoord, const vec3& normal, const vec3& tangent, const vec3& bitangent)
        {
            this->position = position;
            this->texcoord = texcoord;
            this->normal = normal;
            this->tangent = tangent;
            this->bitangent = bitangent;
        }

        Vertex() {};
    };


    class Mesh
    {
    public:
        Mesh(const string& Filename);
        Mesh(const  vector<Vertex>& vertices, const vector<int>& indices);
        ~Mesh();

        bool Load(const string& filename);

        void Draw();

    private:

        void GenBuffers();

        void Clear();
         
        #define INDEX_BUFFER 0 
        #define POS_VB 1
        #define NORMAL_VB 2
        #define TEXCOORD_VB 3 

        GLuint vao;
        GLuint vbo_i;
        GLuint vbo_v;
        //GLuint vbo_mat_wvp;
        //GLuint vbo_mat_world;

        uint numIndices;
        uint numVertices;
    };

}