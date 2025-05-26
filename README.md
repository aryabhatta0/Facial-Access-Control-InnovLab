# Facial Recognition Access Control System - Innovation Lab

This repository contains the organized code for the Innovation Lab project: "Facial Recognition Access Control System." The project utilizes machine learning techniques for face detection and recognition, integrated with real-time hardware for door control.

## 🔐 Project Overview

The system is designed to enhance security through:
*   **Face Detection:** Initially developed with Haar Cascade, later refined with YOLOv8 for improved accuracy.
*   **Facial Recognition:** Implemented using a Siamese Network with Contrastive Loss, trained on a custom dataset.
*   **Hardware Integration:** Real-time door control simulated with a servo motor, LCD, and buzzer, managed by an Arduino Uno communicating with a Python script.

## 📁 Directory Structure
```
facial-recognition-access-control-system/
├── arduino/                            (Arduino sketches for door control and testing) 
│   ├── arduino_door_control.ino
│   └── test_hardware.ino
├── data_preparation/                   (Scripts for data collection and preparation) 
│   └── generate_data.py
├── models/                             (Pre-trained models for face detection and recognition)
│   └── best.pt
│   └── siamese_face_cpu.pt
├── recognition_system/                 (Main Python scripts for face detection and recognition)
│   ├── dataset_utils.py
│   ├── face_detector.py
│   ├── main_access_control.py
│   └── siamese_network.py
├── training_notebooks/                 (Experimental Training Notebooks)
│   ├── siamese_net.ipynb
│   └── yolov8.ipynb
├── requirements.txt
└── README.md
```

## ⚙️ Technologies Used
*   **Machine Learning Framework:** PyTorch
*   **Libraries:** `opencv-python`, `ultralytics`, `matplotlib`, `numpy`, `Pillow`, `torchvision`, `pyserial`, `cvzone`
*   **Hardware:** Arduino Uno, Servo Motor
*   **Programming Language:** Python
*   **Data Annotation:** Roboflow

## 🛠️ Setup and Installation

### Pre-requisites

- Python 3.8+
- Arduino IDE
- Webcam/Camera module
- Arduino Uno + Hardware components

### Installation Guide

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/your-username/facial-recognition-access-control-system.git
    cd facial-recognition-access-control-system
    ```

2.  **Python virtual environment setup (recommended):**
    ```bash
    python -m venv venv
    # On Windows
    .\venv\Scripts\activate
    # On macOS/Linux
    source venv/bin/activate
    ```

3.  **Install dependencies:**
    ```bash
    pip install -r requirements.txt
    ```
4. **Arduino Setup:**

    *   Install the Arduino IDE.
    *   Install necessary libraries: `Servo`, `LiquidCrystal`, `Buzzer`, `Adafruit NeoPixel`. You can install these via the Arduino IDE's Library Manager (`Sketch > Include Library > Manage Libraries...`).
    *   Upload the `arduino/arduino_door_control.ino` sketch to your Arduino Uno board. 
    Ensure the correct COM port and board type are selected in the Arduino IDE.

5. **Hardware Connections**:

    * Ensure your servo motor, LCD, and buzzer are connected to the Arduino Uno as per the original project's specifications (refer to the `.ino` files for pin definitions).

## 🚀 Usage

### 1. Data Preparation
*   Use `data_preparation/generate_data.py` to collect and prepare your own facial datasets.
*   Annotate images using Roboflow for YOLOv8 training.

### 2. Model Training
*   **YOLOv8 Face Detector:** Refer to `training_notebooks/yolov8.ipynb` for details on fine-tuning the YOLOv8 model.
*   **Siamese Network:** Refer to `training_notebooks/siamese_net.ipynb` for training the Siamese Network for facial recognition.

### 3. Running the Access Control System
*   Ensure your hardware (Arduino, servo) is connected and the Arduino sketch is uploaded.
*   Run the main access control script:
    ```bash
    python recognition_system/main_access_control.py
    ```

## 🏆 Results
*   **Enhanced Security:** Utilizes state-of-the-art machine learning for reliable facial recognition.
*   **Real-time Face Detection:** Achieves high accuracy (0.9 mAP) using a fine-tuned YOLOv8 model on a custom dataset of 2165 annotated facial images from Roboflow.
*   **Accurate Face Recognition:** Employs a Siamese Network with Contrastive Loss, achieving 91.5% accuracy on a custom dataset of 600 images across 60 individuals.
*   **Real-time Hardware Integration:** Simulates real-time door control using a servo motor, integrated with Python code with Arduino Uno.
*   **Top-ranked Project:** Got an Ex grade for this project in the Innovation Lab (Jan ’24 - April ’24) course.

## 🤝 Acknowledgements
*   My teammates (Aryan Yadav, Vaibhav Aggarwal, and Tharun V) for their contributions
*   Prof. Debamalya Banerjee
*   Department of Physics, IIT Kharagpur

*This project was developed as part of the Innovation Lab course at IIT Kharagpur during the 2024–25 academic session.*
