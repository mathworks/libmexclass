#pragma once

#include "libmexclass/proxy/method/Context.h"
#include "libmexclass/proxy/method/Name.h"
#include "libmexclass/proxy/method/Method.h"
#include "libmexclass/proxy/method/Object.h"

#include <functional>
#include <unordered_map>

// Macro used for registering methods as callable on oncrete Proxy subclasses.
#define REGISTER_METHOD(class, method) methods[#method] = std::bind(&class::method, this, std::placeholders::_1)

// TODO: Consider if its possible to make use of this templated method instead of a macro.
/*
   template<typename T>
   void registerMethod(const libmexclass::proxy::method::Name& name, void (T::*t)(const libmexclass::proxy::method::Context&)) {
   std::function<void(const libmexclass::proxy::method::Context&)> f = std::bind(t, this, std::placeholders::_1);
   methods[name] = f;
   }
*/ 

namespace libmexclass::proxy {
	class Proxy {
		public:
            Proxy() : methods{} { }
			void invoke(libmexclass::proxy::method::Method& method);
        protected:
            std::unordered_map<libmexclass::proxy::method::Name, libmexclass::proxy::method::Object> methods;
	};
}
