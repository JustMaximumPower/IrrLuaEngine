#ifndef GUI_TestcaseEngine_h
#define GUI_TestcaseEngine_h

#include "LuaEngine.h"

class Game;

namespace Gui
{

    class TestcaseEngine : public LuaEngine
    {

    public:
        TestcaseEngine(irr::IrrlichtDevice* irr, Game* g);

        virtual const luaL_reg* getGlobals();

        virtual void addLibraries();

        //---- Lua funktions ------

        static int lua_ExitGame(lua_State* pLua);

        //---- Lua Constants ------

        static const char * lua_libName ;

        static const luaL_reg lua_lib [];
    
    private:
        Game* m_game;
    };
    

} 

#endif 
