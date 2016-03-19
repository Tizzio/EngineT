#include "font.h"

#include "utils.h" 
#include "texture.h" 

namespace EngineT
{

    Font::Font(Texture* texture, const string& filename)
    {
        Load(texture, filename);
    }

    Font::~Font()
    {
        //TODO: DESTROY ALL Char*
    }


    void Font::Load(Texture* texture, const string& filename)
    {
        ifstream file(filename);
        string line;

        this->texture = texture;
        vector<string> data;
        while(getline(file, line))
        {
            data = Utils::StringToStringArray(line);

            if(data[0] == "char") 
            {
                int id = Utils::GetIntAfter(data[1], '=');
                int x = Utils::GetIntAfter(data[2], '=') - 2;
                int y = Utils::GetIntAfter(data[3], '=') - 2;
                int width = Utils::GetIntAfter(data[4], '=') + 2;
                int height = Utils::GetIntAfter(data[5], '=') + 2;
                int xoffset = Utils::GetIntAfter(data[6], '=');
                int yoffset = Utils::GetIntAfter(data[7], '=');
                int xadvance = Utils::GetIntAfter(data[8], '=');

                float uvX1 = x / texture->width;
                float uvY1 = y / texture->height;
                float uvX2 = (x + width) / texture->width;
                float uvY2 = (y + height) / texture->height;

                int h = yoffset + height;
                if(h > maxHeight)
                    maxHeight = h;

                if(chars.size() <= (size_t)id)
                    chars.resize(id + 1);
                chars[id] = new Char(uvX1, uvY1, uvX2, uvY2, width, height, xoffset, yoffset, xadvance);

            }

        }
    }
}
