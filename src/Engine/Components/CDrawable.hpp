// This is an independent project of an individual developer. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

//
// Created by Andrew Volski on 08.10.18.
//

#ifndef DEMIURGE_CDRAWABLE_HPP
#define DEMIURGE_CDRAWABLE_HPP

#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "IComponent.hpp"
#include "../ThicknessLineArray.hpp"
#include "../CONST_DEFINITIONS.hpp"
#include "CTransform.hpp"

#define TDS TILE_SIZE_DEFAULT

class CDrawable : public IComponent, public sf::Drawable, public CRegisterable<CDrawable>
{
public:
    using CRegisterable<CDrawable>::Create;
    CDrawable(us_int id, us_int entityId, const std::string &name, const std::string &ImagePath = "",
              sf::Color c = sf::Color(91, 97, 91), us_int index = 0);

    virtual ~CDrawable() {};

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual void bodyBuild() = 0;

    virtual void drawBounds();
    virtual void bodyInit(const sf::PrimitiveType &type, us_int vertexCount);
    void hideBounds();

    us_int index;
    bool showBounds;
    bool attachedPosition;

    std::string ImagePath;
    sf::VertexArray body;

    const sf::VertexArray &getBody() const;

protected:
    sf::Texture texture;
    sf::Color color;
    ThicknessLineArray bounds;
    bool canDraw;
    virtual void setPosition(const sf::Vector2f &p) = 0;

public:
    const sf::Color &getColor() const;
    us_int getIndex() const;
    const std::string &getImagePath() const;
    const sf::Texture &getTexture() const;
    virtual void setGlobalPosition(const sf::Vector2f &p);
    virtual void setLocalePosition(const sf::Vector2f &p);
    virtual void rotate(float angle);
    void setShowBounds(bool showBounds);
    void setIndex(us_int index);
    virtual void setColor(const sf::Color &color);
    void setCanDraw(bool isDraw);
    void setIsAttachedPosition(bool isAttachedPosition);
    bool isCanDraw() const;
    bool isShowBounds() const;
    bool isAttachedPosition() const;
};

#endif //DEMIURGE_CDRAWABLE_HPP