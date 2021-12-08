#pragma once
class Game_Engine;
class Scene;

SDL_Event NULL_EVENT;


struct ActionValues
{
	Characters* characters;
	ValuesHolder* values_holder;
	Scene* this_scene;
	SDL_Event event;

	ActionValues(Characters* characters_a, ValuesHolder* vh_a, Scene* sc, SDL_Event event_a):
		characters(characters_a), values_holder(vh_a), this_scene(sc), event(event_a)
	{

	}
}; 




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
	std::function<EngineInstruction(ActionValues&)> action;
	Uint32 trigger;


public:
	Action(Uint32 trigger_a,  std::function<EngineInstruction(ActionValues&)> action_a = [](ActionValues& act) -> EngineInstruction {})
		: action(action_a), trigger(trigger_a) {}
		 
	
	Uint32 get_trigger()
	{
		return trigger;
	}


	virtual EngineInstruction do_action(ActionValues& act_val)
	{
		return action(act_val);
	}


};




class PermAction
{
private:
	std::function<EngineInstruction(Game_Engine&, SDL_Event)> action;
	Uint32 trigger;
public:
	PermAction(Uint32 trigger_a, std::function<EngineInstruction(Game_Engine&, SDL_Event event)> action_a = [](Game_Engine& arg, SDL_Event ev) -> EngineInstruction {}): trigger(trigger_a), action(action_a)
	{

	}
	Uint32 get_trigger()
	{
		return trigger;
	}

	std::function<void(Game_Engine&, SDL_Event)> get_action()
	{
		return action;
	}
	EngineInstruction do_action(Game_Engine& eng, SDL_Event ev)
	{
		return action(eng, ev);
	}

};

