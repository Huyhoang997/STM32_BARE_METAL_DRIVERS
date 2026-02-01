# STM32F401 Bare-Metal Driver Development

Repository này chứa các **driver mức thanh ghi (register-level)** cho vi điều khiển **STM32F401**, được xây dựng **hoàn toàn bare-metal**, **không sử dụng HAL hay LL**.

Mục tiêu của project:
- Hiểu rõ kiến trúc Cortex-M và STM32
- Làm chủ peripheral thông qua mapping thanh ghi
- Xây dựng driver theo hướng module hóa, dễ mở rộng
- Phục vụ học tập và luyện phỏng vấn Embedded Fresher / Junior

---

## 1. Kiến trúc tổng thể

Project được tổ chức theo hướng:
- Một file header trung tâm `stm32f401xx.h`
- Mỗi peripheral là một module độc lập

Các module hiện có:
- GPIO
- TIMER
- NVIC

---

## 2. stm32f401xx.h

File `stm32f401xx.h` được xây dựng tương tự CMSIS device header nhưng **tự triển khai lại từ Reference Manual**.

### Nội dung chính:
- Base address cho các peripheral
- Mapping thanh ghi bằng `struct`
- Macro enable / disable clock
- Định nghĩa bit position quan trọng

### Ví dụ mapping timer:
```c
typedef struct
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint32_t CCMR1;
    volatile uint32_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
} TIMER_RegDef_t;
