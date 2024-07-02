#include "Camera.h"
#include "Math/MyMath.h"
#include "WinApp.h"

void Camera::Initialize(std::shared_ptr<DirectXCommon> dxCommon){
	mFov = 50.0f;
}

void Camera::UpdateMatrix(){
	Matrix4x4 worldMatrix = MakeAffineMatrix({1.0f,1.0f,1.0f}, mRotate, mTranslate);
	mViewMatrix = Inverse(worldMatrix);
	mProjectionMatrix = MakePerspectiveFovMatrix(mFov * (kPi / 180.0f), WinApp::kClientWidth / float(WinApp::kClientHeight), 0.1f, 1000.0f);
}
