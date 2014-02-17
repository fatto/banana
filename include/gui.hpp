//
//  gui.hpp
//  banana
//
//  Created by Marco Fattorel on 11/02/14.
//  Copyright (c) 2014 Marco Fattorel. All rights reserved.
//

#ifndef banana_gui_hpp
#define banana_gui_hpp

#include "entity.hpp"
#define NANOVG_GL3_IMPLEMENTATION
#include "nanovg_gl3.h"

#include <chrono>
#include <string>

class Label : public Entity<Label>, public EntityList<Label>
{
	NVGcontext* vg;
	size_t x = 0, y = 0;
	std::string text;
public:
	void setContext(NVGcontext* _vg)
	{
		vg = _vg;
	}
	void on_draw()
	{
		nvgFontSize(vg, 18.0f);
		nvgFontFace(vg, "sans");
		nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
		nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
		nvgText(vg, x,y, text.c_str(), NULL);
	}
	void setText(const std::string& _text)
	{
		text = _text;
	}
	void setPosition(size_t _x, size_t _y)
	{
		x = _x;
		y = _y;
	}
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
	void setContext(NVGcontext* _vg)
	{
		vg = _vg;
	}
	void on_draw()
	{
		head = (head+1) % FPS_HISTORY_COUNT;
		float new_time = time();
		values[head] = new_time - current_time;
		current_time = new_time;

		size_t i, _head;
		float avg, w, h;

		avg = 0;
		_head = head;
		for (i = 0; i < 10; i++) {
			avg += values[head];
			_head = (head+FPS_HISTORY_COUNT-1) % FPS_HISTORY_COUNT;
		}
		avg /= 10.0f;

		w = 200;
		h = 30;

		nvgBeginPath(vg);
		nvgRect(vg, x,y, w,h);
		nvgFillColor(vg, nvgRGBA(0,0,0,128));
		nvgFill(vg);

		nvgBeginPath(vg);
		nvgMoveTo(vg, x, y+h);
		for (i = 0; i < FPS_HISTORY_COUNT; i++) {
			float v = 1.0f / (0.00001f + values[(head+i) % FPS_HISTORY_COUNT]);
			if (v > 80.0f) v = 80.0f;
			float vx = x + ((float)i/(FPS_HISTORY_COUNT-1)) * w;
			float vy = y + h - ((v / 80.0f) * h);
			nvgLineTo(vg, vx, vy);
		}
		nvgLineTo(vg, x+w, y+h);
		nvgFillColor(vg, nvgRGBA(255,192,0,128));
		nvgFill(vg);

		label.setText(std::to_string(1.f/avg) + " FPS");

		// nvgFontSize(vg, 18.0f);
		// nvgFontFace(vg, "sans");
		// nvgTextAlign(vg,NVG_ALIGN_RIGHT|NVG_ALIGN_MIDDLE);
		// nvgFillColor(vg, nvgRGBA(240,240,240,255));
		// sprintf(str, "%.2f FPS", 1.0f / avg);
		// nvgText(vg, x+w-5,y+h/2, str, NULL);
	}
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
	Label l;
	FPScounter fps;
	GuiData data;
public:
	Gui(size_t _width, size_t _height) : width(_width), height(_height)
	{
		vg = nvgCreateGL3(width, height, 1);
		assert(vg);
		data.init(vg);
		fps.setContext(vg);
		Label::for_each([this](Label& l) { l.setContext(vg); });
	}
	~Gui()
	{
		nvgDeleteGL3(vg);
	}
	void on_update(float t, float dt)
	{
	}
	void on_draw()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		// glEnable(GL_CULL_FACE);
		glDisable(GL_DEPTH_TEST);

		nvgBeginFrame(vg, width, height, 1);
		fps.draw();
		Label::drawEach();

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_BLEND);
	}
};


#endif