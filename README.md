IrrLuaEngine
============

An Engine to enable Lua-scipting in Irrlicht projects. Its early alpha so don't expect stability or Documentation at this stage. 

It's build on top of luajit 2.0.0-beta 10 (latest git head http://luajit.org/download.html) and Irrlicht 1.7.3 (http://irrlicht.sourceforge.net/downloads/).

It's MIT Licensed

Compiling
============

There is a cmake script to compile the code. It assumes a workspace like this:

workspace <br>
+-----  IrrLuaEngine <br>
| <br>
+-----  irrlicht-1.7.3 <br>
| <br>
+-----  luajit-2.0 <br>

Download luajit, Irrlicht and this project in an folder and run cmake then make.
