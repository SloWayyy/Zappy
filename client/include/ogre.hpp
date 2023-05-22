/*
** EPITECH PROJECT, 2023
** Zappy
** File description:
** ogre
*/

#ifndef OGRE_HPP_
    #define OGRE_HPP_

    #include <string>

class KeyHandler : public OgreBites::InputListener
{
    bool keyPressed(const OgreBites::KeyboardEvent& evt) override
    {
        if (evt.keysym.sym == OgreBites::SDLK_ESCAPE) {
            Ogre::Root::getSingleton().queueEndRendering();
        }
        return true;
    }
};

class graphical : public OgreBites::ApplicationContext
{
    public:
        graphical();
        ~graphical() {};
        void createWindow(OgreBites::ApplicationContext ctx);
        void createLight();
        void createCamera();
        void createViewport(OgreBites::ApplicationContext ctx);
        void setRatioCamera(Ogre::Viewport* vp);
        Ogre::Entity *createEntity(std::string mesh);
        void setPositionLight(float x, float y, float z);
        void meshManager(std::string mesh, std::string name);
        OgreBites::ApplicationContext getCtx() { return ctx; };
        Ogre::Camera *getCam() { return cam; };
        Ogre::SceneManager *getScnMgr() { return scnMgr; };
        Ogre::SceneNode *getCamNode() { return camNode; };
        Ogre::Viewport* getVp() { return vp; };
    protected:
        OgreBites::ApplicationContext ctx;
        Ogre::Camera *cam;
        Ogre::SceneManager *scnMgr;
        Ogre::SceneNode *camNode;
        Ogre::Viewport* vp;
        Ogre::Plane plane;
    private:
};

#endif /* !OGRE_HPP_ */
