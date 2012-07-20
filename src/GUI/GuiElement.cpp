#include "GuiElement.h"
#include "LuaEngine.h"


namespace Gui {

    GuiElement::GuiElement(Script::LuaEngine* engine, lua_State* plua)
    {
        m_engine = engine;
        m_parent = NULL;
        m_type = "";
        m_lua = plua;

        m_id = engine->getFreeId(this);
        lua_pushlightuserdata(m_lua, (void *)this);  /* push value */
        lua_newtable(m_lua);
        /* registry[&Key] = myNumber */
        lua_settable(m_lua, LUA_REGISTRYINDEX);
    }

    
    GuiElement::~GuiElement()
    {
        m_engine->freeElement(m_id);
        lua_pushlightuserdata(m_lua, (void *)this);  /* push value */
        lua_pushnil(m_lua);
        /* registry[&Key] = myNumber */
        lua_settable(m_lua, LUA_REGISTRYINDEX);
    }
    
    void GuiElement::pushToStack()
    {
        GuiElement** otherThis = (GuiElement**)lua_newuserdata(m_lua,sizeof(void*));
        *otherThis = this;
        luaL_getmetatable(m_lua, getMetaTableName());
        lua_setmetatable(m_lua, -2);
        grab();
    }
    
    void GuiElement::onEvent(const char* event)
    {
    	//printf("%s\n",event);
        //GuiElement* pthis = *static_cast<GuiElement**>(luaL_checkudata(m_lua, 1, lua_metatableName));
        lua_pushlightuserdata(m_lua, (void *)this);  /* push address */
        lua_gettable(m_lua, LUA_REGISTRYINDEX);  /* retrieve value */
        lua_pushfstring(m_lua,event);
        lua_gettable(m_lua, -2);

        if(lua_isfunction(m_lua,-1))
        {
            pushToStack();
            m_engine->doPCall(1,0);
        }
    }

    void GuiElement::onLuaGC()
    {
        drop();
    }

    void GuiElement::onLuaIndex()
    {
        const char* key = luaL_checkstring(m_lua, 2);

        if(!strcmp("type",key))
        {
            lua_pushstring(m_lua,m_type);
            return;
        }

        lua_getmetatable(m_lua, 1);
        lua_getfield(m_lua, -1, key);

        if(!lua_isnil(m_lua, -1))
	        return;

        lua_settop(m_lua, 2);

        lua_pushlightuserdata(m_lua, (void *)this);  /* push address */
        lua_gettable(m_lua, LUA_REGISTRYINDEX);  /* retrieve value */
        lua_insert(m_lua,2);
        lua_gettable(m_lua, 2);
    }

    void GuiElement::onLuaNewIndex()
    {
        lua_pushlightuserdata(m_lua, (void *)this);  /* push address */
        lua_gettable(m_lua, LUA_REGISTRYINDEX);  /* retrieve value */
        lua_insert(m_lua,2);
        lua_settable(m_lua, 2);
    }


} /* End of namespace Gui */
