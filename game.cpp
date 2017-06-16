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
		connect(unit_list[new_unit->index()].get(), SIGNAL(killed(int)), this, SLOT(destroy_unit(int)));
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
				if (i-1>=0 && i%grid_width != 0){
					if (pathing[i-1]==0)
						pathing[i-1] = j-1;
				}
				if (i+1<=grid_width*grid_height && i%grid_width != 15){
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
	pathing[index] = movement+1;
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

void game::AI_targets(int index, int movement, int unit_type)
{
	for (int i = 0; i < grid_width*grid_height; ++i){
		pathing[i] = 0;
	}
	for (int i = 0; i < grid_width*grid_height; ++i){
		if(unit_list[i]){
			if (unit_list[i]->get_team() == 0)
				pathing[i] = -1;
		}
	}
	pathing[index] = movement+1;
	for (int j = movement+1; j > 0; --j){
		for (int i = 0; i < grid_width*grid_height; ++i){
			if (pathing[i] == j){
				if (i-grid_width>=0){
					if (pathing[i-grid_width]==0)
						pathing[i-grid_width] = j-1;
					else if (pathing[i-grid_width]== -1 && !unit_list[i]){ // check adjacent space and if current space is open
						if(unit_type == unit_list[i-grid_width]->get_type())
							pathing[i-grid_width] = -2;
						else if(unit_type-unit_list[i-grid_width]->get_type() == 1 || unit_type-unit_list[i-grid_width]->get_type() == -2)
							pathing[i-grid_width] = -3;
					}
				}
				if (i+grid_width<=grid_width*grid_height){
					if (pathing[i+grid_width]==0)
						pathing[i+grid_width] = j-1;
					else if (pathing[i+grid_width]== -1 && !unit_list[i]){ // check adjacent space and if current space is open
						if(unit_type == unit_list[i+grid_width]->get_type())
							pathing[i+grid_width] = -2;
						else if(unit_type-unit_list[i+grid_width]->get_type() == 1 || unit_type-unit_list[i+grid_width]->get_type() == -2)
							pathing[i+grid_width] = -3;
					}
				}
				if (i-1>=0 && i%grid_width != 0){
					if (pathing[i-1]==0)
						pathing[i-1] = j-1;
					else if (pathing[i-1]== -1 && !unit_list[i]){ // check adjacent space and if current space is open
						if(unit_type == unit_list[i-1]->get_type())
							pathing[i-1] = -2;
						else if(unit_type-unit_list[i-1]->get_type() == 1 || unit_type-unit_list[i-1]->get_type() == -2)
							pathing[i-1] = -3;
					}
				}
				if (i+1<=grid_width*grid_height && i%grid_width != 15){
					if (pathing[i+1]==0)
						pathing[i+1] = j-1;
					else if (pathing[i+1]== -1 && !unit_list[i]){ // check adjacent space and if current space is open
						if(unit_type == unit_list[i+1]->get_type())
							pathing[i+1] = -2;
						else if(unit_type-unit_list[i+1]->get_type() == 1 || unit_type-unit_list[i+1]->get_type() == -2)
							pathing[i+1] = -3;
					}
				}
			}
		}
	}
	for (int i = 0; i < grid_width*grid_height; ++i){
		if(unit_list[i]){
			if (unit_list[i]->get_team() == 1)
				pathing[i] = 0;
		}
	}
	pathing[index] = movement+1;
}

void game::clear_pathing()
{
	int s = (int)tiles.size();
	for (int i = 0; i<s; ++i){
		delete tiles[s-i-1];
		tiles.pop_back();
	}
}

void game::check_turn()
{
	for (int i = 0; i < grid_width*grid_height; ++i){
		if(unit_list[i]){
			if (unit_list[i]->get_team() == 0){
				if(unit_list[i]->get_status())
					return;
			}
		}
	}
	AI_turn();
}

void game::AI_turn()
{
	bool advantage;
	do {
		advantage = false;
		for (int i = 0; i < grid_width*grid_height; ++i){
			if(unit_list[i]){
				if (unit_list[i]->get_team() == 1 && unit_list[i]->get_status()){ //looks for AI unit that has not moved yet
					AI_targets(i, unit_list[i]->get_move(), unit_list[i]->get_type());
					for(int j = 0; j<grid_width*grid_height; ++j){
						if(pathing[j] < -2){
							bool picked_place = false;
							if (j-grid_width>=0 && !picked_place){
								if (pathing[j-grid_width] > 0){
									update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
									clear_pathing();
									unit_list[i]->set_status(0);
									std::swap(unit_list[i],(unit_list[j-grid_width]));
									unit_list[j-grid_width]->set_index(j-grid_width);
									destroy_unit(j);
									picked_place = true;
									advantage = true;
								}
							}
							if (j+grid_width<=grid_width*grid_height && !picked_place){
								if (pathing[j+grid_width] > 0){
									update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
									clear_pathing();
									unit_list[i]->set_status(0);
									std::swap(unit_list[i],(unit_list[j+grid_width]));
									unit_list[j+grid_width]->set_index(j+grid_width);
									destroy_unit(j);
									picked_place = true;
									advantage = true;
								}
							}
							if (j-1>=0 && !picked_place){
								if (pathing[j-1] > 0){
									update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
									clear_pathing();
									unit_list[i]->set_status(0);
									std::swap(unit_list[i],(unit_list[j-1]));
									unit_list[j-1]->set_index(j-1);
									destroy_unit(j);
									picked_place = true;
									advantage = true;
								}
							}
							if (j+1<=grid_width*grid_height && !picked_place){
								if (pathing[j+1] > 0){
									update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
									clear_pathing();
									unit_list[i]->set_status(0);
									std::swap(unit_list[i],(unit_list[j+1]));
									unit_list[j+1]->set_index(j+1);
									destroy_unit(j);
									picked_place = true;
									advantage = true;
								}
							}
						}
					}
				}
			}
		}
		if(!advantage){
			for (int i = 0; i < grid_width*grid_height; ++i){
				if(unit_list[i]){
					if (unit_list[i]->get_team() == 1 && unit_list[i]->get_status()){ //looks for AI unit that has not moved yet
						AI_targets(i, unit_list[i]->get_move(), unit_list[i]->get_type());
						for(int j = 0; j<grid_width*grid_height; ++j){
							if(pathing[j] < -1){ //attempts stalemate if advantage is missing
								bool picked_place = false;
								if (j-grid_width>=0 && !picked_place){
									if (pathing[j-grid_width] > 0){
										update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
										clear_pathing();
										unit_list[i]->set_status(0);
										std::swap(unit_list[i],(unit_list[j-grid_width]));
										unit_list[j-grid_width]->set_index(j-grid_width);
										destroy_unit(j);
										destroy_unit(j-grid_width);
										picked_place = true;
										advantage = true;
									}
								}
								if (j+grid_width<=grid_width*grid_height && !picked_place){
									if (pathing[j+grid_width] > 0){
										update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
										clear_pathing();
										unit_list[i]->set_status(0);
										std::swap(unit_list[i],(unit_list[j+grid_width]));
										unit_list[j+grid_width]->set_index(j+grid_width);
										destroy_unit(j);
										destroy_unit(j+grid_width);
										picked_place = true;
										advantage = true;
									}
								}
								if (j-1>=0 && !picked_place){
									if (pathing[j-1] > 0){
										update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
										clear_pathing();
										unit_list[i]->set_status(0);
										std::swap(unit_list[i],(unit_list[j-1]));
										unit_list[j-1]->set_index(j-1);
										destroy_unit(j);
										destroy_unit(j-1);
										picked_place = true;
										advantage = true;
									}
								}
								if (j+1<=grid_width*grid_height && !picked_place){
									if (pathing[j+1] > 0){
										update_paths(i, unit_list[i]->get_move(), unit_list[i]->get_team());
										clear_pathing();
										unit_list[i]->set_status(0);
										std::swap(unit_list[i],(unit_list[j+1]));
										unit_list[j+1]->set_index(j+1);
										destroy_unit(j);
										destroy_unit(j+1);
										picked_place = true;
										advantage = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}while(advantage);
	for (int i = 0; i < grid_width*grid_height; ++i){
		if(unit_list[i]){
			unit_list[i]->set_status(1);
		}
	}
}

void game::select(int index)
{
	if (!show_paths){
		if (unit_list[index]){
			if(unit_list[index]->get_team()==0 && unit_list[index]->get_status()){
				selected_index = index;
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
			unit_list[move_index]->set_index(move_index);
			update_targets(move_index, unit_list[move_index]->get_team());
			show_targets = true;
		}
	}
	else{
		if (pathing[index]>0){
			int target_index = index;
			clear_pathing();
			if (target_index != move_index){
				int move_type = unit_list[move_index]->get_type();
				int target_type = unit_list[target_index]->get_type();
				if (move_type == target_type){
					destroy_unit(target_index);
					destroy_unit(move_index);
				}
				else if(move_type-target_type == 1 || move_type-target_type == -2){
					destroy_unit(target_index);
				}
				else if(move_type-target_type == -1 || move_type-target_type == 2){
					destroy_unit(move_index);
				}
			}
			if(unit_list[move_index])
				unit_list[move_index]->set_status(0);
			show_paths = false;
			show_targets = false;
			check_turn();
		}
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

void game::destroy_unit(int dead_index)
{
	unit_list[dead_index].reset(nullptr);
}
