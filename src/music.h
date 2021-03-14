enum soundTypeEnum{
	ST_dummy=-1,
	ST_init,
	ST_gun,
	ST_rotate,
	ST_accelerate,
	ST_ghost,
	ST_line,
	ST_crash,
	ST_explosion,
	ST_pause,
	ST_start,
	ST_gameover,
};

const unsigned char music_init[]={
	0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x45,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x47,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x47,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x45,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x42,0xFF,0xFF,0xFE,
	0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFF,
	0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x45,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x47,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x47,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x45,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x44,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x42,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x40,0xFF,0xFF,0xFE,
	0x40,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0xFF,0xFF,0xFF,0xFC,
};

const unsigned char music_gun[]={
	0x64,0x60,0x58,0x54,0x50,0x48,0x44,0xFC,
};

const unsigned char music_rotate[]={
	0x57,0x60,0x64,0xFC,
};

const unsigned char music_accelerate[]={
	0x57,0xFC,
};

const unsigned char music_ghost[]={
	0x64,0xFE,0xFF,0x64,0xFE,0xFF,0x64,0xFC,
};

const unsigned char music_line[]={
	0x4A,0x4B,0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5A,0x5B,0x60,0x61,
	0x62,0x63,0x64,0xFC,
};

const unsigned char music_crash[]={
	0x24,0x20,0x17,0xFC,
};

const unsigned char music_explosion[]={
	0x29,0x27,0x25,0x23,0x21,0x1B,0x19,0x17,0x15,0x13,0x11,0x0B,0x09,0x0A,0x09,0x0B,
	0x09,0x0A,0x09,0xFC,
};

const unsigned char music_pause[]={
	0x50,0xFF,0x57,0xFF,0x54,0xFF,0x60,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,
};

const unsigned char music_start[]={
	0x57,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x54,0xFF,0xFF,0xFE,0x54,0xFF,0xFF,0xFE,
	0x54,0xFF,0xFF,0xFE,0x57,0xFF,0xFF,0xFE,0x54,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x54,0xFF,0xFF,0xFE,0x59,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x59,0xFF,0xFF,0xFE,
	0x54,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,
	0x52,0xFF,0xFF,0xFE,0x52,0xFF,0xFF,0xFE,0x52,0xFF,0xFF,0xFE,0x54,0xFF,0xFF,0xFE,
	0x52,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFE,0x50,0xFF,0xFF,0xFE,0x49,0xFF,0xFF,0xFE,
	0x52,0xFF,0xFF,0xFE,0x50,0xFF,0xFF,0xFE,0x52,0xFF,0xFF,0xFE,0x54,0xFF,0xFF,0xFE,
	0x57,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,
};

const unsigned char music_gameover[]={
	0x40,0xFF,0xFF,0xFE,0x44,0xFF,0xFF,0xFE,0x47,0xFF,0xFF,0xFE,0x50,0xFF,0xFF,0xFE,
	0x50,0xFF,0xFF,0xFE,0x47,0xFF,0xFF,0xFE,0x44,0xFF,0xFF,0xFE,0x40,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,
};

const unsigned char* const music[]={
	music_init,
	music_gun,
	music_rotate,
	music_accelerate,
	music_ghost,
	music_line,
	music_crash,
	music_explosion,
	music_pause,
	music_start,
	music_gameover,
};
