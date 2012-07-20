#ifndef Main_UserInterface_GuiButton_h
#define Main_UserInterface_GuiButton_h


#include <GuiElement.h>
#include <lua.hpp>



namespace Gui 
{   
    class LuaEngine;
} 

namespace Gui 
{

    class GuiButton : public GuiElement
    {

     public:

        static void createMatatable(lua_State* pLua);

        GuiButton(LuaEngine* engine, GuiElement *parent, lua_State* plua);

        ~GuiButton();

        virtual void draw();

        virtual const luaL_reg* getMethods();
        
        virtual const luaL_reg* getFunktions();

        virtual const char* getTableName();

        virtual const char* getMetaTableName();

        //---- Lua funktions ------

        static int lua_new(lua_State* pLua);

        static int lua_GC(lua_State* pLua);

        static int lua_index(lua_State* pLua);

        static int lua_newindex(lua_State* pLua);

        //---- Lua Constants ------

        static const char* lua_libName;

        static const char* lua_metatableName;

        static const struct luaL_reg lua_lib_m [];

        static const struct luaL_reg lua_lib_f [];

    protected:
        irr::gui::IGUIElement *m_irrElement;
    };

} /* End of namespace Main::UserInterface */


#endif // Main_UserInterface_GuiElement_h
