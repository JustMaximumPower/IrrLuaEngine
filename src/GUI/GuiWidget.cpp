#include "GuiWidget.h"
#include "LuaEngine.h"
#include "GuiPlugin.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiButton.h"
#include "IGUIElement.h"

namespace Gui
{

    const char* GuiWidget::lua_libName = "Widget";

    const struct luaL_reg GuiWidget::lua_lib_m[] =
    {
    { "addElement", luaAddElement },
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiWidget::lua_lib_f[] =
    {
    { "new", luaNew },
    { NULL, NULL } /* sentinel */
    };

    GuiWidget::GuiWidget(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua) :
            GuiElement(plugin, engine, plua)
    {

        const struct luaL_reg* i = lua_lib_m;

        while(i->func && i->name)
        {
            addMethod(i->name, i->func);
            i++;
        }
    }

    GuiWidget::~GuiWidget()
    {

    }

    int GuiWidget::luaNew(lua_State* pLua)
    {
        GuiPlugin* plugin = GuiPlugin::getThisPointer(pLua);
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(pLua);
        GuiWidget* pthis = new GuiWidget(plugin, engine, pLua);

        pthis->pushToStack(pLua);

        pthis->drop();

        lua_pushcfunction(pLua, luaRemove);

        lua_setfield(pLua, -2, "onWindowClose");

        int x = (int) lua_tonumber(pLua, 1);
        int y = (int) lua_tonumber(pLua, 2);
        int w = (int) lua_tonumber(pLua, 3);
        int h = (int) lua_tonumber(pLua, 4);

        size_t len;
        const char* text = luaL_optlstring(pLua, 5, "", &len);
        wchar_t* textw = new wchar_t[++len];
        mbstowcs(textw, text, len);

        irr::gui::IGUIWindow* win =
                engine->getIrrlichtDevice()->getGUIEnvironment()->addWindow(
                        irr::core::recti(x, y, x + w, y + h), false, textw, NULL,
                        pthis->getId());

        pthis->m_irrelement = win;

        //win->getCloseButton()->remove();

        delete textw;

        return 1;
    }

    int GuiWidget::luaAddElement(lua_State* pLua)
    {
        GuiWidget* pthis = dynamic_cast<GuiWidget*>(lua_toGuiElement(pLua));

        if (!pthis)
        {
            luaL_error(pLua, "Type missmatch for arg #1");
        }

        GuiElement* pother = lua_toGuiElement(pLua, 2);

        pthis->m_children.push_back(pother);
        pother->grab();

        irr::gui::IGUIElement* irrE = pother->getIrrlichtElement();

        if (irrE)
        {
            pthis->m_irrelement->addChild(irrE);
        }

        return 0;
    }

} /* End of namespace Gui */

