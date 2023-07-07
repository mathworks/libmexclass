classdef ProxyID < matlab.mixin.Scalar

    properties(SetAccess=private, GetAccess=public)
        % C++ Proxy ID.
        ID = NaN
    end

    methods
        function obj = ProxyID(id)
            if nargin == 1
                validateattributes(id, {'numeric'}, ...
                    {'scalar', 'nonnegative', 'integer'});
                obj.ID = uint64(id);
            end
        end

        function tf = ismissing(obj)
            tf = ismissing(obj.ID);
        end
    end
end
