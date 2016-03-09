#include "ui_text.h"
#include "style.h"
#include "font.h"
#include "texture.h"
#include "utils.h"

namespace EngineT {

	Text::Text(wstring text, Style* style)
	{
		this->name = "text";
		this->style = style;
		if (text.length() <= 0)
			return; 

		GenerateBuffers();
		 

		Texture* tex = style->font->texture;

		SetText(text);

		UpdateBuffers();
	}

	void Text::SetText(wstring text)
	{

		int count = 0;

		for (char32_t c : text)
		{
			//if character exists
			if (c > 0 && c < style->font->chars.size())
				if (style->font->chars[c] != nullptr)
				{
					count++;
				}
		}

		vertices.reserve(count * 4);
		indices.reserve(count * 6);

		//style properties
		int xoffset = style->xoffset;
		int yoffset = style->yoffset;
		int spacing = style->spacing;
		int spaceWidth = style->spaceWidth;
		int lineHeight = style->lineHeight;

		int xpos = 0;
		int ypos = 0;

		uint idx = 0;

		vec4 color = style->color;

		bool openCommand = false;
		string command;

		for (char32_t c : text)
		{
			//check newline
			if (openCommand)
			{
				if (c == ']')
				{
					openCommand = false;

					//execute command
					if (command[0] == '#')
					{
						if (command.length() == 7)
						{
							color = Utils::HexColorToVec4(command);
						}
						else
						{
							color = style->color;
						}
					}

					command = "";
				}
				else
				{
					command.push_back(c);
				}
				continue;
			}
			else
			{
				if (c == '[')
				{
					openCommand = true;
					continue;
				}
			}

			//check newline character
			if (c == 10 || c == 13)
			{
				xpos = 0;
				ypos += style->font->maxHeight + lineHeight;
			}

			//check space
			else if (c == ' ')
				xpos += spaceWidth;
			Font::Char* fc = nullptr;
			if (c > 0 && c < style->font->chars.size())
				fc = style->font->chars[c];
			//if character exists
			if (fc != nullptr)
			{
				vertices.insert(vertices.end(), {
					Vertex(vec2(xpos + fc->xoffset, ypos + fc->yoffset), vec2(fc->uvX1, fc->uvY1), color),
					Vertex(vec2(xpos + fc->width + fc->xoffset, ypos + fc->yoffset), vec2(fc->uvX2, fc->uvY1), color),
					Vertex(vec2(xpos + fc->xoffset, ypos + fc->height + fc->yoffset), vec2(fc->uvX1, fc->uvY2), color),
					Vertex(vec2(xpos + fc->width + fc->xoffset, ypos + fc->height + fc->yoffset), vec2(fc->uvX2, fc->uvY2), color)
				});
				indices.insert(indices.end(), {
					idx + 0, idx + 1, idx + 2, idx + 2, idx + 3, idx + 1
				});

				idx += 4;
				xpos += fc->width + spacing;

			}
		}

	}

	void Text::Draw()
	{ 
		glBindVertexArray(vao);
		if (style->font->texture != nullptr)
			style->font->texture->Bind(GL_TEXTURE0);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}

	void Text::GenerateBuffers()
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
		glEnableVertexAttribArray(2);

		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(class Vertex, pos));
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(class Vertex, uv));
		glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(class Vertex, col));

		glBindVertexArray(0);
	}

	void Text::UpdateBuffers()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo_i);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint)* indices.size(), &indices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glBindBuffer(GL_ARRAY_BUFFER, vbo_v);
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)* vertices.size(), &vertices[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

}

