#include "api.h"
#include "game.h"

#include "renderer.h"
#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "drawbinding.h"
#include "material.h"
#include "renderqueue.h"
#include "rendertarget.h"
#include "vectormath.h"

#if defined(_WIN32)
	#define EXAMPLE_GAME_EXPORT __declspec(dllexport)
#else
	#define EXAMPLE_GAME_EXPORT
#endif

extern "C"
{
	EXAMPLE_GAME_EXPORT Rocket::Game* CreateGame(Rocket::Renderer* renderer);
	EXAMPLE_GAME_EXPORT void ReleaseGame(Rocket::Game* game);
}

class ExampleGame : public Rocket::Game
{
public:
	ExampleGame(Rocket::Renderer* renderer);
	~ExampleGame();
	void Update(float dt);

private:
	Rocket::Renderer* m_renderer;

	Rocket::Buffer* m_vertbuffer;
	Rocket::Buffer* m_indexbuffer;
	Rocket::DrawBinding* m_binding;
	Rocket::Shader* m_shader;
	Rocket::Texture2D* m_texture;
	Rocket::Material* m_material;
	Rocket::ShaderParameters* m_parameters;

	Rocket::RenderTarget* m_renderTarget;
	Rocket::RenderQueue* m_framebufferQueue;

	Rocket::Buffer* m_quadverts;
	Rocket::Buffer* m_quadindices;
	Rocket::DrawBinding* m_quadbinding;
	Rocket::Shader* m_blitshader;
	Rocket::Material* m_blitMaterial;
	Rocket::ShaderParameters* m_blitParameters;
	Rocket::RenderQueue* m_mainQueue;

	float m_angle;
	float m_angle2;
	Rocket::vec2 m_offset;
};