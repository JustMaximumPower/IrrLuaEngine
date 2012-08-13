#include "GuiElement.h"
#include "LuaEngine.h"
#include "GuiPlugin.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiButton.h"
#include "IGUIElement.h"

namespace Gui
{
    const struct luaL_reg GuiElement::lua_lib_m[] =
    {
    { "remove", luaRemove },
    { "getType", luaGetType},
    { "getId", luaId},
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiElement::lua_lib_p[] =
    {
    { "toolTip", luaToolTip },
    { "text", luaText },
    { "enabled", luaEnabled },
    { "visible", luaVisible },
    { "tabOrder", luaTabOrder },
    { "x", luaX },
    { "y", luaY },
    { "height", luaHeight },
    { "width", luaWidth },
    { NULL, NULL } /* sentinel */
    };

    GuiElement::GuiElement(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua) :
            Script::LuaObject(engine)
    {
        m_plugin = plugin;
        m_parent = NULL;

        m_id = m_plugin->getFreeId(this);

        const struct luaL_reg* i = lua_lib_m;

        while(i->func && i->name)
        {
            addMethod(i->name, i->func);
            i++;
        }

        i = lua_lib_p;
        while(i->func && i->name)
        {
            addProperty(i->name, i->func);
            i++;
        }

    }

    GuiElement::~GuiElement()
    {
        printf("GuiElement::~GuiElement\n");

        if (m_irrelement)
        {
            m_irrelement->remove();
            m_irrelement = NULL;
        }
        m_plugin->freeElement(m_id);
    }


    const int GuiElement::getId() const
    {
        return m_id;
    }

    irr::gui::IGUIElement* GuiElement::getIrrlichtElement() const
    {
        return m_irrelement;
    }

    GuiElement* GuiElement::lua_toGuiElement(lua_State* pLua, int index)
    {
        GuiElement* pthis = dynamic_cast<GuiElement*>(Script::LuaObject::lua_toLuaObject(
                pLua, index));

        if (!pthis)
        {
            luaL_error(pLua, "Type missmatch for arg #%i", index);
        }
        return pthis;
    }

    int GuiElement::luaRemove(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);

        pthis->validate(pLua);

        if (pthis->m_irrelement)
        {
            pthis->m_irrelement->remove();
            pthis->m_irrelement = NULL;
        }
        return 0;
    }

    int GuiElement::luaToolTip(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            const irr::core::stringw& wtip = pthis->m_irrelement->getToolTipText();
            char* tip = new char[wtip.size() + 1];
            wcstombs(tip, wtip.c_str(), wtip.size() + 1);
            lua_pushstring(pLua, tip);
            delete tip;
            return 1;
        }
        else
        {
            const char* text = luaL_checkstring(pLua, 3);
            irr::core::stringw wtext(text);
            pthis->m_irrelement->setToolTipText(wtext.c_str());

            return 0;
        }
    }

    int GuiElement::luaText(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            const irr::core::stringw& wtip = pthis->m_irrelement->getText();
            char* tip = new char[wtip.size() + 1];
            wcstombs(tip, wtip.c_str(), wtip.size() + 1);
            lua_pushstring(pLua, tip);
            delete tip;
            return 1;
        }
        else
        {
            const char* text = luaL_checkstring(pLua, 3);
            irr::core::stringw wtext(text);
            pthis->m_irrelement->setText(wtext.c_str());

            return 0;
        }
    }

    int GuiElement::luaEnabled(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, pthis->m_irrelement->isEnabled());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            pthis->m_irrelement->setEnabled(b);

            return 0;
        }
    }

    int GuiElement::luaVisible(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);
        
        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, pthis->m_irrelement->isVisible());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            pthis->m_irrelement->setVisible(b);

            return 0;
        }
    }

    int GuiElement::luaId(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);

        pthis->validate(pLua);

        lua_pushnumber(pLua, pthis->m_id);
        return 1;
    }

    int GuiElement::luaGetType(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);

        pthis->validate(pLua);

        lua_pushstring(pLua, pthis->m_irrelement->getTypeName());
        return 1;
    }

    int GuiElement::luaTabOrder(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushnumber(pLua, pthis->m_irrelement->getTabOrder());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            pthis->m_irrelement->setVisible(b);

            return 0;
        }
    }

    int GuiElement::luaX(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushnumber(pLua, pthis->m_irrelement->getRelativePosition().UpperLeftCorner.X);
            return 1;
        }
        else
        {
            int x = luaL_checknumber(pLua,3);
            irr::core::recti pos = pthis->m_irrelement->getRelativePosition();
            pos.UpperLeftCorner.X = x;
            pthis->m_irrelement->setRelativePosition(pos);
            return 0;
        }
    }

    int GuiElement::luaY(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushnumber(pLua, pthis->m_irrelement->getRelativePosition().UpperLeftCorner.Y);
            return 1;
        }
        else
        {
            int y = luaL_checknumber(pLua,3);
            irr::core::recti pos = pthis->m_irrelement->getRelativePosition();
            pos.UpperLeftCorner.Y = y;
            pthis->m_irrelement->setRelativePosition(pos);
            return 0;
        }
    }

    int GuiElement::luaHeight(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushnumber(pLua, pthis->m_irrelement->getRelativePosition().getHeight());
            return 1;
        }
        else
        {
            int h = luaL_checknumber(pLua,3);
            if(h < 0)
            {
                luaL_error(pLua,"Height must be a positive value");
            }
            irr::core::recti pos = pthis->m_irrelement->getRelativePosition();
            pos.LowerRightCorner.Y = pos.UpperLeftCorner.Y + h;
            pthis->m_irrelement->setRelativePosition(pos);
            return 0;
        }
    }

    int GuiElement::luaWidth(lua_State* pLua)
    {
        GuiElement* pthis = lua_toGuiElement(pLua);
        const char* key = luaL_checkstring(pLua, 2);

        pthis->validate(pLua);

        if (lua_gettop(pLua) == 2)
        {
            lua_pushnumber(pLua, pthis->m_irrelement->getRelativePosition().getWidth());
            return 1;
        }
        else
        {
            int w = luaL_checknumber(pLua,3);
            if(w < 0)
            {
                luaL_error(pLua,"Width must be a positive value");
            }
            irr::core::recti pos = pthis->m_irrelement->getRelativePosition();
            pos.LowerRightCorner.X = pos.UpperLeftCorner.X + w;
            pthis->m_irrelement->setRelativePosition(pos);
            return 0;
        }
    }

    void GuiElement::validate(lua_State* pLua)
    {
        if(!m_irrelement)
        {
            luaL_error(pLua,"Element has been removed");
        }
    }

} /* End of namespace Gui */
