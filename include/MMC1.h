#ifndef MMC1_H
#define MMC1_H

struct MMC1 {
  unsigned char mainControl;
  unsigned char chrBank0;
  unsigned char chrBank1;
  unsigned char prgBank;
  unsigned char shift;
};

unsigned char MMC1Setup(void);
void mmc1Reset(void);
void mmc1Write(unsigned short, unsigned char);
void loadChrBank0(void);
void loadChrBank1(void);
void loadProgramBank();

#endif
