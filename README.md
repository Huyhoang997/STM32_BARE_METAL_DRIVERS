# STM32F401 Bare-Metal Driver Development Repository

Repository này chứa các driver mức thanh ghi (register-level) cho vi điều khiển STM32F401, được xây dựng theo hướng bare-metal, không sử dụng HAL hay LL.

## Mục tiêu của Project

Mục tiêu của project là:

- **Hiểu bản chất phần cứng** bên dưới mỗi dòng code
- **Nắm vững clock tree**, bus architecture, và memory system
- **Viết driver có cấu trúc rõ ràng**, gần với Reference Manual, dễ đọc và dễ mở rộng

---

## 1. Mục tiêu & Phạm vi

Project tập trung vào:

- Hiểu sâu kiến trúc **ARM Cortex-M4**
- Làm việc trực tiếp với hệ thống bus **AHB / APB1 / APB2**
- **Mapping peripheral** thông qua memory-mapped registers
- Tự xây dựng **device header** và **driver** dựa trên STM32F401 Reference Manual
- Thiết kế driver theo hướng **module hóa**, tách biệt:
  - Low-level driver layer
  - Application / example layer

---

## 2. Kiến trúc Tổng thể

Project được tổ chức theo các nguyên tắc sau:

- `stm32f401xx.h` đóng vai trò **device abstraction layer**
- Mỗi peripheral là một **module độc lập**, phản ánh đúng kiến trúc phần cứng
- Các ví dụ (examples) sử dụng driver trực tiếp để kiểm chứng tính đúng đắn

### Các module hiện có:

- **stm32f401xx.h** – Device header (register mapping)
- **GPIO** – General Purpose I/O driver
- **TIMER** – General-purpose Timer driver + Interrupt
- **NVIC** – Nested Vector Interrupt Controller
- **RCC** – Reset and Clock Control
- **FLASH** – Flash access & wait state configuration

---

## 3. stm32f401xx.h – Device Header File

`stm32f401xx.h` được xây dựng theo tinh thần CMSIS device header, nhưng:

- **Không sử dụng** file CMSIS gốc
- **Tự triển khai hoàn toàn** dựa trên Reference Manual của STM32F401

### Nội dung chính:

- Base address của các peripheral
- Mapping thanh ghi bằng struct theo đúng memory layout
- Macro enable / disable clock cho từng peripheral
- Định nghĩa bit position, mask, và các giá trị cấu hình quan trọng

### Ví dụ mapping Timer:
```c
typedef struct {
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

---

## 4. RCC – Reset and Clock Control Module

RCC chịu trách nhiệm cấu hình toàn bộ hệ thống clock của MCU.

### Chức năng chính:

- **Enable / disable clock** cho từng peripheral
- **Cấu hình SYSCLK source**:
  - HSI
  - PLL (từ HSI)
- **Cấu hình PLL parameters**:
  - **PLLM** – Prescaler cho PLL input
  - **PLLN** – Multiplier cho VCO
  - **PLLP** – Prescaler cho PLL output

### Đảm bảo:

- VCO_in nằm trong khoảng **1–2 MHz**
- SYSCLK phù hợp với giới hạn phần cứng

### Triết lý thiết kế:

- API hướng **system-level**, không buộc user phải hiểu mọi bit
- Cung cấp một số cấu hình clock phổ biến (16 / 48 / 64 / 84 MHz)
- Cho phép mở rộng nếu user muốn tự cấu hình PLL chi tiết hơn

---

## 5. FLASH – Flash Access & Wait State

Khi SYSCLK tăng, Flash memory không thể truy cập kịp nếu không cấu hình wait state. Vì vậy module FLASH được tách riêng để xử lý đúng thứ tự phần cứng.

### Chức năng:

- Cấu hình **Flash latency** (wait states) tương ứng với SYSCLK
- Đảm bảo hệ thống hoạt động ổn định khi chạy ở tần số cao
- Tránh lỗi hard fault do đọc Flash quá nhanh

### Nguyên tắc:

- Cấu hình Flash latency **trước** khi switch SYSCLK
- Số wait state tuân theo datasheet của STM32F401

---

## 6. NVIC – Nested Vector Interrupt Controller

NVIC là bộ điều khiển ngắt của ARM Cortex-M4, chịu trách nhiệm quản lý toàn bộ hệ thống interrupt trong MCU.

### Chức năng chính

- **Enable / Disable interrupt** cho từng peripheral
- **Cấu hình priority** (độ ưu tiên) cho từng interrupt
- **Set / Clear pending interrupt**
- Quản lý **nested interrupt** (ngắt lồng nhau)

---

### Priority System & Priority Grouping

STM32F401 (Cortex-M4) sử dụng **8-bit priority field** (0–255), nhưng chỉ implement **4 bit** thực tế  
→ tương đương **16 mức độ ưu tiên (0–15)**.

Priority được chia thành 2 phần:

- **Preemption Priority (Group Priority)**  
  Quyết định khả năng **ngắt lồng nhau**
- **Sub Priority (Response Priority)**  
  Quyết định **thứ tự xử lý** khi nhiều interrupt có cùng preemption priority

---

### Bảng phân chia Priority Bits

| Priority Group | PRIGROUP Value | Preemption Bits | Sub-Priority Bits | Mô tả |
|---------------|----------------|------------------|-------------------|------|
| Group 0 | 0x07 | 0 | 4 | Không có ngắt lồng, 16 mức sub-priority |
| Group 1 | 0x06 | 1 | 3 | 2 mức preemption, 8 mức sub-priority |
| Group 2 | 0x05 | 2 | 2 | 4 mức preemption, 4 mức sub-priority |
| Group 3 | 0x04 | 3 | 1 | 8 mức preemption, 2 mức sub-priority |
| Group 4 | 0x03 | 4 | 0 | 16 mức preemption, không có sub-priority |

---

### Ví dụ minh họa

- EXTI có **preemption priority = 0**
- Timer có **preemption priority = 1**

→ EXTI **có thể ngắt Timer ISR**

Nếu cả hai pending cùng lúc và **cùng preemption priority**  
→ interrupt có **sub-priority nhỏ hơn** sẽ được xử lý trước.

---

### Nguyên tắc thiết kế NVIC driver

- Cung cấp API rõ ràng cho enable / disable interrupt
- Hỗ trợ cấu hình priority trực quan
- Đóng gói logic encode priority từ  
  **preemption + sub-priority**
- Cho phép user lựa chọn priority group phù hợp với ứng dụng

---

### Lưu ý quan trọng

- **Priority càng nhỏ → độ ưu tiên càng cao** (0 là cao nhất)
- Priority group nên được cấu hình **một lần duy nhất** khi khởi tạo hệ thống
- Thay đổi priority group trong lúc runtime có thể gây hành vi không mong muốn
- Với hệ thống đơn giản, **Priority Group 2** là lựa chọn cân bằng tốt

---

## 7. SysTick Timer – System Time Base

SysTick là **timer lõi (core peripheral)** của ARM Cortex-M, thường được sử dụng để xây dựng **time base cho toàn hệ thống**.

Trong project này, SysTick được cấu hình để tạo **interrupt mỗi 1 ms**, làm nền cho các chức năng delay và timeout.

---

### Đặc điểm SysTick

- Chạy trực tiếp từ **processor clock (HCLK)**
- Counter dạng **down-counter**
- Có khả năng tạo interrupt định kỳ
- Hoạt động độc lập với timer peripheral (TIMx)

---

### Mục đích sử dụng SysTick

- Tạo **system tick 1 ms**
- Làm nền cho:
  - Delay millisecond
  - Timeout
  - Scheduling đơn giản

---

### SysTick Initialization Flow

Trình tự khởi tạo đúng theo ARM recommendation:

1. Program **reload value**
2. Clear **current value**
3. Enable counter và interrupt

```c
reload = SystemCoreClock / 1000;   // 1 ms tick

```
---

## 8. Example

### Example_Blinky_LED

Thư mục `Example_Blinky_LED` cung cấp một ví dụ cơ bản nhằm minh họa cách sử dụng các driver đã xây dựng.

Ví dụ này:

- Sử dụng **GPIO driver** để cấu hình chân output
- Sử dụng **Timer driver + Interrupt** để tạo LED blinking
- Kiểm tra xử lý ngắt thông qua `TIMER_IRQHandler`
- Cấu hình **NVIC priority** cho Timer interrupt
- Toàn bộ cấu hình thực hiện ở **mức register-level**
- **Không sử dụng** HAL hoặc LL
- Tách biệt rõ:
  - Driver layer
  - Application layer

### Mục đích:

- Kiểm chứng tính đúng đắn của các driver
- Làm ví dụ chuẩn cho cách tích hợp driver
- Minh họa cách cấu hình interrupt và priority
- Nền tảng cho các example nâng cao hơn trong tương lai (PWM, Input Capture, v.v.)

---

## Kết luận

Repository này là một nền tảng học tập và phát triển driver bare-metal cho STM32F401, giúp người học:

- Hiểu sâu về phần cứng
- Tự tin làm việc với Reference Manual
- Nắm vững cơ chế interrupt và priority của ARM Cortex-M4
- Xây dựng driver chất lượng, dễ bảo trì và mở rộng
