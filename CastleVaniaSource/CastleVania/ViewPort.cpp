#include "ViewPort.h"

ViewPort::ViewPort(float x, float y) {
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
	this->cameraPosition.z = 0;
}

ViewPort::~ViewPort() {};

D3DXVECTOR3 ViewPort::SetPositionInViewPort(D3DXVECTOR3 position) {
	D3DXMATRIX matrix;
	D3DXMatrixIdentity(&matrix); //chuyen matrix ve ma tran dong nhat

	//thiet lap matrix thanh ma tran trung gian
	matrix._22 = -1.0f;
	matrix._41 = -this->cameraPosition.x;
	matrix._42 = this->cameraPosition.y;

	D3DXVECTOR4 vp_pos; 	//toa do moi se luu trong vp_pos
	D3DXVec3Transform(&vp_pos, &position, &matrix); 	//D3DXVEC3TRANSFORM se thuc hien nhan position voi ma tran trung gian de ra toa do moi
	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0); 	//La toa do da duoc chuyen tu toa do the gioi sang toa do trong viewport. Dung toa do nay de ve
}

void ViewPort::SetCameraPosition(float x, float y) {
	this->cameraPosition.x = x;
	this->cameraPosition.y = y;
}

D3DXVECTOR3 ViewPort::GetCameraPosition()
{
	return this->cameraPosition;
}