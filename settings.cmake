# set parameters for lcd libs
# define LCD_PORT PORTC
# define LCD_DDR DDRC
# define LCD_CS PC0
# define LCD_SCLK PC1
# define LCD_SDA PC2

add_definitions (
    -DLCD_PORT=PORTC
    -DLCD_DDR=DDRC
    -DLCD_CS=PC0
    -DLCD_SCLK=PC1
    -DLCD_SDA=PC2
    )

# set font support
add_definitions (
    -DBUILDIN_FONT
    )
