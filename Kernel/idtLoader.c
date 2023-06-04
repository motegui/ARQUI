#include <stdint.h>
#include <idtLoader.h>
#include <defs.h>
#include <interrupts.h>

#pragma pack(push)		/* Aligns */
#pragma pack (1) 		/* Aligns structures to 1 byte */

/* Interrupt descriptor */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		//Reestablishes alignment



DESCR_INT * idt = (DESCR_INT *) 0;	// 255 entry IDT

static void setup_IDT_entry (int index, uint64_t offset);

void load_idt() {

  setup_IDT_entry (0x20, (uint64_t)&_irq00Handler);
  setup_IDT_entry (0x21, (uint64_t)&_irq01Handler);
  setup_IDT_entry (0x00, (uint64_t)&_exception0Handler);
  setup_IDT_entry(0x06, (uint64_t)&_exception6Handler);
  setup_IDT_entry (0x80, (uint64_t)&_int80Handler);


	//only timer tick interrupts
	picMasterMask(0xFC); // 1111 1100
	picSlaveMask(0xFF); //  1111 1111

	_sti();
}

static void setup_IDT_entry (int index, uint64_t offset) {
  idt[index].selector = 0x08;
  idt[index].offset_l = offset & 0xFFFF;
  idt[index].offset_m = (offset >> 16) & 0xFFFF;
  idt[index].offset_h = (offset >> 32) & 0xFFFFFFFF;
  idt[index].access = ACS_INT;
  idt[index].cero = 0;
  idt[index].other_cero = (uint64_t) 0;
}
