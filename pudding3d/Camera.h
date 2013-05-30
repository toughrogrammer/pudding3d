
#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "vector.h"
#include "Matrix.h"
#include "util.h"

class RenderList;
class Viewport;
class Camera
{
public:
	Camera( Vector3 pos, float fov = 90, float nearZ = 1, float farZ = 100 );
	~Camera();
	
	void ComputeWorldToCameraMat();
	void ComputePorjectionMat(Viewport* viewport);
	void WorldToCamera( RenderList* renderList );
	void CameraToScreen( RenderList* renderList, Viewport* viewport );
	void CameraToScreen( Vector4& v, Viewport* viewport );

	Matrix4 GetWorldToCameraMat() { return _worldToCamera; }

	Vector3 GetPosition() { return _pos; }
	void SetPosition( Vector3 pos );

	
private:
	Vector3 _pos, _dir, _up, _right;
	Vector3 _rot;
	float _nearZ, _farZ, _fov;
	float _distance;

	Matrix4 _worldToCamera, _projection;
};

#endif