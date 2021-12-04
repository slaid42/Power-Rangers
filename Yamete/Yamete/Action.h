#pragma once
class Game_Engine;
class Scene;

class EngineInstruction
{
private:
	const char* command;
public:
	EngineInstruction(const char* comm) : command(comm) {}

	const char* get_command()
	{
		return command;
	}

};

class Action
{
private:
	std::function<EngineInstruction(Characters& , ValuesHolder& , Scene* , SDL_Event)> action;
	SDL_EventType trigger;
public:
	Action(SDL_EventType trigger_a,std::function<EngineInstruction(Characters&, ValuesHolder&, Scene*, SDL_Event)> action_a = [](Characters& a, ValuesHolder& b, Scene* c, SDL_Event d) -> EngineInstruction {}) : action(action_a), trigger(trigger_a) {}
		 
	
	SDL_EventType get_trigger()
	{
		return trigger;
	}


	EngineInstruction do_action(Characters& a, ValuesHolder& b, Scene* c, SDL_Event d)
	{
		return action(a, b, c, d);
	}


};

class PermAction
{
private:
	std::function<EngineInstruction(Game_Engine&)> action;
	SDL_EventType trigger;
public:
	PermAction(SDL_EventType trigger_a, std::function<EngineInstruction(Game_Engine&)> action_a = [](Game_Engine& arg) -> EngineInstruction {}): trigger(trigger_a), action(action_a)
	{

	}
	SDL_EventType get_trigger()
	{
		return trigger;
	}

	std::function<void(Game_Engine&)> get_action()
	{
		return action;
	}
	EngineInstruction do_action(Game_Engine& eng)
	{
		return action(eng);
	}

};

