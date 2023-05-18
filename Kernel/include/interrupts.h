#ifndef INTERRUPS_H_
#define INTERRUPS_H_

void _sysCallHandler(int mode, int fd, char * buff, int bytes);
void _irq00Handler(void);
void _irq01Handler(void);
void _irq02Handler(void);
void _irq03Handler(void);
void _irq04Handler(void);
void _irq05Handler(void);
void int80Handler(void);
void _exception0Handler(void);
void _exception6Handler(void);
#endif /* INTERRUPS_H_ */
