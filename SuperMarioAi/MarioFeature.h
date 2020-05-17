#pragma once
#include <string>
class MarioFeature
{
public:
	enum FeatureName {
		isUnderBlock, //2
		closestEnemyX, //GRIDRADIUS-1 TODO(Wenn Enemy unter Mario, ist gleich zu kein Gegner da)
		closestEnemyY, //GRIDRADIUS-1
		distanceToObstacle, //GRIDRADIUS-1
		numberOfEnemies, //siehe Define MAX_NUMBER_ENEMIES
		distanceToHole, //GRIDRADIUS-1
		itemAvailable, //2
		closestItemX, //GRIDRADIUS-1
		closestItemY, //GRIDRADIUS-1
		isJumping,
		obstacleHeight,
		isRightFromObstacle,
		isEnemyLeft,
		isHoleLeft,
		isAboveHole,//new //2
		size
	};

	MarioFeature() = default;
	constexpr MarioFeature(FeatureName feature) :feature(feature) {}
	MarioFeature(int i) { feature = FeatureName(i); }
	operator FeatureName() const { return feature; }
	explicit operator bool() = delete;
	//constexpr bool operator==(MarioFeature a)const { return feature == a.feature; }
	//constexpr bool operator!=(MarioFeature a)const { return feature != a.feature; }
	 std::string toString() const {
		std::string string;
		switch (feature)
		{
		case MarioFeature::closestEnemyX:
			string = "Enemy-X";
			break;
		case MarioFeature::closestEnemyY:
			string = "Enemy-Y";
			break;
		case MarioFeature::isUnderBlock:
			string = "Under Block";
			break;
		case MarioFeature::distanceToObstacle:
			string = "Obstacle Distance";
			break;
		case numberOfEnemies:
			string = "Number of Enemies";
			break;
		
		case distanceToHole:
			string = "Distance to Hole";
			break;
		case isJumping:
			string = "Is Jumping";
			break;
		case obstacleHeight:
			string = "Obstacle Height";
			break;
		case isHoleLeft:
			string = "Hole is Left";
			break;
		case isEnemyLeft:
			string = "Enemy is Left";
			break;
		case isRightFromObstacle:
			string = "Right from Obstacle";
			break;
		case isAboveHole:
			string = "Above Hole";
			break;
		case itemAvailable:
			string = "Item available";
			break;
		case closestItemX:
			string = "Item-X";
			break;
		case closestItemY:
			string = "Item-Y";
			break;
		default:
			string = "NULL";
			break;
		}
		return string;
	}
	 static std::string toString(int i) {
		 MarioFeature feature(i);
		 return feature.toString();
	 }
private:
	FeatureName feature;
};
