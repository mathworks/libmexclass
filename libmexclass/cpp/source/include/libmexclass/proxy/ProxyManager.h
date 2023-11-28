#pragma once

#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/error/Error.h"

#include <deque>
#include <memory>
#include <unordered_map>
#include <variant>

namespace libmexclass::proxy {

template <typename T>
using ProxyResult = std::variant<std::shared_ptr<T>, libmexclass::error::Error>;

// ProxyMangager
// Manages Proxy instances by placing them inside of a map which maps unique IDs
// to Proxy instances. NOTE: ProxyManager uses the "Singleton" design pattern to
// ensure there is only ever one ProxyManager instance.
class ProxyManager {
  public:
    static ID manageProxy(const std::shared_ptr<Proxy> &proxy);
    static void unmanageProxy(ID id);
    static std::shared_ptr<Proxy> getProxy(ID id);

    template <typename T>
    static ProxyResult<T> getTypedProxy(ID id) {
        auto proxy = libmexclass::proxy::ProxyManager::getProxy(id);
        if (!proxy) {
            std::string msg = "Invalid Proxy ID: " + std::to_string(id);
            return libmexclass::error::Error{"libmexclass:proxy:InvalidID", msg};
        }

        auto typed_proxy = std::dynamic_pointer_cast<T>(proxy);
        if (!typed_proxy) {
            std::string msg = "Failed to cast proxy to expected type";
            return libmexclass::error::Error{"libmexclass:proxy:InvalidProxyType", msg};
        }

        return typed_proxy;
    }

  private:
    ID getRecycledID();

    static ProxyManager singleton;
    // The internal map used to associate Proxy instances with unique IDs.
    std::unordered_map<ID, std::shared_ptr<Proxy>> proxy_map;
    
    // TODO: Consider whether it makes sense to "recycle" deleted IDs:
    //
    // 1. Whenever an ID is deleted, enqueue it into an queue of recycled IDs.
    // 2. The getNextId() method should first check if the queue has any
    //    recycled IDs in it. If so, dequeue the first one and use it.
    // 3. If the queue is empty, use the value of "current_id" and then
    //    increment it.
    ID current_proxy_id = 0;
    std::deque<ID> recycled_ids;

};

} // namespace libmexclass::proxy
