#include "ProxyManager.h"

namespace proxy {

	ID ProxyManager::manageProxy(std::shared_ptr<Proxy> proxy) {
		const ID proxy_id = this->current_proxy_id;
		this->proxy_map[proxy_id] = proxy;
        std::cout << "Hello" << std::endl;
		this->current_proxy_id++;
		return proxy_id;
	}

	void ProxyManager::unmanageProxy(ID id) {
		this->proxy_map.erase(id);
	}

	std::shared_ptr<Proxy> ProxyManager::getProxy(ID id) {
		return proxy_map[id];
	}

	// Uses the "Singleton" design pattern to ensure only one instance of the ProxyManager ever exists.
	std::shared_ptr<ProxyManager> ProxyManager::getProxyManager() {
		if (!instance) {
            instance = std::make_shared<ProxyManager>();
			return instance;
		}
		return instance;
	}

}
