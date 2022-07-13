#pragma once

#include "proxy/Context.h"

namespace proxy {
	class Proxy {
		public:
			virtual void proxy(Context& context) = 0;
	};
}