#ifndef __TEMPLATE_VIEW_H
#define __TEMPLATE_VIEW_H

#include "../Page.h"
#include "MeshCube.h"

namespace Page
{

class TemplateView
{
public:
    void Create(lv_obj_t* root);
    void Delete(void);
    void Update(void);
public:
    struct
    {
        lv_obj_t* labelTitle;
        lv_obj_t* labelTick;
    } ui;

    Cube3D* cube3D;
private:

};

}

#endif // !__VIEW_H
