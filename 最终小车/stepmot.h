#ifndef  _StepMot_H_
#define  _StepMot_H_

/**左边电机**/
//函数功能：以指定速度运行
//说明：speed为速度，其单位为：转/分
void MotRun(INT16U );

//函数功能：停止电机
void MotStop(void);

///**左边电机**/
////函数功能：以指定速度运行
////说明：speed为速度，其单位为：转/分
void LMotRun(INT16U );
//
////函数功能：停止电机
//void RMotStop(void);

#endif   //_StepMot_H_