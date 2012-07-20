#ifndef GUI_CLIENTLUAENGINE_h
#define GUI_CLIENTLUAENGINE_h

#include "lua.hpp"
#include "GuiElement.h"
#include "IEventReceiver.h"
#include "IrrlichtDevice.h"

class Game;

namespace Gui
{
    class GuiElement;
}

namespace Gui
{

    class LuaEngine : public irr::IEventReceiver
    {
    public:

        LuaEngine(irr::IrrlichtDevice* irr);

        void init();

        void draw();

        void runFile(const irr::core::stringc& file);

        virtual const luaL_reg* getGlobals() = 0;

        virtual void addLibraries() = 0;
        
        void run();

        int getFreeId(GuiElement* e);

        void freeElement(int i);

        int doPCall(int args,int rets);

        irr::IrrlichtDevice* getIrrlichtDevice();

        template<class T>
        static T* getThisPointer(lua_State* pLua);

        virtual bool OnEvent(const irr::SEvent&);
        
        GuiElement* getElement(int id);

        //---- Lua funktions ------

        static int lua_Suspend(lua_State* pLua);

        //---- Lua Constants ------

        static const luaL_reg lua_globls [];


        

    protected:

        lua_State*           m_lua;
        irr::IrrlichtDevice* m_device; 


    private:
        irr::core::array<GuiElement*>
                            m_elements;
        int         m_errorhandler;

    };
}

#endif
