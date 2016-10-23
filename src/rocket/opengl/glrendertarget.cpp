#include "opengl/glrendertarget.h"
#include "opengl/gltexture.h"
#include "vectormath.h"
#include <cassert>

using namespace Rocket;
using namespace Rocket::OpenGL;

Texture2D* GLPrimaryRenderTarget::GetColorAttachment(int)
{
	// TODO: make this impossible
	assert(false); // Primary target does not expose attachment textures
	return nullptr;
}

Texture2D* GLPrimaryRenderTarget::GetDepthAttachment()
{
	assert(false); // Primary target does not expose depth texture
	return nullptr;
}

GLuint GLPrimaryRenderTarget::GetNativeHandle()
{
	return 0;
}

ivec2 GLPrimaryRenderTarget::GetSize() const
{
	return m_size;
}

void GLPrimaryRenderTarget::SetSize(const ivec2& size)
{
	m_size = size;
}

GLRenderTarget::GLRenderTarget() :
	m_framebuffer(0),
	m_depthAttachment(nullptr)
{
}

GLRenderTarget::~GLRenderTarget()
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

bool GLRenderTarget::Create(const RenderTargetDef& targetDef)
{
	glGenFramebuffers(1, &m_framebuffer);
	assert(m_framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
	
	GLenum* drawBuffers = new GLenum[targetDef.numColorAttachements];

	m_size = ivec2(targetDef.width, targetDef.height);

	for (unsigned i = 0; i < targetDef.numColorAttachements; ++i)
	{
		const RenderTargetColorAttachmentDef attachmentDef = targetDef.colorAttachments[i];

		TextureDef2D attachmentTextureDef;
		attachmentTextureDef.width = targetDef.width;
		attachmentTextureDef.height = targetDef.height;
		attachmentTextureDef.format = attachmentDef.format;
		attachmentTextureDef.sampler = attachmentDef.sampler;
		attachmentTextureDef.data = nullptr;
		attachmentTextureDef.size = targetDef.width * targetDef.height * Texture::PixelSizeForFormat(attachmentDef.format);
		
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

	if (targetDef.depthAttachement)
	{
		TextureFormat format = targetDef.depthAttachement->format;

		assert(format == TEXFMT_DEPTH_16 || format == TEXFMT_DEPTH_32); // Unsupported depth format

		TextureDef2D depthTextureDef;
		depthTextureDef.width = targetDef.width;
		depthTextureDef.height = targetDef.height;
		depthTextureDef.format = format;
		depthTextureDef.sampler = targetDef.depthAttachement->sampler;
		depthTextureDef.data = nullptr;
		depthTextureDef.size = targetDef.width * targetDef.height * Texture::PixelSizeForFormat(format);

		GLTexture2D* attachmentTexture = new GLTexture2D();
		if (attachmentTexture->Create(depthTextureDef) == false)
		{
			delete attachmentTexture;
			return false;
		}

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, attachmentTexture->GetNativeHandle(), 0);
	}

	glDrawBuffers(targetDef.numColorAttachements, drawBuffers);
	
	assert(glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return true;
}

Texture2D* GLRenderTarget::GetColorAttachment(int index)
{
	assert(index >= 0 && (size_t)index < m_framebufferAttachements.size()); // Attachment not found

	return m_framebufferAttachements[index];
}

Texture2D* GLRenderTarget::GetDepthAttachment()
{
	return m_depthAttachment;
}

ivec2 GLRenderTarget::GetSize() const
{
	return m_size;
}

GLuint GLRenderTarget::GetNativeHandle()
{
	return m_framebuffer;
}