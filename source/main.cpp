#include <iostream>

#include "../render/include/window.hpp"
#include "../map/include/map_general.hpp"
#include "../object/include/unit.hpp"
#include "../object/include/tower.hpp"
#include "../object/include/shell.hpp"
#include "../object/include/spawner.hpp"
/*
#include "../render/include/render_loop.hpp"
#include "../event_handlers/include/event_loop.hpp"
#include "../map/include/map_physical.hpp"
*/

void initSDL()
{
	bool success = true;
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}
	}
}

std::deque<SDL_Point>  trajectory;

void initMap(td::map::general& _map)
{
	SDL_Point dest;
	dest = _map.m_physical.blockPos({1, _map.m_physical.blocks().y - 2});
	trajectory.push_back(dest);
	for (int y = _map.m_physical.blocks().y - 2; y > 0 ; y--)
		_map.m_physical.content(SDL_Point ({1, y})).setWalkable(true);
	dest = _map.m_physical.blockPos({1, 1});
	trajectory.push_back(dest);

	for (int x = 1; x < _map.m_physical.blocks().x - 1; x++)
		_map.m_physical.content(SDL_Point ({x, 1})).setWalkable(true);
	dest = _map.m_physical.blockPos({_map.m_physical.blocks().x - 2, 1});
	trajectory.push_back(dest);

	for (int y = 1; y < _map.m_physical.blocks().y - 1 ; y++)
		_map.m_physical.content(SDL_Point ({_map.m_physical.blocks().x - 2, y})).setWalkable(true);
	dest = _map.m_physical.blockPos({_map.m_physical.blocks().x - 2, _map.m_physical.blocks().y - 2});
	trajectory.push_back(dest);
}

int main( int argc, char* args[] )
{
	initSDL();
	SDL_Point wSize = {640, 480};
	SDL_Point fSize = {wSize.x/40, wSize.y/40};
	td::graphic::window window(wSize.x, wSize.y);
	td::graphic::texture_storage tStorage(window.renderer());
	td::map::general map;

	tStorage.load("media/pics/enemy.bmp", "enemy");
	tStorage.load("media/pics/tower.bmp", "tower");
	tStorage.load("media/pics/shell.bmp", "shell");
	map.m_physical.init(fSize, 40);
	initMap(map);

	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) )
	{
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
	}

	auto unit = std::make_unique<td::unit>(tStorage.get("enemy").get(), SDL_Point({0,0}), SDL_Point({24,24}), 0);
	unit->trajectory(trajectory);
	td::spawner uSpawner(std::move(unit), &map.m_objects);
	uSpawner.place(map.m_physical.blockPos({1, fSize.y - 2}));

	auto shell = std::make_unique<td::shell>(tStorage.get("shell").get(), SDL_Point({0,0}), SDL_Point({8,8}), 0, 0);
	td::spawner sSpawner(std::move(shell), &map.m_objects);

	auto tower = std::make_unique<td::tower>(tStorage.get("tower").get(), SDL_Point({0,0}), SDL_Point({40,40}), 0, &sSpawner);
	td::spawner tSpawner(std::move(tower), &map.m_objects);
	tSpawner.place(map.m_physical.blockPos({ fSize.x/2, fSize.y/2 }));
	tSpawner.spawn();

	SDL_Event ev;
	int tick = 0;
	while (true)
	{
		tick++;
		if ((tick %= 120) == 0) uSpawner.spawn();
		map.tick();
		while (SDL_PollEvent(&ev))
		{
			   if (ev.type == SDL_QUIT) return 0;
		}
		map.render(window.renderer(), SDL_Rect ({0, 0, 640, 480}));
		SDL_RenderPresent(window.renderer());
	}


	return 0;
}
