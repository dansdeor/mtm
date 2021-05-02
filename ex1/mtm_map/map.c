#include "map.h"

typedef struct MapElement_t {
	MapKeyElement mapKeyElement;
	MapDataElement mapDataElement;
	struct MapElement_t* nextMapElement;
} *MapElement;

struct Map_t {
	copyMapDataElements copyDataElement;
	copyMapKeyElements copyKeyElement;
	freeMapDataElements freeDataElement;
	freeMapKeyElements freeKeyElement;
	compareMapKeyElements compareKeyElements;
	MapElement head;
	MapElement iterator;
};


Map mapCreate(copyMapDataElements copyDataElement,
			  copyMapKeyElements copyKeyElement,
			  freeMapDataElements freeDataElement,
			  freeMapKeyElements freeKeyElement,
			  compareMapKeyElements compareKeyElements)
{
	if (!copyDataElement || !copyKeyElement || !freeDataElement || !freeKeyElement || !compareKeyElements) {
		return NULL;
	}
	Map map = malloc(sizeof(*Map));
	if (!map) {
		return NULL;
	}
	map->copyDataElement = copyDataElement;
	map->copyKeyElement = copyKeyElement;
	map->freeDataElement = freeDataElement;
	map->freeKeyElement = freeKeyElement;
	map->compareKeyElements = compareKeyElements;
	map->head = NULL;
	map->iterator = NULL;
	return map;
}


void mapDestroy(Map map)
{

}

Map mapCopy(Map map)
{

}

int mapGetSize(Map map)
{
	if (!map) {
		return -1;
	}
	int size = 0;
	for (MapElement i = map->head; i != NULL; i = i->nextMapElement) {
		size++;
	}
	return size
}

bool mapContains(Map map, MapKeyElement element)
{
	if (!map || !element) {
		return false;
	}
	//map->iterator = NULL; needs to check that!!!
	for (MapElement i = map->head; i != NULL; i = i->nextMapElement) {
		if (map->compareKeyElements(i, element) == 0) {
			return true;
		}
	}
	return false;
}


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement)
{

}

MapDataElement mapGet(Map map, MapKeyElement keyElement)
{
	if (!map || !keyElement) {
		return NULL;
	}
	for (MapElement i = map->head; i != NULL; i = i->nextMapElement) {
		if (map->compareKeyElements(i, keyElement) == 0) {
			return i->mapDataElement;
		}
	}
	return NULL;
}


MapResult mapRemove(Map map, MapKeyElement keyElement)
{

}


MapKeyElement mapGetFirst(Map map)
{
	if (!map) {
		return NULL;
	}
	map->iterator = map->head;
	if (!map->iterator) {
		return NULL;
	}
	return map->iterator->mapKeyElement;//needs to create a new key element or not?
}


MapKeyElement mapGetNext(Map map)
{
	if (!map || !map->iterator) {
		return NULL;
	}
	map->iterator = map->iterator->nextMapElement;
	if (!map->iterator) {
		return NULL;
	}
	return map->iterator->mapKeyElement;//needs to create a new key element or not?
}


MapResult mapClear(Map map)
{

}
