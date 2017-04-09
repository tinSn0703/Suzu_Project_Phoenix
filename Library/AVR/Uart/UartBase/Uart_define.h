
#pragma once

//bit UCSRA
#define RXC  7		//��M�����t���O
#define TXC	 6		//���M�����t���O
#define UDRE 5		//���M�f�[�^�󂫃��W�X�^�t���O
#define FE	 4		//�t���[�~���O�ُ�t���O
#define DOR  3		//�f�[�^�I�[�o�[�����t���O
#define UPE  2		//�p���e�B���t���O
#define U2X  1		//�{������
#define MPCM 0		//�����v���Z�b�T�ʐM����

//bit UCSRB
#define RXCIE 7		//��M�������荞�݋���
#define TXCIE 6		//���M�������荞�݋���
#define UDRIE 5		//���M�f�[�^���W�X�^�󂫊��荞�݋���
#define RXEN  4		//��M����
#define TXEN  3		//���M����
#define UCSZ2 2		//�f�[�^�r�b�g���I��2
#define RXB8  1		//��M�f�[�^�r�b�g8
#define TXB8  0		//���M�f�[�^�r�b�g8

//bit UCSRC
#define UMSEL1 7	//USART����I��1
#define UMSEL0 6	//USART����I��0
#define UPM1   5	//�p���e�B�I��1
#define UPM0   4	//�p���e�B�I��0
#define USBS   3	//��~�r�b�g�I��
#define UCSZ1  2	//�f�[�^�r�b�g���I��1
#define UCSZ0  1	//�f�[�^�r�b�g���I��0
#define UCPOL  0	//�N���b�N�ɐ��I��

