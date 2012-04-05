/*
-----------------------------------------------------------------------------
Filename:    OgreKinect.cpp
-----------------------------------------------------------------------------
*/

#include "Stdafx.h"
#include "OgreKinect.h"

//-------------------------------------------------------------------------------------
OgreKinect::OgreKinect(void)
	:kinectController(0),
	character(0),
	accumulator(0),
	dt(0.01),
	dynamicsWorld(0),
	numBalls(0),
	ogreDisplay(0)
{
}
//-------------------------------------------------------------------------------------
OgreKinect::~OgreKinect(void)
{
	if(kinectController)
	{
		kinectController->unInitController();
		delete kinectController;
	}

	if(character) delete character;
}

//-------------------------------------------------------------------------------------
void OgreKinect::createScene(void)
{
	this->setUpKinect();

	character = new ControllableCharacter();
	character->setupCharacter(this->mSceneMgr, this->kinectController);

	// set shadow properties
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_TEXTURE_MODULATIVE);
	mSceneMgr->setShadowColour(Ogre::ColourValue(0.5, 0.5, 0.5));
	mSceneMgr->setShadowTextureSize(2048);
	mSceneMgr->setShadowTextureCount(1);
	
	// use a small amount of ambient lighting
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));

	// add a bright light above the scene
	Ogre::Light* light = mSceneMgr->createLight();
	light->setType(Ogre::Light::LT_POINT);
	light->setPosition(-100, 400, 200);
	light->setSpecularColour(Ogre::ColourValue::White);

	// Fog
	this->mSceneMgr->getCurrentViewport()->setBackgroundColour(Ogre::ColourValue(0.26f, 0.627f, 1.0f));

	// Bullet Physics
	/*
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();
	dispatcher = new btCollisionDispatcher(collisionConfiguration);
	solver = new btSequentialImpulseConstraintSolver;
	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,collisionConfiguration);
	dynamicsWorld->setGravity(btVector3(0, -10, 0));
	/*
	/*
	//create the character physical skeleton
	ogreDisplay = new OgreDisplay(dynamicsWorld);
	ragdoll = new SkeletonToRagdoll(mSceneMgr);
	ragdoll->createRagdoll(dynamicsWorld, character->getEntityNode());
	*/
	// Floor
	Ogre::MeshManager::getSingleton().createPlane("floor", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1000, 1000, 10, 10, true, 1, 10, 10, Ogre::Vector3::UNIT_Z);

	Ogre::Entity* floor = mSceneMgr->createEntity("Floor", "floor");
	floor->setMaterialName("Examples/Steel");
	floor->setCastShadows(false);
	mSceneMgr->getRootSceneNode()->attachObject(floor);

	// create the Bullet ground plane
	/*
	btCollisionShape* groundShape = new btStaticPlaneShape(btVector3(0,1,0), 1);
	btTransform groundTransform;
	groundTransform.setIdentity();
	groundTransform.setOrigin(btVector3(0, 0, 0));
	btDefaultMotionState* myMotionState = new btDefaultMotionState(groundTransform);
	btRigidBody::btRigidBodyConstructionInfo groundRigidBodyCI(0, myMotionState, groundShape, btVector3(0, 0, 0));
	btRigidBody* groundRigidBody = new btRigidBody(groundRigidBodyCI);
	groundRigidBody->setFriction(50.0f);
	dynamicsWorld->addRigidBody(groundRigidBody);
	ragdoll->addIgnoreEventObject(groundRigidBody);
	*/
	// Color Data	
	/*texRenderTarget = Ogre::TextureManager::getSingleton().createManual("texRenderTarget", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		Ogre::TEX_TYPE_2D, 320, 240, 0, Ogre::PF_B8G8R8A8, Ogre::TU_DEFAULT);

	Ogre::Rectangle2D *mMiniScreen = new Ogre::Rectangle2D(true);
	mMiniScreen->setCorners(0.5f, -0.5f, 1.0f, -1.0f);
	mMiniScreen->setBoundingBox(Ogre::AxisAlignedBox(-100000.0f * Ogre::Vector3::UNIT_SCALE, 100000.0f * Ogre::Vector3::UNIT_SCALE));

	Ogre::SceneNode* miniScreenNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("MiniScreenNode");
	miniScreenNode->attachObject(mMiniScreen);*/
	
}

//-------------------------------------------------------------------------------------
void OgreKinect::setUpKinect()
{	
	kinectController = new KinectController();
	kinectController->initController();
}

//-------------------------------------------------------------------------------------
bool OgreKinect::frameRenderingQueued(const Ogre::FrameEvent& arg)
{
	if(!BaseApplication::frameRenderingQueued(arg)) return false;
	
	kinectController->updatePerFrame(arg.timeSinceLastFrame);
	character->updatePerFrame(arg.timeSinceLastFrame);

	// Update Color Data
	this->kinectController->showColorData(this->texRenderTarget);

	/*
	if (dynamicsWorld)
	{
		accumulator += arg.timeSinceLastFrame;
		if(accumulator >= dt)
		{
			dynamicsWorld->stepSimulation(dt);
			accumulator -=dt;
			//get all colliding objects and check for specific collisions 
			dynamicsWorld->performDiscreteCollisionDetection();
			ogreDisplay->update();

			//std::string name = ragdoll->update();
			
			//if(name != "") name = name;
		}

	}
	*/
	return true;
}




