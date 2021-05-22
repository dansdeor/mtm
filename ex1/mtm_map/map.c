#include "map.h"
#include <stdlib.h>


typedef struct MapElement_t {
	MapKeyElement keyElement;
	MapDataElement dataElement;
	struct MapElement_t* nextMapElement;
} *MapElement;


struct Map_t {
	copyMapDataElements CopyDataElement;
	copyMapKeyElements CopyKeyElement;
	freeMapDataElements FreeDataElement;
	freeMapKeyElements FreeKeyElement;
	compareMapKeyElements CompareKeyElements;
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
	map->CopyDataElement = copyDataElement;
	map->CopyKeyElement = copyKeyElement;
	map->FreeDataElement = freeDataElement;
	map->FreeKeyElement = freeKeyElement;
	map->CompareKeyElements = compareKeyElements;
	map->head = NULL;
	map->iterator = NULL;
	return map;
}


void mapDestroy(Map map)
{
	if (!map) {
		return;
	}
	mapClear(map);
	free(map);
}


Map mapCopy(Map map)
{
	if (!map) {
		return NULL;
	}
	Map new_map = mapCreate(map->CopyDataElement,
							map->CopyKeyElement,
							map->FreeDataElement,
							map->FreeKeyElement,
							map->CompareKeyElements);
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
	for (MapElement i = map->head; i != NULL; i = i->nextMapElement) {
		if (map->CompareKeyElements(i->keyElement, element) == 0) {
			return true;
		}
	}
	return false;
}


static MapResult createMapElement(Map map, MapElement* pointer, MapKeyElement keyElement, MapDataElement dataElement)
{
	if (!map || !pointer || !keyElement || !dataElement) {
		return MAP_NULL_ARGUMENT;
	}
	MapElement element = malloc(sizeof(*element));
	if (!element) {
		return MAP_OUT_OF_MEMORY;
	}
	element->keyElement = map->CopyKeyElement(keyElement);
	if (!element->keyElement) {
		free(element);
		return MAP_OUT_OF_MEMORY;
	}
	element->dataElement = map->CopyDataElement(dataElement);
	if (!element->dataElement) {
		free(element->keyElement);
		free(element);
		return MAP_OUT_OF_MEMORY;
	}
	element->nextMapElement = NULL;
	*pointer = element;
	return MAP_SUCCESS;
}


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement)
{
	MapElement element;
	MapResult allocation_result = createMapElement(map, &element, keyElement, dataElement);
	if (allocation_result != MAP_SUCCESS) {
		return allocation_result;
	}
	if (mapContains(map, keyElement)) {
		mapRemove(map, keyElement);
	}
	if (!map->head) {
		map->head = element;
		return MAP_SUCCESS;
	}
	if (map->CompareKeyElements(map->head->keyElement, element->keyElement) > 0) {
		element->nextMapElement = map->head;
		map->head = element;
		return MAP_SUCCESS;
	}
	MapElement iterator = map->head;
	while (iterator->nextMapElement != NULL) {
		if (map->CompareKeyElements(iterator->nextMapElement->keyElement, element->keyElement) > 0) {
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
		if (map->CompareKeyElements(i->keyElement, keyElement) == 0) {
			return i->dataElement;
		}
	}
	return NULL;
}


static void mapElementFree(Map map, MapElement element)
{
	if (!map || !element) {
		return;
	}
	map->FreeKeyElement(element->keyElement);
	map->FreeDataElement(element->dataElement);
	free(element);
}


MapResult mapRemove(Map map, MapKeyElement keyElement)
{
	if (!map || !keyElement) {
		return MAP_NULL_ARGUMENT;
	}
	if (!map->head) {
		return MAP_ITEM_DOES_NOT_EXIST;
	}

	if (map->CompareKeyElements(map->head->keyElement, keyElement) == 0) {
		MapElement element = map->head;
		map->head = map->head->nextMapElement;
		mapElementFree(map, element);
		return MAP_SUCCESS;
	}

	MapElement iterator = map->head;
	while (iterator->nextMapElement != NULL) {
		if (map->CompareKeyElements(iterator->nextMapElement->keyElement, keyElement) == 0) {
			MapElement element = iterator->nextMapElement;
			iterator->nextMapElement = iterator->nextMapElement->nextMapElement;
			mapElementFree(map, element);
			return MAP_SUCCESS;
		}
		iterator = iterator->nextMapElement;
	}
	return MAP_ITEM_DOES_NOT_EXIST;
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
	return map->CopyKeyElement(map->iterator->keyElement);
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
	return map->CopyKeyElement(map->iterator->keyElement);
}


MapResult mapClear(Map map)
{
	if (!map) {
		return MAP_NULL_ARGUMENT;
	}
	MapElement iterator = map->head;
	while (iterator != NULL) {
		MapElement element = iterator;
		iterator = iterator->nextMapElement;
		mapElementFree(map, element);
	}
	map->head = NULL;
	map->iterator = NULL;
	return MAP_SUCCESS;
}
