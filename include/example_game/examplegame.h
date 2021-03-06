#pragma once
#ifndef ROCKET_EXAMPLEGAME_INCLUDED
#define ROCKET_EXAMPLEGAME_INCLUDED

#include "game.h"
#include "gameview.h"
#include "renderer.h"
#include "buffer.h"
#include "shader.h"
#include "texture.h"
#include "drawbinding.h"
#include "material.h"
#include "renderqueue.h"
#include "rendertarget.h"
#include "vectormath.h"
#include "input.h"

class ExampleGame : public Rocket::Game
{
public:
    virtual void Startup(Rocket::GameServices* services);
    virtual void Shutdown(Rocket::GameServices* services);
	virtual void Update(float dt);

private:
    
    struct
    {
        int Color;
        int Transform;
        int Offset;
    } m_properties;

    Rocket::RenderTarget* m_primaryTarget;

	Rocket::Buffer* m_vertbuffer;
	Rocket::Buffer* m_indexbuffer;
	Rocket::DrawBinding* m_binding;
	Rocket::Shader* m_shader;
	Rocket::Texture2D* m_texture;
	Rocket::Material* m_material[3];

	Rocket::RenderTarget* m_renderTarget;
	Rocket::RenderQueue* m_framebufferQueue;

	Rocket::Buffer* m_quadverts;
	Rocket::Buffer* m_quadindices;
	Rocket::DrawBinding* m_quadbinding;
	Rocket::Shader* m_blitshader;
	Rocket::Material* m_blitMaterial;
	Rocket::RenderQueue* m_mainQueue;
    
    Rocket::Input::IButton* m_bumpButton;
    Rocket::Input::IAxis* m_spinAxisX;
    Rocket::Input::IAxis* m_spinAxisY;

	float m_angle;
	float m_angle2;
    float m_spin;
    float m_spin2;
    
	Rocket::vec2 m_offset;
    float m_bump;

};

#endif
