#include "LuaEngine.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "ILuaEnginePlugin.h"


namespace Script 
{

    const struct luaL_reg LuaEngine::lua_globls [] = {
        {"suspend", lua_Suspend},
        {NULL, NULL}  /* sentinel */
    };

    const char* LuaEngine::Lua_Object_Key = "engineKey";


    LuaEngine::LuaEngine(irr::IrrlichtDevice* irr)
    {
        m_device = irr;
        m_lua = lua_open();
        luaL_openlibs(m_lua);


        lua_getglobal(m_lua,"debug");
        lua_getfield(m_lua,-1,"traceback");
        m_errorhandler = lua_gettop(m_lua);

        /* store a number */
        lua_pushlightuserdata(m_lua, (void *)Lua_Object_Key);  /* push address */
        lua_pushlightuserdata(m_lua, (void *)this);  /* push value */
        /* registry[&Key] = myNumber */
        lua_settable(m_lua, LUA_REGISTRYINDEX);
    }

    void LuaEngine::draw()
    {
        m_device->getGUIEnvironment()->drawAll();
    }

    void LuaEngine::run()
    {

    }

    void LuaEngine::addPlugin(ILuaEnginePlugin* p)
    {
        m_plugins.push_back(p);
    }

    LuaEngine* LuaEngine::getThisPointer(lua_State* pLua)
    {
        lua_pushlightuserdata(pLua, (void *)Lua_Object_Key);  /* push address */
        lua_gettable(pLua, LUA_REGISTRYINDEX);  /* retrieve value */
        LuaEngine* e = (LuaEngine*)lua_touserdata(pLua,-1);
        lua_pop(pLua,1);
        return e;
    }


    void LuaEngine::runFile(const irr::core::stringc& file)
    {
        luaL_loadfile(m_lua,file.c_str());
   
        doCall(0,0);
    }

    void LuaEngine::init()
    {
        lua_pushvalue(m_lua,LUA_GLOBALSINDEX);

        luaL_register(m_lua, NULL, lua_globls);

        for(irr::u32 i = 0; i< m_plugins.size(); i++)
        {
            m_plugins[i]->registerFunktions(m_lua);
        }
    }



    int LuaEngine::doCall(int args,int rets)
    {
        int function_index = lua_gettop(m_lua) - args;
        lua_getfield(m_lua,LUA_GLOBALSINDEX,"coroutine");
        lua_getfield(m_lua,-1,"create");
        lua_remove(m_lua, -2);

        lua_pushvalue(m_lua,function_index);
        //lua_remove(m_lua,function_index);

        int error = lua_pcall(m_lua, 1, 1, m_errorhandler);



        if(error)
        {
            const char* c = lua_tostring(m_lua, -1);
            printf("Error in runing Script! %i: \n%s\n", error, c);
            return error;
        }

        //lua_insert(m_lua, function_index);
        //error = lua_resume(m_lua, args);

        lua_getfield(m_lua,LUA_GLOBALSINDEX,"coroutine");
        lua_getfield(m_lua,-1,"resume");
        lua_remove(m_lua, -2);
        lua_insert(m_lua, function_index);

        error = lua_pcall(m_lua, args+1, rets, m_errorhandler);

        if(error)
        {
            const char* c = lua_tostring(m_lua, -1);
            printf("Error in runing Script! %i: \n%s\n", error, c);
        }
        return error;
    }

    irr::IrrlichtDevice* LuaEngine::getIrrlichtDevice()
    {
        return m_device;
    }

    bool LuaEngine::OnEvent(const irr::SEvent& e)
    {
        for(irr::u32 i = 0; i < m_plugins.size(); i++)
        {
            m_plugins[i]->OnEvent(e);
        }
        return false;
    }


    int LuaEngine::lua_Suspend(lua_State* pLua)
    {
        LuaEngine* pthis = getThisPointer(pLua);
        

        return 0;
    }

}
