/************************************************************************
 *
 * billboard.h
 * BillBoard class
 *
 ************************************************************************/

#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "entity.h"
#include "texture.h"

class BillBoard : public Entity
{
public:
    /**
     * Constructor. The texture does not belong to the billboard and must
     * be kept valid while the billboard is used. The texture may be NULL.
     */
    BillBoard(Texture *tex);

    /**
     * Destructor.
     */
    virtual ~BillBoard();

    /**
     * Render the billboard.
     */
    virtual void render(float dt);

private:
    /**
     * The billboard texture. It may be NULL.
     */
    Texture *tex;

    /**
     * The billboard height.
     */
    float h;
};

#endif //BILLBOARD_H
