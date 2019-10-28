#ifndef _JUDGE_H_
#define _JUDGE_H_

#include "stm32f1xx_hal.h"
#include "CRC.h"
#include <string.h>
#include "usart.h"

#define VERSION18

typedef union{
	uint8_t c[2];
	int16_t d;
	uint16_t ud;
}wl2data;

typedef union{
	uint8_t c[4];
	float f;
	uint32_t d;
}wl4data;

extern int JudgeSendFresh;


#ifdef VERSION18

typedef __packed struct {
	uint8_t validFlag;
	float x;
	float y;
	float z;
	float yaw; 
}positon_t;

//0x0001

typedef __packed struct {
	uint16_t stageRemianTime; 
	uint8_t gameProgress; 
	uint8_t robotLevel; 
	uint16_t remainHP; 
	uint16_t maxHP;
}extGameRobotState_t;

//0x0002

typedef __packed struct {
	uint8_t armorType : 4;
	uint8_t hurtType : 4; 
}extRobotHurt_t;

//0x0003

typedef __packed struct {
	uint8_t bulletType; 
	uint8_t bulletFreq; 
	float bulletSpeed;
}extShootData_t;

//0x0004

typedef __packed struct {
	float chassisVolt;
	float chassisCurrent; 
	float chassisPower;
	float chassisPowerBuffer; 
	uint16_t shooterHeat0; 
	uint16_t shooterHeat1;
}extPowerHeatData_t;

//0x0005

typedef __packed struct {
	uint8_t cardType;
	uint8_t cardIdx; 
}extRfidDetect_t;

//0x0006

typedef __packed struct {
	uint8_t winner; 
}extGameResult_t;

//0x0007
typedef __packed struct{
   uint16_t buffMusk;
}extBuffMusk_t;

//0x0008
typedef __packed struct{
    float    x;
    float    y;
    float    z;
    float    yaw;
}extGameRobotPos_t;

//0x0100

typedef __packed struct {
	float data1; 
	float data2; 
	float data3; 
	uint8_t mask; 
}extShowData_t;

extern positon_t 				Judge_Position;
extern extGameRobotState_t     	Judge_extGameRobotState;
extern extRobotHurt_t 			Judge_extRobotHurt;
extern extShootData_t			Judge_extShootData;
extern extPowerHeatData_t		Judge_extPowerHeatData;
extern extRfidDetect_t			Judge_extRfidDetect;
extern extGameResult_t			Judge_extGameResult;
extern extBuffMusk_t			Judge_extGetBuff;
extern extGameRobotPos_t		Judge_extGameRobotPos;
extern extShowData_t  			Judge_extShowData;

extern float ToJudgeData[3];
extern uint8_t ToJudgeMask;
extern uint8_t JudgeFreshSignal[9];

void UploadData(float data1,float data2,float data3,uint8_t mask);
void JudgeData(uint8_t data);

#endif

#ifdef VERSION17
typedef __packed struct
{
	uint8_t flag; //0无效 1有效
	float x;
	float y;
	float z;
	float compass;
}tLocData;

// 0x0001
typedef __packed struct
{
	uint32_t remainTime;
	uint16_t remainLifeValue;
	float realChassisOutV;
	float realChassisOutA;
	tLocData locData;
	float remainPower;
}tGameInfo;

//0x0002

typedef __packed struct
{
	uint8_t weakId:4;
	uint8_t way:4;
	uint16_t value;
}tRealBloodChangedData;

//0x0003
typedef __packed struct
{
	float realBulletShootSpeed;
	float realBulletShootFreq;
	float realGolfShootSpeed;
	float realGolfShootFreq;
}tRealShootData;

//0x0005

typedef __packed struct
{
	float data1;
	float data2;
	float data3;
}UpdateData;

extern tGameInfo 				Judge_GameInfo;
extern tRealBloodChangedData 	Judge_BloodData;
extern tRealShootData 			Judge_ShootData;
extern UpdateData 				Judge_UpdateData;

extern float ToJudgeData[3];

void UploadData(float data1,float data2,float data3);
void JudgeData(uint8_t data);

#endif

extern int imu_receive;

#endif


