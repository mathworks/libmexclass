classdef Custom
% Example Top-Level Client class which wraps a concrete MATLAB Proxy subclass.
% This MATLAB wrapper class provides an extra layer of indirection on top
% of direct proxy calls - making it easy to do pre/post-processing of data
% moving from MATLAB <-> C++, as well as allowing for writing more input /
% output validation logic in MATLAB code.
    properties (Access=private)
        Proxy (1,1) example.CustomProxy;
    end

    methods
        function obj = Custom()
            obj.Proxy = example.CustomProxy();
        end
        % Wrapper function allows for pre/post-processing of
        % inputs/outputs.
        function msg = increment(obj)

            % Call the Proxy.
            msg = obj.Proxy.Foo();

            % Post process the Proxy method call results.
            msg = str2double(extractAfter(msg, "State = "));
        end
    end
end