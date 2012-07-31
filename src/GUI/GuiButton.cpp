#include "GuiButton.h"
#include "LuaEngine.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiPlugin.h"


namespace Gui 
{

    const char* GuiButton::lua_libName = "Button";

    const struct luaL_reg GuiButton::lua_lib_m [] = {
        {NULL, NULL}  /* sentinel */
    };

    const struct luaL_reg GuiButton::lua_lib_f [] = {
        {"new",lua_new},
        {NULL, NULL}  /* sentinel */
    };

    GuiButton::GuiButton(GuiPlugin* plugin, Script::LuaEngine* engine, lua_State* plua):GuiElement(plugin, engine, plua)
    {

    }
    
    GuiButton::~GuiButton()
    {

    }

    int GuiButton::lua_new(lua_State* pLua)
    {
        GuiPlugin* plugin = GuiPlugin::getThisPointer(pLua);
        Script::LuaEngine* engine = Script::LuaEngine::getThisPointer(pLua);
        GuiButton* pthis = new GuiButton(plugin,engine,pLua);

        int x = (int)lua_tonumber(pLua,1);
        int y = (int)lua_tonumber(pLua,2);
        int w = (int)lua_tonumber(pLua,3);
        int h = (int)lua_tonumber(pLua,4);

        size_t len;
        const char* text    = luaL_optlstring(pLua,5,"",&len);
        wchar_t* textw      =  new wchar_t[++len];
        mbstowcs(textw, text, len);
        const char* tooltip = luaL_optlstring(pLua,6,"",&len);
        wchar_t* tooltipw      =  new wchar_t[++len];
        mbstowcs(tooltipw, tooltip, len);


        irr::gui::IGUIButton* b = engine->getIrrlichtDevice()->getGUIEnvironment()->addButton(
                irr::core::recti(x,y,x+w,y+h),
                NULL,
                pthis->getId(),
                textw,
                tooltipw
            );

        pthis->m_irrelement = b;

        delete textw;
        delete tooltipw;

        pthis->pushToStack(pLua);
        pthis->drop();

        return 1;
    }
 

} /* End of namespace Gui */

