#include "LuaEngine.h"
#include "IrrlichtDevice.h"
#include "IGUIEnvironment.h"
#include "GuiButton.h"

namespace Script 
{

    const struct luaL_reg LuaEngine::lua_globls [] = {
        {"suspend", lua_Suspend},
        {NULL, NULL}  /* sentinel */
    };

    static const char* engineKey = "engineKey";


    LuaEngine::LuaEngine(irr::IrrlichtDevice* irr)
    {
        m_device = irr;
        m_lua = lua_open();
        luaL_openlibs(m_lua);


        lua_getglobal(m_lua,"debug");
        lua_getfield(m_lua,-1,"traceback");
        m_errorhandler = lua_gettop(m_lua);

        /* store a number */
        lua_pushlightuserdata(m_lua, (void *)&engineKey);  /* push address */
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

    template<class T>
    T* LuaEngine::getThisPointer(lua_State* pLua)
    {
        lua_pushlightuserdata(pLua, (void *)&engineKey);  /* push address */
        lua_gettable(pLua, LUA_REGISTRYINDEX);  /* retrieve value */
        return (T*)lua_touserdata(pLua,-1);
    }

    void LuaEngine::runFile(const irr::core::stringc& file)
    {
        luaL_loadfile(m_lua,file.c_str());
   
        doPCall(0,0);
    }

    void LuaEngine::init()
    {
        lua_pushvalue(m_lua,LUA_GLOBALSINDEX);

        luaL_register(m_lua, NULL, lua_globls);

        luaL_register(m_lua, NULL, getGlobals());

        addLibraries();

        Gui::GuiButton::createMatatable(m_lua);
    }

    int LuaEngine::getFreeId(Gui::GuiElement* e)
    {
        m_elements.push_back(e);
        return m_elements.size();
    }

    void LuaEngine::freeElement(int i)
    {
        m_elements[i-1] = NULL;
    }

    int LuaEngine::doPCall(int args,int rets)
    {
        int error = lua_pcall(m_lua, args, rets, m_errorhandler);

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
        if(e.EventType == irr::EET_GUI_EVENT)
        {
            if(e.GUIEvent.Caller)
    	    {
			    int id = e.GUIEvent.Caller->getID();
                Gui::GuiElement* element = getElement(id);
                if(element)
			    {
				    switch(e.GUIEvent.EventType)
				    {

                    case irr::gui::EGET_BUTTON_CLICKED:
							    element->onEvent("onButton");
						    break;
                        
                    case irr::gui::EGET_ELEMENT_HOVERED:
							    element->onEvent("onHover");
						    break;

                    case irr::gui::EGET_ELEMENT_FOCUSED:
							    element->onEvent("onFocused");
						    break;
                    
                    case irr::gui::EGET_ELEMENT_FOCUS_LOST:
							    element->onEvent("onFocusLost");
						    break;

				    }
			    }
    	    }
        }
		return false;
    }


    int LuaEngine::lua_Suspend(lua_State* pLua)
    {
        LuaEngine* pthis = getThisPointer<LuaEngine>(pLua);
        


        return 0;
    }

    Gui::GuiElement* LuaEngine::getElement(int id)
    {
        if(id < m_elements.size())
	    {
            if(m_elements[id-1])
            {
                return m_elements[id-1];
            }
        }
        return NULL;
    }

}
