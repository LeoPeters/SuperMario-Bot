#ifndef marioaction_h
#define marioaction_h
#include <string>
class MarioAction {
public:
	enum ActionName {
	moveRight,
	jumpRight,
	jump,
	moveLeft,
	shoot,
	size
	};
	MarioAction() = default;
	constexpr MarioAction(ActionName action) :action(action) {}
	MarioAction(int i)  {action = ActionName(i); }
	operator ActionName() const { return action;}
	explicit operator bool() = delete;
	//bool operator==(MarioAction a)const { return action == a.action; }
	//constexpr bool operator!=(MarioAction a)const { return action != a.action; }

	std::string toString() const {
		std::string string;
		switch (action)
		{
		case MarioAction::moveRight:
			string = "Right";
			break;
		case MarioAction::jump:
			string = "Jump";
			break;
		case MarioAction::jumpRight:
			string = "Jump Right";
			break;
		case MarioAction::moveLeft:
			string = "Left";
			break;
		case MarioAction::shoot:
			string = "Shoot";
			break;
		default:
			string = "NULL";
			break;
		}
		return string;
	}
	static std::string toString(int i) {
		MarioAction action(i);
		return action.toString();
	}

private:
	ActionName action;
};
#endif