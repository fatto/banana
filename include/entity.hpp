#ifndef banana_entity_hpp
#define banana_entity_hpp

#include <list>
#include <cstddef>

template <class T>
struct Entity
{
	void update(float t, float dt)
	{
		static_cast<T*>(this)->on_update(t, dt);
	}
	void draw()
	{
		static_cast<T*>(this)->on_draw();
	}
protected:
	void on_update(float, float) { }
	void on_draw() { }
};

template <class T>
struct EntityList
{
private:
	static std::list<T*> entity_list;
public:
	EntityList()
	{
		entity_list.push_back(static_cast<T*>(this));
	}
	~EntityList()
	{
		entity_list.remove(static_cast<T*>(this));
	}
	template <class F>
	static void for_each(F f)
	{
		for(T* e : entity_list)
			f(*e);
	}
	static void updateEach(float t, float dt)
	{
		for(T* e : entity_list)
			e->on_update(t, dt);
	}
	static void drawEach()
	{
		for(T* e : entity_list)
			e->on_draw();
	}
	static size_t size()
	{
		return entity_list.size();
	}
};

template <class T> std::list<T*> EntityList<T>::entity_list;

#endif
