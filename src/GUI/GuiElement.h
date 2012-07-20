#ifndef Main_UserInterface_GuiElement_h
#define Main_UserInterface_GuiElement_h

//#include "GlobalSettings.h"

#include <IGUIElement.h>
#include <lua.hpp>



namespace Gui 
{   
    class LuaEngine;
} 

namespace Gui 
{

    class GuiElement : public irr::IReferenceCounted 
    {

    public:

        GuiElement(LuaEngine* engine, GuiElement *parent, lua_State* plua);

        ~GuiElement();

        virtual void draw() = 0;

        virtual const luaL_reg* getMethods() = 0;
        
        virtual const luaL_reg* getFunktions() = 0;

        virtual const char* getTableName() = 0;

        virtual const char* getMetaTableName() = 0;

        void pushToStack();

        void onEvent(const char* event);

        const int getId() const
        {
            return m_id;
        }

    protected:

        void onLuaGC();
        void onLuaIndex();
        void onLuaNewIndex();

        GuiElement *m_parent;

        lua_State*  m_lua;

        LuaEngine* m_engine;

    private:

        int m_id;
    };

} 


#endif 
