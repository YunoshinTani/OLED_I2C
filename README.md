# OLED_I2C
有機ELディスプレイ(OLED Display)を制御するためのライブラリです。

# サンプルコード
```cpp
#include <mbed.h>
#include <OLED_I2C.h>

OLED_I2C myOLED(I2C_SDA, I2C_SCL, 0x3C);

int main()
{
    myOLED.init_OLED();
    myOLED.clear_all();

    while (true)
    {
        myOLED.debug_OLED();
    }
}
```