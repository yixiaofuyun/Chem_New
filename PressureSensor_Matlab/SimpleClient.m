classdef SimpleClient < WebSocketClient
    %CLIENT Summary of this class goes here
    %   Detailed explanation goes here
    
    properties
        fgt_status = 0;
    end
    
    methods
        function obj = SimpleClient(varargin)
            %Constructor
            obj@WebSocketClient(varargin{:});
        end
    end
    
    methods (Access = protected)
        function onOpen(obj,message)
            % This function simply displays the message received
            fprintf('%s\n',message);
        end
        
        function onTextMessage(obj,message)
            % This function simply displays the message received
            fprintf('Message received:\n%s\n',message);
            % websocket�������Ӻ���λ�����ʹ�������ʼ���ź�
            if(message == "init")
              %% Initialize the session
                % This step is optional, if not called session will be automatically created
                fgt_init
                
              %% Get information about sensors and read them
                [sensorInfoArray, sensorTypeArray] = fgt_get_sensorChannelsInfo;
                % ������������USB��β��ԣ�ֻҪ����USBѹ��������ͬʱ���ڵ��������нű�
                % sensorInfoArray �����һ���豸һ���� SN=10774��Ӳ�����б�ע�� indexID=1.3863e+09
                % �ڶ����豸һ����SN = 10792��Ӳ�����б�ע�� indexID=1.3864e+09
                for i=1:numel(sensorInfoArray)
                    % SDK indices start at 0
                    sensorIndex = i-1;
                    fprintf('Sensor channel info at index: %d\n', sensorIndex);
                    disp(sensorInfoArray(i));
                    fprintf('Sensor type: %s\n', fgt_SENSOR_TYPE(sensorTypeArray(i)));
                end
                % Get measurement unit
                unit = fgt_get_sensorUnit(0); %�����豸ͬ���λ��ͬ
                % Get sensor range
                [minSensor, maxSensor] = fgt_get_sensorRange(0);
                fprintf('Range %.2f to %.2f %s\n', minSensor, maxSensor, unit);
                
                obj.send('sensor init finish');
                fprintf('fgt sensors init finish\n');
                
            end
            if(message == "start")
                obj.fgt_status = 1;
                % Read the sensor repeatedly
                while(obj.fgt_status == 1 && obj.Status == true)
                    % Get measurement unit
                    unit = fgt_get_sensorUnit(0); %�����豸ͬ���λ��ͬ
                    % ��ȡSN=10774�豸��ֵ��ֻҪSN���䣨Ҳ����䣩,fgt_get_sensorValue(0)���ǻ�ȡ���豸��ֵ
                    measurement1 = fgt_get_sensorValue(0);
                    % ��ȡSN=10792�豸��ֵ��ֻҪSN���䣨Ҳ����䣩,fgt_get_sensorValue(1)���ǻ�ȡ���豸��ֵ
                    measurement2 = fgt_get_sensorValue(1);
                    % ws ����
                    str1 = sprintf('A%.1f,B%.1f',measurement1,measurement2);
                    obj.send(str1);
                    fprintf('Measured sensor1 %.1f %s\nMeasured sensor2 %.1f %s\n', measurement1, unit, measurement2, unit);
                    pause(1);
                    
%                     str2 = sprintf('B%.2f',measurement2);
%                     obj.send(str2);
%                     fprintf('Measured sensor2 %.2f %s\n', measurement2, unit);
%                     pause(0.5);
                end

            end
            if(message == "stop")
                obj.fgt_status = 2;
            end
            if(message == "close")
              %% Close the session
                obj.fgt_status = 0;
                fgt_close
            end
        end
        
        function onBinaryMessage(obj,bytearray)
            % This function simply displays the message received
            fprintf('Binary message received:\n');
            fprintf('Array length: %d\n',length(bytearray));
        end
        
        function onError(obj,message)
            % This function simply displays the message received
            fprintf('Error: %s\n',message);
        end
        
        function onClose(obj,message)
            % This function simply displays the message received
            fprintf('%s\n',message);
        end
    end
end


