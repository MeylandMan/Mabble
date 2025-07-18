#pragma once

#include <sstream>

#define BIT(x) (1 << x)
#define BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

enum class EventType 
{
	None = 0,
	WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
	AppTick, AppUpdate, AppRender,
	KeyPressed, KeyReleased, KeyTyped,
	MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
};

enum EventCategory 
{
	None = 0,
	EventCategoryApplication = BIT(0),
	EventCategoryInput = BIT(1),
	EventCategoryKeyboard = BIT(2),
	EventCategoryMouse = BIT(3),
	EventCategoryMouseButton = BIT(4)
};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

class Event
{
public:
	virtual ~Event() = default;

	bool Handled = false;

	virtual EventType GetEventType() const = 0;
	virtual const char* GetName() const = 0;
	virtual int GetCategoryFlags() const = 0;
	virtual std::string ToString() const { return GetName(); }

	bool IsInCategory(EventCategory category)
	{
		return GetCategoryFlags() & category;
	}
};

class EventDispatcher
{
public:
	EventDispatcher(Ref<Event> event)
		: m_Event(event)
	{
	}

	// F will be deduced by the compiler
	template<typename T, typename F>
	bool Dispatch(const F& func)
	{
		if (m_Event->GetEventType() == T::GetStaticType())
		{
			m_Event->Handled |= func(static_cast<T&>(*m_Event));
			return true;
		}
		return false;
	}
private:
	Ref<Event> m_Event;
};

class EventQueue
{
public:
	using EventCallback = std::function<void(Ref<Event>)>;

	void PushEvent(Ref<Event> event)
	{
		m_EventQueue.push(event);
	}

	void ProcessEvents()
	{
		while (!m_EventQueue.empty())
		{
			auto event = m_EventQueue.front();
			m_EventQueue.pop();

			// Dispatch the event to the registered callback
			if (m_EventCallback)
			{
				m_EventCallback(event);
			}
		}
	}

	void SetEventCallback(const EventCallback& callback)
	{
		m_EventCallback = callback;
	}

private:
	std::queue<Ref<Event>> m_EventQueue;
	EventCallback m_EventCallback;
};

namespace fmt {
	template <>
	struct formatter<Nanonite::Event> {
		constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
			return ctx.begin();
		}

		template <typename FormatContext>
		auto format(const Nanonite::Event& e, FormatContext& ctx) const -> decltype(ctx.out()) {
			return fmt::format_to(ctx.out(), "{}", e.ToString());
		}
	};

	template <>
	struct formatter<Nanonite::Ref<Nanonite::Event>> {
		constexpr auto parse(format_parse_context& ctx) -> decltype(ctx.begin()) {
			return ctx.begin();
		}

		template <typename FormatContext>
		auto format(const Nanonite::Ref<Nanonite::Event>& e, FormatContext& ctx) const -> decltype(ctx.out()) {
			return fmt::format_to(ctx.out(), "{}", e->ToString());
		}
	};
}
