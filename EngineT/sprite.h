#pragma once  

#include "engine_t.h"  
 

namespace EngineT
{
	class Sprite 
	{ 

	public:
		class Vertex
		{
		public:
			vec2 pos;
			vec2 uv;
			Vertex(vec2 position, vec2 UV){
				pos = position;
				uv = UV;
			};
		};
		 
		class Image
		{
			friend class Sprite;
		private:
			uint vertexIndex;
		};

		~Sprite();
		Sprite();
		Sprite(Texture* texture, string filename);
		void Load(Texture* texture, string filename);
		void LoadSliced(Texture* texture, string filename, vec2 size);
		void ResizeSliced(vec2 size);
		void Draw(int imageIndex);
		void CreateSingle(Texture* texture);
		void CreateFromStrip(Texture* texture, uint count, float width, float height); 

		vector<Image> frames;
		string name;
		float width;
		float height;
		float xoffset;
		float yoffset;
		float borderLeft;
		float borderTop;
		float borderRight;
		float borderBottom;

	private:
		void GenerateBuffers();
		void UpdateBuffers();
		int frameIndices = 6;
		Texture* texture;
		vector<Vertex> vertices;
		vector <uint> indices;
		GLuint vao;
		GLuint vbo_i;
		GLuint vbo_v; 


		class SubImage
		{
		public:
			int x, y;
			SubImage(vector<int> data){
				x = data[0];
				y = data[1];
			}
		};

		vector<SubImage> subImages;
		void ReadFile(string& filename);

	};
}
