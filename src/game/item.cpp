/************************************************************************
 *
 * item.cpp
 * Item class implementation
 *
 ************************************************************************/

#include "item.h"
#include "itemaction.h"
#include "billboard.h"

#include <GL/gl.h>

#include <iostream>
#include <map>

/**
 * The item textures. Since there are only a few item types, only one copy
 * of each texture is stored.
 */
std::map<Item::ItemType, Texture*> textures;

/**
 * The item meshes are stored here for similar reasons to the textures.
 */
std::map<Item::ItemType, Mesh*> meshes;

/**
 * This loads the appropriate texture for an item, if one has not
 * been loaded already. The texture is returned and is guaranteed not to be
 * NULL.
 */
Texture *getItemTexture(Item::ItemType type)
{
    std::map<Item::ItemType, Texture*>::iterator i = textures.find(type);
    if (i != textures.end()) {
        return (*i).second;
    }

    std::string filename;  //choose filename
    switch(type)
    {
	case Item::HEALTH: filename = "images/overlay/gothealth.png";
	    break;
	case Item::ENERGY: filename = "images/overlay/gotenergy.png";
	    break;
	case Item::GRENADE: filename = "images/overlay/gotammo.png";
	    break;
	case Item::TRAP: filename = "images/overlay/gottrap.png";
	    break;
    };

    Texture *tex = Texture::load(filename);
    assert(tex);
    textures[type] = tex;
    return tex;
}

/**
 * This loads the cube mesh, which is what all items look like, and returns it.
 */
Mesh *getItemMesh(Item::ItemType type)
{
    //load cube
    Mesh *mesh = Mesh::makeCube(0.25);
    //make sure it loaded
    assert(mesh);
    //return it.
    return mesh;
}


/**
 * Default constructor.
 */
Item::Item(Level* l)
    : Entity(), level(l)
{
    setVisibility(false);
    spent = false;
}

/**
 * Destructor.
 */
Item::~Item()
{
    //nothing to destruct
}

/**
 * Renders the item and checks if it has been picked up by the hero.
 */
void Item::render(float dt)
{
    // change the colour depending on the item type
    switch(getType()) 
    {
	case HEALTH:  glColor3f(1, 0, 1); break;
	case ENERGY:  glColor3f(0, 0, 1); break;
	case GRENADE: glColor3f(0.31, 0.59, 0.20); break;
	case TRAP: glColor3f(0.5, 0.5, 0.5); break;
    }

    //call the superclass
    Entity::render(dt);

    if (!spent) {
        //if the hero or the haggis land on this cell, activate this item
        if (level->getHero()->getCell() == getCell()) { //the hero got it
            level->notifyGeneralAction(new ItemAction(this, level->getHero()));
            setVisibility(true);
            spent = true;
        } else if (level->getHaggis()->getCell() == getCell()) { //the haggis got it
            level->notifyGeneralAction(new ItemAction(this, level->getHaggis()));
            setVisibility(true);
            spent = true;
        }
    }
}

/**
 * Sets the item type.
 */
void Item::setType(ItemType it)
{
    itemType = it;
    setMesh(getItemMesh(it));
}

/**
 * Returns the item type.
 */
Item::ItemType Item::getType()
{
    return itemType;
}

/**
 * Turns the item into billboard so that it can float.
 */
BillBoard *Item::makeBillBoard()
{
    //create billboard object
    BillBoard *bb = new BillBoard(getItemTexture(itemType));
    vector4 p = getPosition();
    //lift it above the cell
    p.y += 3;
    //set its position
    bb->setPosition(p);
    //set its cell
    bb->setCell(getCell());
    //return it
    return bb;
}
