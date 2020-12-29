#include <cstdio>
#include <memory.h>
#include <unistd.h>
#include <sys/stat.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "mkbmp.h"

void mkbmp(int suf, int label, double* data)
{

    BITMAPFILEHEADER header;
    BITMAPINFOHEADER info;
    BITMAPCOLORPALET palet;

    memset(&header, 0, sizeof(header));
    memset(&info, 0, sizeof(info));
    memset(&palet, 0, sizeof(palet));

    header.bfType = FILE_TYPE;         /**< ファイルタイプ、必ず"BM" */
    header.bfOffBits = FILE_HEADER_SIZE + INFO_HEADER_SIZE;      /**< 先頭から画像情報までのオフセット */
    info.biSizeImage = 28 * 28 * sizeof(palet);    /**< 画像領域のサイズ */
    header.bfSize = header.bfOffBits + info.biSizeImage;        /**< ファイルサイズ */

    info.biSize = INFO_HEADER_SIZE;         /**< この構造体のサイズ */
    info.biWidth = 28;         /**< 画像の幅 */
    info.biHeight = 28;        /**< 画像の高さ */
    info.biPlanes = 1;       /**< 画像の枚数、通常1 */
    info.biBitCount = 32;     /**< 一色のビット数 */
    info.biCompression = 0;  /**< 圧縮形式 */
    info.biXPelsPerMeter = 96; /**< 画像の横方向解像度情報 */
    info.biYPelsPerMeter = 96; /**< 画像の縦方向解像度情報*/
    info.biClrUsed = 0;      /**< カラーパレットのうち実際に使っている色の個数 */
    info.biClrImportant = 0; /**< カラーパレットのうち重要な色の数 */

    std::string folder = "bmp2";
    mkdir(folder.c_str(), 0777);

    std::ostringstream oss;
    oss << folder << "/"
        << std::setw(6) << std::setfill('0') << suf
        << "_" << label << ".bmp";
    std::ofstream ofs(oss.str());
    if (!ofs) {
        std::cerr << "file open error" << oss.str() << std::endl;
    }

    // bitmap を 作成 する
    ofs.write((const char*)&header, sizeof(header));
    ofs.write((const char*)&info, sizeof(info));

    for (int y = 27; y >= 0; --y)
    {
        for (int x = 0; x < 28; x++)
        {
            palet.rgbGreen = (uint8_t)(data[(28 * y) + x] * 256);
            palet.rgbBlue = (uint8_t)(data[(28 * y) + x] * 256);
            palet.rgbRed = (uint8_t)(data[(28 * y) + x] * 256);
            palet.rgbReserved = 0;
            ofs.write((const char*)&palet, sizeof(palet));
        }
    }
    // ファイル に 保存 する 
    ofs.close();
}

uint32_t ByteOrdeChange32(uint32_t _v) {
    return _v;
    //return
    //	((_v & 0xff) << (8 * 3)) +
    //	((_v & 0xff00) << (8 * 1)) +
    //	((_v & 0xff0000) >> (8 * 1)) +
    //	((_v & 0xff000000) >> (8 * 3));
}

uint16_t ByteOrdeChange16(uint16_t _v) {
    return _v;
    //return
    //	((_v & 0xff) << (8 * 1)) +
    //	((_v & 0xff00) >> (8 * 1));
}
