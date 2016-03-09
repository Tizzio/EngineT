
#pragma once


#include "engine_t.h"

namespace EngineT
{

    typedef int Layer;

    class Scene
    {
        friend class Renderer;
    private:
        //non renderable objects
        unordered_map<Layer, vector<GameObject*> > objLayers;
        //renderable objects
        unordered_map<Layer, vector<GameObject3D*> > obj3DLayers;
        unordered_map<Layer, vector<GameObject2D*> > obj2DLayers;
        unordered_map<Layer, vector<Text*> > textLayers;
        vector<Layer> layerList;
        Layer currentLayerId = 0;

    public:
        vector<Camera*> cameras;
        vector<Light*> lights;
        Scene();
        ~Scene();

        Layer CreateLayer();
        void DeleteLayer(Layer layer);

        void Add(GameObject* gameObject, Layer layer);
        void Remove(GameObject* gameObject);

        void Add(GameObject3D* gameObject, Layer layer);
        void Remove(GameObject3D* gameObject);

        void Add(GameObject2D* gameObject, Layer layer);
        void Remove(GameObject2D* gameObject);

        void Add(Text* text, Layer layer);
        void Remove(Text* text);

        void Add(Light* light);
        void Remove(Light* light);

        void Add(Camera* camera, Layer layer);
        void Remove(Camera* camera);

        void Update();


    };
}

