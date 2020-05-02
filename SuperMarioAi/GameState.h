#pragma once
#include <string>
class GameState
{
public:	
	enum  State{
		MarioAlive,
		GameOver,
		Win,
		MarioNotFound
	};
	GameState() = default;
	GameState(int i) { state = State(i); }
	constexpr GameState(State state) :state(state) {}
	operator State() const { return state; }
	explicit operator bool() = delete;

	//constexpr bool operator==(GameState a)const { return state == a.state; }
	//constexpr bool operator!=(GameState a)const { return state != a.state; }
	std::string toString() const {
		std::string string;
		switch (state)
		{
		case GameState::MarioAlive:
			string = "Mario Alive";
			break;
		case GameState::GameOver:
			string = "Game Over";
			break;
		case GameState::Win:
			string = "Win";
			break;
		case GameState::MarioNotFound:
			string = "Mario not found";
			break;
		default:
			string = "NULL";
			break;
		}
		return string;
	}
	static std::string toString(int i) {
		std::string string;
		switch (i)
		{
		case GameState::MarioAlive:
			string = "Mario Alive";
			break;
		case GameState::GameOver:
			string = "Game Over";
			break;
		case GameState::Win:
			string = "Win";
			break;
		case GameState::MarioNotFound:
			string = "Mario not found";
			break;
		default:
			string = "NULL";
			break;
		}
		return string;
	}
	static const int size = State::MarioNotFound + 1;
private:
	State state;
};
