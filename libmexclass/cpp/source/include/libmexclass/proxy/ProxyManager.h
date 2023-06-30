#pragma once

#include "libmexclass/proxy/ID.h"
#include "libmexclass/proxy/Proxy.h"
#include "libmexclass/error/Error.h"

#include <memory>
#include <unordered_map>
#include <variant>

namespace libmexclass::proxy {

using ProxyResult = std::variant<std::shared_ptr<Proxy>, libmexclass::error::Error>;

// ProxyMangager
// Manages Proxy instances by placing them inside of a map which maps unique IDs
// to Proxy instances. NOTE: ProxyManager uses the "Singleton" design pattern to
// ensure there is only ever one ProxyManager instance.
class ProxyManager {
  public:
    static ID manageProxy(const std::shared_ptr<Proxy> &proxy);
    static void unmanageProxy(ID id);
    static ProxyResult getProxy(ID id);
    
    
    
    template <typename T = libmexclass::proxy::Proxy>
    static std::shared_ptr<T> getProxy(ID id) {
        auto proxy_key_value = ProxyManager::singleton.proxy_map.find(id);
        if (proxy_key_value == ProxyManager::singleton.proxy_map.end()) {
            return nullptr;
        }
        auto typed_proxy = std::dynamic_pointer_cast<T>(proxy_key_value->second);
        return typed_proxy;
    }
    
    template <>
    static std::shared_ptr<libmexclass::proxy::Proxy> getProxy(ID id) {
        auto proxy_key_value = ProxyManager::singleton.proxy_map.find(id);
        if (proxy_key_value == ProxyManager::singleton.proxy_map.end()) {
            return nullptr;
        }
        return proxy_key_value->second;
    }

  private:
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
};
} // namespace libmexclass::proxy
