%% Basic Read Sensor Data
% This example shows how to retrieve data from a sensor channel
% 			
% Requires at least one Fluigent sensor (Flow Unit or IPS)
%
% <matlab:edit('Fluigent_SDK_BasicReadSensorData') Open this M File>

%% ���� WebSocket �ͻ��˶���  
% �⣺https://github.com/jebej/MatlabWebSocket
% ����SimpleClient��
import SimpleClient;
% ���ӵ�������  
% ws_Client = SimpleClient('ws://localhost:3003');

% ����һ����ʱ������  (û������)
timerObj = timer('Name', 'myTimer','Period',2, 'TimerFcn', @myFunction, 'StartFcn', @start);  
  
% ������ʱ��  
timerObj.StartFcn = @start;  
start(timerObj);

% ����ص�����  
function start(~,~)  
    disp('Timer started!');  
    ws_Client = SimpleClient('ws://localhost:3003');
    while ~ws_Client.Status 
        fprintf('Failed to connect to the server. Trying again...\n');
        pause(1); % ��ͣ1����ٴγ�������
        ws_Client = SimpleClient('ws://localhost:3003'); 
    end
    % �������ȷ��websocekt��������
    ws_Client.send('sensor websocket connect');
end  
  
% ���嶨ʱ������ʱҪ���õĺ���  
function myFunction(~,~)  
    disp('Executing myFunction...');  
    if(ws_Client.Status == false)   
        fprintf('Failed to connect to the server. Trying again...\n');
        pause(1); % ��ͣ1����ٴγ�������
        ws_Client = SimpleClient('ws://localhost:3003'); 
        % �������ȷ��websocekt��������
        ws_Client.send('sensor websocket connect');
    end
end  
  


% ֮������λ����ָ����ƴ������ĸ��ֲ�������������ʼ������ȡ���رյȺ�����д��simpleclient�ļ���onTextMessage����������

