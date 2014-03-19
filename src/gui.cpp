#include <GLFW/glfw3.h>
#include "gui.hpp"

#define NANOVG_GL3_IMPLEMENTATION
// #include "nanovg_gl3buf.h"
#include "nanovg_gl3.h"

void Label::setContext(NVGcontext* _vg)
{
	vg = _vg;
}
void Label::on_draw()
{
	nvgFontSize(vg, 18.0f);
	nvgFontFace(vg, "sans");
	nvgTextAlign(vg, NVG_ALIGN_RIGHT | NVG_ALIGN_MIDDLE);
	nvgFillColor(vg, nvgRGBA(240, 240, 240, 255));
	nvgText(vg, x,y, text.c_str(), NULL);
}
void Label::setText(const std::string& _text)
{
	text = _text;
}
void Label::setPosition(size_t _x, size_t _y)
{
	x = _x;
	y = _y;
}


void FPScounter::setContext(NVGcontext* _vg)
{
	vg = _vg;
}
void FPScounter::on_draw()
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
	label.setPosition(x+w-5, y+h/2);

	// nvgFontSize(vg, 18.0f);
	// nvgFontFace(vg, "sans");
	// nvgTextAlign(vg,NVG_ALIGN_RIGHT|NVG_ALIGN_MIDDLE);
	// nvgFillColor(vg, nvgRGBA(240,240,240,255));
	// sprintf(str, "%.2f FPS", 1.0f / avg);
	// nvgText(vg, x+w-5,y+h/2, str, NULL);
}


Gui::Gui(size_t _width, size_t _height) : width(_width), height(_height)
{
	vg = nvgCreateGL3(width, height, NVG_ANTIALIAS);
	assert(vg);
	data.init(vg);
	fps.setContext(vg);
	Label::for_each([this](Label& l) { l.setContext(vg); });
}
Gui::~Gui()
{
	nvgDeleteGL3(vg);
}
void Gui::on_update(float t, float dt)
{
}
void Gui::on_draw()
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// glEnable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);

	nvgBeginFrame(vg, width, height, 1.f, NVG_STRAIGHT_ALPHA);
	fps.draw();
	Label::drawEach();

	glEnable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}