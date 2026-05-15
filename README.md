* [中文说明](./README_CN.md)

### RTL8721Dx PWM Example — raw API (FreeRTOS)

🔹 This example demonstrates how to use the PWM timer of the **RTL8721Dx series SoC** with a **raw (low-level) API** on FreeRTOS to drive an RGB LED and create a smooth breathing-light effect.

- 📎 Development board purchase links:  
  - [🛒 Taobao](https://item.taobao.com/item.htm?id=904981157046)  
  - [📦 Amazon](https://www.amazon.com/-/zh/dp/B0FB33DT2C/)  
- 📄 [Chip & module information](https://aiot.realmcu.com/cn/module/index.html)  
- 📚 [PWM / Timer documentation](https://aiot.realmcu.com/zh/latest/rtos/peripherals/timer/index.html)  
- 🎬 [Ameba SoC PWM tutorial video](https://aiot.realmcu.com/zh/center/videos/detail/29?theme_id=3)

---

### Features

✅ Initialize GPIOs corresponding to the RGB LED on the EVB:

```c
// Define three GPIOs for the RGB LED on EVB
#define PWM_RGB_CHANNEL 3
#define PWM1_G _PA_14   // Green
#define PWM2_R _PA_15   // Red
#define PWM3_B _PA_16   // Blue
```

✅ After initializing the PWM timers, the three RGB channels fade in and out in sequence:  
- Each color LED changes its duty cycle to achieve:  
  **dark → gradually brighter → brightest → gradually back to dark**  
- Channels are switched in the order **G → R → B** for demonstration.

✅ Difference from `pwm_mbed_api_demo`:  
- This example uses the **raw PWM API** and updates the duty cycle every **1 ms**;  
- For each channel, the duty cycle is adjusted about **1000 steps up (brighten)** and **1000 steps down (dim)**;  
- A full “fade in → fade out” breathing cycle for one channel takes about **4 seconds**;  
- As a result, the visual transition is smoother and more natural, closer to a real “breathing LED” effect.

---

### Hardware Setup

1️⃣ **Required Components**

- 3 x LEDs (optional)  
  ⚠️ The EVB already has an on-board RGB LED, so in most cases you can directly observe the blinking effect.  
  If you want a more visible demo, you can connect 3 external LEDs.

2️⃣ **Wiring (for external LEDs)**

Connect each LED to the board and GND:

- `LED1_PIN (_PA_14)` — Green channel  
- `LED2_PIN (_PA_15)` — Red channel  
- `LED3_PIN (_PA_16)` — Blue channel  
- The other side of each LED should be connected through a current-limiting resistor to `GND` (recommended to protect both LED and IO pins).

> If you only want to evaluate the function, the on-board RGB LED is sufficient and no external components are required.

---

### Getting Started

1️⃣ **Initialize SDK Environment**

Set up the `env.sh` (or `env.bat` on Windows) path:

```bash
source {sdk}/env.sh
```

Replace `{sdk}` with the **absolute path** to the root directory of the [ameba-rtos SDK](https://github.com/Ameba-AIoT/ameba-rtos).

⚡ **Note**: This example requires SDK version **≥ v1.2**.

---

2️⃣ **Build the Example Project**

```bash
source env.sh
ameba.py build
```

---

3️⃣ **Flash the Firmware to Flash**

Standard flashing method (using binaries generated in the current project directory):

```bash
ameba.py flash --p COMx \
  --image boot.bin 0x08000000 0x8014000 \
  --image app.bin 0x08014000 0x8200000
```

⚠️ If you want to use the **prebuilt binaries** provided in the project directory (parent folder), run:

```bash
ameba.py flash --p COMx \
  --image ../boot.bin 0x08000000 0x8014000 \
  --image ../app.bin 0x08014000 0x8200000
```

> ⚠️ **Note on binary filenames**: The output filenames depend on your SDK revision.
> The latest SDK generates `boot.bin` + `app.bin`;
> older SDK revisions generate `km4_boot_all.bin` + `km0_km4_app.bin`.
> Replace the filenames in the commands above to match your actual build output.

Replace `COMx` with the actual serial port, e.g. `COM5`.

---

4️⃣ **Open Serial Monitor**

Use the following command to view the runtime logs:

```bash
ameba.py monitor --port COMx --b 1500000
```

Again, replace `COMx` with your actual port.

---

5️⃣ **Observe the RGB Breathing Effect**

- Press the **RST** button on the EVB to reset the board;  
- Watch the on-board or external RGB LEDs:  
  - The green channel shows a full breathing cycle (fade in, then fade out);  
  - Then the red channel runs the same breathing cycle;  
  - Then the blue channel follows;  
- The serial log shows when each PWM channel starts its breathing phase.

---

### Log Example

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
