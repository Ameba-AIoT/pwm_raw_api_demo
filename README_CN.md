* [English Version](./README.md)

### RTL8721Dx PWM 示例 — raw API（FreeRTOS）

🔹 本示例展示如何在 **RTL8721Dx 系列 SoC** 上，基于 raw API 和 FreeRTOS，使用 PWM 定时器驱动 RGB LED，呈现更加自然的呼吸灯效果。

- 📎 开发板购买链接：  
  - [🛒 Taobao](https://item.taobao.com/item.htm?id=904981157046)  
  - [📦 Amazon](https://www.amazon.com/-/zh/dp/B0FB33DT2C/)  
- 📄 [芯片与模组详情](https://aiot.realmcu.com/cn/module/index.html)  
- 📚 [PWM 文档（Timer 外设）](https://aiot.realmcu.com/zh/latest/rtos/peripherals/timer/index.html)  
- 🎬 [Ameba SoC PWM 学习视频](https://aiot.realmcu.com/zh/center/videos/detail/29?theme_id=3)

---

### 功能说明

✅ 初始化与 EVB 上 RGB LED 对应的 GPIO 引脚：  

```c
// 定义三个 GPIO，对应 EVB 上 RGB 三色 LED
#define PWM_RGB_CHANNEL 3
#define PWM1_G _PA_14   // 绿色
#define PWM2_R _PA_15   // 红色
#define PWM3_B _PA_16   // 蓝色
```

✅ 初始化 PWM 定时器后，RGB 三色依次进行亮度渐变：  
- 每个颜色 LED 通过修改占空比，实现：  
  **最暗 → 逐步变亮 → 最亮 → 再逐步变暗**  
- 依次切换 G / R / B 三个通道进行演示。

✅ 与 `pwm_mbed_api_demo` 的区别：  
- 本例使用 **raw API**，以 **1 ms 为步进周期** 调整占空比；  
- 每个通道在“变亮”方向调整约 1000 次，在“变暗”方向再调整约 1000 次；  
- 单个通道完整一次“亮→灭”呼吸周期约为 **4 秒左右**；  
- 因此整体视觉效果比 mbed API 示例更加平滑、自然，更接近实际“呼吸灯”效果。

---

### 硬件环境搭建

1️⃣ **所需组件**  

- 3 个 LED（可选）  
  ⚠️ 开发板上已集成 RGB LED，通常可以直接观察板载 LED 的闪烁效果，如需更直观展示，可外接 3 颗 LED。

2️⃣ **连线说明（如使用外接 LED）**  

- 将 LED 分别连接到开发板对应引脚与 GND：  
  - `LED1_PIN (_PA_14)` —— 绿色通道  
  - `LED2_PIN (_PA_15)` —— 红色通道  
  - `LED3_PIN (_PA_16)` —— 蓝色通道  
  - LED 另一端串联限流电阻后接 `GND`（推荐加限流电阻以保护 LED 和 IO 口）

> 若仅体验功能，可直接使用开发板板载 RGB LED，无需外接元件。

---

### 快速开始

1️⃣ **初始化 SDK 环境**

- 配置 `env.sh`（或 Windows 下的 `env.bat`）路径：

  ```bash
  source {sdk}/env.sh
  ```

- 将 `{sdk}` 替换为 [ameba-rtos SDK](https://github.com/Ameba-AIoT/ameba-rtos) 根目录的**绝对路径**。

⚡ **注意**：本示例仅支持 SDK 版本 **≥ v1.2**。

---

2️⃣ **编译示例工程**

```bash
source env.sh
ameba.py build
```

---

3️⃣ **烧录固件到 Flash**

标准烧录方式（使用当前工程目录下生成的 bin 文件）：

```bash
ameba.py flash --p COMx \
  --image km4_boot_all.bin 0x08000000 0x8014000 \
  --image km0_km4_app.bin 0x08014000 0x8200000
```

⚠️ 若直接使用项目目录中已提供的**预编译 bin 文件**，可使用如下命令（注意相对路径）：

```bash
ameba.py flash --p COMx \
  --image ../km4_boot_all.bin 0x08000000 0x8014000 \
  --image ../km0_km4_app.bin 0x08014000 0x8200000
```

请将 `COMx` 替换为实际串口号（如 `COM5`）。

---

4️⃣ **打开串口监视器**

使用以下命令查看运行日志：

```bash
ameba.py monitor --port COMx --b 1500000
```

同样将 `COMx` 替换为实际端口号。

---

5️⃣ **观察 RGB LED 呼吸灯效果**

- 按下 EVB 上的 **RST**（复位）按钮；  
- 观察板载或外接的 RGB LED：  
  - 绿色通道先呈现呼吸效果（从暗到亮、再从亮到暗）  
  - 完成后切换到红色通道，再完成一次完整呼吸周期  
  - 接着切换到蓝色通道，依次循环  
- 对应串口日志中可看到各 PWM 通道切换的时间点和标记。

---

### 日志示例

```text
[MONITOR] 2026-04-02 19:07:15.996 ROM:[V1.1]
[MONITOR] 2026-04-02 19:07:15.996 FLASH RATE:1, Pinmux:1
[MONITOR] 2026-04-02 19:07:15.996 IMG1(OTA1) VALID, ret: 0
[MONITOR] 2026-04-02 19:07:15.996 IMG1 ENTRY[f800779:0]
[MONITOR] 2026-04-02 19:07:15.996 [BOOT-I] KM4 BOOT REASON 0: Initial Power on
[MONITOR] 2026-04-02 19:07:15.996 [BOOT-I] KM4 CPU CLK: 240000000 Hz
[MONITOR] 2026-04-02 19:07:15.996 [BOOT-I] KM0 CPU CLK: 96000000 Hz
[MONITOR] 2026-04-02 19:07:15.996 [BOOT-I] PSRAM Ctrl CLK: 240000000 Hz
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] IMG1 ENTER MSP:[30009FDC]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] Build Time: Apr  1 2026 18:25:00
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] IMG1 SECURE STATE: 1
[MONITOR] 2026-04-02 19:07:16.006 [FLASH-I] FLASH CLK: 80000000 Hz
[MONITOR] 2026-04-02 19:07:16.006 [FLASH-I] Flash ID: 85-20-16 (Capacity: 32M-bit)
[MONITOR] 2026-04-02 19:07:16.006 [FLASH-I] Flash Read 4IO
[MONITOR] 2026-04-02 19:07:16.006 [FLASH-I] FLASH HandShake[0x2 OK]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM0 XIP IMG[0c000000:8400]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM0 SRAM[20068000:860]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM0 PSRAM[0c008c60:20]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM0 ENTRY[20004d00:60]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM4 XIP IMG[0e000000:18500]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM4 SRAM[2000b000:540]
[MONITOR] 2026-04-02 19:07:16.006 [BOOT-I] KM4 PSRAM[0e018a40:20]
[MONITOR] 2026-04-02 19:07:16.016 [BOOT-I] KM4 ENTRY[20004d80:40]
[MONITOR] 2026-04-02 19:07:16.016 [BOOT-I] IMG2 BOOT from OTA 1, Version: 1.1
[MONITOR] 2026-04-02 19:07:16.016 [BOOT-I] Image2Entry @ 0xe0078c9 ...
[MONITOR] 2026-04-02 19:07:16.016 [APP-I] KM4 APP [LOCKS-ISTART
[MONITOR] 2026-04-02 19:07:16.016 ] KM0 in[APP-I] it_retarVTOR: 30get_lock007000, VTOR_NS:s
[MONITOR] 2026-04-02 19:07:16.016 30007000
[MONITOR] 2026-04-02 19:07:16.016 [APP-I] VTOR: 30007000, VTOR_NS:30007000
[MONITOR] 2026-04-02 19:07:16.016 [APP-I] IMG2 SECURE [MAIN-I]STATE: 1 IWDG
[MONITOR] 2026-04-02 19:07:16.016 refresh on!
[MONITOR] 2026-04-02 19:07:16.016 [MAIN-I] KM0 OS START
[MONITOR] 2026-04-02 19:07:16.016 [CLK-I] [CAL4M]: delta:2 target:320 PPM: 6250 PPM_Limit:30000
[MONITOR] 2026-04-02 19:07:16.026 [CLK-I] [CAL131K]: delta:12 target:2441 PPM: 4916 PPM_Limit:30000
[MONITOR] 2026-04-02 19:07:16.026 [LOCKS-I] KM4 init_retarget_locks
[MONITOR] 2026-04-02 19:07:16.026 [APP-I] BOR arises when supply voltage decreases under 2.57V and recovers above 2.7V.
[MONITOR] 2026-04-02 19:07:16.026 [MAIN-I] KM4 MAIN
[MONITOR] 2026-04-02 19:07:16.026 [VER-I] AMEBA-RTOS SDK VERSION: 1.2.0
[MONITOR] 2026-04-02 19:07:16.026 [MAIN-I] File System Init Success
[MONITOR] 2026-04-02 19:07:16.026 [TAG-I] pwm_raw_RGB_demo start!
[MONITOR] 2026-04-02 19:07:16.026 [MAIN-I] KM4 START SCHEDULER
[MONITOR] 2026-04-02 19:07:16.026 [TAG-I] pwm_chan_0
[MONITOR] 2026-04-02 19:07:20.251 [TAG-I] pwm_chan_1
[MONITOR] 2026-04-02 19:07:24.467 [TAG-I] pwm_chan_2
[MONITOR] 2026-04-02 19:07:30.693 [TAG-I] pwm_chan_0
[MONITOR] 2026-04-02 19:07:34.908 [TAG-I] pwm_chan_1
[MONITOR] 2026-04-02 19:07:39.123 [TAG-I] pwm_chan_2
[MONITOR] 2026-04-02 19:07:45.351 [TAG-I] pwm_chan_0
[MONITOR] 2026-04-02 19:07:49.567 [TAG-I] pwm_chan_1
[MONITOR] 2026-04-02 19:07:53.782 [TAG-I] pwm_chan_2
[MONITOR] 2026-04-02 19:08:00.012 [TAG-I] pwm_chan_0
[MONITOR] 2026-04-02 19:08:04.229 [TAG-I] pwm_chan_1
...
```
