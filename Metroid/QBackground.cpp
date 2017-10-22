#include "QBackground.h"

QBackground::QBackground(void)
{
	listTile = NULL;
}

QBackground::QBackground(int level)
{
	string fileName;
	string _fileName;
	fileName = "Resources\\Maps\\fullmap_map.txt";

	ifstream map(fileName);

	// ma trận tile
	if (map.is_open())
	{
		int posX, posY;
		int value;
		int countTileWidth, countTileHeight;
		int countWidth, countHeight;
		map >> countTileWidth >> countTileHeight;

		//Load file tile
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\fullmap.png", countTileWidth, countTileHeight, countTileWidth*countTileHeight), 1000);

		/*switch (level)
		{
		case 1:
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level1.png", count, 1, count), 1000);
		break;
		case 2:
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level2.png", count, 1, count), 1000);
		break;
		case 3:
		bgSprite = new CSprite(new CTexture("Resources\\Maps\\Level3.png", count, 1, count), 1000);
		break;
		}*/
		map >> countHeight >> countWidth;
		int id = 0;
		listTile = new std::map<int, Tile*>();

		Tile* _obj;
		for (int i = countHeight - 1; i > 0; i--)
		{
			for (int j = 0; j < countWidth; j++)
			{
				map >> value;
				posX = (j * 32) + 16;
				posY = (i * 32) - 16;
				id = i*countWidth + j;
				listTile->insert(pair<int, Tile*>(id, new Tile(value, posX, posY)));
			}
		}
		
		map.close();
	}

}


void QBackground::Draw(CCamera *camera)
{
	map<int, Tile*>::iterator _itBegin;
	for (_itBegin = listTile->begin(); _itBegin != listTile->end(); _itBegin++)
	{
		Tile* obj = _itBegin->second;
		D3DXVECTOR2 t = camera->Transform(obj->posX, obj->posY);  
		bgSprite->DrawIndex(obj->ID, t.x, t.y); //Vẽ từng ô tile
		//bgSprite->DrawScale(obj->ID, t.x, t.y);
	}
}

QBackground::~QBackground(void)
{
}