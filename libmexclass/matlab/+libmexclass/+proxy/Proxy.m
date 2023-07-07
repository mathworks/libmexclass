classdef Proxy < matlab.mixin.indexing.RedefinesDot & handle

    properties
        % C++ Proxy ID.
        ProxyID(1, 1) libmexclass.proxy.ProxyID;
        % C++ Proxy Name.
        Name (1,1) string;
    end

    methods

        function obj = Proxy(options)
            arguments
                options.ID (1,1) libmexclass.proxy.ProxyID {mustBeNonmissing}
                options.Name (1,1) string {mustBeNonmissing}
                options.ConstructorArguments (1,:) cell
            end

            if ~isfield(options, "Name")
                error("libmexclass:proxy:NoName", "The name of a registered C++ Proxy must be specified when constructing a Proxy instance.");
            end

            obj.Name = options.Name;

            if isfield(options, "ID")
                obj.ProxyID = options.ID;
            else
                if ~isfield(options, "ConstructorArguments")
                    error("libmexclass:proxy:NoConstructorArguments", """ConstructorArguments"" must be specified when constructing a new Proxy instance.");
                else
                    % Create the an instance of the specified C++ Proxy class and return its
                    % Proxy ID To be stored on the MATLAB Proxy object.
                    obj.ProxyID = libmexclass.proxy.gateway("Create", options.Name, options.ConstructorArguments);
                end
            end
        end

        % Destroy the proxy upon destruction.
        function delete(obj)
            % Destroy the corresponding C++ Proxy instance when destroying
            % the MATLAB object. ID may be empty if an error occured during
            % construction. If so, do not call destroy.
            if ~ismissing(obj.ProxyID)
                libmexclass.proxy.gateway("Destroy", obj.ProxyID.ID);
            end
        end
    end

    methods (Access=protected)
        function varargout = dotReference(obj,indexOp)
            if indexOp(1).Type == "Dot" && indexOp(2).Type == "Paren"
                op1 = indexOp(1);
                methodArgs = indexOp(2).Indices;
                methodName = string(op1.Name);
                [varargout{1:nargout}] = libmexclass.proxy.gateway("MethodCall", obj.ProxyID.ID, methodName, methodArgs);
            end
        end

        function obj = dotAssign(obj,indexOp,varargin)
            [obj.AddedFields.(indexOp)] = varargin{:};
        end

        function n = dotListLength(obj,indexOp,indexContext)
            n = listLength(obj.AddedFields,indexOp,indexContext);
        end
    end
end
