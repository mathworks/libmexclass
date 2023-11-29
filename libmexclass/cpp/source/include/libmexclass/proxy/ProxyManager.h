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
    

    // The next proxy id to hande out if recycled_ids is empty.
    ID current_proxy_id = 0;

    // A list of previously managed proxy ids that can be re-used.
    // If this deque is not empty, manageProxy removes ID at the
    // front of the deque to use as the next proxy ID.
    std::deque<ID> recycled_ids;

};

} // namespace libmexclass::proxy
