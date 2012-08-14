#include "GuiButton.h"
#include "LuaEngine.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiPlugin.h"

namespace Gui
{

    const char* GuiButton::lua_libName = "Button";

    const struct luaL_reg GuiButton::lua_lib_m[] =
    {
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiButton::lua_lib_p[] =
    {
    { "useAlpha", luaUseAlpha },
    { "scaled", luaScaled },
    { "drawBorder", luaDrawBorder },
    { "isPushButton", luaDrawBorder },
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiButton::lua_lib_f[] =
    {
    { "new", luaNew },
    { NULL, NULL } /* sentinel */
    };

    GuiButton::GuiButton(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua) :
            GuiElement(plugin, engine, plua)
    {
        addMethods(lua_lib_m);
        addProperties(lua_lib_p);
    }

    GuiButton::~GuiButton()
    {

    }

    int GuiButton::luaNew(lua_State* pLua)
    {
        GuiPlugin* plugin = GuiPlugin::getThisPointer(pLua);
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(pLua);
        GuiButton* pthis = new GuiButton(plugin, engine, pLua);

        int x = (int) lua_tonumber(pLua, 1);
        int y = (int) lua_tonumber(pLua, 2);
        int w = (int) lua_tonumber(pLua, 3);
        int h = (int) lua_tonumber(pLua, 4);

        size_t len;
        const char* text = luaL_optlstring(pLua, 5, "", &len);
        wchar_t* textw = new wchar_t[++len];
        mbstowcs(textw, text, len);
        const char* tooltip = luaL_optlstring(pLua, 6, "", &len);
        wchar_t* tooltipw = new wchar_t[++len];
        mbstowcs(tooltipw, tooltip, len);

        irr::gui::IGUIButton* b =
                engine->getIrrlichtDevice()->getGUIEnvironment()->addButton(
                        irr::core::recti(x, y, x + w, y + h), NULL, pthis->getId(), textw,
                        tooltipw);

        pthis->m_irrelement = b;

        delete textw;
        delete tooltipw;

        pthis->pushToStack(pLua);
        pthis->drop();

        return 1;
    }

    int GuiButton::luaUseAlpha(lua_State* pLua)
    {
        GuiButton* pthis = lua_toGuiButton(pLua,1);
        const char* key = luaL_checkstring(pLua, 2);
        
        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, static_cast<irr::gui::IGUIButton*>(pthis->m_irrelement)->isAlphaChannelUsed());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            static_cast<irr::gui::IGUIButton*>(pthis->m_irrelement)->setUseAlphaChannel(b);
            return 0;
        }
    }

    int GuiButton::luaScaled(lua_State* pLua)
    {
        GuiButton* pthis = lua_toGuiButton(pLua,1);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, static_cast<irr::gui::IGUIButton*>(pthis->m_irrelement)->isScalingImage());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            static_cast<irr::gui::IGUIButton*>(pthis->m_irrelement)->setScaleImage(b);
            return 0;
        }
    }

    int GuiButton::luaDrawBorder(lua_State* pLua)
    {
        GuiButton* pthis = lua_toGuiButton(pLua,1);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, static_cast<irr::gui::IGUIButton*>(pthis->m_irrelement)->isDrawingBorder());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            static_cast<irr::gui::IGUIButton*>(pthis->m_irrelement)->setDrawBorder(b);
            return 0;
        }
    }

    GuiButton* GuiButton::lua_toGuiButton(lua_State* pLua,int index)
    {
        GuiButton* pthis = dynamic_cast<GuiButton*>(lua_toGuiElement(pLua,index));
        if (!pthis)
        {
            luaL_error(pLua, "Type missmatch for arg #1");
        }
        return pthis;
    }

} /* End of namespace Gui */

