#include "Game.h"
#include <fstream>
#include <time.h>
#include "GuiPlugin.h"
#include "LuaEngine.h"

using namespace irr;

const char* Game::Lua_Object_Key = "GameKey";

const char* Game::lua_libName = "Game";

const luaL_reg Game::lua_lib[] = {
        {"exit",lua_ExitGame},
        {NULL, NULL}  /* sentinel */
    };

Game::Game()
{
    m_script = NULL;
	m_device = NULL;
	m_driver = NULL;
}

Game::~Game()
{
    delete m_script;
}

void Game::init(int argc, const char* argv[])
{
	irr::SIrrlichtCreationParameters s;

	s.AntiAlias = 0;
	s.Bits = 32;
    s.DriverType = irr::video::EDT_OPENGL;
	s.Fullscreen = false;
	s.Vsync = true;
	s.Stencilbuffer = false;
    s.WindowSize = irr::core::dimension2di(800,600);

	m_device = createDeviceEx(s);
    m_driver = m_device->getVideoDriver();

	//assert(m_device != NULL);

	m_device->setWindowCaption(L"LuaEngine Test");

	irr::gui::IGUIFont* font = m_device->getGUIEnvironment()->getFont(
			"font.xml");
	irr::gui::IGUISkin* skin = m_device->getGUIEnvironment()->getSkin();
	skin->setFont(font);
	m_device->getGUIEnvironment()->setSkin(skin);

    m_script = new Script::LuaEngine(m_device);
    

        /* store a number */
    lua_pushlightuserdata(m_script->getLuaState(), (void *)Lua_Object_Key);  /* push address */
    lua_pushlightuserdata(m_script->getLuaState(), (void *)this);  /* push value */
    /* registry[&Key] = myNumber */
    lua_settable(m_script->getLuaState(), LUA_REGISTRYINDEX);

    m_script->addPlugin(new Gui::GuiPlugin(m_device));

    m_script->init();
    m_script->runFile("main.lua");

	m_device->setEventReceiver(m_script);
}

int Game::runGame()
{
	while (m_device->run())
	{
        m_script->run();

		m_driver->beginScene(true, true);
        m_device->getGUIEnvironment()->drawAll();
		m_driver->endScene();
		m_device->yield();
	}

	return 0;
}

void Game::closeGame()
{
    m_device->closeDevice();
}

irr::IrrlichtDevice* Game::getIrrlichtDevice() const
{
	return m_device;
}

irr::video::IVideoDriver* Game::getVideoDriver() const
{
	return m_driver;
}

int Game::lua_ExitGame(lua_State* pLua)
{
    Game* pthis = getThisPointer(pLua);
        
    pthis->closeGame();

    return 0;
}

Game* Game::getThisPointer(lua_State* pLua)
{
    lua_pushlightuserdata(pLua, (void *)Lua_Object_Key);  /* push address */
    lua_gettable(pLua, LUA_REGISTRYINDEX);  /* retrieve value */
    Game* e = (Game*)lua_touserdata(pLua,-1);
    lua_pop(pLua,1);
    return e;
}

void Game::registerFunktions(lua_State* pLua)
{
    luaL_register(pLua, lua_libName, lua_lib);
    
    /* store a number */
    lua_pushlightuserdata(pLua, (void *)Lua_Object_Key);  /* push address */
    lua_pushlightuserdata(pLua, (void *)this);  /* push value */
    /* registry[&Key] = myNumber */
    lua_settable(pLua, LUA_REGISTRYINDEX);
}

void Game::run()
{

}

bool Game::OnEvent(const irr::SEvent&)
{
    return false;
}

