classdef Proxy < matlab.mixin.indexing.RedefinesDot
    properties
        ID uint64;
    end

    methods
        function obj = Proxy(varargin)
            % Get the metaclass info for the concrete
            % Proxy subclass that is being created.
            % The classname is used to automatically select the
            % corresponding C++ Proxy instance to create.
            classInfo = metaclass(obj);
            packageName = string(classInfo.ContainingPackage.Name);
            classNameWithPackage = string(classInfo.Name);
            proxyName = extractAfter(classNameWithPackage, packageName + ".");

            % Create the corresponding C++ Proxy instance and return it's
            % Proxy ID To be stored on the MATLAB Proxy object.
            obj.ID = gateway("Create", proxyName, varargin);
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