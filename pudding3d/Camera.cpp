
#include "Camera.h"
#include "RenderList.h"
#include "Viewport.h"

Camera::Camera( Vector3 pos, float fov, float nearZ, float farZ )
	:_pos(pos),
	_dir(pos.x, pos.y, pos.z + 1),
	_up(0, 1, 0),
	_fov(fov),
	_nearZ(nearZ),
	_farZ(farZ)
{
	_worldToCamera.Identity();
	_projection.Identity();

	ComputeWorldToCameraMat();
}

Camera::~Camera()
{

}


void Camera::SetPosition( Vector3 pos )
{
	_pos = pos;
	_dir.Set( pos.x, pos.y, pos.z + 1 );

	_worldToCamera.Identity();
	_projection.Identity();

	ComputeWorldToCameraMat();
}

void Camera::ComputeWorldToCameraMat()
{
	Vector3 zaxis;
	zaxis.Set( _dir.x - _pos.x, _dir.y - _pos.y, _dir.z - _pos.z );
	zaxis.Normalize();
	
	// xaxis = zaxis X up
	Vector3 xaxis;
	xaxis = cross(zaxis, _up);
	xaxis.Normalize();

	Vector3 yaxis;
	yaxis = cross(zaxis, xaxis);

	_worldToCamera.Identity();

	_worldToCamera.a11 = xaxis.x;
	_worldToCamera.a12 = yaxis.x;
	_worldToCamera.a13 = zaxis.x;
	_worldToCamera.a14 = 0;

	_worldToCamera.a21 = xaxis.y;
	_worldToCamera.a22 = yaxis.y;
	_worldToCamera.a23 = zaxis.y;
	_worldToCamera.a24 = 0;

	_worldToCamera.a31 = xaxis.z;
	_worldToCamera.a32 = yaxis.z;
	_worldToCamera.a33 = zaxis.z;
	_worldToCamera.a34 = 0;

	_worldToCamera.a41 = -dot(xaxis, _pos);
	_worldToCamera.a42 = -dot(yaxis, _pos);
	_worldToCamera.a43 = -dot(zaxis, _pos);
	_worldToCamera.a44 = 1;
}

void Camera::ComputeProjectionMat( Viewport* viewport)
{
	int width = viewport->_width;
	int height = viewport->_height;
	//float tanfov = (float)tan(_fov * 0.5f);
	float cot = 1.0f / tan( _fov * 0.5f );
	float aspect = (float)(width / height);

	_projection.Identity();

	_projection.a11 = cot / aspect;
	_projection.a12 = 0;
	_projection.a13 = 0;
	_projection.a14 = 0;

	_projection.a21 = 0;
	_projection.a22 = cot;
	_projection.a23 = 0;
	_projection.a24 = 0;

	_projection.a31 = 0;
	_projection.a32 = 0;
	_projection.a33 = -1 * (_farZ + _nearZ) / ( _farZ - _nearZ );
	_projection.a34 = 2 * ( _nearZ * _farZ ) / ( _farZ - _nearZ );

	_projection.a41 = 0;
	_projection.a42 = 0;
	_projection.a43 = 1;
	_projection.a44 = 0;
}

void Camera::WorldToCamera( RenderList* renderList )
{
	RenderList::Triangles& triangles = renderList->triangles();

	for( auto& t : triangles )
	{
		t.Clipping( _pos.z + _nearZ, _pos.z + _farZ );
		if( false == t.IsClipped() )
			t.Transform( _worldToCamera );
	}
}

void Camera::CameraToScreen( RenderList* renderList, Viewport* viewport )
{
	ComputeProjectionMat(viewport);

	RenderList::Triangles& triangles = renderList->triangles();

	for( auto& t : triangles )
	{
		if( t.IsClipped() )
			continue;

		Vector4& v1 = t.v(0).pos;
		Vector4& v2 = t.v(1).pos;
		Vector4& v3 = t.v(2).pos;

		CameraToScreen( v1, viewport );
		CameraToScreen( v2, viewport );
		CameraToScreen( v3, viewport );
	}
}

void Camera::CameraToScreen( Vector4& v, Viewport* viewport )
{
	// back up vertex's z coordinate for zbuffer
	float z = v.z;

	v *= _projection;
	v /= v.w;

	float nx = v.x;
	float ny = v.y;

	float wx = ( nx + 1 ) * ( viewport->_width / 2 ) + ( viewport->_x );
	float wy = ( ny + 1 ) * ( viewport->_height / 2 ) + ( viewport->_y );

	v.x = wx;
	v.y = wy;
	v.z = z;
}