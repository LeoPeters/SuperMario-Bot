#include "DataExtractorPerTile.h"
#include <filesystem>
/*#define SKY 0
#define MARIO 1
#define BLOCK 2
#define ENEMY 3
#define ITEM 4
#define WINNINGCONDS 5*/
#define MAX_DATA_COUNT 5000
namespace fs = std::filesystem;

int DataExtractorPerTile::returnDirCount(const char* directory)
{
	int count = 0;
	for (auto& p : fs::directory_iterator(directory)) {
		count++;
	}
	return count;
}

std::string DataExtractorPerTile::return_name(int num)
{
	switch (num) {
	case SKY: return std::string("aiTrainingData/pictures/sky");
	case MARIO: return std::string("aiTrainingData/pictures/mario");
	case BLOCK: return std::string("aiTrainingData/pictures/block");
	case ENEMY: return std::string("aiTrainingData/pictures/enemy");
	case ITEM: return std::string("aiTrainingData/pictures/item");
	case WINNINGCONDS: return std::string("aiTrainingData/pictures/winningconds");
	}
}

DataExtractorPerTile::DataExtractorPerTile() :resizer(), distr()
{
	counts[SKY] = returnDirCount(return_name(SKY).c_str());
	counts[MARIO] = returnDirCount(return_name(MARIO).c_str());
	counts[BLOCK] = returnDirCount(return_name(BLOCK).c_str());
	counts[ENEMY] = returnDirCount(return_name(ENEMY).c_str());
	counts[ITEM] = returnDirCount(return_name(ITEM).c_str());
	counts[WINNINGCONDS] = returnDirCount(return_name(WINNINGCONDS).c_str());
}

bool DataExtractorPerTile::createTrainDataFromArray(int ergarray[GRIDRADIUS][GRIDRADIUS])
{
	for (int xgrid = 0; xgrid < GRIDRADIUS; xgrid++) {
		for (int ygrid = 0; ygrid < GRIDRADIUS; ygrid++) {
			int data = ergarray[xgrid][ygrid];
			if (counts[data] < MAX_DATA_COUNT) {
				std::string name(return_name(data));
				name += "/pic" + std::to_string(counts[data]) + ".png";
				int xstart = xgrid * TILESIZE;
				int xend = xgrid * TILESIZE + TILESIZE -1;
				int ystart = ygrid * TILESIZE;
				int yend = ygrid * TILESIZE + TILESIZE -1;
				resizer.resizer(distr.grab_resized_img(), name.c_str(), xstart, ystart,
					xend, yend);
				counts[data]++;
			}
		}
	}
	return is_finished();
}


bool DataExtractorPerTile::is_finished() {
	int fin_count = 0;
	for (int i = 0; i < LABELS; i++) {
		if (counts[LABELS] >= MAX_DATA_COUNT-1) {
			fin_count + 1;
		}
	}
	return fin_count >= 6;
}
