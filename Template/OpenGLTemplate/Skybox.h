#pragma once

#include "Texture.h"
#include "VertexBufferObject.h"

// This is a class for creating and rendering a skybox
class CSkybox
{
public:
	CSkybox();
	~CSkybox();
	void Create(string directory, string front, string back, string left, string right, string top, string bottom, float size);
	void Render();
	void Release();

private:
	UINT m_vao;
	CVertexBufferObject m_vbo;
	CTexture m_textures[6];
	string m_directory;
	string m_front, m_back, m_left, m_right, m_top, m_bottom;
};