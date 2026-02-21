# 🏥 Hospital Management System (C + SQLite)

A menu-driven **Command Line Interface (CLI)** based Hospital Management System developed in **C**, integrated with **SQLite** for persistent database storage.
The system is designed to digitize hospital workflows including patient registration, medical record management, billing with EMI support, and genetic counseling risk assessment.


## 📌 Features

* **Patient Management**

  * Add and view patient details
  * Stores demographic and financial information securely

* **Medical Records Management**

  * Link diagnoses and treatments using Patient ID
  * Retrieve complete medical history for a patient

* **Billing System**

  * Record billing details and payment status
  * Supports multiple payment modes (Cash / Card / Insurance / EMI)

* **EMI Calculation Module**

  * Determines EMI eligibility based on family income
  * Applies dynamic interest rates
  * Updates or inserts EMI billing records automatically

* **Genetic Counseling Module**

  * Risk assessment for hereditary diseases:

    * Diabetes
    * Heart Disease
    * Color Blindness
    * Hearing Loss
    * Alzheimer’s Disease
  * Categorizes risk as Low / Moderate / High

* **SQLite-backed Persistent Storage**

  * Relational database with referential integrity
  * Uses SQLite C APIs for safe data operations

## 🛠 Tech Stack

* **Programming Language:** C
* **Database:** SQLite3
* **Compiler:** GCC (MinGW-w64)
* **Platform:** Windows
* **Interface:** Command Line (CLI)


## 📂 Project Structure

```
hospital-management-system-c-sqlite/
│
├── src/
│   └── hms.c
│
├── db/
│   └── HFBhospital_management.db
│
├── sqlite3.dll
└── README.md
```

---

## ⚙️ Database Schema

The system uses three relational tables:

* **Patients** – Stores personal and financial details
* **MedicalRecords** – Stores diagnoses and treatments linked via PatientID
* **Billing** – Stores billing details including EMI information

Foreign key relationships ensure data consistency across modules.

---

## ▶️ How to Compile

Ensure `sqlite3.dll` is present in the project root.

```bash
gcc src/hms.c -o hms -ID:\sqlite -LD:\sqlite -lsqlite3
```

---

## ▶️ How to Run

```bash
./hms
```

---

## 📖 Menu Options

* View Patients Table
* View Medical Records
* View Billing Table
* Add New Patient
* Add Medical Record
* Add New Bill
* Retrieve Records by Patient ID
* Genetic Counseling
* EMI Calculation System

---

## 🎓 Learning Outcomes

* Practical integration of **C with SQLite databases**
* Use of **SQLite C APIs** for CRUD operations
* Modular CLI-based application design
* Real-world healthcare workflow modeling
* Handling financial logic and risk assessment in C

---

## 🚀 Future Enhancements

* User authentication and role-based access (Admin / Doctor / Patient)
* GUI-based interface
* Notification system (SMS / Email)
* Enhanced genetic data modeling
* Report generation and analytics

---

## 👩‍💻 Author

**Yashika R S**
Department of Electronics and Communication Engineering

---

