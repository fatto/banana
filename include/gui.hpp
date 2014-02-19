#ifndef banana_gui_hpp
#define banana_gui_hpp

#include "entity.hpp"
#include "nanovg.h"

#include <chrono>
#include <string>
#include <cassert>

class Label : public Entity<Label>, public EntityList<Label>
{
	NVGcontext* vg;
	size_t x = 0, y = 0;
	std::string text;
public:
	void setContext(NVGcontext* _vg);
	void on_draw();
	void setText(const std::string& _text);
	void setPosition(size_t _x, size_t _y);
};

class FPScounter : public Entity<FPScounter>
{
	static const size_t FPS_HISTORY_COUNT = 100;
	float values[FPS_HISTORY_COUNT] = { 0.f };
	size_t head = 0;
	float current_time = 0.f;
	NVGcontext* vg;
	size_t x = 5, y = 5;
	Label label;

	float time()
	{
		using timer = std::chrono::high_resolution_clock;
		
		static timer::time_point start = timer::now();
		const float ratio = float(timer::period::num)/float(timer::period::den);
		
		timer::time_point now = timer::now();
		
		return (now - start).count() * ratio;
	}
public:
	void setContext(NVGcontext* _vg);
	void on_draw();
};


class Gui : public Entity<Gui>
{
	struct GuiData
	{
		int fontNormal, fontBold;
		void init(NVGcontext* vg)
		{
			fontNormal = nvgCreateFont(vg, "sans", "assets/Roboto-Regular.ttf");
			assert(fontNormal != -1);
		}
	};

	NVGcontext* vg;
	size_t width, height;
	FPScounter fps;
	GuiData data;
public:
	Gui(size_t _width, size_t _height);
	~Gui();
	void on_update(float t, float dt);
	void on_draw();
};


#endif