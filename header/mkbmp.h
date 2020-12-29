#pragma once
#include <stdint.h>

#define FILE_TYPE 0x4D42    /**< "BM"�����g���G���f�B�A���ŉ��߂����l */
#define FILE_HEADER_SIZE 14 /**< BMP�t�@�C���w�b�_�T�C�Y */
#define INFO_HEADER_SIZE 40 /**< Windows�w�b�_�T�C�Y */
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)
/**< �W���̃w�b�_�T�C�Y */


#pragma pack(2)
typedef struct BITMAPFILEHEADER {
	uint16_t bfType;         /**< �t�@�C���^�C�v�A�K��"BM" */
	uint32_t bfSize;         /**< �t�@�C���T�C�Y */
	uint16_t bfReserved1;    /**< ���U�[�u */
	uint16_t bfReserved2;    /**< ���T�[�u */
	uint32_t bfOffBits;      /**< �擪����摜���܂ł̃I�t�Z�b�g */
} BITMAPFILEHEADER;
#pragma pack()
#pragma pack(2)
typedef struct BITMAPINFOHEADER {
	uint32_t biSize;         /**< ���̍\���̂̃T�C�Y */
	int32_t biWidth;         /**< �摜�̕� */
	int32_t biHeight;        /**< �摜�̍��� */
	uint16_t biPlanes;       /**< �摜�̖����A�ʏ�1 */
	uint16_t biBitCount;     /**< ��F�̃r�b�g�� */
	uint32_t biCompression;  /**< ���k�`�� */
	uint32_t biSizeImage;    /**< �摜�̈�̃T�C�Y */
	int32_t biXPelsPerMeter; /**< �摜�̉������𑜓x��� */
	int32_t biYPelsPerMeter; /**< �摜�̏c�����𑜓x���*/
	uint32_t biClrUsed;      /**< �J���[�p���b�g�̂������ۂɎg���Ă���F�̌� */
	uint32_t biClrImportant; /**< �J���[�p���b�g�̂����d�v�ȐF�̐� */
} BITMAPINFOHEADER;
#pragma pack()

typedef struct BITMAPCOLORPALET {
	uint8_t rgbBlue;         /**< �� 0 �` 255 */
	uint8_t rgbGreen;        /**< �� 0 �` 255 */
	uint8_t rgbRed;          /**< �� 0 �` 255 */
	uint8_t rgbReserved;     /**< �\��̈� 0 */
} BITMAPCOLORPALET;

void mkbmp(int suf, int label, double *data);
uint32_t ByteOrdeChange32(uint32_t _v);
uint16_t ByteOrdeChange16(uint16_t _v);
