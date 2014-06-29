//
//  OGKInGameScene.cpp
//  OgreGameKit
//
//  Created by Alex on 6/24/14.
//
//

#include "OGKInGameScene.h"

#include "OGKGame.h"

// DEFAULT THEME
class Gui3DHUDTheme : public Gui3D::PanelColors
{
public:
    inline Gui3DHUDTheme():Gui3D::PanelColors()
    {
        transparent = Gorilla::rgb(0,0,0,0);
        
        // Panel
        panelBackgroundSpriteName = "panelBackground";
        panelCursorSpriteName = "mousepointer";
        panelCursorSpriteSizeX = 12;
        panelCursorSpriteSizeY = 18;
        
        // Button
        //        buttonInactiveSpriteName = "buttonInactive";
        //        buttonOveredSpriteName = "buttonOvered";
        //        buttonNotOveredSpriteName = "buttonNotOvered";
        //        buttonClickedSpriteName = "buttonClicked";
        
        buttonBackgroundClickedGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundClickedGradientStart = Gorilla::rgb(255, 255, 255, 200);
        buttonBackgroundClickedGradientEnd = Gorilla::rgb(255, 255, 255, 170);
        
        buttonBackgroundOveredGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundOveredGradientStart = Gorilla::rgb(255, 255, 255, 128);
        buttonBackgroundOveredGradientEnd = Gorilla::rgb(255, 255, 255, 100);
        
        buttonBackgroundNotOveredGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundNotOveredGradientStart = Gorilla::rgb(255, 255, 255, 80);
        buttonBackgroundNotOveredGradientEnd = Gorilla::rgb(255, 255, 255, 50);
        
        buttonBackgroundInactiveGradientType = Gorilla::Gradient_NorthSouth;
        buttonBackgroundInactiveGradientStart = Gorilla::rgb(255, 255, 255, 15);
        buttonBackgroundInactiveGradientEnd = Gorilla::rgb(255, 255, 255, 5);
        
        buttonText = Gorilla::rgb(255, 255, 255, 255);
        buttonTextInactive = Gorilla::rgb(255, 255, 255, 70);
        buttonTextSize = 14;
        
        // @TODO add other button styles
        
        // Caption
        captionBackgroundGradientType = Gorilla::Gradient_NorthSouth;
        captionBackgroundGradientStart = transparent;
        captionBackgroundGradientEnd = transparent;
        
        captionBorder = transparent;
        captionText = Ogre::ColourValue::White;
        captionTextSize = 14;
        captionBorderSize = 0;
    }
};

static Gui3DHUDTheme gui3DHUDTheme;

OGKInGameScene::OGKInGameScene(const Ogre::String& name):OGKScene(name),
mGUI(NULL),
mPanel(NULL)
{
    init();
}

OGKInGameScene::~OGKInGameScene()
{
    
}

bool OGKInGameScene::buttonPressed(Gui3D::PanelElement *e)
{
    OGKGame::getSingletonPtr()->mLog->logMessage("Switching to menu scene");
    
    OGKGame::getSingletonPtr()->mGameSceneManager->setActiveScene("menu", 3 * 1000);
    
    return true;
}

void OGKInGameScene::init()
{
    OGKScene::init();
    
    mGUI = OGRE_NEW Gui3D::Gui3D(&gui3DHUDTheme);
}

void OGKInGameScene::onEnter()
{
    OGKScene::onEnter();
    
	OGKGame::getSingletonPtr()->mSceneManager->setSkyBox(true, "OGK/DefaultSkyBox");
    
    Ogre::Viewport *vp = mCamera->getCamera()->getViewport();
	vp->setBackgroundColour(Ogre::ColourValue(0.2f, 0.0f, 0.0f, 1.0f));
    
    mScreen = mGUI->createScreenRenderable2D(vp, "default_theme","ingame");
    mSceneNode->attachObject(mScreen);

    mPanel = OGRE_NEW Gui3D::ScreenRenderable2DPanel(mGUI,
                                                     mScreen,
                                                     Ogre::Vector2(vp->getActualWidth()/2 - 150,vp->getActualHeight()/2 - 100),
                                                     Ogre::Vector2(300,200),
                                                     "default_theme",
                                                     "testPanel");
    mPanel->hideInternalMousePointer();
    
    mButton = mPanel->makeButton(50, 10, 200, 30, "MENU");
    mButton->setPressedCallback(this, &OGKInGameScene::buttonPressed);
    
    // Mouse Cursor
//    mMouseLayer = mScreen->createLayer(4);
//    mMouseCursor = mMouseLayer->createRectangle(vp->getActualWidth()/2,
//                                                vp->getActualHeight()/2,
//                                                15,22);
//    mMouseCursor->background_image("mousepointer");
    
    OGKInputManager::getSingletonPtr()->addMouseListener(this, "ingameScene");
}

void OGKInGameScene::onEnterTransitionDidFinish()
{
    OGKScene::onEnter();
    
    mPanel->showInternalMousePointer();
}

void OGKInGameScene::onExit()
{
    OGKScene::onExit();
    
    if(mGUI) mGUI->destroyScreenRenderable2D("ingame");
    mScreen = NULL;    
}

void OGKInGameScene::onExitTransitionDidStart()
{
    OGKScene::onExitTransitionDidStart();
    
    if(mPanel) mPanel->hideInternalMousePointer();
    
    OGKInputManager::getSingletonPtr()->removeMouseListener("ingameScene");
}

void OGKInGameScene::update(Ogre::Real elapsedTime)
{
    OGKScene::update(elapsedTime);
}

#ifdef OGRE_IS_IOS
bool OGKInGameScene::touchMoved(const OIS::MultiTouchEvent &evt) { return true; }
bool OGKInGameScene::touchPressed(const OIS::MultiTouchEvent &evt)  { return true; }
bool OGKInGameScene::touchReleased(const OIS::MultiTouchEvent &evt)  { return true; }
bool OGKInGameScene::touchCancelled(const OIS::MultiTouchEvent &evt)  { return true; }
#else
bool OGKInGameScene::mouseMoved(const OIS::MouseEvent &evt)
{
//    if(mMouseCursor) mMouseCursor->position(evt.state.X.abs, evt.state.Y.abs);
    if(mPanel)mPanel->injectMouseMoved(evt.state.X.abs, evt.state.Y.abs);
    return false;
}

bool OGKInGameScene::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(mPanel)mPanel->injectMousePressed(evt, id);
    return false;
}
bool OGKInGameScene::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
{
    if(mPanel)mPanel->injectMouseReleased(evt, id);
    return false;
}
#endif