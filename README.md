# 🛡️ SMARTFENCE – Intruder Prevention Warning System (IPWS)

A smart, IoT-based security system that integrates motion sensing, video surveillance, and adaptive electric fencing to detect and respond to unauthorized intrusions in real time.



## 📖 Abstract

This project designs an integrated **Intruder Prevention Warning System (IPWS)** combining physical barriers, motion detection, video surveillance, and wireless alert mechanisms. It uses a **PIR sensor**, **ESP32-CAM**, **OpenCV**, and **Telegram bot integration** for real-time alerting and action. The fencing is activated with variable voltage based on the size/type of intruder and can be deactivated via user feedback.

**Key Features:**
- Motion detection with PIR sensor
- Real-time video capture and analysis
- Telegram-based alerting system
- Intelligent fencing activation based on intruder size
- Servo motor-based gate access
- User feedback-based override mechanism

---

## 🔧 Working & Implementation

### 1. PIR Motion Detection
Detects infrared radiation from moving objects and signals ESP32-CAM on motion.

### 2. Data Transmission via ESP32-CAM
Captures image/video and processes locally using OpenCV.

### 3. Image Analysis using OpenCV
Classifies the intruder (human/animal/object) to decide fencing voltage.

### 4. Alert via Telegram
Sends image and classification alert to the user via Telegram bot.

### 5. Electric Fencing Activation
- Big Intruder: 3.3V  
- Small Intruder: 2.5V  
- Human: 1.5V  

### 6. Fencing Deactivation
Deactivates fencing automatically after intruder leaves.

### 7. User Feedback
User can reply "friend" to deactivate fencing and open gate via servo.

### 8. Servo-Controlled Gate
Opens/closes gate upon user authorization.

### 9. Continuous Monitoring
System loops in low-power mode and activates only when needed.




## 🔮 Future Upgradations

- ✅ Replace ESP32-CAM with **Raspberry Pi** for faster processing.
- ✅ Use higher resolution **camera modules**.
- ✅ Implement **segment-wise fencing voltage control**.
- ✅ Add **audible buzzer alert** for real-time intruder warning.

---

## 🔗 References

- https://www.electroniclinic.com/esp32-cam-with-python-opencv-yolo-v3-for-object-detection-and-identification/
- https://how2electronics.com/esp32-cam-based-object-detection-identification-with-opencv/


## ✅ Conclusion

**SMARTFENCE** demonstrates a practical and innovative approach to automated security using IoT and real-time feedback systems. Its integration of motion detection, intelligent fencing, and remote user control makes it scalable, energy-efficient, and highly secure. This project showcases how modern technologies like OpenCV, ESP32, and Telegram bots can work together to protect premises in a smart, automated way.

---

