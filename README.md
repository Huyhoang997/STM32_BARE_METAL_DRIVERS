# STM32F401 Bare-Metal Driver Development

Repository này chứa các **driver mức thanh ghi (register-level)** cho vi điều khiển **STM32F401**, được xây dựng theo hướng **bare-metal**, **không sử dụng HAL hay LL**.

Project tập trung vào:
- Hiểu sâu kiến trúc **ARM Cortex-M4** và hệ thống bus (**AHB / APB**)
- Làm việc trực tiếp với peripheral thông qua **mapping thanh ghi**
- Tự xây dựng device header và driver dựa trên **Reference Manual**
- Thiết kế driver theo hướng **module hóa**, rõ ràng và dễ mở rộng

---

## 1. Kiến trúc tổng thể

Project được tổ chức theo hướng:
- Một file header trung tâm `stm32f401xx.h` đóng vai trò **device abstraction**
- Mỗi peripheral được tách thành một **module độc lập**, phản ánh đúng kiến trúc phần cứng
- Các ví dụ (examples) sử dụng trực tiếp driver để kiểm chứng chức năng

Các module hiện có:
- GPIO
- TIMER
- NVIC

---

## 2. stm32f401xx.h

File `stm32f401xx.h` được xây dựng tương tự **CMSIS device header**, nhưng **tự triển khai lại hoàn toàn dựa trên Reference Manual của STM32F401**.

### Nội dung chính:
- Base address của các peripheral
- Mapping thanh ghi bằng `struct` theo đúng **memory layout**
- Macro enable / disable clock
- Định nghĩa bit position và mask quan trọng

### Ví dụ mapping Timer:
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

```
## 3. Example

### Example_Blinky_LED

Thư mục `Example_Blinky_LED` cung cấp một ví dụ cơ bản nhằm **minh họa cách sử dụng các driver đã xây dựng** trong project.

Ví dụ này:
- Test các function của TIMER_IRQHandling và EXTI0_IRQHandling
- Sử dụng **GPIO driver** để cấu hình chân output
- Sử dụng **Timer driver** để tạo delay cho LED blinking
- Không sử dụng HAL hoặc LL, toàn bộ cấu hình thực hiện ở mức **register-level**
- Tách biệt rõ **driver layer** và **application layer**

Mục đích của example:
- Kiểm chứng tính đúng đắn của các driver
- Làm ví dụ tham khảo cho cách tích hợp driver vào ứng dụng
- Đóng vai trò nền tảng cho các example nâng cao trong tương lai
