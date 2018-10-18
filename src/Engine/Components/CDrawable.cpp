// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#include "CDrawable.hpp"
CDrawable::CDrawable(us_int id, us_int entityId, const std::string &name, const std::string &ImagePath, sf::Color c,
                     us_int index) : IComponent(id, entityId, name)
{
    this->color = c;
    this->index = index;
    this->ImagePath = ImagePath;
    showBounds = false;
    bodyInit(sf::PrimitiveType::Quads, 4);
}

void CDrawable::bodyBuild()
{
    body[0].position = {0, 0};
    body[1].position = {TDS, 0};
    body[2].position = {TDS, TDS};
    body[3].position = {0, TDS};
    setColor(color);
}

void CDrawable::setColor(const sf::Color &color)
{
    this->color = color;
    body[0].color = color;
    body[1].color = color;
    body[2].color = color;
    body[3].color = color;
}

void CDrawable::setPosition(const sf::Vector2f &p)
{
    body[0].position = {p.x, p.y};
    body[1].position = {p.x + TDS, p.y};
    body[2].position = {p.x + TDS, p.y + TDS};
    body[3].position = {p.x, p.y + TDS};
}

void CDrawable::bodyInit(sf::PrimitiveType type, us_int vertexCount)
{
    body.setPrimitiveType(type);
    body.resize(vertexCount);
    bounds = ThicknessLineArray();
    bodyBuild();
}
const sf::Color &CDrawable::getColor() const
{
    return color;
}
us_int CDrawable::getIndex() const
{
    return index;
}
const std::string &CDrawable::getImagePath() const
{
    return ImagePath;
}
void CDrawable::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(body, states);
    target.draw(bounds, states);
}
const sf::Texture &CDrawable::getTexture() const
{
    return texture;
}
void CDrawable::drawBounds()
{
    bounds.Clear();
    bounds.append({body[0].position, body[1].position});
    bounds.append({body[1].position, body[2].position});
    bounds.append({body[2].position, body[3].position});
    bounds.append({body[3].position, body[0].position});
}
bool CDrawable::isShowBounds() const
{
    return showBounds;
}
void CDrawable::setShowBounds(bool showBounds)
{
    CDrawable::showBounds = showBounds;
}
void CDrawable::hideBounds()
{
    bounds.Clear();
    showBounds = false;
}
void CDrawable::setIndex(us_int index)
{
    this->index = index;
}