#pragma once
class Action
{
private:
	std::function<void(Characters&, ValuesHolder&, Scene*)> action;
	std::function<bool(SDL_EventType)> condition;
	SDL_EventType trigger;
public:
	Action(SDL_EventType trigger_a, std::function<void(Characters&, ValuesHolder&, Scene*)> action_a = [](Characters& a, ValuesHolder& b, Scene* c) {},
		std::function<bool(SDL_EventType)> condition_a = [](SDL_EventType a) {return true; }) : action(action_a), condition(condition_a), trigger(trigger_a) {}
  
};
