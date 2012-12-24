#ifndef __MY_HEX__
#define __MY_HEX__

class Hex{
public:
	// 以十六进制形式显示 data 之后的 len 个字节
	virtual void ShowHexText(char *data, int len)=0;
};

#endif