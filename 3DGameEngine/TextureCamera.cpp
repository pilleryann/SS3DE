#include "TextureCamera.h"






TextureCamera::TextureCamera(int width, int height)
{
	m_width = width;
	m_height = height;
	InitTexture();
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

	//completInitTexture();

}

void TextureCamera::CreateTexture()
{
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_ID, 0);
}

void TextureCamera::RemoveTexture()
{
	//TODO  A mettre un autre jour 
}

void TextureCamera::BindTextureToFrameBuffer()
{
	

}

void TextureCamera::CreateFrameBuffer()
{
	glGenFramebuffers(1, &m_frameBufferID);


	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);





}

void TextureCamera::CreateRenderBufferObject()
{

	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject);
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE) {
		printf("Error to create framebuffer !");

	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

}


/*
	IT's a model. not use .
*/
void TextureCamera::completInitTexture()
{


	// framebuffer configuration
	// -------------------------
	
	glGenFramebuffers(1, &m_frameBufferID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_frameBufferID);
	// create a color attachment texture
	
	glGenTextures(1, &texture_ID);
	glBindTexture(GL_TEXTURE_2D, texture_ID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_ID, 0);
	// create a renderbuffer object for depth and stencil attachment (we won't be sampling these)
	
	glGenRenderbuffers(1, &m_renderBufferObject);
	glBindRenderbuffer(GL_RENDERBUFFER, m_renderBufferObject);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_width, m_height); // use a single renderbuffer object for both a depth AND stencil buffer.
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderBufferObject); // now actually attach it
																								  // now that we actually created the framebuffer and added all attachments we want to check if it is actually complete now
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		printf("Error to create framebuffer !");
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
