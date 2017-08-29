#ifndef		__EWINV_DEFINE_
#define		__EWINV_DEFINE_

#define igbt_pwm_freq   8000

typedef union
{
	float	dword;			/* float word : 32bit */
	struct
	{
		int word0;		/* ���� 16��Ʈ(least siginificant word) */
		int word1;		/* ���� 16��Ʈ(most siginificant word) */
	} word;	
	struct
	{
		unsigned byte0	:8;	/* LSB */
		unsigned byte1	:8;
		unsigned byte2	:8;	/* sign + MSB */
		unsigned byte3	:8;	/* exponent */
	} byte;
} union32;

typedef struct {
	int Cmd;
	int Address;
	float Data;
} CMD_MSG;


#endif
