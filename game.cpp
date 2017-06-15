#include "game.h"

game::game(int w, int h, QGraphicsScene* new_scene): width(w), height(h), scene(new_scene){
	unit_list[w*h];
	for (int i=0; i<w*h; i++){
		unit_list[i] = nullptr;
	}
}

void game::add_unit(unit* new_unit)
{
	if(!unit_list[new_unit->index()]){
		unit_list[new_unit->index()].reset(new_unit);
		scene->addItem(unit_list[new_unit->index()].get());
	}
}

void game::update_paths(int index, int movement, int unit_team)
{
	for (int i = 0; i < grid_width*grid_height; ++i){
		pathing[i] = 0;
	}
	for (int i = 0; i < grid_width*grid_height; ++i){
		if(unit_list[i]){
			if (unit_list[i]->get_team() == 1-unit_team)
				pathing[i] = -1;
		}
	}
	pathing[index] = movement+1;
	for (int j = movement+1; j > 1; --j){
		for (int i = 0; i < grid_width*grid_height; ++i){
			if (pathing[i] == j){
				if (i-grid_width>=0){
					if (pathing[i-grid_width]==0)
						pathing[i-grid_width] = j-1;
				}
				if (i+grid_width<=grid_width*grid_height){
					if (pathing[i+grid_width]==0)
						pathing[i+grid_width] = j-1;
				}
				if (i-1>=0){
					if (pathing[i-1]==0)
						pathing[i-1] = j-1;
				}
				if (i+1<=grid_width*grid_height){
					if (pathing[i+1]==0)
						pathing[i+1] = j-1;
				}
			}
		}
	}
	for (int i = 0; i < grid_width*grid_height; ++i){
		if(unit_list[i]){
			if (unit_list[i]->get_team() == unit_team)
				pathing[i] = 0;
		}
	}
	for (int i = 0; i < grid_width*grid_height; ++i){
		if (pathing[i] > 0)
			tiles.push_back(new QGraphicsRectItem((i%grid_width)*grid_size,(i/grid_width)*grid_size,grid_size,grid_size));
	}
	for (int i = 0; i < tiles.size(); ++i)
		scene->addItem(tiles[i]);
}

void game::update_targets(int index, int unit_team)
{
	for (int i = 0; i < grid_width*grid_height; ++i){
		pathing[i] = 0;
	}
	pathing[index] = 2;
	tiles.push_back(new QGraphicsRectItem((index%grid_width)*grid_size,(index/grid_width)*grid_size,grid_size,grid_size));
	if (index-grid_width>=0){
		if (unit_list[index-grid_width]){
			if (unit_list[index-grid_width]->get_team() == 1-unit_team){
				pathing[index-grid_width] = 1;
				tiles.push_back(new QGraphicsRectItem(((index-grid_width)%grid_width)*grid_size,((index-grid_width)/grid_width)*grid_size,grid_size,grid_size));
			}
		}
	}
	if (index+grid_width<=grid_width*grid_height){
		if (unit_list[index+grid_width]){
			if (unit_list[index+grid_width]->get_team() == 1-unit_team){
				pathing[index+grid_width] = 1;
				tiles.push_back(new QGraphicsRectItem(((index+grid_width)%grid_width)*grid_size,((index+grid_width)/grid_width)*grid_size,grid_size,grid_size));
			}
		}
	}
	if (index-1>=0){
		if (unit_list[index-1]){
			if (unit_list[index-1]->get_team() == 1-unit_team){
				pathing[index-1] = 1;
				tiles.push_back(new QGraphicsRectItem(((index-1)%grid_width)*grid_size,((index-1)/grid_width)*grid_size,grid_size,grid_size));
			}
		}
	}
	if (index+1<=grid_width*grid_height){
		if (unit_list[index+1]){
			if (unit_list[index+1]->get_team() == 1-unit_team){
				pathing[index+1] = 1;
				tiles.push_back(new QGraphicsRectItem(((index+1)%grid_width)*grid_size,((index+1)/grid_width)*grid_size,grid_size,grid_size));
			}
		}
	}
	for (int i = 0; i < tiles.size(); ++i)
		scene->addItem(tiles[i]);
}

void game::clear_pathing()
{
	int s = (int)tiles.size();
	for (int i = 0; i<s; ++i){
		delete tiles[s-i-1];
		tiles.pop_back();
	}
}

void game::select(int index)
{
	if (!show_paths){
		if (unit_list[index]){
			if(unit_list[index]->get_team()==0 && unit_list[index]->get_status()){
				selected_index = index;
				connect(this, SIGNAL(selected(int)), unit_list[index].get(), SLOT(activated()));
				emit SIGNAL(selected(int));
				disconnect(this, SIGNAL(selected(int)), unit_list[index].get(), SLOT(activated()));
				update_paths(index, unit_list[index]->get_move(), unit_list[index]->get_team());
				show_paths = true;
			}
		}
	}
	else if (!show_targets){
		if (pathing[index]>0){
			move_index = index;
			clear_pathing();
			std::swap(unit_list[selected_index],(unit_list[move_index]));
			if(unit_list[selected_index])
				unit_list[selected_index]->set_index(selected_index);
			if(unit_list[move_index])
				unit_list[move_index]->set_index(move_index);
			update_targets(move_index, unit_list[move_index]->get_team());
			show_targets = true;
		}
	}
	else{

	}
}

void game::back()
{
	if (show_targets){
		clear_pathing();
		std::swap(unit_list[selected_index], unit_list[move_index]);
		if(unit_list[selected_index])
			unit_list[selected_index]->set_index(selected_index);
		if(unit_list[move_index])
			unit_list[move_index]->set_index(move_index);
		update_paths(selected_index, unit_list[selected_index]->get_move(), unit_list[selected_index]->get_team());
		show_targets = false;
	}
	else if (show_paths){
		clear_pathing();
		show_paths = false;
	}
}
