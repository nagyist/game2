#include <vector>

#include "GlobalData.h"
#include "Common/ThreadLock.h"
#include "GameEngine.h"
#include "GamePlay/EntityFabric.h"

unsigned int GlobalData::PLAYER_ID_1 = 1;
unsigned int GlobalData::PLAYER_ID_2 = 2;


bool GlobalData::init_scene()
{	
	camera = new Camera();

	//-----TEST-----
	Entity * generator1 =
		EntityFabric::create_energy_generator(Vec2f(-0.6f, -0.4f), 0.3, 0.4);
	logic.add_entity(generator1);
	
	Entity * generator2 =
		EntityFabric::create_energy_generator(Vec2f(0.4f, 0.7f), 0.3, 0.2);
	logic.add_entity(generator2);
	
    base_tower_player_1 = EntityFabric::get_tower(NULL, Vec2f(0.0f,-0.4f));
	GetCmpt(PlayerIdComponent, plr_id_1_cmpt, base_tower_player_1);
	plr_id_1_cmpt->player_id = PLAYER_ID_1;
	GetCmpt(EnergyStorageComponent, enesto_1, base_tower_player_1);
	enesto_1->value = enesto_1->limit;
	logic.add_tower(base_tower_player_1);
	
	base_tower_player_2 = EntityFabric::get_tower(NULL, Vec2f(-0.2f, 0.6f));
	GetCmpt(PlayerIdComponent, plr_id_2_cmpt, base_tower_player_2);
	plr_id_2_cmpt->player_id = PLAYER_ID_2;
	GetCmpt(EnergyStorageComponent, enesto_2, base_tower_player_2);
	enesto_2->value = enesto_2->limit;
	logic.add_tower(base_tower_player_2);	
	//-----TEST-----
	
    return true;
}

Vec2f GlobalData::convert_coordinates(Vec2f screen_coord)
{
	Vec2f result;
	 // @todo: too expencive every time
	
	result.x = 2.0f * screen_coord.x / screen.width - 1.0f + camera->coords.x;
	result.y = ( screen.height - 2.0f * screen_coord.y ) * screen.ratio / screen.height;
	result.y += camera->coords.y;
	
	return result;
}