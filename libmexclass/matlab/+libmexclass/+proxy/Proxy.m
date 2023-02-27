classdef Proxy < matlab.mixin.indexing.RedefinesDot & handle

    properties
        % C++ Proxy ID.
        ID (1,1) uint64;
        % C++ Proxy Name.
        Name (1,1) string;
    end

    methods

        function obj = Proxy(options)
            arguments
                options.ID (1,1) uint64
                options.Name (1,1) string
                options.ConstructorArguments (1,:) cell
            end

            if ~isfield(options, "Name")
                error("libmexclass:proxy:NoName", "The name of a registered C++ Proxy must be specified when constructing a Proxy instance.");
            end

            obj.Name = options.Name;

            if isfield(options, "ID")
                obj.ID = options.ID;
            else
                if ~isfield(options, "ConstructorArguments")
                    error("libmexclass:proxy:NoConstructorArguments", """ConstructorArguments"" must be specified when constructing a new Proxy instance.");
                else
                    % Create the an instance of the specified C++ Proxy class and return its
                    % Proxy ID To be stored on the MATLAB Proxy object.
                    obj.ID = libmexclass.proxy.gateway("Create", obj.Name, options.ConstructorArguments);
                end
            end
        end

        % Destroy the proxy upon destruction.
        function delete(obj)
            % Destroy the corresponding C++ Proxy instance when destroying
            % the MATLAB object.
            libmexclass.proxy.gateway("Destroy", obj.ID);
        end
    end

    methods (Access=protected)
        function varargout = dotReference(obj,indexOp)
            if indexOp(1).Type == "Dot" && indexOp(2).Type == "Paren"
                op1 = indexOp(1);
                methodArgs = indexOp(2).Indices;
                methodName = string(op1.Name);
                [varargout{1:nargout}] = libmexclass.proxy.gateway("MethodCall", obj.ID, methodName, methodArgs);
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
