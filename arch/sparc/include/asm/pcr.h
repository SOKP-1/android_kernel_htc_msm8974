#ifndef __PCR_H
#define __PCR_H

struct pcr_ops {
	u64 (*read)(void);
	void (*write)(u64);
};
extern const struct pcr_ops *pcr_ops;

extern void deferred_pcr_work_irq(int irq, struct pt_regs *regs);
extern void schedule_deferred_pcr_work(void);

#define PCR_PIC_PRIV		0x00000001 
#define PCR_STRACE		0x00000002 
#define PCR_UTRACE		0x00000004 
#define PCR_N2_HTRACE		0x00000008 
#define PCR_N2_TOE_OV0		0x00000010 
#define PCR_N2_TOE_OV1		0x00000020 
#define PCR_N2_MASK0		0x00003fc0
#define PCR_N2_MASK0_SHIFT	6
#define PCR_N2_SL0		0x0003c000
#define PCR_N2_SL0_SHIFT	14
#define PCR_N2_OV0		0x00040000
#define PCR_N2_MASK1		0x07f80000
#define PCR_N2_MASK1_SHIFT	19
#define PCR_N2_SL1		0x78000000
#define PCR_N2_SL1_SHIFT	27
#define PCR_N2_OV1		0x80000000

extern unsigned int picl_shift;

static inline u64 picl_value(unsigned int nmi_hz)
{
	u32 delta = local_cpu_data().clock_tick / (nmi_hz << picl_shift);

	return ((u64)((0 - delta) & 0xffffffff)) << 32;
}

extern u64 pcr_enable;

extern int pcr_arch_init(void);

#endif 
