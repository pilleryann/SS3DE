#include "Transform3D.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "glm\gtc\matrix_transform.hpp"









Transform3D::Transform3D(GameObject * gameObject, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale):Component(gameObject)
{
	m_position = position;
	m_rotation = rotation;
	m_scale = scale;
}

Transform3D::~Transform3D()
{
}

void Transform3D::Start()
{
}

void Transform3D::Update()
{
}

glm::vec3 Transform3D::GetPosition()
{
	return m_position;
}

glm::vec3 Transform3D::GeRotation()
{
	float x = glm::degrees(m_rotation.x);
	float y = glm::degrees(m_rotation.y);
	float z = glm::degrees(m_rotation.z);
	glm::vec3 newRotation = glm::vec3(x,y,z);
	return newRotation;
}

glm::vec3 Transform3D::GetScale()
{
	return m_scale;
}

void Transform3D::SetPosition(glm::vec3 position)
{
	m_position = position;
}

void Transform3D::SetRotation(glm::vec3 rotation)
{
	m_rotation.x = glm::radians(rotation.x);
	m_rotation.y = glm::radians(rotation.y);
	m_rotation.z = glm::radians(rotation.z);

	
}

void Transform3D::SetScale(glm::vec3 scale)
{
	m_scale = scale;
}

glm::mat4 Transform3D::GetMatrixTransformation()
{
	glm::mat4 TranslationMat4 = glm::translate(m_position);
	glm::mat4 ScaleMat4 = glm::scale(m_scale);
//	glm::vec3 rotationAxis = glm::vec3(rotationQuaternion.x, rotationQuaternion.y, rotationQuaternion.z);
	//glm::mat4 RotationMat4 = glm::rotate(rotationQuaternion.w, rotationAxis);
	glm::mat4 RotationMat4 = glm::eulerAngleXYZ(m_rotation.x, m_rotation.y, m_rotation.z);
	glm::mat4 modelMatrix = TranslationMat4 * RotationMat4 * ScaleMat4;

	return modelMatrix;
}
