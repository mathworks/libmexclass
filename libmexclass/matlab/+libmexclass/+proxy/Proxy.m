classdef Proxy < matlab.mixin.indexing.RedefinesDot
    properties
        ID uint64;
    end

    methods
        function obj = Proxy(varargin)
            % Create the corresponding C++ Proxy instance and return it's
            % Proxy ID To be stored on the MATLAB Proxy object.
            obj.ID = gateway("Create", string(class(obj)), varargin);
        end

        % Delete the proxy upon destruction.
        function delete(obj)
            % Delete the corresponding C++ Proxy instance when destroying
            % the MATLAB object.
            gateway("Delete", obj.ID);
        end
    end

    methods (Access=protected)
        function varargout = dotReference(obj,indexOp)
            if indexOp(1).Type == "Dot" && indexOp(2).Type == "Paren"
                op1 = indexOp(1);
                methodArgs = indexOp(2).Indices;
                methodName = string(op1.Name);
                [varargout{1:nargout}] = gateway("MethodCall", obj.ID, methodName, methodArgs);
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
