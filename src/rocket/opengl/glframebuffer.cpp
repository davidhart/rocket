#include "opengl/glframebuffer.h"
#include "opengl/gltexture.h"
#include "vectormath.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

GLFramebuffer::GLFramebuffer() :
	m_framebuffer(0),
	m_depthAttachment(nullptr)
{
}

GLFramebuffer::~GLFramebuffer()
{
	if (m_framebuffer)
	{
		glDeleteFramebuffers(1, &m_framebuffer);
	}

	for (size_t i = 0; i < m_framebufferAttachements.size(); ++i)
	{
		delete m_framebufferAttachements[i];
	}
}

bool GLFramebuffer::Create(const FramebufferDef& framebufferDef)
{
	glGenFramebuffers(1, &m_framebuffer);
	assert(m_framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	
	GLenum* drawBuffers = new GLenum[framebufferDef.numColorAttachements];

	m_size = ivec2(framebufferDef.width, framebufferDef.height);

	for (unsigned i = 0; i < framebufferDef.numColorAttachements; ++i)
	{
		const FramebufferColorAttachmentDef attachmentDef = framebufferDef.colorAttachments[i];

		TextureDef2D attachmentTextureDef;
		attachmentTextureDef.width = framebufferDef.width;
		attachmentTextureDef.height = framebufferDef.height;
		attachmentTextureDef.format = attachmentDef.format;
		attachmentTextureDef.sampler = attachmentDef.sampler;
		attachmentTextureDef.data = nullptr;
		attachmentTextureDef.size = framebufferDef.width * framebufferDef.height * Texture::PixelSizeForFormat(attachmentDef.format);
		
		GLTexture2D* attachmentTexture = new GLTexture2D();

		if (attachmentTexture->Create(attachmentTextureDef) == false)
		{
			delete attachmentTexture;
			return false;
		}

		GLenum attachment = GL_COLOR_ATTACHMENT0 + i;

		glFramebufferTexture2D(GL_FRAMEBUFFER, attachment, GL_TEXTURE_2D, attachmentTexture->GetNativeHandle(), 0);
		
		drawBuffers[i] = attachment;
		m_framebufferAttachements.push_back(attachmentTexture);
	}

	if (framebufferDef.depthAttachement)
	{
		TextureFormat format = framebufferDef.depthAttachement->format;

		assert(format == TEXFMT_DEPTH_16 || format == TEXFMT_DEPTH_32); // Unsupported depth format

		TextureDef2D depthTextureDef;
		depthTextureDef.width = framebufferDef.width;
		depthTextureDef.height = framebufferDef.height;
		depthTextureDef.format = format;
		depthTextureDef.sampler = framebufferDef.depthAttachement->sampler;
		depthTextureDef.data = nullptr;
		depthTextureDef.size = framebufferDef.width * framebufferDef.height * Texture::PixelSizeForFormat(format);

		GLTexture2D* attachmentTexture = new GLTexture2D();
		if (attachmentTexture->Create(depthTextureDef) == false)
		{
			delete attachmentTexture;
			return false;
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, attachmentTexture->GetNativeHandle(), 0);
	}

	glDrawBuffers(framebufferDef.numColorAttachements, drawBuffers);
	
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

Texture2D* GLFramebuffer::GetColorAttachment(int index)
{
	assert(index >= 0 && (size_t)index < m_framebufferAttachements.size()); // Attachment not found

	return m_framebufferAttachements[index];
}

Texture2D* GLFramebuffer::GetDepthAttachment()
{
	return m_depthAttachment;
}

ivec2 GLFramebuffer::GetSize()
{
	return m_size;
}

GLuint GLFramebuffer::GetNativeHandle()
{
	return m_framebuffer;
}