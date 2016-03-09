
#include "Game.h"
#include "scene.h"
#include "camera.h"
#include "texture.h"
#include "sprite.h"
#include "mesh.h"
#include "renderer.h"
#include "gameobject.h"
#include "transform.h"
#include "light.h"
#include "utils.h"
#include "labyr.h"
#include "font.h"
#include "style.h"
#include "ui_text.h"
//#include "zlib\zlib.h"

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

	//create a rendering layer
	Layer mainLayer = scene->CreateLayer();

	//create a rendering layer for 2D objects
	Layer layer2D = scene->CreateLayer();

	//load textures
	//auto tex_font0 = make_unique<Texture>("data/fonts/font16.png");
	Texture* tex_font0 = new Texture("data/fonts/font16.png");
	Texture* tex_test = new Texture("data/textures/test.png", 3);
	Texture* tex_bricks = new Texture("data/textures/tex_bricks.png", 3);

	Texture* tex_atlas0 = new Texture("data/textures/atlas0.png");

	Sprite* spr_window = new Sprite();
	spr_window->LoadSliced(tex_atlas0, "data/sprites/spr_window.spr", vec2(400, 250));

	Sprite* spr_spider = new Sprite(tex_atlas0, "data/sprites/spr_spider.spr");
	Sprite* spr_tree = new Sprite(tex_atlas0, "data/sprites/spr_tree.spr");
	//spr_test->CreateFromStrip(tex_sprite_test, 11*21, tex_sprite_test->width / 11, tex_sprite_test->height / 21);


	//load airplane
	Mesh* mesh_airplane = new Mesh("data/models/airplane.obj");
	mesh_airplane->SetTexture(tex_test, 0, 0);

	//load farm
	/*Mesh* mesh_farm = new Mesh("data/models/farm.obj");
	mesh_farm->SetTexture(tex_farm, 0, 0);*/

	//create 3D camera
	Camera* camera = new Camera(Engine.windowWidth, Engine.windowHeight);
	scene->Add(camera, mainLayer);

	//create 2D camera
	Camera* camera2D = new Camera(Engine.windowWidth, Engine.windowHeight);
	camera2D->SetOrtho(-100.0f, -100.0f, Engine.windowWidth, Engine.windowHeight, 0.001f, 1000.0f);
	camera2D->SetPosition(vec3(0, 0, 1000.0f));
	scene->Add(camera2D, layer2D);

	/*Obj3D* farm = new Obj3D();
	farm->SetMesh(mesh_farm);*/
	//scene->Add(farm, mainLayer);

	for(int i = 0; i < 5; i++){
		Obj3D* airplane = new Obj3D();
		airplane->SetMesh(mesh_airplane);

		airplane->transform.SetScaling(vec3(0.2f, 0.2f, 0.2f));
		airplane->transform.SetPosition(vec3(
			cos(i * 15 * 0.01745) * 35.0f,
			10.0f + i*1.0f,
			sin(i * 15 * 0.01745) * 35.0f
			));
		scene->Add(airplane, mainLayer);
	}

	//2d spider
	Obj2D* obj_spider = new Obj2D();
	obj_spider->SetSprite(spr_spider);
	obj_spider->transform.SetScaling(vec3(2, 2, 2));
	obj_spider->imageSpeed = 0.1f;
	scene->Add(obj_spider, layer2D);

	//test window
	Obj2D* obj_window = new Obj2D();
	obj_window->SetSprite(spr_window);
	obj_window->transform.SetPosition(vec3(50, 50, 0));
	scene->Add(obj_window, layer2D);

	//2d tree
	Obj2D* obj_tree = new Obj2D();
	obj_tree->SetSprite(spr_tree);
	obj_tree->transform.SetPosition(vec3(300, 100, 0));
	scene->Add(obj_tree, layer2D);

	//labirynth
	Labyr * labyr = new Labyr();
	labyr->set_difficulty(1);
	labyr->set_dimensions(32, 32);
	labyr->build_labyrinth();

	Mesh* mesh_labyr = labyr->generate_mesh(1);
	mesh_labyr->SetTexture(tex_bricks, 0, 0);

	Obj3D* obj_labyr = new Obj3D();
	obj_labyr->SetMesh(mesh_labyr);
	obj_labyr->transform.SetPosition(vec3(-16.0f, 50.0f, -16.0f));
	//scene->Add(obj_labyr, mainLayer);

	/*
	//Add a start and and a goal
	labyr->set_start_goal();

	//Access to labyrinth matrix a takes the value of labyrinth in row 10 and columnm 23
	//0 is a free space, 1 is a wall, 2 is the start, 3 is the goal
	//int a = labyr->labyrinth[10][23];

	//delete labyr;
	*/

	//DEBUG floor
	Obj3D* obj_test_plane = new Obj3D();
	Rigidbody* body_plane = new Rigidbody(obj_test_plane);
	btCollisionShape* shape_plane = new btStaticPlaneShape(btVector3(0, 1, 0), 0);
	body_plane->Instantiate(shape_plane, 0, btVector3(0, 0, 0));
	Mesh* mesh_floor = MeshGenerator::GenerateFloor(1250.0f, 1250.0f)->Finalize();
	mesh_floor->SetTexture(tex_bricks, 0, 0);
	Obj3D* floor = new Obj3D();
	floor->SetMesh(mesh_floor);
	floor->transform.SetPosition(vec3(-25.0f, 0, -25.0f));
	scene->Add(floor, mainLayer);

	//RIGIDBODY CUBE
	Mesh* mesh_cube = new Mesh("data/models/cube.obj");
	mesh_cube->SetTexture(tex_bricks, 0, 0);

	for(int i = 0; i < 12; i++)
	{

		Obj3D* obj_cube = new Obj3D();
		obj_cube->SetMesh(mesh_cube);
		obj_cube->transform.SetPosition(vec3(0, i*1.2f + 5.0f, 0));
		//scene->Add(obj_cube, mainLayer);

		Rigidbody* body_cube = new Rigidbody(obj_cube);
		btCollisionShape* shape_cube = new btBoxShape(btVector3(0.5f, 0.5f, 0.5f));
		//body_cube->Instantiate(shape_cube, 1.0f, btVector3(0, 0, 0));
	}




	//create lights
	Light* light;
	light = new Light(LightType::Directional);
	light->color = vec3(0.3f, 0.3f, 0.3f);
	light->transform.AddRotation(-90.0f, vec3(1.0f, 0.0f, 0.0f));
	scene->Add(light);

	/*light = new Light(LightType::Point);
	light->color = vec3(1.0f, 0.0f, 0.0f);
	light->transform.SetPosition(vec3(20.0f, 3.0f, 0.0f));
	scene->Add(light);

	light = new Light(LightType::Point);
	light->color = vec3(0.0f, 0.0f, 1.0f);
	light->transform.SetPosition(vec3(-20.0f, 10.0f, 0.0f));
	scene->Add(light);*/

	//first person controller
	FlyController* controller = new FlyController(camera);
	controller->SetPosition(vec3(1.0f, 2.0f, 1.0f));
	scene->Add(controller, mainLayer);
	/*
	FpsController* controller = new FpsController(camera);
	controller->Setup();
	controller->SetPosition(vec3(1.0f, 2.0f, 1.0f));
	scene->Add(controller, mainLayer);
	*/


	tex_font0->SetFilter(TextureFilter::Point);
	Font* font0 = new Font(tex_font0, "data/fonts/font16.fnt");
	Style* style0 = new Style(font0);

	Text* text = new Text(L"O_o il [#3333aa]testo[#]\nche va a capo!\ Ænche con caratteri\nspeciali e [#aa3333]Colorati[#] ", style0);
	//text->transform.SetScaling(vec3(2,2,2));
	//text->transform.SetPosition(vec3(50, 250, 0));
	scene->Add(text, layer2D);

	//set the current scene
	Engine.SetScene(scene);
}
