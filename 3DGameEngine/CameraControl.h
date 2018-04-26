#pragma once
#ifndef  CAMERA_CONTROL
#define CAMERA_CONTROL


#include "Component.h"
class Camera;

class CameraControl :
	public Component
{
public:
	CameraControl(GameObject * gameObject);
	~CameraControl();

	 void Start()override;
	 void Update() override;

private :
	Camera * m_camera;
	


 
};
#endif // ! CAMERA_CONTROL
