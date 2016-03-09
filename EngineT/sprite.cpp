#include "sprite.h"
#include "texture.h" 
#include "utils.h" 

namespace EngineT
{



	Sprite::~Sprite()
	{
		glDeleteBuffers(1, &vbo_v);
		glDeleteBuffers(1, &vbo_i);
		glDeleteVertexArrays(1, &vao);
	}


	Sprite::Sprite() {}

	Sprite::Sprite(Texture* texture, string filename)
	{
		Load(texture, filename);
	}


	void Sprite::ResizeSliced(vec2 size)
	{

		frameIndices = 6 * 9; //9 quads

		int w = (int) size.x;
		int h = (int) size.y;

		float bL = borderLeft;
		float bT = borderTop;
		float bR = borderRight;
		float bB = borderBottom;

		if(w < bL + bR)
			w = (int) (bL + bR);
		if(h < bT + bB)
			h = (int) (bT + bB);


		for(uint i = 0; i < subImages.size(); i++)
		{
			SubImage img = subImages[i];

			float uvX1 = img.x / texture->width;
			float uvY1 = img.y / texture->height;
			float uvX2 = (img.x + width) / texture->width;
			float uvY2 = (img.y + height) / texture->height;


			float uvL = bL / texture->width; //left
			float uvT = bT / texture->height; //top
			float uvR = bR / texture->width; //right
			float uvB = bB / texture->height; //bottom


			//TODO: add the size argument to each Vertex(...)
			vertices.insert(vertices.end(), {
				Vertex(vec2(0, 0), vec2(uvX1, uvY1)), //0
				Vertex(vec2(bL, 0), vec2(uvX1 + uvL, uvY1)), //1
				Vertex(vec2(w - bR, 0), vec2(uvX2 - uvR, uvY1)), //2
				Vertex(vec2(w, 0), vec2(uvX2, uvY1)), //3

				Vertex(vec2(0, bT), vec2(uvX1, uvY1 + uvT)), //4
				Vertex(vec2(bL, bT), vec2(uvX1 + uvL, uvY1 + uvT)), //5
				Vertex(vec2(w - bR, bT), vec2(uvX2 - uvR, uvY1 + uvT)), //6
				Vertex(vec2(w, bT), vec2(uvX2, uvY1 + uvT)), //7

				Vertex(vec2(0, h - bB), vec2(uvX1, uvY2 - uvB)), //8
				Vertex(vec2(bL, h - bB), vec2(uvX1 + uvL, uvY2 - uvB)), //9
				Vertex(vec2(w - bR, h - bB), vec2(uvX2 - uvR, uvY2 - uvB)),//10
				Vertex(vec2(w, h - bB), vec2(uvX2, uvY2 - uvB)),//11

				Vertex(vec2(0, h), vec2(uvX1, uvY2)), //12
				Vertex(vec2(bL, h), vec2(uvX1 + uvL, uvY2)), //13
				Vertex(vec2(w - bR, h), vec2(uvX2 - uvR, uvY2)),//14
				Vertex(vec2(w, h), vec2(uvX2, uvY2))//15
			});

			// 0, 1, 2, 2, 3, 1,
			indices.insert(indices.end(), {
				0, 1, 4, 4, 5, 1,
				1, 2, 5, 5, 6, 2,
				2, 3, 6, 6, 7, 3,
				4, 5, 8, 8, 9, 5,
				5, 6, 9, 9, 10, 6,
				6, 7, 10, 10, 11, 7,
				8, 9, 12, 12, 13, 9,
				9, 10, 13, 13, 14, 10,
				10, 11, 14, 14, 15, 11,
			});
			frames[i].vertexIndex = i * 9;

		}

		UpdateBuffers();

	}

	void Sprite::LoadSliced(Texture* texture, string filename, vec2 size)
	{

		//read the sprite file
		ReadFile(filename);

		frameIndices = 6 * 9; //9 quads

		int w = size.x;
		int h = size.y;

		float bL = borderLeft;
		float bT = borderTop;
		float bR = borderRight;
		float bB = borderBottom;

		cout << bL << endl;
		if(w < bL + bR)
			w = bL + bR;
		if(h < bT + bB)
			h = bT + bB;


		this->texture = texture;
		if(subImages.size() <= 0)
			return;

		GenerateBuffers();

		vertices.reserve(subImages.size() * 15);
		indices.reserve(subImages.size() * 6 * 9);

		frames.resize(subImages.size());


		for(uint i = 0; i < subImages.size(); i++)
		{
			SubImage img = subImages[i];

			float uvX1 = img.x / texture->width;
			float uvY1 = img.y / texture->height;
			float uvX2 = (img.x + width) / texture->width;
			float uvY2 = (img.y + height) / texture->height;


			float uvL = bL / texture->width; //left
			float uvT = bT / texture->height; //top
			float uvR = bR / texture->width; //right
			float uvB = bB / texture->height; //bottom


			/* sliced vertices id
			0---1---2---3
			|   |   |   |
			4---5---6---7
			|   |   |   |
			8---9---10--11
			|   |   |   |
			12--13--14--15
			*/


			//TODO: add the size argument to each Vertex(...)
			vertices.insert(vertices.end(), {
				Vertex(vec2(0, 0), vec2(uvX1, uvY1)), //0
				Vertex(vec2(bL, 0), vec2(uvX1 + uvL, uvY1)), //1
				Vertex(vec2(w - bR, 0), vec2(uvX2 - uvR, uvY1)), //2
				Vertex(vec2(w, 0), vec2(uvX2, uvY1)), //3

				Vertex(vec2(0, bT), vec2(uvX1, uvY1 + uvT)), //4
				Vertex(vec2(bL, bT), vec2(uvX1 + uvL, uvY1 + uvT)), //5
				Vertex(vec2(w - bR, bT), vec2(uvX2 - uvR, uvY1 + uvT)), //6
				Vertex(vec2(w, bT), vec2(uvX2, uvY1 + uvT)), //7

				Vertex(vec2(0, h - bB), vec2(uvX1, uvY2 - uvB)), //8
				Vertex(vec2(bL, h - bB), vec2(uvX1 + uvL, uvY2 - uvB)), //9
				Vertex(vec2(w - bR, h - bB), vec2(uvX2 - uvR, uvY2 - uvB)),//10
				Vertex(vec2(w, h - bB), vec2(uvX2, uvY2 - uvB)),//11

				Vertex(vec2(0, h), vec2(uvX1, uvY2)), //12
				Vertex(vec2(bL, h), vec2(uvX1 + uvL, uvY2)), //13
				Vertex(vec2(w - bR, h), vec2(uvX2 - uvR, uvY2)),//14
				Vertex(vec2(w, h), vec2(uvX2, uvY2))//15
			});

			// 0, 1, 2, 2, 3, 1,
			indices.insert(indices.end(), {
				0, 1, 4, 4, 5, 1,
				1, 2, 5, 5, 6, 2,
				2, 3, 6, 6, 7, 3,
				4, 5, 8, 8, 9, 5,
				5, 6, 9, 9, 10, 6,
				6, 7, 10, 10, 11, 7,
				8, 9, 12, 12, 13, 9,
				9, 10, 13, 13, 14, 10,
				10, 11, 14, 14, 15, 11,
			});
			frames[i].vertexIndex = i * 9;


		}

		UpdateBuffers();
	}


	void Sprite::Load(Texture* texture, string filename)
	{

		//read the sprite file
		ReadFile(filename);


		this->texture = texture;
		if(subImages.size() <= 0)
			return;

		GenerateBuffers();

		vertices.reserve(subImages.size() * 4);
		indices.reserve(subImages.size() * 6);

		frames.resize(subImages.size());

		for(uint i = 0; i < subImages.size(); i++)
		{
			SubImage img = subImages[i];

			float uvX1 = img.x / texture->width;
			float uvY1 = img.y / texture->height;
			float uvX2 = (img.x + width) / texture->width;
			float uvY2 = (img.y + height) / texture->height;

			/*cout << "uvX " << uvX << " ,  uvY " << uvY << endl;
			cout << "width " << width << " ,  height " << height << endl;
			cout << "xoffset " << xoffset << " ,  yoffset " << yoffset << endl;*/
			vertices.insert(vertices.end(), {
				Vertex(vec2(0.0f - xoffset, 0.0f - yoffset), vec2(uvX1, uvY1)),
				Vertex(vec2(width - xoffset, 0.0f - yoffset), vec2(uvX2, uvY1)),
				Vertex(vec2(0.0f - xoffset, height - yoffset), vec2(uvX1, uvY2)),
				Vertex(vec2(width - xoffset, height - yoffset), vec2(uvX2 , uvY2))
			});

			indices.insert(indices.end(), {
				0, 1, 2, 2, 3, 1
			});
			frames[i].vertexIndex = i * 4;

		}

		UpdateBuffers();
	}

	void Sprite::ReadFile(string& filename)
	{
		ifstream file(filename);
		string line;
		while(getline(file, line))
		{
			if(line.length() == 0)
				continue;

			//if not comment
			if(line[0] != '#')
			{
				//x  y  w  h xo yo
				if(line[0] == 's')
				{

					//get sprite count
					vector<string> data = Utils::StringToStringArray(line);
					if(data.size() == 11)
					{
						name = data[1];
						int count = stoi(data[2]);
						width = stof(data[3]);
						height = stof(data[4]);
						xoffset = stof(data[5]);
						yoffset = stof(data[6]);

						borderLeft = stof(data[7]);
						borderTop = stof(data[8]);
						borderRight = stof(data[9]);
						borderBottom = stof(data[10]);

						subImages.reserve(count);
					}
					else
					{
						cout << "ERROR: Wrong sprite format" << endl;
					}
				}
				else
				{
					//add new spriteraw
					vector<int> data = Utils::StringToIntArray(line);
					if(data.size() == 2)
					{
						subImages.push_back(SubImage(data));
					}
					else
					{
						cout << "ERROR: Wrong sprite format" << endl;
					}
				}
			}
		}
	}
	void Sprite::GenerateBuffers()
	{
		//Vertex array object
		glGenVertexArrays(1, &vao);
		glGenBuffers(1, &vbo_v);
		glGenBuffers(1, &vbo_i);

		glBindVertexArray(vao);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
		glBindBuffer(GL_ARRAY_BUFFER, vbo_v);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);


		uint offset = 0;
		//Position
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, pos));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(class Vertex, uv));

		glBindVertexArray(0);
	}

	void Sprite::UpdateBuffers()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* indices.size(), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void Sprite::CreateFromStrip(Texture* texture, uint count, float width, float height)
	{

		GenerateBuffers();

		this->width = width;
		this->height = height;

		frames.resize(count);
		this->texture = texture;
		float uRatio = width / texture->width;
		float vRatio = height / texture->height;


		vertices.reserve(count * 4);
		indices.reserve(count * 6);

		//cout << "u " << uRatio << " ,  v " << vRatio << endl;
		int sideCount = (int) sqrt(count);
		for(uint i = 0; i < count; i++)
		{
			uint x = i % sideCount;
			uint y = (i / sideCount);
			//cout << "x " << uRatio * x << " ,  y " << vRatio * y << endl;
			vertices.insert(vertices.end(), {
				Vertex(vec2(0.0f, 0.0f), vec2(uRatio * x,				vRatio * y)),
				Vertex(vec2(width, 0.0f), vec2(uRatio * x + uRatio,		vRatio * y)),
				Vertex(vec2(0.0f, height), vec2(uRatio * x,				vRatio * y + vRatio)),
				Vertex(vec2(width, height), vec2(uRatio * x + uRatio,	vRatio * y + vRatio))
			});
			indices.insert(indices.end(), {
				0, 1, 2, 2, 3, 1
			});


			frames[i].vertexIndex = i * 4;
		}

		UpdateBuffers();


	}


	void Sprite::Draw(int imageIndex)
	{
		glBindVertexArray(vao);
		if(texture != nullptr)
			texture->Bind(GL_TEXTURE0);
		glDrawElementsBaseVertex(GL_TRIANGLES, frameIndices, GL_UNSIGNED_INT, 0, frames[imageIndex].vertexIndex);
		glBindVertexArray(0);
	}
}