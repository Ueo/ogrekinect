
#include "Stdafx.h"
#include "KinectController.h"

//-------------------------------------------------------------------------------------
KinectController::KinectController(void)
	: kinectManager(0),
	skeleton(0)
{
}

//-------------------------------------------------------------------------------------
KinectController::~KinectController(void)
{	
}

//-------------------------------------------------------------------------------------
void KinectController::initController(void)
{
	kinectManager = new KinectManager();
	kinectManager->InitNui();
}

//-------------------------------------------------------------------------------------
void KinectController::unInitController(void)
{
	//if(skeleton) delete skeleton;

	if(kinectManager)
	{
		kinectManager->UnInitNui();
		delete kinectManager;
	}
}

//-------------------------------------------------------------------------------------
void KinectController::updatePerFrame(Ogre::Real elapsedTime)
{
	skeleton = kinectManager->getSkeleton();
}

//-------------------------------------------------------------------------------------
NUI_SKELETON_DATA* KinectController::getSkeletonData()
{
	return skeleton;
}

//-------------------------------------------------------------------------------------
Ogre::Vector4 KinectController::convertToOgreVector4(Vector4 nuiVector)
{
	return Ogre::Vector4(nuiVector.x, nuiVector.y, nuiVector.z, nuiVector.w);
}

//-------------------------------------------------------------------------------------
Ogre::Vector3 KinectController::convertToOgreVector3(Vector4 nuiVector)
{
	return Ogre::Vector3(nuiVector.x, nuiVector.y, nuiVector.z);
}

//-------------------------------------------------------------------------------------
Ogre::Vector3 KinectController::getJointPosition(NuiManager::NuiJointIndex idx)
{
	return this->convertToOgreVector3(this->getSkeletonData()->SkeletonPositions[idx]);
}

//-------------------------------------------------------------------------------------