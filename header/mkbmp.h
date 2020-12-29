#pragma once
#include <stdint.h>

#define FILE_TYPE 0x4D42    /**< "BM"をリトルエンディアンで解釈した値 */
#define FILE_HEADER_SIZE 14 /**< BMPファイルヘッダサイズ */
#define INFO_HEADER_SIZE 40 /**< Windowsヘッダサイズ */
#define DEFAULT_HEADER_SIZE (FILE_HEADER_SIZE + INFO_HEADER_SIZE)
/**< 標準のヘッダサイズ */


#pragma pack(2)
typedef struct BITMAPFILEHEADER {
	uint16_t bfType;         /**< ファイルタイプ、必ず"BM" */
	uint32_t bfSize;         /**< ファイルサイズ */
	uint16_t bfReserved1;    /**< リザーブ */
	uint16_t bfReserved2;    /**< リサーブ */
	uint32_t bfOffBits;      /**< 先頭から画像情報までのオフセット */
} BITMAPFILEHEADER;
#pragma pack()
#pragma pack(2)
typedef struct BITMAPINFOHEADER {
	uint32_t biSize;         /**< この構造体のサイズ */
	int32_t biWidth;         /**< 画像の幅 */
	int32_t biHeight;        /**< 画像の高さ */
	uint16_t biPlanes;       /**< 画像の枚数、通常1 */
	uint16_t biBitCount;     /**< 一色のビット数 */
	uint32_t biCompression;  /**< 圧縮形式 */
	uint32_t biSizeImage;    /**< 画像領域のサイズ */
	int32_t biXPelsPerMeter; /**< 画像の横方向解像度情報 */
	int32_t biYPelsPerMeter; /**< 画像の縦方向解像度情報*/
	uint32_t biClrUsed;      /**< カラーパレットのうち実際に使っている色の個数 */
	uint32_t biClrImportant; /**< カラーパレットのうち重要な色の数 */
} BITMAPINFOHEADER;
#pragma pack()

typedef struct BITMAPCOLORPALET {
	uint8_t rgbBlue;         /**< 青 0 ～ 255 */
	uint8_t rgbGreen;        /**< 緑 0 ～ 255 */
	uint8_t rgbRed;          /**< 赤 0 ～ 255 */
	uint8_t rgbReserved;     /**< 予約領域 0 */
} BITMAPCOLORPALET;

void mkbmp(int suf, int label, double *data);
uint32_t ByteOrdeChange32(uint32_t _v);
uint16_t ByteOrdeChange16(uint16_t _v);
