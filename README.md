# Distributed ECU Health Monitoring System

## Overview

The Distributed ECU Health Monitoring System is an embedded systems and machine learning project that simulates multiple automotive Electronic Control Units (ECUs), telemetry communication, predictive diagnostics, and intelligent fault prediction.

The system generates real-time telemetry data from Engine, Battery, and Brake ECUs, performs health monitoring, detects warning and fault conditions, logs operational data, and applies machine learning models to predict ECU health states.

---

## Key Features

### Embedded System Simulation

* Multi-ECU architecture
* Engine ECU simulation
* Battery ECU simulation
* Brake ECU simulation
* Real-time telemetry generation

### Diagnostics and Monitoring

* ECU state machine implementation
* Warning detection
* Fault detection
* Event logging
* Ring buffer implementation

### Communication Layer

* Telemetry queue implementation
* Queue-based ECU communication
* CAN bus simulation
* CAN frame encoding and decoding
* ECU communication model

### Predictive Diagnostics

* Historical telemetry monitoring
* Trend analysis
* Predictive warning generation
* Early fault indication

### Machine Learning

* Automatic dataset generation
* Logistic Regression
* Decision Tree
* Random Forest
* Gradient Boosting
* Best-model selection
* Real-time fault prediction

---

## System Architecture

```text
Engine ECU Task
Battery ECU Task
Brake ECU Task
        │
        ▼
RTOS-Based Task Architecture
────────────────────────────
• Task Decomposition
• Producer-Consumer Model
• Queue-Based Communication
• Independent ECU Tasks
• Modular Software Design
────────────────────────────
        │
        ▼
CAN Bus Simulation
        │
        ▼
CSV Logging
        │
        ▼
Predictive Diagnostics
        │
        ▼
Machine Learning
        │
        ▼
Fault Prediction
```

## Build Instructions

### Requirements

#### C Environment

* GCC (MinGW)

#### Python Environment

* Python 3.10+
* pandas
* scikit-learn
* matplotlib
* seaborn
* joblib

### Compile

```bash
gcc src/main.c src/ecu.c src/logger.c src/ring_buffer.c src/engine_task.c src/battery_task.c src/brake_task.c src/logger_task.c src/telemetry_queue.c src/can.c src/can_encoder.c src/csv_logger.c src/predictive_diagnostics.c -Iinclude -o ecu_simulator.exe
```

### Run Simulator

```bash
.\ecu_simulator.exe
```

---

## Machine Learning Pipeline

### Train Models

```bash
python ml/train_model.py
```

### Predict ECU State

```bash
python ml/predict_fault.py
```

---

## Dataset

### Input Features

* Temperature
* Voltage
* Current

### Output Classes

* RUNNING
* WARNING
* FAULT

### Dataset Size

* 1008 Telemetry Samples

---

## Model Performance

| Model               | Accuracy | Precision | Recall | F1-Score |
| ------------------- | -------: | --------: | -----: | -------: |
| Logistic Regression |   71.29% |    70.69% | 71.29% |   70.88% |
| Decision Tree       |   98.02% |    98.02% | 98.02% |   98.02% |
| Random Forest       |   99.01% |    99.02% | 99.01% |   99.01% |
| Gradient Boosting   |   99.01% |    99.02% | 99.01% |   99.01% |

### Best Performing Model

**Random Forest Classifier**

Performance Metrics:

* Accuracy: 99.01%
* Precision: 99.02%
* Recall: 99.01%
* F1-Score: 99.01%

---

## Data Analysis and Visualization

The project includes:

* Correlation Heatmap
* Class Distribution Analysis
* Feature Importance Analysis
* Model Comparison Visualization
* Confusion Matrix Heatmaps

---

## Results

Experimental evaluation demonstrates that ensemble learning methods significantly outperform linear models for ECU fault-state prediction.

### Key Findings

* Logistic Regression achieved moderate performance due to the non-linear nature of ECU fault conditions.
* Decision Trees effectively captured threshold-based diagnostic behavior.
* Random Forest and Gradient Boosting achieved the highest predictive performance.
* Random Forest was selected as the final deployment model.

---

## RTOS-Based Architecture

The system adopts an RTOS-based task architecture where each ECU is modeled as an independent processing task. Communication between software components is organized using queue-based producer-consumer mechanisms, enabling modular and scalable system design.

Architectural principles include:

* Task decomposition of Engine, Battery, and Brake ECUs
* Queue-based telemetry communication
* Producer-consumer processing model
* Independent ECU task design
* Modular software architecture
* Scalable distributed ECU design

The current implementation executes sequentially in a desktop simulation environment while preserving compatibility with future deployment on STM32 hardware using a real-time operating system.

---

## Future Work

* STM32 deployment
* Real FreeRTOS scheduler integration
* Hardware CAN communication
* Hardware-in-the-loop testing
* Advanced predictive maintenance algorithms
* Deep learning-based fault prediction

---

## Technologies Used

### Embedded Systems

* C Programming
* Data Structures
* Queue Management
* Ring Buffers
* CAN Communication Concepts

### Machine Learning

* Python
* Scikit-Learn
* Pandas
* Matplotlib
* Seaborn

### Development Tools

* GCC (MinGW)
* Visual Studio Code
* Git
* GitHub

---

## Author

**Vinay Medisetti**

