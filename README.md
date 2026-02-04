# STM32F401 Bare-Metal Driver Development Repository

Repository này chứa các driver mức thanh ghi (register-level) cho vi điều khiển STM32F401, được xây dựng theo hướng bare-metal, không sử dụng HAL hay LL.

## Mục tiêu của Project

Mục tiêu của project không chỉ là "chạy được", mà là:

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

## 6. Example

### Example_Blinky_LED

Thư mục `Example_Blinky_LED` cung cấp một ví dụ cơ bản nhằm minh họa cách sử dụng các driver đã xây dựng.

Ví dụ này:

- Sử dụng **GPIO driver** để cấu hình chân output
- Sử dụng **Timer driver + Interrupt** để tạo LED blinking
- Kiểm tra xử lý ngắt thông qua `TIMER_IRQHandler`
- Toàn bộ cấu hình thực hiện ở **mức register-level**
- **Không sử dụng** HAL hoặc LL
- Tách biệt rõ:
  - Driver layer
  - Application layer

### Mục đích:

- Kiểm chứng tính đúng đắn của các driver
- Làm ví dụ chuẩn cho cách tích hợp driver
- Nền tảng cho các example nâng cao hơn trong tương lai (PWM, Input Capture, v.v.)

---

## Kết luận

Repository này là một nền tảng học tập và phát triển driver bare-metal cho STM32F401, giúp người học:

- Hiểu sâu về phần cứng
- Tự tin làm việc với Reference Manual
- Xây dựng driver chất lượng, dễ bảo trì và mở rộng
