#include "TextureCamera.h"






TextureCamera::TextureCamera(int width, int height)
{
	m_width = width;
	m_height = height;
}

TextureCamera::~TextureCamera()
{
	glDeleteFramebuffers(1, &m_frameBufferID);
}

GLuint TextureCamera::GetTexureID()
{
	return texture_ID;
}

GLuint TextureCamera::GetFrameBufferID()
{
	return m_frameBufferID;
}

void TextureCamera::setHeight(int height)
{
	m_height = height;
	RemoveTexture();
	CreateTexture();
	BindTextureToFrameBuffer();
}

void TextureCamera::setWidth(int width)
{
	m_width = width;
	RemoveTexture();
	CreateTexture();
	BindTextureToFrameBuffer();
}

void TextureCamera::setSize(glm::vec2 size)
{
	m_width = size.x;
	m_height = size.y;

	RemoveTexture();
	CreateTexture();
	BindTextureToFrameBuffer();
}

void TextureCamera::InitTexture()
{

	CreateFrameBuffer();
	CreateTexture();
	BindTextureToFrameBuffer();
	CreateRenderBufferObject();

}

void TextureCamera::CreateTexture()
{
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void TextureCamera::RemoveTexture()
{
	//TODO  A mettre un autre jour 
}

void TextureCamera::BindTextureToFrameBuffer()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_ID, 0);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}

void TextureCamera::CreateFrameBuffer()
{
	glGenBuffers(1, &m_frameBufferID);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		printf("Error to create framebuffer !");
		return;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);


}

void TextureCamera::CreateRenderBufferObject()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
