#ifndef CFS_COM_EVENTSYSTEM_HPP
#define CFS_COM_EVENTSYSTEM_HPP

#include <unordered_map>
#include <string>
#include <functional>
#include <mutex>
#include <cfs/edar/LoggingService.hpp>

namespace cfs::edar
{
class EventSystem
{

    LOG4CXX_DECLARE_STATIC_LOGGER

 public:

    using EventHandler = std::function<void()>;

    EventSystem() = default;
    EventSystem(const EventSystem&) = default;
    EventSystem(EventSystem&&) = default;
    EventSystem& operator=(const EventSystem&) = default;
    EventSystem& operator=(EventSystem&&) = default;
    virtual ~EventSystem() = default;

    static void registerEventHandler(std::string event_id, EventHandler * handler);
    static void unregisterEventHandler(std::string event_id, EventHandler* handler);
    static void reportEvent(std::string event_id);
    template<typename... _args>
    static void raiseEvent(std::string event_id, _args&&... args);

protected:
private:

    static std::unordered_map<std::string, std::vector<EventHandler*>> s_handlers;
    static std::mutex s_mutex;

};

}

#endif

