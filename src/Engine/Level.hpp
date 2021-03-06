
// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 10.07.18.
//

#ifndef DEMIURGE_LEVEL_HPP
#define DEMIURGE_LEVEL_HPP

#include <string>
#include <string.h>
#include <vector>
#include <memory>
#include <algorithm>
#include <dirent.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <TGUI/Widgets/Label.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <TGUI/Widgets/ScrollablePanel.hpp>
#include <forward_list>
#include <mutex>
#include "Systems/UIWrapper.hpp"
#include "Components/CDrawable.hpp"

class IEntity;
class EObject;
class ComponentManager;
class EntityManager;
class Level
{
protected:
    std::mutex guard;

    us_int Id;
    std::string Name;
    std::vector<us_int> ObjectIds;
    std::vector<std::shared_ptr<CDrawable>> DrawableComponents;
    std::vector<tgui::Widget::Ptr> guiContainer;
    std::vector<std::string> ImagesFormats;
    std::vector<std::string> PathToImages;
    sf::Clock clock;
    sf::View *MainCamera;
    virtual void loadGui(sf::RenderWindow &window);
    virtual void initGui(sf::RenderWindow &window);
    bool findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats);
    std::unique_ptr<UIWrapper> UserInterface;

    static us_int currentId;
    static us_int getNextId();
public:
    Level() = delete;
    Level(const std::string &Name);
    Level(const Level&)             = delete;
    Level(Level&&)                  = delete;
    Level&operator=(const Level&)   = delete;
    Level&operator=(Level&&)        = delete;
    ~Level();
    virtual void draw(sf::RenderWindow &window);

    virtual bool prepareLevel(sf::RenderWindow &window);
    virtual void MouseCallbacks(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void KeyBoardCallbacks(sf::RenderWindow &window, sf::Event &event) = 0;
    virtual void HandleGUIEvent(sf::Event &event);
    virtual std::string getName() const;

    bool DestroyEntity(us_int entityId);

    void addObject(us_int entityId);
    void sortedObjectsByIndex();
    void setCamera(sf::View &camera);
    us_int getObjCount();
    std::vector<us_int> &getAllObjectsIds();
    sf::Color backgroundColor;
    std::string ImageDirectory;
    float fps;
};

#endif //DEMIURGE_LEVEL_HPP