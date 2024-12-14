#include "OLED_I2C.h"

OLED_I2C::OLED_I2C(PinName SDA_PIN, PinName SCL_PIN, uint8_t I2C_ADDRESS) : _myOLED(SDA_PIN, SCL_PIN)
{
    OLED_ADDRESS = I2C_ADDRESS << 1;
    // _myOLED.frequency(400000);
}

void OLED_I2C::send_command(uint8_t COMMAND)
{
    char data[2] = {0x00, COMMAND};
    _myOLED.write(OLED_ADDRESS, data, 2);
}

void OLED_I2C::send_data(uint8_t DATA)
{
    char buffer[2] = {0x40, DATA};
    _myOLED.write(OLED_ADDRESS, buffer, 2);
}

void OLED_I2C::init_OLED()
{
    _myOLED.frequency(400000); // 400kHzの通信速度に設定

    // 初期化コマンド
    send_command(0xAE);  // ディスプレイOFF
    send_command(0xD5);  // クロック分周比/オシレータ周波数
    send_command(0x80);
    send_command(0xA8);  // マルチプレクス比設定
    send_command(0x3F);
    send_command(0xD3);  // ディスプレイオフセット
    send_command(0x00);
    send_command(0x40);  // ディスプレイスタートライン
    send_command(0x8D);  // 電荷ポンプ
    send_command(0x14);
    send_command(0x20);  // メモリモード
    send_command(0x00);
    send_command(0xA1);  // セグメント再マップ
    send_command(0xC8);  // 出力スキャン方向
    send_command(0xDA);  // COMピンハードウェア設定
    send_command(0x12);
    send_command(0x81);  // コントラスト設定
    send_command(0xCF);
    send_command(0xD9);  // プリチャージ期間
    send_command(0xF1);
    send_command(0xDB);  // VCOMHディセレクトレベル
    send_command(0x40);
    send_command(0xA4);  // ディスプレイ全体ON
    send_command(0xA6);  // ノーマルディスプレイ
    send_command(0xAF);  // ディスプレイON

    set_cursor(0,0);
}

int OLED_I2C::test_OLED()
{
    int i2c_error_code = _myOLED.write(OLED_ADDRESS, 0x00, 1, false);
    return i2c_error_code;
}

void OLED_I2C::clear_all()
{
    for (int i = 0; i < OLED_WIDTH * OLED_HEGHT / 8; i++){
        send_data(0x00);
    }
}

void OLED_I2C::fill_all()
{
    for (int i= 0; i< OLED_WIDTH * OLED_HEGHT / 8; i++){
        send_data(0xFF);
    }
}

void OLED_I2C::set_cursor(uint8_t POINT_X, uint8_t POINT_Y)
{
    send_command(0xB0 + POINT_Y);
    send_command(0x00 + (POINT_X & 0x0F));
    send_command(0x10 + ((POINT_X >> 4) & 0x0F));
}

void OLED_I2C::draw_char(char CHAR_DATA, bool FILL_TEXT)
{
    if (FILL_TEXT){
        send_data(0xFF);
        for (uint8_t i = 0; i < 5; i++){
            send_data(~(OLED_I2C::FONT5x8[CHAR_DATA-32][i]));
        }
        send_data(0xFF);
    }
    else{
        send_data(0x00);
        for (uint8_t i = 0; i < 5; i++){
            send_data(OLED_I2C::FONT5x8[CHAR_DATA-32][i]);
        }
        send_data(0x00);
    }
}

void OLED_I2C::draw_text(const char *TEXT, uint8_t POINT_X, uint8_t POINT_Y, bool FILL_TEXT)
{
    if (FILL_TEXT){
        set_cursor(POINT_X, POINT_Y);
        while(*TEXT){
            draw_char(*TEXT++, true);
        }
    }
    else{
        set_cursor(POINT_X, POINT_Y);
        while(*TEXT){
            draw_char(*TEXT++, false);
        } 
    }
}

void OLED_I2C::draw_QR(uint8_t POINT_X, uint8_t POINT_Y)
{
    for (int num_y = 0; num_y < 5; num_y++)
    {
        for (int num_x = 0; num_x < 5; num_x++)
        {
            set_cursor(num_x * 8 + POINT_X, num_y + POINT_Y);

            for (int i = 0; i < 8; i++)
            {
                send_data(OLED_I2C::qr_data[num_x + 5 * num_y][i]);
            }
        }
    }
}

void OLED_I2C::debug_OLED()
{
    printf("%d\n", test_OLED());

    draw_text("PAGE 1", 80, 0);
    draw_text("COPYRIGHT", 0, 0);
    draw_text("Shun", 10, 6);
    draw_text("Yotsuya", 30, 7);

    draw_text("git", 100, 7);
    draw_QR(90,2);
}