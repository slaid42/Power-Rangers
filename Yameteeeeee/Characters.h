#pragma once
#include <SDL.h>
#include "Graphics.h"
#include <unordered_map>

class Character {
private:
	const char *name;
	SDL_Color color;
	std::map<const char*, Image> im_holder;
public:
	Character(const char* _name, SDL_Color _color) {
		name = _name;
		color = _color;
	}
	Character(const Character& other) {
		name = other.name;
		color = other.color;
		im_holder = other.im_holder;
	}
	void Change_Color(SDL_Color other) {
		color = other;
	}
	~Character() {
		delete name;
	}
	Character& operator=(const Character& other) {
		name = other.name;
		color = other.color;
		im_holder = other.im_holder;
		return *this;
	};
	const char* get_name() {
		return name;
	}
	void AddImage(const char* v_name, Image im) {
		im_holder.insert(std::make_pair(v_name, im));
	}
	void DeleteImage(const char* v_name) {
		im_holder.erase(v_name);
	}
	void Appear(const char* im_name) {
		im_holder[im_name].Load();
	}
	void Disappear(const char* im_name) {
		im_holder[im_name].Disappear();
	}
};
