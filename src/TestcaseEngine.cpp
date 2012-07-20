#include "TestcaseEngine.h"
#include "Game.h"
#include "IrrlichtDevice.h"



const char * TestcaseEngine::lua_libName = "Game";

const luaL_reg TestcaseEngine::lua_lib [] = {
    {"exit", lua_ExitGame},
    {NULL, NULL}  /* sentinel */
};

TestcaseEngine::TestcaseEngine(irr::IrrlichtDevice* irr, Game* g):LuaEngine(irr)
{
    m_game = g;
}


int TestcaseEngine::lua_ExitGame(lua_State* pLua)
{
    TestcaseEngine* pthis = (TestcaseEngine*) getThisPointer<LuaEngine>(pLua);
        
    pthis->m_game->closeGame();

    return 0;
}

const luaL_reg* TestcaseEngine::getGlobals()
{
    return lua_lib;
}

void TestcaseEngine::addLibraries()
{
    luaL_register(m_lua, lua_libName, lua_lib);
}


