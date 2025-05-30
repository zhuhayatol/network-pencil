import serial # type: ignore
import serial.tools.list_ports # type: ignore
import numpy as np # type: ignore
import tensorflow as tf # type: ignore
from tensorflow.keras.models import load_model # type: ignore
DEF_TITLE_STRING = 'IMU\n'
DEF_MODEL_NAME = 'model.h5'
DEF_BAUD_RATE = 921600
DEF_N_ROWS = 60

motion_name = ['Zero' , 'One', 'Two', 'Three', 'Four', 'Five', 'Six', 'Seven', 'Eight', 'Nine']

port_list = list(serial.tools.list_ports.comports())

#鏄剧ず鎵€鏈夊彲鐢ㄤ覆鍙�
#Show all the port avaliable on current device
def show_all_com():
    index = 0
    port_list_name = []
    if len(port_list) <= 0:
        print("the serial port can't find!")
    else:
        for itms in port_list:
            index += 1
            print(index,':',list(itms)[0], list(itms)[1])
            port_list_name.append(itms.device)

    return port_list_name

#璇锋眰鐢ㄦ埛鏍规嵁绱㈠紩鍊奸€夋嫨骞跺垵濮嬪寲涓€涓覆鍙�
#Ask a index number for serial port from user and initializes it.
def Serial_init():
    port_avaliable = show_all_com()
    port_avaliable_size = len(port_avaliable)
    index = int(input("\nChoose a port:"))
    
    #
    while index > port_avaliable_size or index <= 0:
        if  index > port_avaliable_size or index <= 0:
            print("Invalid Input.Check and try again")
            index = int(input("Choose a port:"))
            
    print(f"\nSerial port",port_avaliable[index - 1],f"initalized successfully.\nBaud rate:{DEF_BAUD_RATE} Byte size:8  Parity:None  Stop bit:1")
    
    return serial.Serial(port=port_avaliable[index - 1],
                                baudrate=DEF_BAUD_RATE,
                                bytesize=serial.EIGHTBITS,
                                parity=serial.PARITY_NONE,
                                stopbits=serial.STOPBITS_ONE,
                                timeout=0.5) 
    
#妫€鏌ユ暟鎹覆鍙ｆ暟鎹爣棰樻槸鍚︾鍚堝畾涔夌殑鏍囬锛屾暟鎹殑鏍囬鍙互淇敼DEF_TITLE_STRING
#Check if the title from recerived data same as DEF_TITLE_STRING.
def Check_Title(Received_String):
    i = 0
    Title_Buffer = ''
    while Received_String[i] != '\n':
        Title_Buffer += Received_String[i]
        i += 1
    Title_Buffer+='\n'
    if(Title_Buffer == DEF_TITLE_STRING):
        return True
    else:
        return False
    
#浠庢暟鎹爣棰樹箣鍚庤鍓嚭鍙敤鐨勬暟鎹�
#Cut off the tiltle from recerived data.
def IMU_String(Received_String):
        return Received_String[len(DEF_TITLE_STRING)::1]
    
def Str2Array(str):
    # 灏嗗瓧绗︿覆鍒嗗壊鎴愯
    lines = str.split('\n')

    # 浣跨敤鍒楄〃鎺ㄥ寮忓皢姣忎竴琛岃浆鎹负鍒楄〃锛屽苟鍙栫1鍒椼€佺2鍒楀拰绗�3鍒�
    data_list = [list(map(float, [line.split()[0], line.split()[1], line.split()[2]])) for line in lines if line.strip()]
    
    # 灏嗗垪琛ㄨ浆鎹负NumPy鏁扮粍
    data_array = np.array(data_list)
    data_array = np.array(data_list).T  # 杞疆鏁扮粍
    
    return data_array

# 瀹氫箟 num_classes
num_classes = len(motion_name)

model = load_model(DEF_MODEL_NAME)

def predict_motion(inputs_array):
    # 杞崲涓哄紶閲忓苟澧炲姞鎵规缁村害
    inputs_tensor = tf.convert_to_tensor(inputs_array, dtype=tf.float32)
    inputs_tensor = tf.expand_dims(inputs_array, axis=0)  # 鐜板湪褰㈢姸涓� (1, channels, time_steps)
    
    # 鐜板湪鍙互瀹夊叏鍦拌闂甶nputs
    outputs = model(inputs_tensor)
    print(outputs)
    index = 0
    temp = 0
    for i in range(0,12,1):
        if outputs[0][i] > temp:
            temp = outputs[0][i]
            index = i
    
    print(temp)
    if temp >= 0.90:
        return motion_name[index]
    else:
        return "Unrecognized"

# 涓诲嚱鏁�
def main():
    serial_using = Serial_init()
    user_input = 'y'
    while user_input == 'y':
        test_count = int(input("How many tests:"))
        while test_count >= 0:
            received = serial_using.readall().decode("ASCII")
            if len(received) != 0 and Check_Title(received):
                test_string = IMU_String(received)
                inputs_array = Str2Array(test_string)
                inputs_array = inputs_array.T
                print(predict_motion(inputs_array))
                test_count -= 1
        user_input = input("Again? (y/n)")
    print("Bye!")

main()
