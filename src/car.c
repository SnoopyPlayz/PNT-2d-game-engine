// ENTIRY FILE
void initGame(){
	treeInit();
	carInit();
	raceTrackInit();
}

void destoyGame(){
	treeDestructor();
	carDestructor();
	raceTrackDestructor();
}

// CAR FILE 
void treeInit(){
	int tree = entity_add(tree, "texturePath", "ModelPath", pos, rot);
}

void treeDestructor(){
	entity_remove(tree);
}

void treeUpdate(){
	tree = &entity[tree];
	tree.pos.z += 1;

}
