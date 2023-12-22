//Onewire experiment Stmf767
//написать функции 1-4:
//сброс/присутствие, чтение, запись 0, запись 1
// 
//
//
//
#include "mbed.h"

#define SAMPLE_FLAG1 (1UL << 0)
#define SAMPLE_FLAG2 (1UL << 9)

EventFlags event_flags;

void worker_thread_fun()
{
    printf("Waiting for any flag from 0x%08lx.\r\n", SAMPLE_FLAG1 | SAMPLE_FLAG2);
    uint32_t flags_read = 0;
    while (true) {
        flags_read = event_flags.wait_any(SAMPLE_FLAG1 | SAMPLE_FLAG2);
        printf("Got: 0x%08lx\r\n", flags_read);
    }
    
}

__STATIC_INLINE void DWT_Delay_us(volatile uint32_t au32_microseconds)
{
  uint32_t au32_initial_ticks = DWT->CYCCNT;
  uint32_t au32_ticks = (HAL_RCC_GetHCLKFreq() / 1000000);
  au32_microseconds *= au32_ticks;
  while ((DWT->CYCCNT - au32_initial_ticks) < au32_microseconds-au32_ticks);
}
void OW_reset()
{
//0 for 480us
    DWT_Delay_us(480);
// уст 1
//ждём <60us "1" длительностью >60us  
}
void OW_read()
{
//0 for 1-15 us
//ждём >15us 

}
void OW_write1()
{
    // 0 for 1-15 us
    //
}
void OW_write0()
{
    // 0 for 60-120 us
}


int main() 
{
    Thread worker_thread;
    worker_thread.start(mbed::callback(worker_thread_fun));

    while (true) {
        ThisThread::sleep_for(1000);
        event_flags.set(SAMPLE_FLAG1);
        ThisThread::sleep_for(500);
        event_flags.set(SAMPLE_FLAG2);
    }
}


