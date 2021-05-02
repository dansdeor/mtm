#include "map.h"

typedef struct {
	MapKeyElement mapKeyElement;
	MapDataElement mapDataElement;
	MapElement nextMapElement;
} MapElement;

struct Map_t {
	copyMapDataElements copyDataElement;
	copyMapKeyElements copyKeyElement;
	freeMapDataElements freeDataElement;
	freeMapKeyElements freeKeyElement;
	compareMapKeyElements compareKeyElements;

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

}

bool mapContains(Map map, MapKeyElement element)
{

}


MapResult mapPut(Map map, MapKeyElement keyElement, MapDataElement dataElement)
{

}

MapDataElement mapGet(Map map, MapKeyElement keyElement)
{

}


MapResult mapRemove(Map map, MapKeyElement keyElement)
{

}


MapKeyElement mapGetFirst(Map map)
{

}


MapKeyElement mapGetNext(Map map)
{

}


MapResult mapClear(Map map)
{

}
