#include "libmexclass/proxy/ProxyManager.h"

namespace libmexclass::proxy {

ID ProxyManager::manageProxy(const std::shared_ptr<Proxy> &proxy) {
    const ID proxy_id = ProxyManager::singleton.current_proxy_id++;
    ProxyManager::singleton.proxy_map[proxy_id] = proxy;
    return proxy_id;
}

void ProxyManager::unmanageProxy(ID id) {
    ProxyManager::singleton.proxy_map.erase(id);
}

ProxyResult ProxyManager::getProxy(ID id) {
    auto proxy_key_value = ProxyManager::singleton.proxy_map.find(id);
    if (proxy_key_value->first == ProxyManager::singleton.proxy_map.end()) {
        const std::string msg = "Unknown Proxy ID: " + std::to_string(id);
        return libmexclass::error::Error{"libmexclass:proxy:UnknownID", msg};
    } else {
        return proxy_key_value->second;
    }
}

ProxyManager ProxyManager::singleton{};
} // namespace libmexclass::proxy
