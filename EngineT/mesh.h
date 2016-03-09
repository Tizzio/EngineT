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

		Vertex(const vec3& position, const vec2& texcoord, const vec3& normal)
		{
			this->position = position;
			this->texcoord = texcoord;
			this->normal = normal;
		}
		Vertex() {};
	};


	class Mesh
	{
	public:
		Mesh();
		Mesh(const string& Filename);
		Mesh(const  vector<Vertex>& vertices, const vector<int>& indices);
		~Mesh();

		bool Load(const string& Filename);

		void Draw();
		void SetTexture(Texture* texture, uint subMesh, uint index);

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
		GLuint vbo_mat_wvp;
		GLuint vbo_mat_world;

		struct SubMesh
		{
		public:
			uint firstVertex = 0;
			uint firstIndex = 0;
			uint numIndices = 0;
			vector<Texture*> textures;
		};


		vector<SubMesh> subMeshes;
	};

}