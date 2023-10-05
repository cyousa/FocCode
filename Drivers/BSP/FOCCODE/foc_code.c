#include "foc_code.h"
#include "math.h"


float Aangle_Now;


float Ksp;
float cos_value,sin_value;//一次PWM周期只算一次

float Ualpha,Ubata;
float Uq,Ud; 
float Vbus;
void Park_change_Contrary()//Park逆变换
{
	cos_value=arm_cos_f32(Aangle_Now);
	sin_value=arm_sin_f32(Aangle_Now);
	Ksp=17320.5f/Vbus;
	
	Ualpha=Ud*cos_value-Uq*sin_value;
	Ubata= Uq*cos_value+Ud*sin_value;
	
}


float Id_ref ,Iq_ref;
void Park_change(float Ia,float Ib,float angel)//Park变换
{
	
		Id_ref=Ia*cos_value+Ib*sin_value;
		Iq_ref=-Ia*sin_value+Ib*cos_value;
	
}

float Ua,Ub,Uc;
void Klark_change_Contrary()//克拉克逆变换
{
	Ua=Ualpha;
	Ub=(1.7320508f*Ubata-Ualpha)/2.f;
	Uc=(-Ualpha-1.7320508f*Ubata)/2.f;
	
}

float I_ref_ahp,I_ref_beta;
void Klark_change(float Ia,float Ib,float Ic)
{
	I_ref_ahp=Ia;
	I_ref_beta=0.5774f*Ia+1.1547f*Ib;	
}


float ta,tb,tc;
uint8_t sector;
void sector_judg()
{
	float u1,u2,u3;
	float t0,t1,t2,t3,t4,t5,t6,t7;
	u1=Ubata;
	u2=squrt3*Ualpha/2.f-Ubata/2.f;
	u3=-squrt3*Ualpha/2.f-Ubata/2.f;
		
	sector=(u1>0.0)+((u2>0.0)<<1)+((u3>0.0)<<2);	
	float X=Ksp*Ubata;
	float Y=Ksp*(-(squrt3/2.0f)*Ualpha-0.5f*Ubata);
	float Z=Ksp*((squrt3/2.0f)*Ualpha-0.5f*Ubata);

	if(sector==3)//第1扇区
	{
			t4=Z;
			t6=X;		
			t7=(PWM_Max-t4-t6)/2;
			ta=t4+t6+t7;
			tb=t6+t7;
			tc=t7;
	}
	if(sector==1)//第2扇区
	{	
			t2=-Z;
			t6=-Y;
			t7=(PWM_Max-t2-t6)/2;
			ta=t6+t7;
			tb=t2+t6+t7;
			tc=t7;
	}
	if(sector==5)//第3扇区
	{	
			t2=X;
			t3=Y;		
			t7=(PWM_Max-t2-t3)/2;
			ta=t7;
			tb=t2+t3+t7;
			tc=t3+t7;
	}
	if(sector==4)//第4扇区
	{	
			t1=-X;
			t3=-Z;	
			t7=(PWM_Max-t1-t3)/2;
			ta=t7;
			tb=t3+t7;
			tc=t1+t3+t7;
	}
	if(sector==6)//第5扇区
	{	
			t1=Y;
			t5=Z;	
			t7=(PWM_Max-t1-t5)/2;
			ta=t5+t7;
			tb=t7;
			tc=t1+t5+t7;
	}
	if(sector==2)//第6扇区
	{	
			t4=-Y;
			t5=-X;	
			t7=(PWM_Max-t4-t5)/2;
			ta=t4+t5+t7;
			tb=t7;
			tc=t5+t7;
	}

}
void SVPWM()
{
	

	
	PWM_SetDuty_A((uint16_t)ta);
	PWM_SetDuty_B((uint16_t)tb);
	PWM_SetDuty_C((uint16_t)tc);
	

}

extern uint16_t ADC_DMA_data[60];
float Id_ref_last ,Iq_ref_last;
uint16_t Ib_sum;
uint16_t Ic_sum;
uint16_t Vbus_sum;
float Ic,Ib,Ia;
float Iq_sum,Iq_avarge;
uint8_t iq_count;
		void Current_sampling()
		{
				for (int i = 0; i < 60; i++)
				{
					if (i % 3 == 0) 
						{
							
							Ib_sum += ADC_DMA_data[i];
							
						} 
						else if (i % 3 == 1)
						{
							
							Ic_sum += ADC_DMA_data[i];
							
						} 
					else
					{						
							Vbus_sum += ADC_DMA_data[i];						
					}
				}
				
				Ib=((float)Ib_sum/20.0f/4096)*3.3-1.65f;
				Ic=((float)Ic_sum/20.0f/4096)*3.3-1.65f;
				Ia=-(Ib+Ic);
				Vbus=((float)Vbus_sum/20.0f/4096)*3.3f*11.f;
				Ib_sum=0;
				Ic_sum=0;
				Vbus_sum=0;	
				Klark_change(Ia,Ib,Ic);
			  Park_change(I_ref_ahp,I_ref_beta,Aangle_Now);//Park变换
				Id_ref=0.5f*Id_ref+0.5f*Id_ref_last;
				Iq_ref=0.5f*Iq_ref+0.5f*Iq_ref_last;
				
				Iq_sum+=Iq_ref;				
				iq_count++;
				if(iq_count==10)
				{
					Iq_avarge=Iq_sum/10;
					iq_count=0;
					Iq_sum=0;
				}
				
				Id_ref_last=Id_ref;
				Iq_ref_last=Iq_ref;
			}
 

float current_target_uq=0;
float kp_cur=2;
float	ki_cur=0;
float Ud_kp=7;
float Ud_ki;	
			float Uq_current_error;
			float Uq_current_error_sum;
			
			float Ud_current_error;
			float Ud_current_error_sum;
			
			float ud_target=0.6;
	void Current_loop()
	{
				
		Uq_current_error=current_target_uq-Iq_ref;
			
		if(Uq_current_error_sum>6.93) Uq_current_error_sum=6.93;
		if(Uq_current_error_sum<-6.93) Uq_current_error_sum=-6.93;
		Uq=Uq_current_error*kp_cur+Uq_current_error_sum*ki_cur;
		Uq_current_error_sum+=Uq_current_error;
		//Ud=ud_target;//(ud_target-Id_ref)*kp_cur;
		
		Ud_current_error=ud_target-Id_ref;
		
		if(Ud_current_error_sum>6.93) Ud_current_error_sum=6.93;
		if(Ud_current_error_sum<-6.93) Ud_current_error_sum=-6.93;
		Ud=Ud_current_error*Ud_kp+Ud_current_error_sum*Ud_ki;
		Ud_current_error_sum+=Ud_current_error;
	}		
	
	float target_position;
	float now_position;
	extern 	TIM_HandleTypeDef TIM_Encoder_init;
	float position_error;
	float position_kp=1;
	void Position_loop()
	{
			now_position=(short)__HAL_TIM_GET_COUNTER(&TIM_Encoder_init)*7/326.1146;
			position_error=position_kp*(target_position-now_position);
	
	}
	
	float target_speed=0.01;
	float now_speed;
	float speed_error;
	float speed_last_error;
	float speed_kp=1;
	float speed_out;
	
void Speed_loop()
	{
		now_speed=TIM1->CNT;//*7/326.1146;
		

	
	}