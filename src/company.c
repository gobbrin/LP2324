#include "company.h"
#include <stdio.h>
#include <string.h>

// Helper function to ensure null-terminated string
static void copyString(char *destination, const char *source, size_t size) {
    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0'; // Ensure null-termination, due to strncpy and fixed size
}

void createCompany(Company *company, int NIF, const char *name, Category category,
                   BusinessSector sector, const char *street, const char *locality,
                   const char *postalCode) {
    company->NIF = NIF;
    copyString(company->name, name, sizeof(company->name));
    company->category = category;
    company->sector = sector;
    copyString(company->street, street, sizeof(company->street));
    copyString(company->locality, locality, sizeof(company->locality));
    copyString(company->postalCode, postalCode, sizeof(company->postalCode));
    company->isActive = 1; // Set to active by default
}

void createCompanyAdmin(Company *companies, int *numCompanies) {
    // Check if the array is full
    if (*numCompanies >= MAX_COMPANIES) {
        printf("Cannot create more companies. Maximum limit reached.\n");
        return;
    }

    // Get input for the new company
    int NIF;
    char name[MAX_NAME_LENGTH];
    Category category;
    BusinessSector sector;
    char street[MAX_LOC_LENGTH];
    char locality[MAX_LOC_LENGTH];
    char postalCode[MAX_LOC_LENGTH];

    printf("Enter NIF: ");
    scanf("%d", &NIF);

    printf("Enter Company Name: ");
    scanf("%s", name); // Assume no spaces in the company name for simplicity

    printf("Enter Category (0 for Micro, 1 for PME, 2 for Grande Empresa): ");
    scanf("%d", &category);

    printf("Enter Business Sector (0 for Agricultura, 1 for Eletricidade_Gas_Agua, "
           "2 for Texteis_Vestuario, 3 for Construcao, 4 for Bancos_Seguros): ");
    scanf("%d", &sector);

    printf("Enter Street: ");
    scanf("%s", street);

    printf("Enter Locality: ");
    scanf("%s", locality);

    printf("Enter Postal Code: ");
    scanf("%s", postalCode);

    // Create and add the new company to the array
    createCompany(&companies[*numCompanies], NIF, name, category, sector, street, locality, postalCode);
    (*numCompanies)++;

    printf("Company created successfully!\n");
}

void displayCompany(const Company *company) {
    const char *categoryStrings[] = {"Micro", "PME", "Grande Empresa"};
    const char *sectorStrings[] = {"Agricultura", "Eletricidade, gás e água",
                                   "Têxteis e vestuário", "Construção", "Bancos e Seguros"};

    printf("NIF: %d\nName: %s\nCategory: %s\nSector: %s\nStreet: %s\nLocality: %s\nPostal Code: %s\nStatus: %s\n",
           company->NIF, company->name, categoryStrings[company->category],
           sectorStrings[company->sector], company->street, company->locality,
           company->postalCode, company->isActive ? "Active" : "Inactive");
}

// Helper function to find a company by its NIF
static int findCompanyByNIF(const Company *companies, int numCompanies, int targetNIF) {
    for (int i = 0; i < numCompanies; ++i) {
        if (companies[i].NIF == targetNIF) {
            return i; // Return the index of the found company
        }
    }
    return -1; // Return -1 if the company is not found
}

// Helper function to remove a company from the array
static void removeCompany(Company *companies, int *numCompanies, int index) {
    // Move the last company to the position of the deleted one
    companies[index] = companies[*numCompanies - 1];
    (*numCompanies)--;
}

void listCompanies(const Company *companies, int numCompanies) {
    printf("\nList of Companies\n");
    printf("==================\n");

    for (int i = 0; i < numCompanies; ++i) {
        if (companies[i].isActive) {
            displayCompany(&companies[i]);
            printf("\n");
        }
    }
}

void deleteCompany(Company *companies, int *numCompanies) {
    int targetNIF;
    printf("Enter the NIF of the company to delete: ");
    scanf("%d", &targetNIF);

    int index = findCompanyByNIF(companies, *numCompanies, targetNIF);

    if (index != -1) {
        // Found the company, now check if it has user comments
        if (companies[index].numRatings > 0) {
            printf("Cannot delete a company with user comments. Marking as inactive instead.\n");
            companies[index].isActive = 0; // Mark as inactive instead of deletion
        } else {
            removeCompany(companies, numCompanies, index);
            printf("Company deleted successfully!\n");
        }
    } else {
        printf("Company with NIF %d not found.\n", targetNIF);
    }
}
