/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** Main.cpp
*/

#include <OgreApplicationContext.h>
#include <OgreInput.h>
#include <OgreRoot.h>
#include <OgreEntity.h>
#include <OgreTexture.h>
#include <OgreRenderWindow.h>
#include <OgreColourValue.h>
#include <OgreSceneManager.h>
#include "../include/ogre.hpp"

void graphical::createWindow(OgreBites::ApplicationContext ctx)
{
    Ogre::Root *root = ctx.getRoot();
    scnMgr = root->createSceneManager();
    Ogre::RTShader::ShaderGenerator *shadergen = Ogre::RTShader::ShaderGenerator::getSingletonPtr();
    shadergen->addSceneManager(scnMgr);
}

void graphical::createCamera()
{
    cam = scnMgr->createCamera("myCam");
    cam->setNearClipDistance(5); // specific to this sample
    cam->setAutoAspectRatio(true);
    camNode->attachObject(cam);
}

void graphical::createLight()
{
    Ogre::Light *light = scnMgr->createLight("MainLight");
    Ogre::SceneNode *lightNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    lightNode->setPosition(0, 10, 15);
    lightNode->attachObject(light);
}

void graphical::setPositionLight(float x, float y, float z)
{
    camNode = scnMgr->getRootSceneNode()->createChildSceneNode();
    camNode->setPosition(x, y, z);
    camNode->lookAt(Ogre::Vector3(0, 0, -1), Ogre::Node::TS_PARENT);
}

Ogre::Entity *graphical::createEntity(std::string mesh)
{
    Ogre::Entity *ent = scnMgr->createEntity(mesh);
    Ogre::SceneNode *node = scnMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(ent);
    return ent;
}

int main()
{
    OgreBites::ApplicationContext ctx("Zappy GUI");
    graphical g;
    ctx.initApp();
    g.createWindow(ctx);
    g.createLight();
    g.setPositionLight(10, 0, 15);
    g.createCamera();
    ctx.getRenderWindow()->addViewport(g.getCam());
    Ogre::SceneManager* scnMgr = g.getScnMgr();

    Ogre::Entity *ent_one = g.createEntity("Sinbad.mesh");

    KeyHandler keyHandler;
    ctx.addInputListener(&keyHandler);
 
    scnMgr->setAmbientLight(Ogre::ColourValue(0.5, 0.5, 0.5));
    ctx.getRoot()->startRendering();
    ctx.closeApp();
}
