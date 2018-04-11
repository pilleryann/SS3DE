#include "GameObject.h"
#include "Component.h"
#include "Transform3D.h"
#include "Render3D.h"





GameObject::GameObject(Engine * engine,std::string name)
{
	//m_transform = Transform3D(this);
	m_transform = new Transform3D(this);
	m_engine = engine;
	m_name = name;
}

GameObject::~GameObject()
{
	
	for (int i = 0; i < m_components.size(); i++) {
		delete m_components[i];
	}

	delete m_transform;
	if(m_render3D!=NULL)
		delete m_render3D;
	
}

void GameObject::Start()
{
	for (int i = 0; i < m_components.size(); i++) {
		m_components[i]->Start();
	}
	if(m_render3D!=NULL)
		m_render3D->Start();
}

void GameObject::Update()
{
	for (int i = 0; i < m_components.size(); i++) {
		m_components[i]->Update();
	}
}

void GameObject::Render()
{
	if (m_render3D == nullptr)
	{
	//	printf("Gameobject sans render 3D \n");
		return;
	}

	m_render3D->Update();
}

void GameObject::End()
{
	//TODO implementer une fin 
}



void GameObject::AddComponent(Component * component)
{
	printf("Coponent type : %s \n", typeid(*component).name());
	//printf("Render 3D  type : %s \n", typeid(m_render3D).name());
	Render3D * render3D = dynamic_cast<Render3D*>(component);	
	
	if (render3D !=NULL) {
		printf("Coponent type is super coool : %s \n", typeid(*component).name());
		m_render3D = render3D;
		return;
	}
	//Can't add transform in the components list. It' created in the contructor of component.
	Transform3D * transfromTest = dynamic_cast<Transform3D*>(component);
	if (transfromTest !=NULL) {
		return;
	}

	m_components.push_back(component);
}



Engine * GameObject::GetEngine()
{
	
	return m_engine;
}

Transform3D * GameObject::GetTransform()
{
	return m_transform;
}
