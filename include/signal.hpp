#ifndef banana_signal_hpp
#define banana_signal_hpp

#include <functional>
#include <list>

template<class... TS>
struct Signal
{
	typedef std::function<void(TS...)> fun_type;
	typedef typename std::list<fun_type>::iterator handle_type;

	void emit(TS&... args)
	{
		for(auto& h : handlers)
			h(args...);
	}

	handle_type connect(fun_type f)
	{
		handle_type ret = handlers.end();
		handlers.push_back(f);
		return ret;
	}

	void remove(handle_type h)
	{
		handlers.erase(h);
	}

	// Signal(Signal&&) = default;
	// Signal& operator=(Signal&&) = default;

private:
	std::list<fun_type> handlers;
};

#endif