#pragma once
#include <SDL.h>
#include "Graphics.h"

class Character {
private:
	const char *name;
	SDL_Color color;
	Image image;
public:
	Character(const char* _name, SDL_Color _color, Image _image) {
		name = _name;
		color = _color;
		image = _image;
	}
	Character(const Character& other) {
		name = other.name;
		color = other.color;
		image = other.image;
	}
	Character(Character& other) = delete;
	void Change_Color(SDL_Color other) {
		color = other;
	}
	void Change_Image(Image other) {
		image = other;
	}
	~Character() {
		delete name;
	}
	Character& operator=(const Character& other) {
		name = other.name;
		color = other.color;
		image = other.image;
		return *this;
	};
	Character& operator=(Character& other) = delete;
	void Speak(const char* replic) {
		Game_text(replic);
	}
	void Appear() {
		image.Load();
	}
	void Disappear() {
		image.Disappear();
	}
};
