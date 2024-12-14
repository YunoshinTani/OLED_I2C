#ifndef OLED_I2C_H
#define OLED_I2C_H

#include <mbed.h>

/**
 * @brief OLEDディスプレイを制御するためのクラス
 */
class OLED_I2C
{
public:
    /**
     * @brief コンストラクタ
     *
     * @param SDA_PIN I2CのSDAピン
     * @param SCL_PIN I2CのSCLピン
     * @param I2C_ADDRESS I2Cアドレス
     */
    OLED_I2C(PinName SDA_PIN, PinName SCL_PIN, uint8_t I2C_ADDRESS);

    /**
     * @brief コマンドを送る
     *
     * @param COMMAND コマンドの内容
     */
    void send_command(uint8_t COMMAND);

    /**
     * @brief データを送る
     *
     * @param DATA DATAの内容
     */
    void send_data(uint8_t DATA);

    /**
     * @brief OLEDディスプレイ初期化
     */
    void init_OLED();

    /**
     * @brief OLEDディスプレイの接続状態確認
     * 
     * @return OLEDディスプレイの接続状態(0:正常, それ以外:異常)
     */
    int test_OLED();

    /**
     * @brief 画面に表示しているのを全て消す
     * 
     * @note 一回だとすべて消えないことがある？
     */
    void clear_all();

    /**
     * @brief 画面を全て表示で埋めれる
     * 
     * @note draw_textのFILL_TEXTをtrue(文字と背景を反転させる)と組み合わせると黒文字,色背景ができる
     */
    void fill_all();

    /**
     * @brief コンストラクタ
     *
     * @param TEXT 表示したいテキストのポインタ
     * @param POINT_X テキストの開始のX座標
     * @param POINT_Y テキストの開始のY座標
     * @param FILL_TEXT 文字と背景を反転させるか
     * 
     * @note FILL_TEXT = true は選択されていることを示すことに使ったりもできる
     */
    void draw_text(const char *TEXT, uint8_t POINT_X, uint8_t POINT_Y, bool FILL_TEXT = false);

    /**
     * @brief コンストラクタ
     *
     * @param POINT_X QRコード左上のx座標
     * @param POINT_Y QRコード左上のy座標
     */
    void draw_QR(uint8_t POINT_X, uint8_t POINT_Y);

    /**
     * @brief デバッグ用関数
     */
    void debug_OLED();

private:
    /**
     * @brief I2C通信用オブジェクト
     */
    I2C _myOLED;

    /**
     * @brief OLEDディスプレイのI2Cアドレス(mbedのとっての)
     */
    uint8_t OLED_ADDRESS;

    /**
     * @brief OLEDディスプレイの横ドット数
     */
    #define OLED_WIDTH 128

    /**
     * @brief OLEDディスプレイの縦ドット数
     */
    #define OLED_HEGHT 64

    /**
     * @brief カーソルを指定
     *
     * @param POINT_X カーソルのX座標
     * @param POINT_Y カーソルのY座標
     */
    void set_cursor(uint8_t POINT_X, uint8_t POINT_Y);

    /**
     * @brief char型の値をディスプレイに表示
     *
     * @param CHAR_DATA 表示するchar型のデータ
     * @param FILL_TEXT 文字と背景を反転するか
     */
    void draw_char(char CHAR_DATA, bool FILL_TEXT = false);

    /**
     * @brief 英数字のフォントデータ
     */
    const uint8_t FONT5x8[91][5] = {
        {0x00, 0x00, 0x00, 0x00, 0x00},  // スペース ' '
        {0x00, 0x00, 0x5F, 0x00, 0x00},  // '!'
        {0x00, 0x07, 0x00, 0x07, 0x00},  // '"'
        {0x14, 0x7F, 0x14, 0x7F, 0x14},  // '#'
        {0x24, 0x2A, 0x7F, 0x2A, 0x12},  // '$'
        {0x23, 0x13, 0x08, 0x64, 0x62},  // '%'
        {0x36, 0x49, 0x55, 0x22, 0x50},  // '&'
        {0x00, 0x05, 0x03, 0x00, 0x00},  // '''
        {0x00, 0x1C, 0x22, 0x41, 0x00},  // '('
        {0x00, 0x41, 0x22, 0x1C, 0x00},  // ')'
        {0x14, 0x08, 0x3E, 0x08, 0x14},  // '*'
        {0x08, 0x08, 0x3E, 0x08, 0x08},  // '+'
        {0x00, 0x50, 0x30, 0x00, 0x00},  // ','
        {0x08, 0x08, 0x08, 0x08, 0x08},  // '-'
        {0x00, 0x60, 0x60, 0x00, 0x00},  // '.'
        {0x20, 0x10, 0x08, 0x04, 0x02},  // '/'
        {0x3E, 0x51, 0x49, 0x45, 0x3E},  // '0'
        {0x00, 0x42, 0x7F, 0x40, 0x00},  // '1'
        {0x42, 0x61, 0x51, 0x49, 0x46},  // '2'
        {0x21, 0x41, 0x45, 0x4B, 0x31},  // '3'
        {0x18, 0x14, 0x12, 0x7F, 0x10},  // '4'
        {0x27, 0x45, 0x45, 0x45, 0x39},  // '5'
        {0x3C, 0x4A, 0x49, 0x49, 0x30},  // '6'
        {0x01, 0x71, 0x09, 0x05, 0x03},  // '7'
        {0x36, 0x49, 0x49, 0x49, 0x36},  // '8'
        {0x06, 0x49, 0x49, 0x29, 0x1E},  // '9'
        {0x00, 0x36, 0x36, 0x00, 0x00},  // ':'
        {0x00, 0x56, 0x36, 0x00, 0x00},  // ';'
        {0x08, 0x14, 0x22, 0x41, 0x00},  // '<'
        {0x14, 0x14, 0x14, 0x14, 0x14},  // '='
        {0x00, 0x41, 0x22, 0x14, 0x08},  // '>'
        {0x02, 0x01, 0x51, 0x09, 0x06},  // '?'
        {0x32, 0x49, 0x79, 0x41, 0x3E},  // '@'
        {0x7E, 0x11, 0x11, 0x11, 0x7E},  // 'A'
        {0x7F, 0x49, 0x49, 0x49, 0x36},  // 'B'
        {0x3E, 0x41, 0x41, 0x41, 0x22},  // 'C'
        {0x7F, 0x41, 0x41, 0x22, 0x1C},  // 'D'
        {0x7F, 0x49, 0x49, 0x49, 0x41},  // 'E'
        {0x7F, 0x09, 0x09, 0x09, 0x01},  // 'F'
        {0x3E, 0x41, 0x49, 0x49, 0x7A},  // 'G'
        {0x7F, 0x08, 0x08, 0x08, 0x7F},  // 'H'
        {0x00, 0x41, 0x7F, 0x41, 0x00},  // 'I'
        {0x20, 0x40, 0x41, 0x3F, 0x01},  // 'J'
        {0x7F, 0x08, 0x14, 0x22, 0x41},  // 'K'
        {0x7F, 0x40, 0x40, 0x40, 0x40},  // 'L'
        {0x7F, 0x02, 0x0C, 0x02, 0x7F},  // 'M'
        {0x7F, 0x04, 0x08, 0x10, 0x7F},  // 'N'
        {0x3E, 0x41, 0x41, 0x41, 0x3E},  // 'O'
        {0x7F, 0x09, 0x09, 0x09, 0x06},  // 'P'
        {0x3E, 0x41, 0x51, 0x21, 0x5E},  // 'Q'
        {0x7F, 0x09, 0x19, 0x29, 0x46},  // 'R'
        {0x46, 0x49, 0x49, 0x49, 0x31},  // 'S'
        {0x01, 0x01, 0x7F, 0x01, 0x01},  // 'T'
        {0x3F, 0x40, 0x40, 0x40, 0x3F},  // 'U'
        {0x1F, 0x20, 0x40, 0x20, 0x1F},  // 'V'
        {0x3F, 0x40, 0x38, 0x40, 0x3F},  // 'W'
        {0x63, 0x14, 0x08, 0x14, 0x63},  // 'X'
        {0x03, 0x04, 0x78, 0x04, 0x03},  // 'Y'
        {0x61, 0x51, 0x49, 0x45, 0x43},  // 'Z'
        {0x00, 0x7F, 0x41, 0x41, 0x00},  // '['
        {0x02, 0x04, 0x08, 0x10, 0x20},  // '\'
        {0x00, 0x41, 0x41, 0x7F, 0x00},  // ']'
        {0x04, 0x02, 0x01, 0x02, 0x04},  // '^'
        {0x40, 0x40, 0x40, 0x40, 0x40},  // '_'
        {0x01, 0x02, 0x04, 0x00, 0x00},  // '`'
        {0x20, 0x54, 0x54, 0x54, 0x78},  // 'a'
        {0x7F, 0x48, 0x44, 0x44, 0x38},  // 'b'
        {0x38, 0x44, 0x44, 0x44, 0x20},  // 'c'
        {0x38, 0x44, 0x44, 0x48, 0x7F},  // 'd'
        {0x38, 0x54, 0x54, 0x54, 0x18},  // 'e'
        {0x08, 0x7E, 0x09, 0x01, 0x02},  // 'f'
        {0x08, 0x14, 0x54, 0x54, 0x3C},  // 'g'
        {0x7F, 0x08, 0x04, 0x04, 0x78},  // 'h'
        {0x00, 0x44, 0x7D, 0x40, 0x00},  // 'i'
        {0x20, 0x40, 0x44, 0x3D, 0x00},  // 'j'
        {0x7F, 0x10, 0x28, 0x44, 0x00},  // 'k'
        {0x00, 0x41, 0x7F, 0x40, 0x00},  // 'l'
        {0x7C, 0x04, 0x18, 0x04, 0x78},  // 'm'
        {0x7C, 0x08, 0x04, 0x04, 0x78},  // 'n'
        {0x38, 0x44, 0x44, 0x44, 0x38},  // 'o'
        {0x7C, 0x14, 0x14, 0x14, 0x08},  // 'p'
        {0x08, 0x14, 0x14, 0x18, 0x7C},  // 'q'
        {0x7C, 0x08, 0x04, 0x04, 0x08},  // 'r'
        {0x48, 0x54, 0x54, 0x54, 0x20},  // 's'
        {0x04, 0x3F, 0x44, 0x40, 0x20},  // 't'
        {0x3C, 0x40, 0x40, 0x20, 0x7C},  // 'u'
        {0x1C, 0x20, 0x40, 0x20, 0x1C},  // 'v'
        {0x3C, 0x40, 0x30, 0x40, 0x3C},  // 'w'
        {0x44, 0x28, 0x10, 0x28, 0x44},  // 'x'
        {0x0C, 0x50, 0x50, 0x50, 0x3C},  // 'y'
        {0x44, 0x64, 0x54, 0x4C, 0x44},  // 'z'
    };

    /**
     * @brief QRコード表示のテスト用
     */
    const uint8_t qr_data[25][8] = {
        {0b01111111,0b01000001,0b01011101,0b01011101,0b01011101,0b01000001,0b01111111,0b00000000},
        {0b11010101,0b10111101,0b11100111,0b00001101,0b11100110,0b00011010,0b01000011,0b10110010},
        {0b01010000,0b00100101,0b01101000,0b10110010,0b01100100,0b10010010,0b11000111,0b10110110},
        {0b11101000,0b00001000,0b11000101,0b10001100,0b11101111,0b00000000,0b01111111,0b01000001},
        {0b01011101,0b01011101,0b01011101,0b01000001,0b01111111,0b00000000,0b00000000,0b00000000},

        {0b11010110,0b01100100,0b10100110,0b00001000,0b10001100,0b10100001,0b01010101,0b01101000},
        {0b00110010,0b11000111,0b00110000,0b01000101,0b11101000,0b11010010,0b00011111,0b01010111},
        {0b00011001,0b01010110,0b11110000,0b00110011,0b11111001,0b00100001,0b01000111,0b01100100},
        {0b00001011,0b01100110,0b01001100,0b01101000,0b00111000,0b01100010,0b00011111,0b11110100},
        {0b01000011,0b11011010,0b10100011,0b01011110,0b11010101,0b00000000,0b00000000,0b00000000},

        {0b10111001,0b11100110,0b01111010,0b10101110,0b10100100,0b10110111,0b01010101,0b01000101},
        {0b00010000,0b01001100,0b10011100,0b11111111,0b00111101,0b00100110,0b11001111,0b10100010},
        {0b10011101,0b01111101,0b00100101,0b00100000,0b11001100,0b10001100,0b00111100,0b10000111},
        {0b00100000,0b11110001,0b01011101,0b11101111,0b00101010,0b01010101,0b00010101,0b10110100},
        {0b00110001,0b11101100,0b00110111,0b01101001,0b11010101,0b00000000,0b00000000,0b00000000},

        {0b11000001,0b01011101,0b01001110,0b01011100,0b01001101,0b01010010,0b11010101,0b00000001},
        {0b10110011,0b01110111,0b11001010,0b10101110,0b01111101,0b01110000,0b10110111,0b00110010},
        {0b11110001,0b00110001,0b10110110,0b10010011,0b11101010,0b01010011,0b11001101,0b11111101},
        {0b10010101,0b00110101,0b00010100,0b10110100,0b11111100,0b00011000,0b01010110,0b00011011},
        {0b11110111,0b11110100,0b01001100,0b10110100,0b11000100,0b00000000,0b00000000,0b00000000},

        {0b00011111,0b00010000,0b00010111,0b00010111,0b00010111,0b00010000,0b00011111,0b00000000},
        {0b00000000,0b00000101,0b00011010,0b00011111,0b00000100,0b00001100,0b00000011,0b00010000},
        {0b00010000,0b00010011,0b00000001,0b00011100,0b00001001,0b00011101,0b00001111,0b00010000},
        {0b00011010,0b00000101,0b00001011,0b00000011,0b00011101,0b00000101,0b00001011,0b00010101},
        {0b00011001,0b00011010,0b00000011,0b00000000,0b00011100,0b00000000,0b00000000,0b00000000}
    };
};

#endif //OLED_I2C_H