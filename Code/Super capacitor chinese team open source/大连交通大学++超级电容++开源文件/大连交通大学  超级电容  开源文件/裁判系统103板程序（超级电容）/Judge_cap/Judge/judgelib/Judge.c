#include "Judge.h"

uint8_t rbuff[255];
uint8_t HeaderData[20],ReceiveData[255];
uint8_t UpData[50];
int32_t fps;
int16_t datatype;
int JudgeFresh = 0;

int JudgeSendFresh = 0;
int imu_receive = 0;

#ifdef VERSION18

float ToJudgeData[3];
uint8_t ToJudgeMask;
uint8_t JudgeFreshSignal[9] = {0};

positon_t 				Judge_Position;
extGameRobotState_t     Judge_extGameRobotState;
extRobotHurt_t 			Judge_extRobotHurt;
extShootData_t			Judge_extShootData;
extPowerHeatData_t		Judge_extPowerHeatData;
extRfidDetect_t			Judge_extRfidDetect;
extGameResult_t			Judge_extGameResult;
extBuffMusk_t			Judge_extGetBuff;
extGameRobotPos_t		Judge_extGameRobotPos;
extShowData_t  			Judge_extShowData;

wl2data w2data;
wl4data w4data;

void UploadData(float data1,float data2,float data3,uint8_t mask){
	static uint8_t seq;
	if(seq == 255) seq = 0;
	seq++;
	UpData[0] 	= 0xA5;
	w2data.d 	= 13;
	UpData[1] 	= w2data.c[0];
	UpData[2] 	= w2data.c[1];
	UpData[3] 	= seq;
	Append_CRC8_Check_Sum(UpData,5);
	w2data.d 	= 0x0100;
	UpData[5] 	= w2data.c[0];
	UpData[6] 	= w2data.c[1];
	w4data.f 	= data1;
	UpData[7] 	= w4data.c[0];
	UpData[8] 	= w4data.c[1];
	UpData[9] 	= w4data.c[2];
	UpData[10] 	= w4data.c[3];
	w4data.f 	= data2;
	UpData[11] 	= w4data.c[0];
	UpData[12] 	= w4data.c[1];
	UpData[13] 	= w4data.c[2];
	UpData[14] 	= w4data.c[3];
	w4data.f 	= data3;
	UpData[15] 	= w4data.c[0];
	UpData[16] 	= w4data.c[1];
	UpData[17] 	= w4data.c[2];
	UpData[18] 	= w4data.c[3];
	UpData[19] 	= mask;
	Append_CRC16_Check_Sum(UpData,22);
	HAL_UART_Transmit_IT(&huart1,UpData,22);
}

void JudgeData(uint8_t data){
	static int HeaderIndex;
	static int dataIndex;
	static int InfoStartReceive;
	static int16_t datalength;
	static uint8_t packindex;
	if(data == 0xA5){
		HeaderIndex = 1;
		HeaderData[0] = data;
		InfoStartReceive = 0;
	}else{
		if(HeaderIndex < 5){
			HeaderData[HeaderIndex++] = data;
			if(HeaderIndex == 5 && Verify_CRC8_Check_Sum(HeaderData,5)){
				w2data.c[0] = HeaderData[1];
				w2data.c[1] = HeaderData[2];
				datalength = w2data.d;
				packindex = HeaderData[3];
				InfoStartReceive = 1;
				dataIndex = 5;
				memcpy(ReceiveData,HeaderData,5);
				return;
			}
		}
		if(InfoStartReceive){
			if(dataIndex < datalength+9){
				ReceiveData[dataIndex++] = data;
			}
			if(dataIndex == datalength+9){
				InfoStartReceive = 0;
				if(Verify_CRC16_Check_Sum(ReceiveData,datalength+9)){
					w2data.c[0] = ReceiveData[5];
					w2data.c[1] = ReceiveData[6];
					datatype = w2data.d;
					fps++;
					JudgeFresh = 1;
					switch(datatype){
						case 0x0001:{
							JudgeFreshSignal[0] = 1;
							memcpy(&Judge_extGameRobotState,&ReceiveData[7],sizeof(extGameRobotState_t));
							break;
						}
						case 0x0002:{
							JudgeFreshSignal[1] = 1;
							memcpy(&Judge_extRobotHurt,&ReceiveData[7],sizeof(extRobotHurt_t));
							break;
						}
						case 0x0003:{
							JudgeFreshSignal[2] = 1;
							memcpy(&Judge_extShootData,&ReceiveData[7],sizeof(extShootData_t));
							break;
						}
						case 0x0004:{
							JudgeFreshSignal[3] = 1;
							memcpy(&Judge_extPowerHeatData,&ReceiveData[7],sizeof(extPowerHeatData_t));
							break;
						}
						case 0x0005:{
							JudgeFreshSignal[4] = 1;
							memcpy(&Judge_extRfidDetect,&ReceiveData[7],sizeof(extRfidDetect_t));
							break;
						}
						case 0x0006:{
							JudgeFreshSignal[5] = 1;
							memcpy(&Judge_extGameResult,&ReceiveData[7],sizeof(extGameResult_t));
							break;
						}
						case 0x0007:{
							JudgeFreshSignal[6] = 1;
							memcpy(&Judge_extGetBuff,&ReceiveData[7],sizeof(extBuffMusk_t));
							break;
						}
						case 0x0008:{
							JudgeFreshSignal[7] = 1;
							memcpy(&Judge_extGameRobotPos,&ReceiveData[7],sizeof(extGameRobotPos_t));
							break;
						}
						case 0x0100:{
							JudgeFreshSignal[8] = 1;
							memcpy(&Judge_extShowData,&ReceiveData[7],sizeof(extShowData_t));
							break;
						}
					}
				}
			}
			
		}
	}
}

#endif

#ifdef VERSION17

float ToJudgeData[3];

tGameInfo 				Judge_GameInfo;
tRealBloodChangedData 	Judge_BloodData;
tRealShootData 			Judge_ShootData;
UpdateData 				Judge_UpdateData;


wl2data w2data;
wl4data w4data;

void UploadData(float data1,float data2,float data3){
	static uint8_t seq;
	if(seq == 255) seq = 0;
	seq++;
	UpData[0] 	= 0xA5;
	w2data.d 	= 13;
	UpData[1] 	= w2data.c[0];
	UpData[2] 	= w2data.c[1];
	UpData[3] 	= seq;
	Append_CRC8_Check_Sum(UpData,5);
	w2data.d 	= 0x0100;
	UpData[5] 	= w2data.c[0];
	UpData[6] 	= w2data.c[1];
	w4data.f 	= data1;
	UpData[7] 	= w4data.c[0];
	UpData[8] 	= w4data.c[1];
	UpData[9] 	= w4data.c[2];
	UpData[10] 	= w4data.c[3];
	w4data.f 	= data2;
	UpData[11] 	= w4data.c[0];
	UpData[12] 	= w4data.c[1];
	UpData[13] 	= w4data.c[2];
	UpData[14] 	= w4data.c[3];
	w4data.f 	= data3;
	UpData[15] 	= w4data.c[0];
	UpData[16] 	= w4data.c[1];
	UpData[17] 	= w4data.c[2];
	UpData[18] 	= w4data.c[3];
	Append_CRC16_Check_Sum(UpData,21);
	HAL_UART_Transmit_IT(&huart1,UpData,21);
}

void JudgeData(uint8_t data){
	static int HeaderIndex;
	static int dataIndex;
	static int InfoStartReceive;
	static int16_t datalength;
	static uint8_t packindex;
	if(data == 0xA5){
		HeaderIndex = 1;
		HeaderData[0] = data;
		InfoStartReceive = 0;
	}else{
		if(HeaderIndex < 5){
			HeaderData[HeaderIndex++] = data;
			if(HeaderIndex == 5 && Verify_CRC8_Check_Sum(HeaderData,5)){
				w2data.c[0] = HeaderData[1];
				w2data.c[1] = HeaderData[2];
				datalength = w2data.d;
				packindex = HeaderData[3];
				InfoStartReceive = 1;
				dataIndex = 5;
				memcpy(ReceiveData,HeaderData,5);
				return;
			}
		}
		if(InfoStartReceive){
			if(dataIndex < datalength+9){
				ReceiveData[dataIndex++] = data;
			}
			if(dataIndex == datalength+9){
				InfoStartReceive = 0;
				if(Verify_CRC16_Check_Sum(ReceiveData,datalength+9)){
					w2data.c[0] = ReceiveData[5];
					w2data.c[1] = ReceiveData[6];
					datatype = w2data.d;
					JudgeFresh = 1;
					fps++;
					switch(datatype){
						case 0x0001:{
							memcpy(&Judge_GameInfo,&ReceiveData[7],sizeof(tGameInfo));
							break;
						}
						case 0x0002:{
							memcpy(&Judge_BloodData,&ReceiveData[7],sizeof(tRealBloodChangedData));
							break;
						}
						case 0x0003:{
							memcpy(&Judge_ShootData,&ReceiveData[7],sizeof(tRealShootData));
							break;
						}
					}
				}
			}
		}
	}
}



#endif

