# set parameters for lcd libs
# define LCD_PORT PORTC
# define LCD_DDR DDRC
# define LCD_CS PC0
# define LCD_SCLK PC1
# define LCD_SDA PC2

# set parameters for one wire interface
# define DS1WIRE_DDR DDRD
# define DS1WIRE_PIN PIND
# define DS1WIRE_LINE PD6

add_definitions (
    -DLCD_PORT=PORTC
    -DLCD_DDR=DDRC
    -DLCD_CS=PC0
    -DLCD_SCLK=PC1
    -DLCD_SDA=PC2
    -DDS1WIRE_DDR=DDRD
    -DDS1WIRE_PIN=PIND
    -DDS1WIRE_LINE=PD6
    )

# set font support
add_definitions (
    -DBUILDIN_FONT
    )
