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

std::shared_ptr<Proxy> ProxyManager::getProxy(ID id) {
    auto proxy_key_value = ProxyManager::singleton.proxy_map.find(id);
    if (proxy_key_value != ProxyManager::singleton.proxy_map.end()) {
        return proxy_key_value->second;
    } else {
        return nullptr;
    }
}

ProxyManager ProxyManager::singleton{};
} // namespace libmexclass::proxy
