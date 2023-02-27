classdef Car

    properties (Dependent)
        Make (1,1) string
        Model (1,1) string
        Color (1,1) string
        Speed (1,1) uint64
        Headlights (1,1) logical
    end

    properties (Access=private)
        Proxy
    end

    methods
        function obj = Car(make, model, color)
            obj.Proxy = libmexclass.proxy.Proxy("Name", "example.proxy.Car", "ConstructorArguments", {make, model, color});
        end

        function Accelerate(obj)
            obj.Proxy.Accelerate();
        end

        function Decelerate(obj)
            obj.Proxy.Decelerate();
        end

        function Stop(obj)
            obj.Proxy.Stop();
        end

        function obj = set.Headlights(obj, value)
            obj.Proxy.Headlights(logical(value));
        end

        function obj = set.Speed(obj, value)
            obj.Proxy.SetSpeed(uint64(value));
        end

        function value = get.Speed(obj)
            value = obj.Proxy.GetSpeed();
        end

        function value = get.Make(obj)
            value = obj.Proxy.GetMake();
        end

        function value = get.Model(obj)
            value = obj.Proxy.GetModel();
        end

        function value = get.Color(obj)
            value = obj.Proxy.GetColor();
        end

        function Print(obj)
            obj.Proxy.Print();
        end

    end
end
