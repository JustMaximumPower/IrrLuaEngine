#include "GuiImage.h"
#include "LuaEngine.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiPlugin.h"

namespace Gui
{

    const char* GuiImage::lua_libName = "Image";

    const struct luaL_reg GuiImage::lua_lib_m[] =
    {
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiImage::lua_lib_p[] =
    {
    { "useAlpha", luaUseAlpha },
    { "scaled", luaScaled },
    { NULL, NULL } /* sentinel */
    };

    const struct luaL_reg GuiImage::lua_lib_f[] =
    {
    { "new", luaNew },
    { NULL, NULL } /* sentinel */
    };

    GuiImage::GuiImage(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua) :
            GuiElement(plugin, engine, plua)
    {
        const struct luaL_reg* i = lua_lib_p;

        while(i->func && i->name)
        {
            addProperty(i->name, i->func);
            i++;
        }
    }

    GuiImage::~GuiImage()
    {

    }

    int GuiImage::luaNew(lua_State* pLua)
    {
        GuiPlugin* plugin = GuiPlugin::getThisPointer(pLua);
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(pLua);
        GuiImage* pthis = new GuiImage(plugin, engine, pLua);

        int x = (int) lua_tonumber(pLua, 1);
        int y = (int) lua_tonumber(pLua, 2);
        int w = (int) lua_tonumber(pLua, 3);
        int h = (int) lua_tonumber(pLua, 4);

        size_t len;
        const char* text = luaL_optlstring(pLua, 5, "", &len);
        wchar_t* textw = new wchar_t[++len];
        mbstowcs(textw, text, len);

        irr::gui::IGUIImage* image =
            engine->getIrrlichtDevice()->getGUIEnvironment()->addImage(
                        irr::core::recti(x, y, x + w, y + h), NULL, pthis->getId(), textw);

        pthis->m_irrelement = image;

        delete textw;

        pthis->pushToStack(pLua);
        pthis->drop();

        return 1;
    }

    int GuiImage::luaUseAlpha(lua_State* pLua)
    {
        GuiImage* pthis = dynamic_cast<GuiImage*>(lua_toGuiElement(pLua));
        const char* key = luaL_checkstring(pLua, 2);

        if (!pthis)
        {
            luaL_error(pLua, "Type missmatch for arg #1");
        }
        
        pthis->validate(pLua);


        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, static_cast<irr::gui::IGUIImage*>(pthis->m_irrelement)->isAlphaChannelUsed());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            static_cast<irr::gui::IGUIImage*>(pthis->m_irrelement)->setUseAlphaChannel(b);
            return 0;
        }
    }

    int GuiImage::luaScaled(lua_State* pLua)
    {
        GuiImage* pthis = dynamic_cast<GuiImage*>(lua_toGuiElement(pLua));
        const char* key = luaL_checkstring(pLua, 2);

        if (!pthis)
        {
            luaL_error(pLua, "Type missmatch for arg #1");
        }
        
        pthis->validate(pLua);


        if (lua_gettop(pLua) == 2)
        {
            lua_pushboolean(pLua, static_cast<irr::gui::IGUIImage*>(pthis->m_irrelement)->isImageScaled());
            return 1;
        }
        else
        {
            bool b = lua_toboolean(pLua, 3) != 0;
            static_cast<irr::gui::IGUIImage*>(pthis->m_irrelement)->setScaleImage(b);
            return 0;
        }
    }

} /* End of namespace Gui */

