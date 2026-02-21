CREATE TABLE Patients (
    PatientID INTEGER PRIMARY KEY AUTOINCREMENT,
    Name TEXT,
    Age INTEGER,
    Gender TEXT,
    Contact TEXT,
    Address TEXT,
    BloodGroup TEXT,
    FamilyIncome REAL
);

CREATE TABLE MedicalRecords (
    RecordID INTEGER PRIMARY KEY AUTOINCREMENT,
    PatientID INTEGER,
    Diagnosis TEXT,
    Treatment TEXT,
    Doctor TEXT,
    AdmissionDate TEXT,
    DischargeDate TEXT,
    FOREIGN KEY (PatientID) REFERENCES Patients(PatientID)
);

CREATE TABLE Billing (
    BillID INTEGER PRIMARY KEY AUTOINCREMENT,
    PatientID INTEGER,
    TotalAmount REAL,
    PaymentStatus TEXT,
    PaymentMode TEXT,
    EMIEligible TEXT,
    emi_amount REAL,
    emi_duration INTEGER,
    roi REAL,
    FOREIGN KEY (PatientID) REFERENCES Patients(PatientID)
);