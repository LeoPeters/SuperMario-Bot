#pragma once
#include <string>
class MarioFeature
{
public:
	enum FeatureName {
		isUnderBlock,
		closestEnemyX,
		closestEnemyy,
		distanceToObstacleRight
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
		case MarioFeature::closestEnemyy:
			string = "Enemy-Y";
			break;
		case MarioFeature::isUnderBlock:
			string = "Under Block";
			break;
		case MarioFeature::distanceToObstacleRight:
			string = "Obstacle Distance";
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

	 static const int size = FeatureName::distanceToObstacleRight + 1;
private:
	FeatureName feature;
};
