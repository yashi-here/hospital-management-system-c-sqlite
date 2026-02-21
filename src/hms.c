#include <stdio.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
 
// Function Prototypes
void showMenu();
void viewTable(sqlite3 *db, const char *tableName);
void insertPatient(sqlite3 *db);
void insertMedicalRecord(sqlite3 *db);
void insertnewbill(sqlite3 *db);
void retrieveByPatientID(sqlite3 *db);
void geneticCounseling();
void emiCalculation(sqlite3 *db);
float calculateEMI(float principal, float rate, int months);
void updateBilling(sqlite3 *db, int patient_id, float principal, float emi, int months, float rate);
 
// Main Function
int main() {
    sqlite3 *db;
    int rc = sqlite3_open("db/HFBhospital_management.db", &db);
    if (rc) {
        printf("Cannot open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
 
    int choice;
    while (1) {
        showMenu();
        scanf("%d", &choice);
 
        switch (choice) {
            case 1: viewTable(db, "Patients"); break;
            case 2: viewTable(db, "MedicalRecords"); break;
            case 3: viewTable(db, "Billing"); break;
            case 4: insertPatient(db); break;
            case 5: insertMedicalRecord(db); break;
            case 6: insertnewbill(db); break;
            case 7: retrieveByPatientID(db); break;
            case 8: geneticCounseling(); break;
            case 9: emiCalculation(db); break;
            case 10: printf("Exiting...\n"); sqlite3_close(db); return 0;
            default: printf("Invalid choice. Try again.\n");
        }
    }
 
    sqlite3_close(db);
    return 0;
}
 
// Function to display the menu
void showMenu() {
    printf("\nHFBHospital Management System\n");
    printf("1. View Patients Table\n");
    printf("2. View Medical Records\n");
    printf("3. View Billing Table\n");
    printf("4. Add New Patient\n");
    printf("5. Add Medical Record\n");
    printf("6. Add New Bill Detail\n");
    printf("7. Retrieve Medical Record or Bill by Patient ID\n");
    printf("8. Genetic Counseling\n");
    printf("9. EMI Calculation System\n");
    printf("10.Exit\n");
    printf("Enter your choice: ");
}
 
// Function to view a table
void viewTable(sqlite3 *db, const char *tableName) {
    char query[256];
    sprintf(query, "SELECT * FROM %s;", tableName);
 
    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) == SQLITE_OK) {
        int cols = sqlite3_column_count(stmt);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            for (int i = 0; i < cols; i++) {
                printf("%s | ", sqlite3_column_text(stmt, i));
            }
            printf("\n");
        }
    }
    sqlite3_finalize(stmt);
}
 
// Function to insert a new patient
void insertPatient(sqlite3 *db) {
    char sql[500];
    sqlite3_stmt *stmt;
    
    char name[100], gender[10], contact[20], address[200], bloodGroup[5];
    int age;
    float familyIncome;
 
    printf("Enter Patient Name: "); scanf(" %[^\n]", name);
    printf("Enter Age: "); scanf("%d", &age);
    printf("Enter Gender: "); scanf(" %s", gender);
    printf("Enter Contact Number: "); scanf(" %s", contact);
    printf("Enter Address: "); scanf(" %[^\n]", address);
    printf("Enter Blood Group: "); scanf(" %s", bloodGroup);
    printf("Enter Family Income: "); scanf("%f", &familyIncome);
 
    sprintf(sql, "INSERT INTO Patients (Name, Age, Gender, Contact, Address, BloodGroup, FamilyIncome) VALUES (?, ?, ?, ?, ?, ?, ?);");
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    sqlite3_bind_int(stmt, 2, age);
    sqlite3_bind_text(stmt, 3, gender, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, contact, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, address, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, bloodGroup, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 7, familyIncome);
 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    printf("Patient added successfully!\n");
}
 
// Function to insert a medical record
void insertMedicalRecord(sqlite3 *db) {
    int patientID;
    char diagnosis[200], treatment[200], doctor[100], admissionDate[15], dischargeDate[15];
 
    printf("Enter Patient ID: "); scanf("%d", &patientID);
    printf("Enter Diagnosis: "); scanf(" %[^\n]", diagnosis);
    printf("Enter Treatment: "); scanf(" %[^\n]", treatment);
    printf("Enter Doctor Name: "); scanf(" %[^\n]", doctor);
    printf("Enter Admission Date: "); scanf(" %s", admissionDate);
    printf("Enter Discharge Date: "); scanf(" %s", dischargeDate);
 
    char sql[500];
    sprintf(sql, "INSERT INTO MedicalRecords (PatientID, Diagnosis, Treatment, Doctor, AdmissionDate, DischargeDate) VALUES (?, ?, ?, ?, ?, ?);");
    sqlite3_stmt *stmt;
    sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    sqlite3_bind_int(stmt, 1, patientID);
    sqlite3_bind_text(stmt, 2, diagnosis, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 3, treatment, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 4, doctor, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 5, admissionDate, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 6, dischargeDate, -1, SQLITE_STATIC);
 
    sqlite3_step(stmt);
    sqlite3_finalize(stmt);
    printf("Medical record added successfully!\n");
}
void addBillingRecord(sqlite3 *db) {
    char *errMsg = 0;
    char sql[512];
    int patientID;
    double totalAmount, emiAmount = 0, roi = 0;
    int emiDuration = 0;
    char paymentStatus[20], paymentMode[20], emiEligible[5];
 
    printf("Enter PatientID: ");
    scanf("%d", &patientID);
    printf("Enter Total Amount: ");
    scanf("%lf", &totalAmount);
    printf("Enter Payment Status (Pending/Completed): ");
    scanf("%s", paymentStatus);
    printf("Enter Payment Mode (Cash/Card/Insurance/EMI): ");
    scanf("%s", paymentMode);
    printf("Is EMI Eligible? (Yes/No): ");
    scanf("%s", emiEligible);
    
    if (strcmp(emiEligible, "Yes") == 0) {
        printf("Enter EMI Amount: ");
        scanf("%lf", &emiAmount);
        printf("Enter EMI Duration (Months): ");
        scanf("%d", &emiDuration);
        printf("Enter Rate of Interest (ROI in %%): ");
        scanf("%lf", &roi);
    }
    
    if (strcmp(emiEligible, "Yes") == 0) {
        snprintf(sql, sizeof(sql), 
                 "INSERT INTO Billing (PatientID, TotalAmount, PaymentStatus, PaymentMode, EMIEligible, emi_amount, emi_duration, roi) "
                 "VALUES (%d, %.2f, '%s', '%s', '%s', %.2f, %d, %.2f);", 
                 patientID, totalAmount, paymentStatus, paymentMode, emiEligible,
                 emiAmount, emiDuration, roi);
    } else {
        snprintf(sql, sizeof(sql), 
                 "INSERT INTO Billing (PatientID, TotalAmount, PaymentStatus, PaymentMode, EMIEligible, emi_amount, emi_duration, roi) "
                 "VALUES (%d, %.2f, '%s', '%s', '%s', NULL, NULL, NULL);", 
                 patientID, totalAmount, paymentStatus, paymentMode, emiEligible);
    }
    
    if (sqlite3_exec(db, sql, 0, 0, &errMsg) != SQLITE_OK) {
        fprintf(stderr, "Error inserting data: %s\n", errMsg);
        sqlite3_free(errMsg);
    } else {
        printf("Billing record added successfully!\n");
    }
}
 
void insertnewbill(sqlite3 *db) {
    addBillingRecord(db);
}
 
//genetic counselling
// Function to prompt the user and return their response
int getYesNoResponse(const char* question) {
    int response;
    printf("%s (1 for Yes, 0 for No): ", question);
    scanf("%d", &response);
    return response;
}
 
// Function to assess risk based on family history
float assessFamilyHistory(const char* disease) {
    int choice;
    float riskScore = 0.0;
 
    printf("\n=== Genetic Counseling: Family History of %s ===\n", disease);
    if (!getYesNoResponse("Do you have a family history of this disease?")) {
        printf("Low risk of %s based on family history.\n", disease);
        return 0.0;
    }
 
    printf("\nSelect family members diagnosed with %s (enter 0 when done):\n", disease);
    printf("1. Male (Partner 1)\n2. Female (Partner 2)\n3. Male's Mother\n4. Male's Father\n5. Female's Mother\n6. Female's Father\n");
    
    while (1) {
        printf("Enter choice (0 to finish): ");
        scanf("%d", &choice);
        if (choice == 0) break;
 
        switch (choice) {
            case 1: case 2:
                riskScore += 3.0;
                break;
            case 3: case 4: case 5: case 6:
                riskScore += 1.5;
                break;
            default:
                printf("Invalid option. Choose a number from 1 to 6 or 0 to finish.\n");
        }
    }
 
    return riskScore;
}
 
// Function to evaluate risk level
void evaluateRisk(float riskScore, const char* disease) {
    float percentageRisk = (riskScore / 12.0) * 100.0;
    printf("\n=== Risk Assessment for %s ===\n", disease);
    if (riskScore == 0) {
        printf("Low risk of %s based on family history.\n", disease);
    } else if (riskScore <= 3.0) {
        printf("Low risk of %s. Risk score: %.1f/12 (%.1f%% chance)\n", disease, riskScore, percentageRisk);
    } else if (riskScore <= 6.0) {
        printf("Moderate risk of %s. Risk score: %.1f/12 (%.1f%% chance)\n", disease, riskScore, percentageRisk);
    } else {
        printf("High risk of %s. Risk score: %.1f/12 (%.1f%% chance)\n", disease, riskScore, percentageRisk);
    }
}
 
// function for genetic counselling
void geneticCounseling() {
    char diseases[][30] = {"Diabetes", "Heart Diseases", "Color Blindness", "Hearing Loss", "Alzheimer's Disease"};
    int numDiseases = sizeof(diseases) / sizeof(diseases[0]);
    int i;
    
    for (i = 0; i < numDiseases; i++) {
        float score = assessFamilyHistory(diseases[i]);
        evaluateRisk(score, diseases[i]);
    }
 
}
void retrieveByPatientID(sqlite3 *db) {
    int patientID;
    printf("Enter Patient ID to retrieve record: ");
    scanf("%d", &patientID);
 
    char sql[500];
    sqlite3_stmt *stmt;
 
    // Retrieve Medical Records
    sprintf(sql, "SELECT * FROM MedicalRecords WHERE PatientID = %d;", patientID);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        int cols = sqlite3_column_count(stmt);  // Declared inside the if-block
        printf("\nMedical Records for Patient ID %d:\n", patientID);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            for (int i = 0; i < cols; i++) {
                printf("%s | ", sqlite3_column_text(stmt, i));
            }
            printf("\n");
        }
    } else {
        printf("Error retrieving medical records: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
 
    // Retrieve Billing Records
    sprintf(sql, "SELECT * FROM Billing WHERE PatientID = %d;", patientID);
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) == SQLITE_OK) {
        int cols = sqlite3_column_count(stmt);  // Re-declare inside this block
        printf("\nBilling Details for Patient ID %d:\n", patientID);
        while (sqlite3_step(stmt) == SQLITE_ROW) {
            for (int i = 0; i < cols; i++) {
                printf("%s | ", sqlite3_column_text(stmt, i));
            }
            printf("\n");
        }
    } else {
        printf("Error retrieving billing details: %s\n", sqlite3_errmsg(db));
    }
    sqlite3_finalize(stmt);
}
//EMI
 
float calculateEMI(float principal, float rate, int months) {
    float monthlyRate = rate / (12 * 100);
    return principal * monthlyRate * pow(1 + monthlyRate, months) / (pow(1 + monthlyRate, months) - 1);
}
 
int getFamilyIncome(sqlite3 *db, int patient_id) {
    sqlite3_stmt *stmt;
    int income = 0;
    char query[256];
 
    // Fixed column and table names to match schema
    sprintf(query, "SELECT FamilyIncome FROM Patients WHERE PatientID = %d;", patient_id);
 
    if (sqlite3_prepare_v2(db, query, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            income = sqlite3_column_int(stmt, 0);
        } else {
            printf("No matching patient found.\n");  // Debug print
        }
    } else {
        printf("SQL Error: %s\n", sqlite3_errmsg(db));  // Debug print
    }
 
    sqlite3_finalize(stmt);
    return income;
}
 
 
void upsertBillingWithEMI(sqlite3 *db, int patient_id, float principal, float emi, int months, float rate) {
    sqlite3_stmt *stmt;
    char checkQuery[256];
    sprintf(checkQuery, "SELECT COUNT(*) FROM Billing WHERE PatientID = %d;", patient_id);
 
    int count = 0;
    if (sqlite3_prepare_v2(db, checkQuery, -1, &stmt, NULL) == SQLITE_OK) {
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            count = sqlite3_column_int(stmt, 0);
        }
    }
    sqlite3_finalize(stmt);
 
    char query[512];
    if (count > 0) {
        // Update if patient already has a billing record
        sprintf(query, "UPDATE Billing SET PaymentStatus = 'Pending', PaymentMode = 'EMI', EMIEligible = 'Yes', emi_amount = %.2f, emi_duration = %d, roi = %.2f, TotalAmount = %.2f WHERE PatientID = %d;",
                emi, months, rate, principal, patient_id);
        if (sqlite3_exec(db, query, 0, 0, NULL) == SQLITE_OK) {
            printf("Billing record updated successfully!\n");
        } else {
            printf("Failed to update billing record.\n");
        }
    } else {
        // Insert a new billing record
        sprintf(query,
            "INSERT INTO Billing (PatientID, TotalAmount, PaymentStatus, PaymentMode, EMIEligible, emi_amount, emi_duration, roi) "
            "VALUES (%d, %.2f, 'Pending', 'EMI', 'Yes', %.2f, %d, %.2f);",
            patient_id, principal, emi, months, rate);
        if (sqlite3_exec(db, query, 0, 0, NULL) == SQLITE_OK) {
            printf("Billing record inserted successfully!\n");
        } else {
            printf("Failed to insert billing record.\n");
        }
    }
}
 
void emiCalculation(sqlite3 *db) {
    int patient_id, months;
    float principal, rate, emi;

    printf("Enter Patient ID: ");
    scanf("%d", &patient_id);

    printf("Enter total bill amount: ");
    scanf("%f", &principal);

    int salary = getFamilyIncome(db, patient_id);
    if (salary == 0) {
        printf("Patient not found or income not available.\n");
        return;
    }

    if (salary > principal) {
        printf("Salary is higher than bill. No EMI required.\n");
        return;
    } else if (salary >= (principal / 2)) {
        rate = 15.0;
    } else {
        rate = 10.0;
    }

    printf("Enter the number of months for EMI: ");
    scanf("%d", &months);

    emi = calculateEMI(principal, rate, months);

    printf("\nFor bill amount of %.2f with interest rate of %.2f%% over %d months,\n",
           principal, rate, months);
    printf("Monthly EMI: %.2f\n", emi);

    upsertBillingWithEMI(db, patient_id, principal, emi, months, rate);
}