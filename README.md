# raspberry-stm32
Develope stm32 on the raspberry pi 3

#��������
��ݮ�ɰ��������߱༭���룬���룬ͨ��stm32flash���ص�stm32��flash�У�ʵ�����߱��stm32,���Ի��ڴ˿�����ݮ�ɣ�stm32һЩ��Ȥ����Ŀ��

## Ӳ��
	1. ��ݮ�ɣ� B+

	2. stm32������

	3. �Ű��ߣ���

## ��ݮ���ϵ����
	1. ��ݮ�ɰ�װ��ϵͳ����ssh��¼

	2. stm32flash

	3. arm-none-eabi-gcc

##����װ����
�ڽ������²���ǰ�ȱ�֤��ݮ�ɣ�����������stm32���������������������uart���á�

### 1. stm32flash��װ
	1).����Դ��

	https://sourceforge.net/projects/stm32flash/files/?source=navbar

	2). ����Ŀ¼�����룬��װ��Ĭ�ϰ�װ��/usr/local/binĿ¼�£�����б�Ҫ�Ļ����˼��뵽PATH�м���
	
	$ make

	$ sudo make install

	3). ���԰�װ�����ִ��stm32flash���ӡ������Ϣ

	$ stm32flash

### 2. ��ݮ�ɣ���������
��ݮ�ɣ�ϵͳĬ��ʹ�ô���0��Ϊ�����豸ͨ�Žӿڣ������Ҫ�������ã�����ʹ�ô������س���stm32�ϡ�

	1). �ر��ն˴��ڵ��ԣ��ͷŴ���0��ִ��raspi-config,�߼���������رյ��Դ��ڣ����Կ�/boot/cmdline.txt���鿴consle=�ǲ����Ѿ�����serial0��

	$ raspi-config

	2). �޸�/boot/config.txt, ������´��룺 
	
	dtoverlay=pi3-miniuart-bt
	enable_uart=1

	3). �����󼴿�ʹ�ô���0�������ڵ���/dev/serial0, ���֮ǰ����ݮ�ɰ汾��̫һ�����ɲ���/dev/ttyAMA0

### 3. Ӳ������
	

