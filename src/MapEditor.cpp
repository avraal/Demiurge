//
// Created by andrew on 03.04.18.
//

#include "MapEditor.h"

bool MapEditor::initWindow()
{
    window.create(sf::VideoMode(1280, 720), "Hello, SFML"/*, sf::Style::Titlebar | sf::Style::Close*/);
    findAllFiles(PathToImages, ImagesFormats);
    drawTileMap();
    tgui::Gui gui{window};
    tgui::Theme theme{"tgui_themes/Black.txt"};

    scrollPanel = tgui::ScrollablePanel::create({"20%", "80%"});
    auto grid = tgui::Grid::create();
    scrollPanel->setPosition(10, 10);
    grid->setPosition(20, 20);
    scrollPanel->getRenderer()->setBackgroundColor(sf::Color(0, 0, 0, 128));

    uint x = 0, y = 0;
    for (auto i : PathToImages)
    {
        auto pic = tgui::Picture::create(i);
        pic->connect(pic->onClick.getName(), &MapEditor::AddObject, this, i);
        if (y == 2)
        {
            x++;
            y = 0;
        }
        y++;
        grid->addWidget(pic, x, y, {10, 10, 10, 10});
    }

    scrollPanel->setHorizontalScrollbarPolicy(tgui::ScrollablePanel::ScrollbarPolicy::Never);
    scrollPanel->add(grid);

    gui.add(scrollPanel);

    window.setVerticalSyncEnabled(true);

    while (window.isOpen())
    {
        sf::Event event;
        window.clear(sf::Color(42, 76, 61));

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            MouseCallbacks(event);

            gui.handleEvent(event);
        }
        for (auto t : TileMap)
        {
            window.draw(*t);
        }
        for (auto o : ObjList)
        {
            window.draw(*o);
        }
        gui.draw();
        window.display();
    }
    return true;
}

void MapEditor::findAllFiles(std::vector<std::string> &Container, std::vector<std::string> FileFormats)
{
    DIR *dir;
    dirent *directory;
    if ((dir = opendir(MapEditor::CurrentDirectory.c_str())) != NULL)
    {
        while ((directory = readdir(dir)) != NULL)
        {
            char *last = strrchr(directory->d_name, '.');
            if (last != NULL)
            {
                for (auto f : FileFormats)
                {
                    if (strcmp(last, f.c_str()) == 0)
                    {
                        std::cout << MapEditor::CurrentDirectory << directory->d_name << " added to stack" << std::endl;
                        Container.push_back(MapEditor::CurrentDirectory + directory->d_name);
                    }
                }
            }
        }
        closedir(dir);
    } else
    {
        std::cerr << "Cant open a dir" << std::endl;
    }
}
void MapEditor::AddObject(std::string imagePath)
{
    CurrentPathFile = imagePath;
}
void MapEditor::drawTileMap()
{
    int height = 10;
    int width = 10;
    std::vector<std::string> Tiles;
    std::vector<std::string> Formats;
    Formats.push_back(".png");
    findAllFiles(Tiles, Formats);
    //added tiles
    for (uint i = 0; i < height * width - 1; i++)
    {
        TileMap.push_back(std::move(std::shared_ptr<MapEntity>(
                new MapEntity("", 0, 0))));
    }
    //set position
    uint x = 0, y = 0;
    for (auto t : TileMap)
    {
        t->setPosition(x * 65, y * 65);

        if (x++ == width)
        {
            y++;
            x = 0;
        }
    }
}
void MapEditor::MouseCallbacks(sf::Event event)
{
    if (event.type == sf::Event::MouseButtonPressed)
    {
        if (event.mouseButton.button == sf::Mouse::Right)
        {
            window.create(sf::VideoMode(720, 480), "");
        }

        if (event.mouseButton.button == sf::Mouse::Left &&
            !scrollPanel->mouseOnWidget(tgui::Vector2f(event.mouseButton.x, event.mouseButton.y)))
        {
            for (auto t : TileMap)
            {
                if (!CurrentPathFile.empty())
                {

                    if (event.mouseButton.x > t->getPosition().x && event.mouseButton.y > t->getPosition().y
                        && event.mouseButton.x < t->getPosition().x + t->getSize().x
                        && event.mouseButton.y < t->getPosition().y + t->getSize().y)
                    {
                        for (auto o : ObjList)
                        {
                            if (o != nullptr)
                            {
                                if (t->getPosition() == o->getPosition())
                                {
                                    auto it = std::find(ObjList.begin(), ObjList.end(), o);
                                    if (it != ObjList.end())
                                    {
                                        ObjList.erase(it);
                                    }
                                }
                            }
                        }
                        ObjList.push_back(std::move(std::shared_ptr<MapEntity>(
                                new MapEntity(CurrentPathFile, t->getPosition().x, t->getPosition().y))));
                    }
                } else
                {
                    std::cout << "[WARNING | MapEditor]: Current Path File is empty" << std::endl;
                }
            }
        }
    }
}
