#![no_std]
#![no_main]

use ag_lcd::{Display, LcdDisplay};
use panic_halt as _;

#[arduino_hal::entry]
fn main() -> ! {
    let dp = arduino_hal::Peripherals::take().unwrap();
    let pins = arduino_hal::pins!(dp);

    let rs = pins.d8.into_output().downgrade();
    let en = pins.d9.into_output().downgrade(); // Can also use d11
    let d4 = pins.d4.into_output().downgrade();
    let d5 = pins.d5.into_output().downgrade();
    let d6 = pins.d6.into_output().downgrade();
    let d7 = pins.d7.into_output().downgrade();

    // Setting up LCD
    let delay = arduino_hal::Delay::new();
    let mut lcd: LcdDisplay<_, _> = LcdDisplay::new(rs, en, delay)
        .with_half_bus(d4, d5, d6, d7)
        .with_display(Display::On)
        .build();

    lcd.print("Hello, World");
    loop {}
}

// #![no_std]
// #![no_main]

// use panic_halt as _;

// #[arduino_hal::entry]
// fn main() -> ! {
    // let dp = arduino_hal::Peripherals::take().unwrap();
    // let pins = arduino_hal::pins!(dp);

    /*
     * For examples (and inspiration), head to
     *
     *     https://github.com/Rahix/avr-hal/tree/main/examples
     *
     * NOTE: Not all examples were ported to all boards!  There is a good chance though, that code
     * for a different board can be adapted for yours.  The Arduino Uno currently has the most
     * examples available.
     */

    // let mut led = pins.d13.into_output();

    // loop {
        // led.toggle();
        // arduino_hal::delay_ms(1000);
    // }
// }
