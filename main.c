#include <avr/io.h>
#include <util/delay.h>

#define BTN_DIR  DDRB &=~ _BV(PB3)
#define BTN_HIGH PINB &   _BV(PB3)

#define PC2ON_DIR  DDRB &=~ _BV(PB0)
#define PC2ON_HIGH PINB &   _BV(PB0)

#define LINE_DIR  DDRB  |=  _BV(PB4)
#define LINE_HIGH PORTB |=  _BV(PB4)
#define LINE_LOW  PORTB &=~ _BV(PB4)

#define PC1LED_DIR  DDRB  |=  _BV(PB2)
#define PC1LED_HIGH PORTB |=  _BV(PB2)
#define PC1LED_LOW  PORTB &=~ _BV(PB2)

#define PC2LED_DIR  DDRB  |=  _BV(PB1)
#define PC2LED_HIGH PORTB |=  _BV(PB1)
#define PC2LED_LOW  PORTB &=~ _BV(PB1)

volatile uint8_t bt_state=0;

void pcled(void) {
	if( PC2ON_HIGH ) {
		PC1LED_LOW;
		PC2LED_HIGH;
	} else {
		PC1LED_HIGH;
		PC2LED_LOW;
	}
}

int main(void) {
	BTN_DIR;
	PC2ON_DIR;

	LINE_DIR;
	LINE_HIGH;

	PC1LED_DIR;
	PC1LED_HIGH;

	PC2LED_DIR;
	PC2LED_HIGH;

	_delay_ms(500);

	PC1LED_LOW;
	PC2LED_LOW;

    for(;;){

		if( BTN_HIGH ) {
			bt_state=1;

		} else {
			if( bt_state == 1 ) {
				LINE_LOW;
				_delay_ms(10);
				LINE_HIGH;
				for(uint8_t i=0;i<=5;i++) {
					PC1LED_HIGH; PC2LED_HIGH;
					_delay_ms(30);
					PC1LED_LOW; PC2LED_LOW;
					_delay_ms(30);
				}
				pcled();
				for(uint8_t i=0;i<=3;i++) {
					PC1LED_LOW; PC2LED_LOW;
					_delay_ms(100);
					pcled();
					_delay_ms(100);
				}

			}
			bt_state = 0;
		}
		pcled();
		_delay_ms(10);
    }
    return 0;
}

