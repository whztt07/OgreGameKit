//
//  OGKCamera.h
//  OgreGameKit
//
//  Created by Alex on 6/19/14.
//
//

#ifndef __OgreGameKit__OGKCamera__
#define __OgreGameKit__OGKCamera__

#include <Ogre.h>
#include "OGKStaticPluginLoader.h"

// input
#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#ifdef OGRE_IS_IOS
#include <OISMultiTouch.h>
class OGKCamera : public OIS::KeyListener, OIS::MultiTouchListener
#else
class OGKCamera : public OIS::KeyListener, OIS::MouseListener
#endif
{
public:
    OGKCamera(Ogre::SceneManager *sceneManager, Ogre::RenderWindow *renderWindow);
    ~OGKCamera();
    
    enum CameraMode {
        FREE,
        FIXED,
        FIRST_PERSON,
        THIRD_PERSON
    };
    
    Ogre::Camera *getCamera();
    
    OGKCamera::CameraMode getMode();
    void setMode(OGKCamera::CameraMode mode);
    
    Ogre::Real getMoveSpeed();
    void setMoveSpeed(Ogre::Real moveSpeed);
    
    // tightness (3rd person only)
    Ogre::Real getTightness();
    void setTightness(Ogre::Real tightness);
    
    void update(Ogre::Real elapsedTime);
    
	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);
    
#ifdef OGRE_IS_IOS
	bool touchMoved(const OIS::MultiTouchEvent &evt);
	bool touchPressed(const OIS::MultiTouchEvent &evt);
	bool touchReleased(const OIS::MultiTouchEvent &evt);
	bool touchCancelled(const OIS::MultiTouchEvent &evt);
#else
	bool mouseMoved(const OIS::MouseEvent &evt);
    bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
    bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
#endif
private:
    Ogre::Camera *mCamera;
    
    // mode
    CameraMode mMode;
    
    // nodes
    Ogre::SceneNode *mCameraNode;
    Ogre::SceneNode *mTargetNode;
    
    // tightness (3rd person only)
    Ogre::Real mMoveSpeed;
    Ogre::Real mTightness;
    
    Ogre::Viewport *mViewport;
    
    int mViewportOrientation;
};

#endif /* defined(__OgreGameKit__OGKCamera__) */