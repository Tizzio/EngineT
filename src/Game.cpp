
#include "Game.h"
#include "scene.h"
#include "camera.h"
#include "texture.h"
#include "sprite.h"
#include "mesh.h"
#include "render_manager.h"
#include "gameobject.h"
#include "transform.h"
#include "light.h"
#include "utils.h"
#include "labyr.h"
#include "font.h"
#include "style.h"
#include "ui_text.h"
#include "shader_manager.h" 
#include "material.h" 
#include "mesh_generator.h"
#include "physics.h" 
#include "fly_controller.h" 
#include "fps_controller.h" 
#include "obj_2d.h"
#include "obj_3d.h"
using namespace EngineT;

Game::Game()
{
    Scene* scene = new Scene();
    
    //load textures
    //Texture* tex_font0 = new Texture("data/fonts/font16.png");

    Shader* shader_unlit = Engine.shaderManager->Load("data/shaders/unlit.shader");
    Shader* shader_diffuse = Engine.shaderManager->Load("data/shaders/diffuse.shader");
    Shader* shader_specular = Engine.shaderManager->Load("data/shaders/specular.shader");
    Shader* shader_normalmap = Engine.shaderManager->Load("data/shaders/normalmap.shader");

   
    //Texture* tex_atlas0 = new Texture("data/textures/atlas0.png"); 
    //Sprite* spr_window = new Sprite();
    //spr_window->LoadSliced(tex_atlas0, "data/sprites/spr_window.spr", vec2(400, 250));

    //Sprite* spr_spider = new Sprite(tex_atlas0, "data/sprites/spr_spider.spr");
    //Sprite* spr_tree = new Sprite(tex_atlas0, "data/sprites/spr_tree.spr");
    //spr_test->CreateFromStrip(tex_sprite_test, 11*21, tex_sprite_test->width / 11, tex_sprite_test->height / 21);


    //load farm
    //Mesh* mesh_farm = new Mesh("data/models/farm.obj");
    //mesh_farm->SetTexture(tex_farm, 0, 0);*/

    //create 3D camera
    Camera* camera = new Camera(Engine.windowWidth, Engine.windowHeight);
    scene->Add(camera);

    ////create 2D camera
    //Camera* camera2D = new Camera(Engine.windowWidth, Engine.windowHeight);
    //camera2D->SetOrtho(-100.0f, -100.0f, Engine.windowWidth, Engine.windowHeight, 0.001f, 1000.0f);
    //camera2D->SetPosition(vec3(0, 0, 1000.0f));
    //scene->Add(camera2D);

    //=======================
    //= Skybox
    //======================= 
    auto tex_skybox = new Texture("data/textures/tex_skybox.png", 3);
    auto mat_skybox = new Material(shader_unlit, tex_skybox);
    auto mesh_skybox = new Mesh("data/models/skybox.obj");

    auto skybox = new Obj3D();
    skybox->SetMesh(mesh_skybox);
    skybox->SetMaterial(mat_skybox);

    skybox->transform.SetScaling(vec3(30, 30, 30));
    skybox->transform.SetPosition(vec3(0, -160, 0));
    scene->Add(skybox); 
     
    //=======================
    //= Spaceship
    //======================= 
    auto tex_ship = new Texture("data/textures/tex_ship.png", 3);
    auto mat_ship = new Material(shader_specular, tex_ship);
    auto mesh_ship = new Mesh("data/models/ship.obj");

    for(int i = 0; i < 15; i++)
    {
        Obj3D* spaceship = new Obj3D();
        spaceship->SetMesh(mesh_ship);
        spaceship->SetMaterial(mat_ship);

        spaceship->transform.SetScaling(vec3(0.2f, 0.2f, 0.2f));
        spaceship->transform.SetPosition(vec3(
            cos(i * 15 * 0.01745) * 15.0f,
            2.0f + i*1.0f,
            sin(i * 15 * 0.01745) * 15.0f
            ));
        scene->Add(spaceship);
    }

    ////2d spider
    //Obj2D* obj_spider = new Obj2D();
    //obj_spider->SetSprite(spr_spider);
    //obj_spider->transform.SetScaling(vec3(2, 2, 2));
    //obj_spider->imageSpeed = 0.1f;
    //scene->Add(obj_spider);

    ////test window
    //Obj2D* obj_window = new Obj2D();
    //obj_window->SetSprite(spr_window);
    //obj_window->transform.SetPosition(vec3(50, 50, 0));
    //scene->Add(obj_window);

    ////2d tree
    //Obj2D* obj_tree = new Obj2D();
    //obj_tree->SetSprite(spr_tree);
    //obj_tree->transform.SetPosition(vec3(300, 100, 0));
    //scene->Add(obj_tree);
    //
    /*
    //labirynth
    Labyr * labyr = new Labyr();
    labyr->set_difficulty(1);
    labyr->set_dimensions(32, 32);
    labyr->build_labyrinth();

    Mesh* mesh_labyr = labyr->generate_mesh(3.0f);
    mesh_labyr->SetTexture(tex_bricks, 0, 0);

    Obj3D* obj_labyr = new Obj3D();
    obj_labyr->SetMesh(mesh_labyr);
    obj_labyr->transform.SetPosition(vec3(-16.0f, 0, -16.0f));
    scene->Add(obj_labyr);
    */

    /*
    //Add a start and and a goal
    labyr->set_start_goal();

    //Access to labyrinth matrix a takes the value of labyrinth in row 10 and columnm 23
    //0 is a free space, 1 is a wall, 2 is the start, 3 is the goal
    //int a = labyr->labyrinth[10][23];

    //delete labyr;
    */


    //=======================
    //= Ground
    //======================= 

    
    auto tex_bricks = new Texture("data/textures/tex_bricks.png", 3);
    auto mat_ground = new Material(shader_diffuse, tex_bricks);
    auto mesh_floor = MeshGenerator::GenerateFloor(250.0f, 250.0f, false, 0, 0, 3, 3)->Finalize();
 
    auto obj_floor = new Obj3D();
    obj_floor->SetMesh(mesh_floor);
    obj_floor->SetMaterial(mat_ground);
    obj_floor->transform.SetPosition(vec3(-125.0f, 0, -125.0f));
  
    Rigidbody* body_plane = new Rigidbody(obj_floor);
    btCollisionShape* shape_plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
    body_plane->Instantiate(shape_plane, 0);

    scene->Add(obj_floor);
    

    //obj_test_plane->AddComponent<ComponentTest>();
    //ComponentTest* t = obj_test_plane->GetComponent<ComponentTest>();
    //if(t != nullptr)
    //    cout << "trovato componente: " << t->GetType() << endl;
  
    //=======================
    //= Rigidbody cube
    //======================= 

    auto tex_crate = new Texture("data/textures/tex_wall.png", 3);
    auto tex_crate_normal = new Texture("data/textures/norm_wall.png", 3);
    auto mat_crate = new Material(shader_normalmap, tex_crate, tex_crate_normal);
    auto mesh_cube = new Mesh("data/models/mod_cube.obj");
    
    for(int i = 0; i < 32; i++)
    {
        auto obj_cube = new Obj3D();
        obj_cube->SetMesh(mesh_cube);
        obj_cube->SetMaterial(mat_crate);

        obj_cube->transform.SetPosition(vec3(10, i*1.2f + 5.0f, 0));
        scene->Add(obj_cube);

        Rigidbody* body_cube = new Rigidbody(obj_cube);
        btCollisionShape* shape_cube = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
        body_cube->Instantiate(shape_cube, 1.0f);
    }

    //=======================
    //= Character controller
    //======================= 

    // fly controller
    FlyController* controller = new FlyController(camera);
    controller->SetPosition(vec3(1.0f, 2.0f, 1.0f));
    scene->Add(controller);

    /*
    // first person controller
    FpsController* controller = new FpsController(camera);
    controller->Setup();
    controller->SetPosition(vec3(1.0f, 2.0f, 1.0f));
    scene->Add(controller);
    */

    //=======================
    //= Lights
    //======================= 

    Light* light;
    light = new Light(LightType::Directional);
    light->color = vec3(0.8f, 0.5f, 0.0f);
    light->transform.AddRotation(-15, vec3(1.0f, 0.0f, 0.0f)); 
    scene->Add(light);

    light = new Light(LightType::Point);
    light->color = vec3(1.0f, 0.0f, 0.0f);
    light->transform.SetPosition(vec3(20.0f, 1.0f, 0.0f));
    scene->Add(light);
    controller->light = light;

    //light = new Light(LightType::Point);
    //light->color = vec3(0.0f, 0.0f, 1.0f);
    //light->transform.SetPosition(vec3(-20.0f, 1.0f, 0.0f));
    //scene->Add(light);


    //tex_font0->SetFilter(TextureFilter::Point);
    //Font* font0 = new Font(tex_font0, "data/fonts/font16.fnt");
    //Style* style0 = new Style(font0);

    /*Text* text = new Text(L"O_o il [#3333aa]testo[#]\nche va a capo!\nÆnche con caratteri\nspeciali e [#aa3333]Colorati[#] ", style0);
    text->transform.SetScaling(vec3(2,2,2));
    text->transform.SetPosition(vec3(50, 250, 0));
    scene->Add(text);*/
    
    //set the current scene
    Engine.SetScene(scene);
}
