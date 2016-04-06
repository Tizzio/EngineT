#pragma once

#include "gameobject.h" 

namespace EngineT
{
    class Text : GameObject
    {
        friend class RenderManager;
        friend class Scene;
    public:

        string text;
        TransformRenderable transform;
        Text(wstring text, Style* style = nullptr);
        ~Text();

        void SetText(wstring text);

        class Vertex
        {
        public:
            vec2 pos;
            vec2 uv;
            vec4 col;
            Vertex(vec2 position, vec2 UV, vec4 color)
            {
                pos = position;
                uv = UV;
                col = color;

            };
        };

    private:
        void Update() {};
        void Draw();
        void GenerateBuffers();
        void UpdateBuffers();

        Style* style;

        vector<Vertex> vertices;
        vector <uint> indices;
        GLuint vao;
        GLuint vbo_i;
        GLuint vbo_v;
    };
}