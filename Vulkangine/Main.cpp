#include<stdio.h>
#include <iostream>
#include "Object3D.h"
#include "Icosaptree.h"
#include <time.h>       /* time */


int main(int argc, char ** argv) {
	printf("Vulkangine v0.0.1\n");
	srand(1991);
	Icosaptree * tree = new Icosaptree(1);
	int mapSize = 8000;
	for(int i=0; i < 100000 ; ++i){
		Object3D * obj = new Object3D(Vector3(rand()% mapSize, rand() % mapSize, rand() % mapSize),1);
		tree->insert(obj);
	}
	std::cout << "ready" << std::endl;
	std::cout << "IcosaptreeNode " << sizeof(IcosaptreeNode) << std::endl;
	std::cout << "Nodes " << tree->root->total() << std::endl;

	getchar();
	return 0;
}