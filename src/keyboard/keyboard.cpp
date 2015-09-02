#include "keyboard.h"
#include "SDL2/SDL.h"
#include "filereader/FileReader.h"
#include <iostream>
#include <fstream>

static bool strToKeycode(std::string name, SDL_Keycode & output)
{
	#define BEGIN_CASE()\
	if(false){}
	
	
	
	#define MAP_CASE(str1, str2)\
	else if(name == str1)\
		output = SDLK_##str2
	
	#define GEN_CASE(str) MAP_CASE(#str, str)
	
	#define END_CASE()\
	else{\
		std::cerr << "unknown button " << name << std::endl;\
		return false;\
	}\
	return true;\
	
	BEGIN_CASE()
	MAP_CASE("up", UP);
	MAP_CASE("down", DOWN);
	MAP_CASE("left", LEFT);
	MAP_CASE("right", RIGHT);
	
	MAP_CASE("backspace", BACKSPACE);
	
	MAP_CASE("tab", TAB);
	MAP_CASE("\t", TAB);
	
	MAP_CASE("return", RETURN);
	MAP_CASE("enter", RETURN);
	
	MAP_CASE("space", SPACE);
	MAP_CASE(" ", SPACE);
	
	MAP_CASE("backslash", BACKSLASH);
	MAP_CASE("\\", BACKSLASH);
	
	MAP_CASE("quote", QUOTE);
	MAP_CASE("'", QUOTE);
	
	MAP_CASE("semicolon", SEMICOLON);
	MAP_CASE(";", SEMICOLON);
	
	MAP_CASE("<", COMMA);
	MAP_CASE(",", COMMA);
	
	MAP_CASE(">", PERIOD);
	MAP_CASE(".", PERIOD);
	
	GEN_CASE(a);
	GEN_CASE(b);
	GEN_CASE(c);
	GEN_CASE(d);
	GEN_CASE(e);
	GEN_CASE(f);
	GEN_CASE(g);
	GEN_CASE(h);
	GEN_CASE(i);
	GEN_CASE(j);
	GEN_CASE(k);
	GEN_CASE(l);
	GEN_CASE(m);
	GEN_CASE(n);
	GEN_CASE(o);
	GEN_CASE(p);
	GEN_CASE(q);
	GEN_CASE(r);
	GEN_CASE(s);
	GEN_CASE(t);
	GEN_CASE(u);
	GEN_CASE(v);
	GEN_CASE(w);
	GEN_CASE(x);
	GEN_CASE(y);
	GEN_CASE(z);
	
	GEN_CASE(0);
	GEN_CASE(1);
	GEN_CASE(2);
	GEN_CASE(3);
	GEN_CASE(4);
	GEN_CASE(5);
	GEN_CASE(6);
	GEN_CASE(7);
	GEN_CASE(8);
	GEN_CASE(9);
	
	END_CASE()
	
	#undef GEN_CASE
	#undef BEGIN_CASE
	#undef END_CASE
}

KeyBinding::KeyBinding()
{
	faster = SDLK_UP;
	slower = SDLK_DOWN;
	left = SDLK_LEFT;
	right = SDLK_RIGHT;
	shoot = SDLK_z;
	reset = SDLK_r;
}

void KeyBinding::load(char const * path)
{
	std::ifstream is(path);
	fr::FileReader reader(is);
	
	auto obj = reader.getString("reset");
	if(obj != nullptr)
		strToKeycode(obj->datum, reset);

	auto obj = reader.getString("faster");
	if(obj != nullptr)
		strToKeycode(obj->datum, faster);
	
	obj = reader.getString("slower");
	if(obj != nullptr)
		strToKeycode(obj->datum, slower);
	
	obj = reader.getString("left");
	if(obj != nullptr)
		strToKeycode(obj->datum, left);
	
	obj = reader.getString("right");
	if(obj != nullptr)
		strToKeycode(obj->datum, right);
	
	obj = reader.getString("fire");
	if(obj != nullptr)
		strToKeycode(obj->datum, shoot);
}

Keyboard::Keyboard()
{
	SDL_InitSubSystem(SDL_INIT_EVENTS);
}

Keyboard::~Keyboard()
{
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
}

void Keyboard::update()
{
	keyPress.any = false;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		if(e.type == SDL_KEYDOWN)
		{
			keyPress.any = true;
			SDL_Keycode symbol = e.key.keysym.sym;
			if(symbol == keyBinding.faster)
				keyPress.faster = true;
			else if(symbol == keyBinding.slower)
				keyPress.slower = true;
			else if(symbol == keyBinding.left)
				keyPress.left = true;
			else if(symbol == keyBinding.right)
				keyPress.right = true;
			else if(symbol == keyBinding.fire)
				keyPress.fire = true;
			else if(symbol == SDLK_ESCAPE)
				keyPress.quit = true;
		}
		else if(e.type == SDL_KEYUP)
		{
			SDL_Keycode symbol = e.key.keysym.sym;
			if(symbol == keyBinding.faster)
				keyPress.faster = false;
			else if(symbol == keyBinding.slower)
				keyPress.slower = false;
			else if(symbol == keyBinding.left)
				keyPress.left = false;
			else if(symbol == keyBinding.right)
				keyPress.right = false;
			else if(symbol == keyBinding.fire)
				keyPress.fire = false;
		}
		else if(e.type == SDL_QUIT)
		{
			keyPress.quit = true;
		}
	}
}
