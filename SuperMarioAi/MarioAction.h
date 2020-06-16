#ifndef marioaction_h
#define marioaction_h
#include <string>
class MarioAction {
public:
	enum ActionName {
		right,
		jumpRight,
		left,
		jumpLeft,
		rightB,
		jumpRightB,
		leftB,
		jumpLeftB,
		jump,
		B,
		idle,
		down,
		size
	};
	MarioAction() = default;
	constexpr MarioAction(ActionName action) :action(action) {}
	MarioAction(int i) { action = ActionName(i); }
	operator ActionName() const { return action; }
	explicit operator bool() = delete;
	//bool operator==(MarioAction a)const { return action == a.action; }
	//constexpr bool operator!=(MarioAction a)const { return action != a.action; }

	std::string toString() const {
		std::string string;
		switch (action)
		{
		case MarioAction::right:
			string = "Right";
			break;
		case MarioAction::jumpRight:
			string = "Jump Right";
			break;
		case MarioAction::left:
			string = "Left";
			break;
		case MarioAction::jumpLeft:
			string = "Jump Left";
			break;
		case MarioAction::rightB:
			string = "Right B";
			break;
		case MarioAction::jumpRightB:
			string = "Jump Right B";
			break;
		case MarioAction::leftB:
			string = "Left B";
			break;
		case MarioAction::jumpLeftB:
			string = "Jump Left B";
			break;
		case MarioAction::jump:
			string = "Jump";
			break;
		case MarioAction::B:
			string = "B";
			break;
		case MarioAction::idle:
			string = "Idle";
			break;
		case MarioAction::down:
			string = "Down";
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