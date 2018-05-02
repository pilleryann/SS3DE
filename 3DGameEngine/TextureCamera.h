#pragma once
#include "TextureBase.h"
#include "glm\glm.hpp"
class TextureCamera :
	public TextureBase
{
public:
	TextureCamera(int width=800,int height=600);
	~TextureCamera();

	GLuint GetTexureID() override;
	GLuint GetFrameBufferID();
	GLuint GetRenderBufferObjectID();

	void setHeight(int height);
	void setWidth(int width);

	void setSize(glm::vec2 size);

private:

	GLuint m_frameBufferID;
	GLuint m_renderBufferObject;

	int m_width;
	int m_height;

	

	void InitTexture();
	void CreateTexture();
	void RemoveTexture();
	void BindTextureToFrameBuffer();
	void CreateFrameBuffer();
	void CreateRenderBufferObject();
	void completInitTexture();


};

