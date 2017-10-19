// Bitmaps. (L x W || Row x Column)
// 16 x 8
uint8_t heroBitmap[] = {
  0b00000111, 0b10000000,
	0b00001100, 0b11000000,
	0b00001111, 0b11000000,
	0b01111111, 0b11111000,
  0b11000111, 0b10001100,
	0b10000111, 0b10000100,
	0b00011000, 0b01100000,
	0b00110000, 0b00110000,
};
// 3 x 22
uint8_t vertWallBitmap[] = {
  0b11100000,
	0b11100000,
	0b11100000,
	0b11100000,
  0b11100000,
	0b11100000,
	0b11100000,
	0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
  0b11100000,
};
// 12 x 24
uint8_t horWallBitmap[] = {
  0b11111111, 0b11111111, 0b11111111,
	0b11111111, 0b11111111, 0b11111111,
	0b11111111, 0b11111111, 0b11111111,
};
// 8 x 5
uint8_t enemyBitmap[] = {
  0b01111110,
  0b11011011,
  0b11111111,
  0b11111111,
  0b11011011,
};
// 8 x 3
uint8_t keyBitmap[] = {
  0b11100000,
  0b10111111,
  0b11100101,
};
// 8 x 3
uint8_t treasureBitmap[] = {
  0b00011000,
  0b01111110,
  0b11111111,
};
// 8 x 3
uint8_t bowBitmap[] = {
  0b00111100,
  0b01100110,
  0b11000011,
};
// 2 x 2
uint8_t arrowBitmap[] = {
  0b1110000,
  0b1110000,
  0b1110000,
};
// 8 x 4
uint8_t shieldBitmap[] = {
  0b11111111,
  0b10101011,
  0b11010101,
  0b11111111,
};
// 6 x 4
uint8_t bombBitmap[] = {
  0b00011000,
  0b01100100,
  0b11110000,
  0b01100000,
};
// 8 x 3
uint8_t crosshairBitmap[] = {
  0b00011000,
  0b00011000,
  0b00011000,
  0b11111111,
  0b11111111,
  0b00011000,
  0b00011000,
  0b00011000,
};
// 10 x 24
uint8_t doorBitmap[] = {
  0b00000000, 0b00111100, 0b00000000,
  0b00000001, 0b11111111, 0b10000000,
  0b00000111, 0b00000000, 0b11100000,
  0b00001100, 0b00000000, 0b00110000,
  0b00011100, 0b00000000, 0b00111000,
  0b00110000, 0b00000000, 0b00001100,
  0b00111000, 0b00000001, 0b10001100,
  0b00110000, 0b00000001, 0b10001100,
  0b00110000, 0b00000000, 0b00001100,
  0b01111000, 0b00000000, 0b00001110,
  0b11110000, 0b00000000, 0b00001111,
};
// 80 x 20
uint8_t towerBitmap[] = {
  0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111, 0b11111111,
  0b01110000, 0b00000011, 0b11111111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11111111, 0b11000000, 0b00001110,
  0b00110000, 0b00000011, 0b11111111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11111111, 0b11000000, 0b00001100,
  0b00110000, 0b00000011, 0b11111111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11111111, 0b11000000, 0b00001100,
  0b00110000, 0b00000011, 0b11110111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11101111, 0b11000000, 0b00001100,
  0b00110000, 0b00000011, 0b11100111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11100111, 0b11000000, 0b00001100,
  0b00111000, 0b00000011, 0b11100111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11100111, 0b11000000, 0b00011100,
  0b00011100, 0b00000011, 0b00000000, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b00000000, 0b11000000, 0b00111000,
  0b00011100, 0b00000001, 0b11100111, 0b10000000, 0b00000000, 0b00000000, 0b00000001, 0b11100111, 0b10000000, 0b00111000,
  0b00001100, 0b00000001, 0b11100111, 0b10000000, 0b00000000, 0b00000000, 0b00000001, 0b11100111, 0b10000000, 0b00110000,
  0b00001110, 0b00000000, 0b11101111, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b11110111, 0b00000000, 0b01110000,
  0b00001111, 0b00000000, 0b01111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111110, 0b00000000, 0b11110000,
  0b00000011, 0b10000000, 0b00111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111100, 0b00000001, 0b11000000,
  0b00000011, 0b11100000, 0b00011000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011000, 0b00000111, 0b11000000,
  0b00000000, 0b11111000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00011111, 0b00000000,
  0b00000000, 0b00111110, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b01111100, 0b00000000,
  0b00000000, 0b00001111, 0b11100000, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00000111, 0b11110000, 0b00000000,
  0b00000000, 0b00000001, 0b11111100, 0b00000000, 0b00000000, 0b00000000, 0b00000000, 0b00111111, 0b10000000, 0b00000000,
  0b00000000, 0b00000000, 0b00011111, 0b11000000, 0b00000000, 0b00000000, 0b00000011, 0b11111000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000001, 0b11111111, 0b10000000, 0b00000001, 0b11111111, 0b10000000, 0b00000000, 0b00000000,
  0b00000000, 0b00000000, 0b00000000, 0b00111111, 0b00000000, 0b00000000, 0b11111100, 0b00000000, 0b00000000, 0b00000000,
};
