#include "GameObject.h"
#include "MyGame.h"

GameObject::~GameObject(){
}

GameObject::GameObject(MyGame* myGame){
	mMyGame = myGame;
}

void GameObject::UpdateMatrix(){
	mTransform.UpdateMatrix();
}
