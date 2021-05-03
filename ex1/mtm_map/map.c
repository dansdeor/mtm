#include "map.h"
#include <stdlib.h>

typedef struct MapElement_t {
	MapKeyElement keyElement;
	MapDataElement dataElement;
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
	Map map = malloc(sizeof(*map));
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
	if (!map) {
		return NULL;
	}
	Map new_map = mapCreate(map->copyDataElement,
							map->copyKeyElement,
							map->freeDataElement,
							map->freeKeyElement,
							map->compareKeyElements);
	if (!map->head) {
		return new_map;
	}

	for (MapElement i = map->head; i != NULL; i = i->nextMapElement) {
		if (mapPut(new_map, i->keyElement, i->dataElement) == MAP_OUT_OF_MEMORY) {
			mapDestroy(new_map);
			return NULL;
		}
	}
	return new_map;
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
	return size;
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
	if (!map || !keyElement || !dataElement) {
		return MAP_NULL_ARGUMENT;
	}

	MapElement element = malloc(sizeof(*element));
	if (!element) {
		return MAP_OUT_OF_MEMORY;
	}
	element->keyElement = map->copyKeyElement(keyElement);
	if (!element->keyElement) {
		free(element);
		return MAP_OUT_OF_MEMORY;
	}
	element->dataElement = map->copyDataElement(dataElement);
	if (!element->dataElement) {
		free(element->keyElement);
		free(element);
		return MAP_OUT_OF_MEMORY;
	}
	element->nextMapElement = NULL;

	if (mapContains(map, keyElement)) {
		mapRemove(map, keyElement);
	}
	if (!map->head) {
		map->head = element;
		return MAP_SUCCESS;
	}
	if (map->compareKeyElements(map->head->keyElement, element->keyElement) > 0) {
		element->nextMapElement = map->head;
		map->head = element;
		return MAP_SUCCESS;
	}
	MapElement iterator = map->head;
	while (iterator->nextMapElement != NULL) {
		if (map->compareKeyElements(iterator->nextMapElement->keyElement, element->keyElement) > 0) {
			element->nextMapElement = iterator->nextMapElement;
			iterator->nextMapElement = element;
			return MAP_SUCCESS;
		}
		iterator = iterator->nextMapElement;
	}
	iterator->nextMapElement = element;
	return MAP_SUCCESS;
}

MapDataElement mapGet(Map map, MapKeyElement keyElement)
{
	if (!map || !keyElement) {
		return NULL;
	}
	for (MapElement i = map->head; i != NULL; i = i->nextMapElement) {
		if (map->compareKeyElements(i, keyElement) == 0) {
			return i->dataElement;
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
	return map->iterator->keyElement;//needs to create a new key element or not?
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
	return map->iterator->keyElement;//needs to create a new key element or not?
}


MapResult mapClear(Map map)
{

}
