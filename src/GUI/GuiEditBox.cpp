#include "GuiEditBox.h"
#include "LuaEngine.h"
#include "GuiPlugin.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "IGUIElement.h"
#include "IGUIEditBox.h"

namespace Gui
{

    const char* GuiEditBox::lua_libName = "EditBox";

    const struct luaL_reg GuiEditBox::lua_lib_m[] =
    {
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiEditBox::lua_lib_f[] =
    {
    { "new", luaNew },
    { NULL, NULL } /* sentinel */
    };

    GuiEditBox::GuiEditBox(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua) :
            GuiElement(plugin, engine, plua)
    {

        const struct luaL_reg* i = lua_lib_m;

        while(i->func && i->name)
        {
            addMethod(i->name, i->func);
            i++;
        }
    }

    GuiEditBox::~GuiEditBox()
    {

    }

    int GuiEditBox::luaNew(lua_State* pLua)
    {
        GuiPlugin* plugin = GuiPlugin::getThisPointer(pLua);
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(pLua);
        GuiEditBox* pthis = new GuiEditBox(plugin, engine, pLua);

        pthis->pushToStack(pLua);

        pthis->drop();

        int x = (int) lua_tonumber(pLua, 2);
        int y = (int) lua_tonumber(pLua, 3);
        int w = (int) lua_tonumber(pLua, 4);
        int h = (int) lua_tonumber(pLua, 5);

        size_t len;
        const char* text = luaL_optlstring(pLua, 1, "", &len);
        wchar_t* textw = new wchar_t[++len];
        mbstowcs(textw, text, len);

        irr::gui::IGUIEditBox* win =
                engine->getIrrlichtDevice()->getGUIEnvironment()->addEditBox(textw,
                        irr::core::recti(x, y, x + w, y + h), true, NULL,
                        pthis->getId());

        pthis->m_irrelement = win;

        delete textw;

        return 1;
    }

} /* End of namespace Gui */

